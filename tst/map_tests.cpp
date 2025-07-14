#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "../src/map.hpp"

struct Person {
    std::string name;
    int age;
    Person() : name(""), age(0) {}
    Person(const std::string& n, int a) : name(n), age(a) {}
    bool operator==(const Person& other) const { return name == other.name && age == other.age; }
};

TEST(MapTest, InitializeTest) {
    auto map = ds::Map<int, std::string>();
    ASSERT_EQ(map.size(), 0);
    ASSERT_TRUE(map.empty());
    EXPECT_THROW(map.at(1), std::out_of_range);
}

TEST(MapTest, InsertAndSizeTest) {
    auto map = ds::Map<int, std::string>();
    
    auto result = map.insert(1, "one");
    ASSERT_TRUE(result.first);
    ASSERT_FALSE(map.empty());
    ASSERT_EQ(map.size(), 1);
    
    result = map.insert(2, "two");
    ASSERT_TRUE(result.first);
    ASSERT_EQ(map.size(), 2);
    
    result = map.insert(1, "ONE");
    ASSERT_FALSE(result.first);
    ASSERT_EQ(map.size(), 2);
}

TEST(MapTest, ContainsTest) {
    ds::Map<int, std::string> map;
    map.insert(1, "one");
    map.insert(2, "two");
    
    ASSERT_TRUE(map.contains(1));
    ASSERT_TRUE(map.contains(2));
    ASSERT_FALSE(map.contains(3));
}

TEST(MapTest, AtAccessTest) {
    ds::Map<int, std::string> map;
    map.insert(1, "one");
    map.insert(2, "two");
    
    ASSERT_EQ(map.at(1), "one");
    ASSERT_EQ(map.at(2), "two");
    
    const ds::Map<int, std::string>& constMap = map;
    ASSERT_EQ(constMap.at(1), "one");
    
    map.at(1) = "ONE";
    ASSERT_EQ(map.at(1), "ONE");
    
    EXPECT_THROW(map.at(3), std::out_of_range);
}

TEST(MapTest, BracketOperatorTest) {
    ds::Map<int, std::string> map;
    
    ASSERT_EQ(map.size(), 0);
    map[1] = "one";
    ASSERT_EQ(map.size(), 1);
    ASSERT_EQ(map[1], "one");
    
    map[1] = "ONE";
    ASSERT_EQ(map.size(), 1);
    ASSERT_EQ(map[1], "ONE");
    
    std::string& val = map[2];
    ASSERT_EQ(val, "");
    ASSERT_EQ(map.size(), 2);
}

TEST(MapTest, IterationTest) {
    ds::Map<int, std::string> map;
    map.insert(1, "one");
    map.insert(2, "two");
    map.insert(3, "three");
    
    std::vector<int> keys;
    std::vector<std::string> values;
    
    for (const auto& pair : map) {
        keys.push_back(pair.first);
        values.push_back(pair.second);
    }
    
    ASSERT_EQ(keys.size(), 3);
    ASSERT_EQ(keys[0], 1);
    ASSERT_EQ(keys[1], 2);
    ASSERT_EQ(keys[2], 3);
    
    ASSERT_EQ(values.size(), 3);
    ASSERT_EQ(values[0], "one");
    ASSERT_EQ(values[1], "two");
    ASSERT_EQ(values[2], "three");
}

TEST(MapTest, CustomComparatorTest) {
    ds::Map<int, std::string, std::greater<int>> map;
    map.insert(1, "one");
    map.insert(2, "two");
    map.insert(3, "three");
    
    std::vector<int> keys;
    for (const auto& pair : map) {
        keys.push_back(pair.first);
    }
    
    ASSERT_EQ(keys.size(), 3);
    ASSERT_EQ(keys[0], 3);
    ASSERT_EQ(keys[1], 2);
    ASSERT_EQ(keys[2], 1);
}

TEST(MapTest, CustomStructTest) {
    ds::Map<std::string, Person> people;
    
    people.insert("alice", Person("Alice", 30));
    people.insert("bob", Person("Bob", 25));
    
    ASSERT_TRUE(people.contains("alice"));
    ASSERT_TRUE(people.contains("bob"));
    ASSERT_FALSE(people.contains("charlie"));
    
    ASSERT_EQ(people.at("alice").name, "Alice");
    ASSERT_EQ(people.at("alice").age, 30);
    
    ASSERT_EQ(people.at("bob").name, "Bob");
    ASSERT_EQ(people.at("bob").age, 25);
    
    people["alice"].age = 31;
    ASSERT_EQ(people.at("alice").age, 31);
    
    people["charlie"] = Person("Charlie", 40);
    ASSERT_TRUE(people.contains("charlie"));
    ASSERT_EQ(people.at("charlie").name, "Charlie");
    ASSERT_EQ(people.at("charlie").age, 40);
}

TEST(MapTest, ManyElementsTest) {
    ds::Map<int, int> map;
    const int COUNT = 100;
    
    for (int i = 0; i < COUNT; i++) {
        map.insert(i, i * 10);
    }
    
    ASSERT_EQ(map.size(), COUNT);
    
    for (int i = 0; i < COUNT; i++) {
        ASSERT_TRUE(map.contains(i));
        ASSERT_EQ(map.at(i), i * 10);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}