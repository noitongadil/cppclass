#pragma once

#include "gtest/gtest_prod.h" // for FRIEND_TEST
#include <cstddef> // for size_t
#include <cstdio> // for stderr

namespace cppclass
{
template <typename T> class RingQueue
{
public:
    /// @brief Default constructor.
    RingQueue()
        : m_head(0)
        , m_tail(1)
    {
    }

    /// @brief Array constructor.
    RingQueue(const T *arr, size_t size)
        : m_head(0)
        , m_tail(size + 1)
    {
        for (int i{}; i < size; i++)
        {
            *(m_p_arr + i) = *(arr + i);
        }
    }

    /// @brief Copy constructor.
    RingQueue(const RingQueue &other)
        : m_head(other.m_head)
        , m_tail(other.m_tail)
    {
        for (int i{}; i < other.m_tail; i++)
        {
            *(m_p_arr + i) = *(other.m_p_arr + i);
        }
    }

    /// @brief Move constructor.
    RingQueue(RingQueue &&other)
        : m_p_arr(other.m_p_arr)
        , m_head(other.m_head)
        , m_tail(other.m_tail)
    {
        other.m_p_arr = nullptr;
        other.m_tail = 0;
        other.m_head = 0;
    }

    /// @brief Destructor.
    ~RingQueue()
    {
        delete[] m_p_arr;
    }

    /// @brief Peek at top data.
    const T &top() const
    {
        return *(m_p_arr + m_head);
    }

    /// @brief Remove and return top.
    T pop_front()
    {
        auto tmp = *(m_p_arr + m_head);
        m_head = (m_head >= 1023) ? 0 : m_head + 1;
        return tmp;
    }

    /// @brief Push data to back.
    bool push_back(const T &data)
    {
        if (m_head == m_tail)
        {
            return false;
        }

        *(m_p_arr + m_tail - 1) = data;
        m_tail = (m_tail >= 1023) ? 0 : m_tail + 1;

        return true;
    }

private:
    T *m_p_arr = new T[1024]{}; ///< Container to hold data.
    size_t m_head; ///< Index to the start of valid data.
    size_t m_tail; ///< Index to the end of valid data.

    FRIEND_TEST(BasicRingQueueTest, DefaultConstructor);
    FRIEND_TEST(BasicRingQueueTest, ArrayConstructor);
    FRIEND_TEST(BasicRingQueueTest, CopyConstructor);
    FRIEND_TEST(BasicRingQueueTest, MoveConstructor);
    FRIEND_TEST(RingQueueTest, SetUp);
};

template <typename T> class LinkQueue
{
public:
    struct Node
    {
        T data;
        Node *next;

        Node(T data)
            : data(data)
            , next(nullptr)
        {
        }
    };

    /// @brief Default constructor.
    LinkQueue()
        : m_head(nullptr)
        , m_tail(nullptr)
        , m_size(0)
    {
    }

    /// @brief Array constructor.
    LinkQueue(const T *arr, size_t size)
        : LinkQueue()
    {
        for (int i = 0; i < size; i++)
        {
            push_back(*(arr + i));
        }
    }

    /// @brief Copy constructor.
    LinkQueue(const LinkQueue &other)
        : LinkQueue()
    {
        Node *current = other.m_head;
        for (int i = 0; i < other.m_size; i++)
        {
            push_back(current->data);
            current = current->next;
        }
    }

    /// @brief Move constructor.
    LinkQueue(LinkQueue &&other)
        : m_head(other.m_head)
        , m_tail(other.m_tail)
        , m_size(other.m_size)
    {
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0;
    }

    // @brief Destructor.
    ~LinkQueue()
    {
        while (m_head != nullptr)
        {
            pop_front();
        }
    }

    /// @brief Peek at top data.
    const T &top() const
    {
        if (m_head == nullptr)
        {
            fprintf(stderr, "queue empty");
        }

        return m_head->data;
    }

    /// @brief Remove and return top.
    T pop_front()
    {
        if (m_size == 0)
        {
            fprintf(stderr, "queue empty");
        }

        Node *old_head = m_head;
        T value = old_head->data;
        m_head = m_head->next;
        delete old_head;
        m_size--;

        return value;
    }

    /// @brief Push data to back.
    bool push_back(const T &data)
    {
        Node *new_node = new Node(data);
        if (m_size == 0)
        {
            m_head = new_node;
            m_tail = new_node;
        }
        else
        {
            m_tail->next = new_node;
            m_tail = new_node;
        }
        m_size++;
        return true;
    }

private:
    Node *m_head; ///< Pointer to the start of list.
    Node *m_tail; ///< Pointer to the end of list.
    size_t m_size; ///< Number of nodes in the list.

    FRIEND_TEST(BasicLinkQueueTest, DefaultConstructor);
    FRIEND_TEST(BasicLinkQueueTest, ArrayConstructor);
    FRIEND_TEST(BasicLinkQueueTest, CopyConstructor);
    FRIEND_TEST(BasicLinkQueueTest, MoveConstructor);
    FRIEND_TEST(LinkQueueTest, SetUp);
};
}
