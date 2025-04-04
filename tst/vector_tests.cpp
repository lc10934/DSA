#include <gtest/gtest.h>
#include <optional>
#include <string>
#include "../src/vector.hpp" 

struct Person {
    std::string name;
    int age;
    Person() : name(""), age(0) {} 
    Person(const std::string& n, int a) : name(n), age(a) {}
    bool operator==(const Person &other) const { return name == other.name && age == other.age; }
};

TEST(VectorTest, InitializeTest)
{
    auto v = Vector<int>();
    ASSERT_EQ(v.size(), 0);
    ASSERT_EQ(v.capacity(), 2);
    EXPECT_THROW(v[0], std::out_of_range);
    v.push_back(1);
    ASSERT_EQ(v[0], 1);
    EXPECT_THROW(v[1], std::out_of_range);
    EXPECT_THROW(v[2], std::out_of_range);
}

TEST(VectorTest, PopTest)
{
    auto v = Vector<int>();
    ASSERT_EQ(v.pop(), std::nullopt);
    v.push_back(1);
    ASSERT_EQ(v.pop(), 1);
    ASSERT_EQ(v.size(), 0);
    ASSERT_EQ(v.capacity(), 2);
}

TEST(VectorTest, CharTest)
{
    auto v = Vector<char>();
    v.push_back('a');
    ASSERT_EQ(v.pop(), 'a');
    ASSERT_EQ(v.size(), 0);
    ASSERT_EQ(v.capacity(), 2);
}

TEST(VectorTest, StringTest)
{
    auto v = Vector<std::string>();
    v.push_back("Test");
    ASSERT_EQ(v.pop(), "Test");
    ASSERT_EQ(v.size(), 0);
    ASSERT_EQ(v.capacity(), 2);
}

TEST(VectorTest, ResizeAndAccessBeyondInitialCapacity)
{
    Vector<int> v;
    for (int i = 0; i < 10; ++i)
    {
        v.push_back(i);
    }
    ASSERT_EQ(v.size(), 10);
    ASSERT_GE(v.capacity(), 10);

    for (int i = 0; i < 10; ++i)
    {
        ASSERT_EQ(v[i], i);
    }
    EXPECT_THROW(v[10], std::out_of_range);
}

TEST(VectorTest, MultiplePops)
{
    Vector<int> v;
    v.push_back(5);
    v.push_back(10);
    v.push_back(15);

    ASSERT_EQ(v.pop(), 15);
    ASSERT_EQ(v.pop(), 10);
    ASSERT_EQ(v.pop(), 5);
    ASSERT_EQ(v.pop(), std::nullopt);
}

TEST(VectorTest, CustomStructTest)
{
    Vector<Person> people;
    people.push_back({"Alice", 30});
    people.push_back({"Bob", 25});

    auto p1 = people.pop();
    ASSERT_TRUE(p1.has_value());
    ASSERT_EQ(p1.value(), Person("Bob", 25));

    auto p2 = people.pop();
    ASSERT_TRUE(p2.has_value());
    ASSERT_EQ(p2.value(), Person("Alice", 30));

    ASSERT_EQ(people.size(), 0);
}

TEST(VectorTest, PushAndAccessAfterReallocation)
{
    Vector<std::string> v;
    for (int i = 0; i < 100; ++i)
    {
        v.push_back("Item " + std::to_string(i));
    }

    ASSERT_EQ(v.size(), 100);
    for (int i = 0; i < 100; ++i)
    {
        ASSERT_EQ(v[i], "Item " + std::to_string(i));
    }
}

TEST(VectorTest, AlternatingPushPop)
{
    Vector<std::string> v;

    v.push_back("A");
    ASSERT_EQ(v.pop(), "A");

    v.push_back("B");
    v.push_back("C");
    ASSERT_EQ(v.pop(), "C");

    v.push_back("D");
    ASSERT_EQ(v.size(), 2);
    ASSERT_EQ(v[0], "B");
    ASSERT_EQ(v[1], "D");
}

TEST(VectorTest, Bruh)
{
    Vector<int> v;
    for (int i = 0; i < 10; ++i)
    {
        v.push_back(i);
    }
    ASSERT_EQ(v.size(), 10);
    ASSERT_GE(v.capacity(), 10);
    
    v[6] = 2;
    ASSERT_EQ(v[6], 2);
}
