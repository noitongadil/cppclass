#pragma once

#include <cstddef> // for size_t

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
        Node(const T &data, const size_t height);

        /**
         * @brief Destroys a node.
         */
        ~Node();
    };

public:
    /**
     * @brief Constructs an empty skip list.
     */
    SkipList();

    /**
     * @brief Constructs a skip list from an array.
     *
     * @param arr Pointer to the array.
     * @param size Size of the array.
     */
    SkipList(const T *arr, const size_t size);

    /**
     * @brief Copy constructs a skip list from @p other.
     *
     * @param other Reference to the skip list to copy from.
     */
    SkipList(const SkipList &other);

    /**
     * @brief Move contructs a skip list from @p other
     *
     * @param other R-Value reference to the skip list to move from.
     */
    SkipList(SkipList &&other);

    /**
     * @brief Destroys the skip list.
     */
    ~SkipList();

    /**
     * @brief Searches the skip list for the node with @p data.
     *
     * @param data Data to search for.
     * @return If found pointer to the node with @p data, else nullptr.
     */
    Node *search(const T &data) const;

    /**
     * @brief Inserts a node with @p data into the skip list.
     *
     * @param data Data to add to skip list.
     * @return True if inserted, otherwise false.
     */
    bool insert(const T &data);

    /**
     * @brief Removes an element with @p data from the list.
     *
     * @param data The data of the item to be removed from the list.
     * @return True if removed, otherwise false.
     */
    bool remove(const T &data);

    /**
     * @brief Returns the number of nodes in the list.
     *
     * @return Number of nodes in the list.
     */
    size_t size() const;

    /**
     * @brief Checks if two skip lists are equal in values and order.
     *
     * @param other Reference to other skip list.
     * @return True, if values and order are identical. False otherwise.
     */
    bool operator==(const SkipList &other) const;

    /**
     * @brief Checks if two skip lists are inequal in values and order.
     *
     * @param other Reference to other skip list.
     * @return True, if values and order are not identical. False otherwise.
     */
    bool operator!=(const SkipList &other) const;

private:
    size_t m_size; ///< Number of nodes in the skip list.
    Node *m_head; ///< Pointer to the first node in the skip list.
};
}
