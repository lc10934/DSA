#include <gtest/gtest.h>
#include "../src/set.hpp"
#include <vector>
#include <string>

TEST(SetTest, EmptyInitially) {
    ds::Set<int> s;
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0u);
}

TEST(SetTest, InsertAndContains) {
    ds::Set<std::string> s;
    EXPECT_TRUE(s.insert("apple"));
    EXPECT_TRUE(s.insert("banana"));
    EXPECT_TRUE(s.insert("cherry"));
    EXPECT_EQ(s.size(), 3u);
    EXPECT_FALSE(s.insert("banana"));
    EXPECT_EQ(s.size(), 3u);
    EXPECT_TRUE(s.contains("apple"));
    EXPECT_FALSE(s.contains("durian"));
}

TEST(SetTest, InOrderIteration) {
    ds::Set<int> s;
    std::vector<int> input = {4,1,3,2};
    for (int v : input) s.insert(v);
    std::vector<int> collected;
    for (auto it = s.begin(); it != s.end(); ++it) {
        collected.push_back(*it);
    }
    EXPECT_EQ(collected, std::vector<int>({1,2,3,4}));
}

TEST(SetTest, CustomType) {
    struct Person {
        std::string name;
        int age;
        Person() : name(""), age(0) {}
        Person(std::string n, int a) : name(std::move(n)), age(a) {}
        bool operator<(Person const& o) const {
            return age < o.age || (age==o.age && name < o.name);
        }
        bool operator==(Person const& o) const {
            return age==o.age && name==o.name;
        }
    };
    ds::Set<Person> s;
    Person a{"Alice",30}, b{"Bob",25}, c{"Charlie",35};
    EXPECT_TRUE(s.insert(a));
    EXPECT_TRUE(s.insert(b));
    EXPECT_TRUE(s.insert(c));
    EXPECT_EQ(s.size(), 3u);
    EXPECT_TRUE(s.contains(b));
    EXPECT_FALSE(s.contains(Person{"David",40}));
    std::vector<Person> out;
    for (auto it = s.begin(); it != s.end(); ++it) {
        out.push_back(*it);
    }
    EXPECT_EQ(out[0].age, 25);
    EXPECT_EQ(out[1].age, 30);
    EXPECT_EQ(out[2].age, 35);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
