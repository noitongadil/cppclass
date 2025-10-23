#include "hw10.h"
#include "gtest/gtest.h"
#include "gtest/gtest_prod.h"
#include <stdexcept>
#include <iostream>

namespace cppclass
{
class BasicSkipListTest : public ::testing::Test
{
protected:
    BasicSkipListTest()
    {
    }

    virtual ~BasicSkipListTest()
    {
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(BasicSkipListTest, DefaultConstructor)
{
    SkipList<int, 20> sl;
    EXPECT_EQ(sl.m_head->height, 20);
    EXPECT_EQ(sl.m_size, 0);
}

TEST_F(BasicSkipListTest, Insert)
{
    SkipList<int, 20> sl;
    sl.insert(10);
    EXPECT_EQ(sl.size(), 1);

    EXPECT_EQ(sl.m_head->levels[0]->data, 10);
}

TEST_F(BasicSkipListTest, Erase)
{
    SkipList<int, 20> sl;
    sl.insert(10);
    EXPECT_TRUE(sl.remove(10));

    EXPECT_EQ(sl.size(), 0);
}

TEST_F(BasicSkipListTest, ArrayConstructor)
{
    int arr[20];
    for (int i = 0; i < 20; i++)
    {
        *(arr + i) = i;
    }

    SkipList<int, 20> sl(arr, 20);
    EXPECT_EQ(sl.size(), 20);
    for (int i = 0; i < 20; i++)
    {
        EXPECT_NE(sl.search(i), nullptr);
    }
}

TEST_F(BasicSkipListTest, CopyConstructor)
{
    int arr[20];
    for (int i = 0; i < 20; i++)
    {
        *(arr + i) = i;
    }

    SkipList<int, 20> src(arr, 20);
    SkipList<int, 20> sl(src);
    EXPECT_TRUE(sl == src);
}

TEST_F(BasicSkipListTest, MoveConstructor)
{
}
}
