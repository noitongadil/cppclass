#pragma once

#include <vector> // for std::vector
#include <stdlib.h> // for size_t

#include "gtest/gtest.h"

namespace cppclass
{
template <typename T> class Heap
{
public:
    /// @brief Constructs an empty heap.
    Heap()
    {
        m_vect.reserve(10);
    }

    /**
     * @brief Constructs a heap from an array.
     *
     * @param arr Pointer to the array.
     * @param size Size of the array.
     */
    Heap(const T *arr, size_t size)
    {
        for (int i = 0; i < size; i++)
        {
            insert(*(arr + i));
        }
    }

    /**
     * @brief Copy constructs a heap from another heap.
     *
     * @param other Reference to the heap to copy from.
     */
    Heap(const Heap &other)
        : m_vect(other.m_vect)
    {
    }

    /**
     * @brief Copy assignment operator.
     *
     * @param other Reference to the heap to copy from.
     * @return Reference to this heap after assignment.
     */
    Heap &operator=(const Heap &other)
    {
        m_vect = other.m_vect;
    }

    /**
     * @brief Move constructs a heap from another heap.
     *
     * @param other R-Value reference to the heap to move from.
     */
    Heap(Heap &&other)
        : m_vect(std::move(other.m_vect))
    {
    }

    /**
     * @brief Move assignment operator.
     *
     * @param other R-Value reference to the heap to move from.
     * @return Reference to this heap after assignment.
     */
    Heap &operator=(Heap &&other)
    {
        m_vect = std::move(other.m_vect);
    }

    /// @brief Destroys the heap.
    ~Heap() = default;

    /**
     * @brief Peek at the root of the heap.
     *
     * @return The root of the heap.
     */
    const T &top() const
    {
        return m_vect[0];
    }

    /**
     * @brief Removes and returns the root of the heap.
     *
     * @return The root of the heap.
     */
    T pop()
    {
        T tmp = m_vect[0];
        std::swap(m_vect[0], m_vect.back());
        m_vect.pop_back();
        heapify_down();
        return tmp;
    }

    /**
     * @brief Inserts @p data to the heap.
     *
     * @param data Data to insert into the heap.
     */
    void insert(const T &data)
    {
        m_vect.emplace_back(data);
        heapify_up(m_vect.size() - 1);
    }

    /// @brief Returns the number of elements in the heap.
    size_t size() const
    {
        return m_vect.size();
    }

    /**
     * @brief Equality comparison.
     *
     * @param other The heap to compare with.
     * @return True if the heaps do not differ in order or value.
     */
    bool operator==(const Heap &other) const
    {
        return m_vect == other.m_vect;
    }

    /**
     * @brief Inequality comparison.
     *
     * @param other The heap to compare with.
     * @return True if the heaps differ in order or value.
     */
    bool operator!=(const Heap &other) const
    {
        return !(*this == other);
    }

private:
    std::vector<T> m_vect; ///< Container to hold the heap's elements.

    /**
     * @brief Checks the validity of the heap.
     *
     * @return True if valid, false if invalid.
     */
    bool is_valid() const
    {
        const size_t SIZE = m_vect.size();
        for (int i = 0; left_child(i) < SIZE; i++)
        {
            if (m_vect[left_child(i)] < m_vect[i] ||
                (right_child(i) < SIZE && m_vect[right_child(i)] < m_vect[i]))
            {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief Restores the heap property by moving the element at @p index up.
     *
     * @param index Index of the element to move up.
     */
    void heapify_up(size_t child_index)
    {
        size_t parent_index = parent(child_index);
        while (child_index > 0)
        {
            if (m_vect[child_index] >= m_vect[parent_index])
            {
                return;
            }

            std::swap(m_vect[child_index], m_vect[parent_index]);
            child_index = parent_index;
            parent_index = parent(child_index);
        }
    }

    /**
     * @brief Maintains the heap property by moving the root down for deletion.
     */
    void heapify_down()
    {
        size_t parent = 0;
        size_t l_child;
        size_t r_child;
        size_t smallest;
        const size_t SIZE = m_vect.size();

        while (true)
        {
            l_child = left_child(parent);
            r_child = right_child(parent);
            smallest = parent;

            if (l_child < SIZE && m_vect[l_child] < m_vect[smallest])
            {
                smallest = l_child;
            }

            if (r_child < SIZE && m_vect[r_child] < m_vect[smallest])
            {
                smallest = r_child;
            }

            if (smallest == parent)
            {
                break;
            }

            std::swap(m_vect[parent], m_vect[smallest]);
            parent = smallest;
        }
    }

    /**
     * @brief Returns the index of the left child of @p parent.
     *
     * @param parent_index Index of the parent.
     * @return Index of the left child;
     */
    inline size_t left_child(size_t parent_index) const
    {
        return parent_index * 2 + 1;
    }

    /**
     * @brief Returns the index of the right child of @p parent.
     *
     * @param parent_index Index of the parent.
     * @return Index of the right child;
     */
    inline size_t right_child(size_t parent_index) const
    {
        return parent_index * 2 + 2;
    }

    /**
     * @brief Returns the index of the parent of @p child.
     *
     * @param child_index Index of the child.
     * @return Index of the parent;
     */
    inline size_t parent(size_t child_index) const
    {
        return (child_index - 1) / 2;
    }

    void print()
    {
    }

    FRIEND_TEST(BasicHeapTest, Insert);
    FRIEND_TEST(BasicHeapTest, Pop);
};
} // namespace cppclass
