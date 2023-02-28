#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "D:/doctest.h"

#include "dLList.hpp"

TEST_CASE("The list is empty when created") 
{
    DLList<int> l;
    CHECK(l.empty());
}

TEST_CASE("When adding an item to a list, it is no longer empty") 
{
    DLList<int> l;
    REQUIRE(l.insertLast(42));
    CHECK(!l.empty());
}

TEST_CASE("Sequentially adding elements to the list and traversing it") 
{
    DLList<int> l;
    for(int i = 1; i <= 10; i++)
    {
        REQUIRE(l.insertLast(i));
    }

    int i = 1;
    for(int x : l)
    {
        CHECK_EQ(i++, x);
    }
    CHECK_EQ(i, 11);
}

TEST_CASE("Sequentially adding elements to the list from the beginning and traversing it") 
{
    DLList<int> l;
    for(int i = 1; i <= 10; i++)
    {
        REQUIRE(l.insertFirst(i));
    }

    int i = 10;
    for(int x : l)
    {
        CHECK_EQ(i--, x);
    }
    CHECK_EQ(i, 0);
}

TEST_CASE("Sequentially adding elements to the list and traversing it backwards") 
{
    DLList<int> l;
    for(int i = 1; i <= 10; i++)
    {
        REQUIRE(l.insertLast(i));
    }

    int i = 10;
    for(DLListIterator<int> it = l.last(); it.valid(); --it)
    {
        CHECK_EQ(*it, i--);
    }
    CHECK_EQ(i, 0);
}

TEST_CASE("Sequentially adding elements to the list from the beginning and traversing it backwards") 
{
    DLList<int> l;
    for(int i = 1; i <= 10; i++)
    {
        REQUIRE(l.insertFirst(i));
    }

    int i = 1;
    for(DLListIterator<int> it = l.last(); it.valid(); --it)
    {
        CHECK_EQ(*it, i++);
    }
    CHECK_EQ(i, 11);
}

TEST_CASE("Including elements in even positions") 
{
    DLList<int> l;
    for(int i = 1; i <= 10; i += 2)
    {
        REQUIRE(l.insertLast(i));
    }

    for(DLListIterator<int> it = l.begin(); it != l.end(); ++it, ++it)
    {
        REQUIRE(l.insertAfter(*it + 1, it));
    }

    int i = 1;
    for(int x : l)
    {
        CHECK_EQ(i++, x);
    }
    CHECK_EQ(i, 11);
}

TEST_CASE("Including elements in even positions with insertBefore") 
{
    DLList<int> l;
    for(int i = 2; i <= 10; i += 2)
    {
        REQUIRE(l.insertLast(i));
    }

    for(DLListIterator<int> it = l.begin(); it != l.end(); ++it)
    {
        l.insertBefore(*it - 1, it);
    }

    int i = 1;
    for(int x : l)
    {
        CHECK_EQ(i++, x);
    }
    CHECK_EQ(i, 11);
}

TEST_CASE("Delete elements in even positions with deleteAfter") 
{
    DLList<int> l;
    for(int i = 1; i <= 10; i ++)
    {
        REQUIRE(l.insertLast(i));
    }

    int x;
    int i = 2;

    for(DLListIterator<int> it = l.begin(); it != l.end(); i += 2, ++it) 
    {
        REQUIRE(l.deleteAfter(x, it));
        CHECK_EQ(x, i);
    }
    CHECK_EQ(i, 12);

    REQUIRE(l.insertLast(11));

    i = -1;
    for(int x : l)
    {
        CHECK_EQ(i += 2, x);
    }
    CHECK_EQ(i, 11);
}

TEST_CASE("Sequentially delete the last element in the list") 
{
    DLList<int> l;
    for(int i = 1; i <= 10; i++)
    {
        REQUIRE(l.insertLast(i));
    }

    int x;
    for(int i = 10; i >= 1; i--) 
    {
        REQUIRE(l.deleteLast(x));
        CHECK_EQ(x, i);
    }
    CHECK(l.empty());
}

TEST_CASE("Sequentially delete the first element in the list") 
{
    DLList<int> l;
    for(int i = 1; i <= 10; i++)
    {
        REQUIRE(l.insertLast(i));
    }

    int x;
    for(int i = 1; i <= 10; i++) 
    {
        REQUIRE(l.deleteFirst(x));
        CHECK(l.insertLast(i + 10));
        CHECK_EQ(x, i);
    }

    int i = 11;
    for(int x : l)
    {
        CHECK_EQ(x, i++);
    }
    CHECK_EQ(i, 21);

    for(int i = 1; i <= 10; i++) 
    {
        REQUIRE(l.deleteFirst(x));
    }

    CHECK(l.empty());
}

TEST_CASE("Delete elements in even positions with deleteAt") 
{
    DLList<int> l;
    for(int i = 1; i <= 10; i ++)
    {
        REQUIRE(l.insertLast(i));
    }

    int x;
    int i = 2;

    for(DLListIterator<int> it = l.begin().next(); it != l.end(); i += 2, it && ++it) 
    {
        DLListIterator<int> toDelete = it++;
        REQUIRE(l.deleteAt(x, toDelete));
        CHECK(!toDelete.valid());
        CHECK_EQ(x, i);
    }
    CHECK_EQ(i, 12);

    i = -1;
    for(int x : l)
    {
        CHECK_EQ(i += 2, x);
    }
    CHECK_EQ(i, 9);
}

TEST_CASE("Delete elements in odd positions with deleteBefore") 
{
    DLList<int> l;
    for(int i = 1; i <= 10; i++)
    {
        REQUIRE(l.insertLast(i));
    }

    int i = 1;
    int x;
    for(DLListIterator<int> it = l.begin().next(); it != l.end(); i += 2,  ++it && ++it) 
    {
        REQUIRE(l.deleteBefore(x, it));
        CHECK_EQ(x, i);
    }
    CHECK_EQ(i, 11);

    i = 0;
    for(int x : l)
    {
        CHECK_EQ(i += 2, x);
    }
    CHECK_EQ(i, 10);
}

TEST_CASE("The copy constructor does not share memory") 
{
    DLList<int> l1;
    for(int i = 1; i <= 10; i++)
    {
        l1.insertLast(i);
    }

    DLList<int> l2 = l1;
    l2.insertLast(20);

    for(int i = 1; i <= 10; i++) 
    {
        CHECK(!l1.empty());
        int x;
        REQUIRE(l1.deleteFirst(x));
        CHECK_EQ(x, i);
    }
    CHECK(l1.empty());
}

TEST_CASE("Reversing a list of one element") 
{
    DLList<int> l;
    l.insertLast(42);

    l.reverse();

    for(int x : l)
    {
        CHECK_EQ(x, 42);
    }
}

TEST_CASE("Reversing a list") 
{
    DLList<int> l;
    for(int i = 1; i <= 4; i++)
    {
        REQUIRE(l.insertLast(i * 10));
    }

    l.reverse();

    int i = 4;
    for(int x : l)
    {
        CHECK_EQ(x, i * 10);
        i--;
    }
    CHECK_EQ(i, 0);
}

TEST_CASE("Remove consecutive repeating elements from the list")
{
    DLList<int> l;
    int input[] = { 10, 30, 20, 20, 40, 20, 30, 30, 10, 10, 10 };

    for(int i : input)
    {
        REQUIRE(l.insertLast(i));
    }

    l.removeRepeats();

    int result[] = { 10, 30, 20, 40, 20, 30, 10 };
    int i = 0;

    for(int x : l)
    {
        CHECK_EQ(x, result[i]);
        i++;
    }
    CHECK_EQ(i, 7);
}

TEST_CASE("Remove duplicate elements from the list")
{
    DLList<int> l;
    int input[] = { 10, 30, 20, 20, 40, 20, 30, 30, 10, 10, 10 };

    for(int i : input)
    {
        REQUIRE(l.insertLast(i));
    }

    l.unique();

    int result[] = { 10, 30, 20, 40 };
    int i = 0;

    for(int x : l)
    {
        CHECK_EQ(x, result[i]);
        i++;
    }
    CHECK_EQ(i, 4);
}

TEST_CASE("append testing") 
{
    DLList<int> l1, l2;

    int i = 1;
    for(; i <= 10; i++)
    {
        l1.insertLast(i);
    }

    for(; i <= 20; i++)
    {
        l2.insertLast(i);
    }

    l1.append(l2);
    CHECK(l2.empty());

    i = 1;
    for(int x : l1)
    {
        CHECK_EQ(x, i++);
    }
    CHECK_EQ(i, 21);
}

bool isEven(int num)
{ 
    return num % 2 == 0; 
}

TEST_CASE("divide testing") 
{
    DLList<int> l;
    int input[] = { 5, 2, 7, 9, 1, 0, 3, 8, 4 };

    for(int i : input)
    {
        REQUIRE(l.insertLast(i));
    }

    l.divide(isEven);

    int result[] = { 5, 7, 9, 1, 3, 2, 0, 8, 4 };
    int i = 0;

    for(int x : l)
    {
        CHECK_EQ(x, result[i]);
        i++;
    }
    CHECK_EQ(i, 9);
}
