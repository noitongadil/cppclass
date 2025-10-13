#include "queue.h"
#include "gtest/gtest.h"
#include "gtest/gtest_prod.h"

namespace cppclass
{
class BasicRingQueueTest : public ::testing::Test
{
protected:
    BasicRingQueueTest()
    {
    }

    virtual ~BasicRingQueueTest()
    {
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(BasicRingQueueTest, DefaultConstructor)
{
    RingQueue<int> queue;
    EXPECT_EQ(queue.m_tail, 1);
    EXPECT_EQ(queue.m_head, 0);
}

TEST_F(BasicRingQueueTest, PushBack)
{
    RingQueue<int> queue;
    EXPECT_TRUE(queue.push_back(1));
    EXPECT_TRUE(queue.push_back(2));
    EXPECT_TRUE(queue.push_back(3));
    EXPECT_TRUE(queue.push_back(4));
}

TEST_F(BasicRingQueueTest, Top)
{
    RingQueue<int> queue;
    EXPECT_TRUE(queue.push_back(1));
    EXPECT_TRUE(queue.push_back(2));
    EXPECT_TRUE(queue.push_back(3));
    EXPECT_TRUE(queue.push_back(4));
    EXPECT_EQ(queue.top(), 1);
}

TEST_F(BasicRingQueueTest, PopFront)
{
    RingQueue<int> queue;
    EXPECT_TRUE(queue.push_back(1));
    EXPECT_EQ(queue.pop_front(), 1);
    EXPECT_EQ(queue.top(), 0);
}

TEST_F(BasicRingQueueTest, ArrayConstructor)
{
    int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    RingQueue<int> queue(arr, 10);
    EXPECT_EQ(queue.m_head, 0);
    EXPECT_EQ(queue.m_tail, 11);
    EXPECT_EQ(queue.top(), 0);
}

TEST_F(BasicRingQueueTest, CopyConstructor)
{
    int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    RingQueue<int> queue(arr, 10);
    RingQueue<int> c_queue(queue);

    EXPECT_EQ(c_queue.m_head, 0);
    EXPECT_EQ(c_queue.m_tail, 11);
    EXPECT_EQ(c_queue.top(), 0);

    EXPECT_EQ(queue.m_head, 0);
    EXPECT_EQ(queue.m_tail, 11);
    EXPECT_EQ(queue.top(), 0);
}

TEST_F(BasicRingQueueTest, MoveConstructor)
{
    int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    RingQueue<int> queue(arr, 10);
    EXPECT_EQ(queue.m_head, 0);
    EXPECT_EQ(queue.m_tail, 11);
    EXPECT_EQ(queue.top(), 0);

    RingQueue<int> c_queue(std::move(queue));
    EXPECT_EQ(c_queue.m_head, 0);
    EXPECT_EQ(c_queue.m_tail, 11);
    EXPECT_EQ(c_queue.top(), 0);

    EXPECT_EQ(queue.m_head, 0);
    EXPECT_EQ(queue.m_tail, 0);
}

class RingQueueTest : public BasicRingQueueTest
{
protected:
    RingQueue<int> *p_queue;

    virtual void SetUp()
    {
        BasicRingQueueTest::SetUp();

        p_queue = new RingQueue<int>();
        for (int i = 0; i < 1024; i++)
        {
            p_queue->push_back(i);
        }
    }

    virtual void TearDown()
    {
        BasicRingQueueTest::TearDown();

        delete p_queue;
    }
};

TEST_F(RingQueueTest, MassRemoval)
{
    for (int i = 0; i < 1024; i++)
    {
        EXPECT_EQ(p_queue->top(), p_queue->pop_front());
    }
}

class BasicLinkQueueTest : public ::testing::Test
{
protected:
    BasicLinkQueueTest()
    {
    }

    virtual ~BasicLinkQueueTest()
    {
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(BasicLinkQueueTest, DefaultConstructor)
{
    LinkQueue<int> queue;
    EXPECT_EQ(queue.m_tail, nullptr);
    EXPECT_EQ(queue.m_head, nullptr);
}

TEST_F(BasicLinkQueueTest, PushBack)
{
    LinkQueue<int> queue;
    EXPECT_TRUE(queue.push_back(1));
    EXPECT_TRUE(queue.push_back(2));
    EXPECT_TRUE(queue.push_back(3));
    EXPECT_TRUE(queue.push_back(4));
}

TEST_F(BasicLinkQueueTest, Top)
{
    LinkQueue<int> queue;
    EXPECT_TRUE(queue.push_back(1));
    EXPECT_TRUE(queue.push_back(2));
    EXPECT_TRUE(queue.push_back(3));
    EXPECT_TRUE(queue.push_back(4));
    EXPECT_EQ(queue.top(), 1);
}

TEST_F(BasicLinkQueueTest, PopFront)
{
    LinkQueue<int> queue;
    EXPECT_TRUE(queue.push_back(1));
    EXPECT_EQ(queue.pop_front(), 1);
}

TEST_F(BasicLinkQueueTest, ArrayConstructor)
{
    int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    LinkQueue<int> queue(arr, 10);
    EXPECT_EQ(queue.m_head->data, 0);
    EXPECT_EQ(queue.m_tail->data, 9);
    EXPECT_EQ(queue.top(), 0);
}

TEST_F(BasicLinkQueueTest, CopyConstructor)
{
    int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    LinkQueue<int> queue(arr, 10);
    LinkQueue<int> c_queue(queue);

    EXPECT_EQ(c_queue.m_head->data, queue.m_head->data);
    EXPECT_EQ(c_queue.m_tail->data, queue.m_tail->data);
    EXPECT_EQ(c_queue.top(), 0);
    EXPECT_EQ(queue.top(), 0);
}

TEST_F(BasicLinkQueueTest, MoveConstructor)
{
    int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    LinkQueue<int> queue(arr, 10);
    EXPECT_EQ(queue.m_head->data, 0);
    EXPECT_EQ(queue.m_tail->data, 9);
    EXPECT_EQ(queue.top(), 0);

    LinkQueue<int> m_queue(std::move(queue));
    EXPECT_EQ(m_queue.m_head->data, 0);
    EXPECT_EQ(m_queue.m_tail->data, 9);
    EXPECT_EQ(m_queue.top(), 0);

    EXPECT_EQ(queue.m_head, nullptr);
    EXPECT_EQ(queue.m_tail, nullptr);
}

class LinkQueueTest : public BasicLinkQueueTest
{
protected:
    LinkQueue<int> *p_queue;

    virtual void SetUp()
    {
        BasicLinkQueueTest::SetUp();

        p_queue = new LinkQueue<int>();
        for (int i = 0; i < 1024; i++)
        {
            p_queue->push_back(i);
        }
    }

    virtual void TearDown()
    {
        BasicLinkQueueTest::TearDown();

        delete p_queue;
    }
};

TEST_F(LinkQueueTest, MassRemoval)
{
    for (int i = 0; i < 1024; i++)
    {
        EXPECT_EQ(p_queue->pop_front(), i);
    }
}
}
