#include "heap.h"
#include "gtest/gtest.h"

namespace cppclass
{
class BasicHeapTest : public ::testing::Test
{
protected:
    BasicHeapTest()
    {
    }

    virtual ~BasicHeapTest()
    {
    }

    virtual void SetUp()
    {
        auto seed_gen = testing::UnitTest::GetInstance();
        int seed = seed_gen->random_seed();
        std::srand(seed);
        printf("seed=%d\n", seed);
    }

    virtual void TearDown()
    {
    }
};

TEST_F(BasicHeapTest, Insert)
{
    Heap<int> heap;
    heap.insert(5);
    heap.insert(10);
    heap.insert(12);
    heap.insert(11);
    ASSERT_TRUE(heap.is_valid());
}

TEST_F(BasicHeapTest, Top)
{
    Heap<int> heap;
    heap.insert(5);
    heap.insert(10);
    heap.insert(12);
    heap.insert(11);
    EXPECT_EQ(heap.top(), 5);
}

TEST_F(BasicHeapTest, Pop)
{
    Heap<int> heap;
    for (int i = 0; i < 15; i++)
    {
        heap.insert(rand());
        ASSERT_TRUE(heap.is_valid());
    }

    for (int i = 0; i < 15; i++)
    {
        ASSERT_TRUE(heap.pop() >= 0);
        ASSERT_TRUE(heap.is_valid());
    }
    printf("\n");
}
}
