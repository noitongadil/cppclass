#pragma once

#include <cstddef> /// for size_t

namespace cppclass
{
template <typename T> class RingQueue
{
public:
    /// @brief Default constructor.
    RingQueue();

    /// @brief Array constructor.
    RingQueue(const T *arr, size_t size);

    /// @brief Copy constructor.
    RingQueue(const RingQueue &other);

    /// @brief Move constructor.
    RingQueue(RingQueue &&other);

    /// @brief Destructor.
    ~RingQueue();

    /// @brief Peek at top data.
    const T &top() const;

    /// @brief Remove and return top.
    T pop_front();

    /// @brief Push data to back.
    bool push_back(const T &data);

private:
    T *m_p_arr = new T[1024]{}; ///< Container to hold data.
    size_t m_head; ///< Index to the start of valid data.
    size_t m_tail; ///< Index to the end of valid data.
};

template <typename T> class LinkQueue
{
public:
    struct Node
    {
        T data;
        Node *next;

        Node(T data);
    };

    /// @brief Default constructor.
    LinkQueue();

    /// @brief Array constructor.
    LinkQueue(const T *arr, size_t size);

    /// @brief Copy constructor.
    LinkQueue(const LinkQueue &other);

    /// @brief Move constructor.
    LinkQueue(LinkQueue &&other);

    // @brief Destructor.
    ~LinkQueue();

    /// @brief Peek at top data.
    const T &top() const;

    /// @brief Remove and return top.
    T pop_front();

    /// @brief Push data to back.
    bool push_back(const T &data);

private:
    Node *m_head; ///< Pointer to the start of list.
    Node *m_tail; ///< Pointer to the end of list.
    size_t m_size; ///< Number of nodes in the list.
};
}
