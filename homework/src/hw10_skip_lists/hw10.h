#pragma once

#include <cstddef> // for size_t
#include <ctime> // for time()
#include <cstdlib> // for rand()
#include <cmath> // for log2
#include "gtest/gtest_prod.h" // for FRIEND_TEST

namespace cppclass
{
template <typename T, const size_t MAX_LEVEL> class SkipList
{
private:
    struct Node
    {
        T data; ///< The data that the node contains.
        Node **levels; ///< Pointer to an array of pointers. (heap-allocate)
        size_t height; ///< The height of the node (the array).

        /**
         * @brief Constructs a node with the given @p.
         *
         * @param data Reference to the data to be contained.
         * @param height The height of the node.
         */
        Node(const T &data, const size_t height)
            : data(data)
            , height(height)
        {
            levels = new Node *[height];
            for (int i = 0; i < height; i++)
            {
                levels[i] = nullptr;
            }
        }

        /**
         * @brief Destroys a node.
         */
        ~Node()
        {
            delete[] levels;
        }
    };

public:
    /**
     * @brief Constructs an empty skip list.
     */
    SkipList()
        : m_size(0)
    {
        SkipListSetUp();
    }

    /**
     * @brief Constructs a skip list from an array.
     *
     * @param arr Pointer to the array.
     * @param size Size of the array.
     */
    SkipList(const T *arr, const size_t size)
        : m_size(0)
    {
        SkipListSetUp();
        for (int i = 0; i < size; i++)
        {
            insert(*(arr + i));
        }
    }

    /**
     * @brief Copy constructs a skip list from @p other.
     *
     * @param other Reference to the skip list to copy from.
     */
    SkipList(const SkipList &other)
        : m_size(0)
    {
        SkipListSetUp();
        Node *curr = other.m_head->levels[0];
        for (int i = 0; i < other.m_size; i++)
        {
            this->insert(curr->data);
            curr = curr->levels[0];
        }
    }

    /**
     * @brief Move contructs a skip list from @p other
     *
     * @param other R-Value reference to the skip list to move from.
     */
    SkipList(SkipList &&other)
        : m_size(other.m_size)
        , m_head(other.m_head)
    {
        other.m_size = 0;
        other.m_head = nullptr;
    }

    /**
     * @brief Destroys the skip list.
     */
    ~SkipList()
    {
        Node *curr = m_head;
        while (curr != nullptr)
        {
            Node *next = curr->levels[0];
            delete curr;
            curr = next;
        }
    }

    /**
     * @brief Searches the skip list for the node with @p data.
     *
     * @param data Data to search for.
     * @return If found pointer to the node with @p data, else nullptr.
     */
    Node *search(const T &data) const
    {
        if (m_head->levels[0] == nullptr)
        {
            return nullptr;
        }
        Node *curr = m_head;

        for (int lvl = MAX_LEVEL - 1; lvl >= 0; lvl--)
        {
            while (curr->levels[lvl] != nullptr &&
                   curr->levels[lvl]->data < data)
            {
                curr = curr->levels[lvl];
            }
        }

        if (curr->levels[0] != nullptr && curr->levels[0]->data == data)
        {
            return curr->levels[0];
        }

        return nullptr;
    }

    /**
     * @brief Inserts a node with @p data into the skip list.
     *
     * @param data Data to add to skip list.
     * @return True if inserted, false if failed.
     */
    bool insert(const T &data)
    {
        size_t level = log2(rand() % (1 << MAX_LEVEL));
        Node *new_node = new Node(data, level);

        Node *curr = m_head;
        for (int lvl = MAX_LEVEL - 1; lvl >= 0; lvl--)
        {
            while (curr->levels[lvl] != nullptr &&
                   curr->levels[lvl]->data < new_node->data)
            {
                curr = curr->levels[lvl];
            }

            if (lvl < new_node->height)
            {
                new_node->levels[lvl] = curr->levels[lvl];
                curr->levels[lvl] = new_node;
            }
        }

        m_size++;
        return true;
    }

    /**
     * @brief Removes an element with @p data from the list.
     *
     * @param data The data of the item to be removed from the list.
     * @return True if removed, otherwise false.
     */
    bool remove(const T &data)
    {
        Node *curr = m_head;
        Node *node_to_rm = nullptr;

        for (int lvl = MAX_LEVEL - 1; lvl >= 0; lvl--)
        {
            while (curr->levels[lvl] != nullptr &&
                   curr->levels[lvl]->data < data)
            {
                curr = curr->levels[lvl];
            }

            if (curr->levels[lvl] != nullptr && curr->levels[lvl]->data == data)
            {
                node_to_rm = curr->levels[lvl];
                curr->levels[lvl] = curr->levels[lvl]->levels[lvl];
            }
        }

        if (node_to_rm != nullptr)
        {
            delete node_to_rm;
            m_size--;
            return true;
        }

        return false;
    }

    /**
     * @brief Returns the number of nodes in the list.
     *
     * @return Number of nodes in the list.
     */
    size_t size() const
    {
        return m_size;
    }

    /**
     * @brief Checks if two skip lists are equal in values and order.
     *
     * @param other Reference to other skip list.
     * @return True, if values and order are identical. False otherwise.
     */
    bool operator==(const SkipList &other) const
    {
        if (this->m_size != other.m_size)
        {
            return false;
        }

        Node *self_curr = m_head->levels[0];
        Node *other_curr = other.m_head->levels[0];
        for (int i = 0; i < m_size; i++)
        {
            if (self_curr->data != other_curr->data)
            {
                return false;
            }
        }

        return true;
    }

    /**
     * @brief Checks if two skip lists are inequal in values and order.
     *
     * @param other Reference to other skip list.
     * @return True, if values and order are not identical. False otherwise.
     */
    bool operator!=(const SkipList &other) const
    {
        return not(*this == other);
    }

private:
    size_t m_size; ///< Number of nodes in the skip list.
    Node *m_head; ///< Pointer to the first node in the skip list.

    void SkipListSetUp()
    {
        srand(time(0));
        m_head = new Node(T(), MAX_LEVEL);

        for (int i = 0; i < MAX_LEVEL; i++)
        {
            m_head->levels[i] = nullptr;
        }
    }

    FRIEND_TEST(BasicSkipListTest, DefaultConstructor);
    FRIEND_TEST(BasicSkipListTest, Insert);
    FRIEND_TEST(BasicSkipListTest, Erase);
    FRIEND_TEST(BasicSkipListTest, MoveConstructor);
};
}
