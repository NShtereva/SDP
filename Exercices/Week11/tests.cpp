#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "D:/doctest.h"

#include "separateChainingHashTable.hpp"
#include "linearProbingHashTable.hpp"

#include <string>

unsigned lengthHashFunction(std::string const& str) 
{
    return str.length();
}

unsigned firstElementHashFunction(std::string const& str) 
{
    return str[0];
}

unsigned sumHashFunction(std::string const& str) 
{
    unsigned hash = 0;
    for (char c : str)
    {
        hash += c;
    }
    return hash;
}

unsigned betterHashFunction(std::string const& str) 
{
    unsigned hash = 0;
    unsigned i = 1;

    for (char c : str)
    {
        hash += c * ((i += 5) *= 13);
    }

    return hash;
}

// using MySeparateChainingHashTable = SeparateChainingHashTable<std::string, unsigned int, lengthHashFunction>;
// using MySeparateChainingHashTable = SeparateChainingHashTable<std::string, unsigned int, firstElementHashFunction>;
// using MySeparateChainingHashTable = SeparateChainingHashTable<std::string, unsigned int, sumHashFunction>;
using MySeparateChainingHashTable = SeparateChainingHashTable<std::string, unsigned int, betterHashFunction>;

// using MyLinearProbingHashTable = LinearProbingHashTable<std::string, unsigned int, lengthHashFunction>;
// using MyLinearProbingHashTable = LinearProbingHashTable<std::string, unsigned int, firstElementHashFunction>;
// using MyLinearProbingHashTable = LinearProbingHashTable<std::string, unsigned int, sumHashFunction>;
using MyLinearProbingHashTable = LinearProbingHashTable<std::string, unsigned int, betterHashFunction>;

TYPE_TO_STRING(MySeparateChainingHashTable);
TYPE_TO_STRING(MyLinearProbingHashTable);

#define ALL_HASH_TABLES MySeparateChainingHashTable, MyLinearProbingHashTable

TEST_CASE_TEMPLATE("Adding element to an empty hash table.", AnyHashTable, ALL_HASH_TABLES) 
{
    AnyHashTable ht;

    CHECK_EQ(ht.lookup("the_answer"), nullptr);
    REQUIRE(ht.insert("the_answer", 42));
    CHECK_EQ(*ht.lookup("the_answer"), 42);
    CHECK(!ht.insert("the_answer", 43));
}

TEST_CASE_TEMPLATE("Adding and deleting elements.", AnyHashTable, ALL_HASH_TABLES) 
{
    AnyHashTable ht;

    for(int x : { 12, 42, 135, 15, 7})
    {
        REQUIRE(ht.insert(std::to_string(x), x));
    }

    SUBCASE("We can find all added elements.") 
    {
        for(int x : { 12, 42, 135, 15, 7})
        {
            CHECK_EQ(*ht.lookup(std::to_string(x)), x);
        }
    }

    SUBCASE("We can not delete a missing element.") 
    {
        CHECK(!ht.erase("missing"));
    }

    SUBCASE("We successfully delete existing elements=") 
    {
        REQUIRE(ht.erase("135"));
        REQUIRE(ht.erase("15"));

        CHECK_EQ(ht.lookup("135"), nullptr);
        CHECK_EQ(ht.lookup("15"), nullptr);
        CHECK_EQ(*ht.lookup("12"), 12);
        CHECK_EQ(*ht.lookup("42"), 42);
        CHECK_EQ(*ht.lookup("7"), 7);
    }

    SUBCASE("We count the keys correctly.") 
    {
        size_t len = 0;
        for(std::string key : ht.keys()) 
        {
            CHECK((key == "135" || key == "15" || key == "42" || key == "7" || key == "12"));
            len++;
        }
        CHECK_EQ(len, 5);
    }

    SUBCASE("We count the values correctly.") 
    {
        size_t len = 0;
        for(unsigned value : ht.values()) 
        {
            CHECK((value == 135 || value == 15 || value == 42 || value == 7 || value == 12));
            len++;
        }
        CHECK_EQ(len, 5);
    }

}

TEST_CASE_TEMPLATE("Add and delete 100 elements.", AnyHashTable, ALL_HASH_TABLES) 
{
    AnyHashTable ht;

    for(int i = 1; i <= 50; i++) 
    {
        REQUIRE(ht.insert(std::to_string(i), i));
        REQUIRE(ht.insert(std::to_string(101 - i), 101 - i));
    }

    ht.info();

    for(int i = 1; i <= 100; i++)
    {
        CHECK_EQ(*ht.lookup(std::to_string(i)), i);
    }

    for(int i = 50; i > 10; i--) 
    {
        CHECK(ht.erase(std::to_string(i)));
        CHECK(ht.erase(std::to_string(101 - i)));
    }

    ht.info();

    for(int i = 11; i <= 90; i++)
    {
        CHECK_EQ(ht.lookup(std::to_string(i)), nullptr);
    }

    for(int i = 1; i <= 10; i++) 
    {
        CHECK_EQ(*ht.lookup(std::to_string(i)), i);
        CHECK_EQ(*ht.lookup(std::to_string(101 - i)), 101 - i);
    }
}
