#pragma once

#include <cstddef>
#include "gtest/gtest_prod.h"

namespace cppclass {
template <typename T> class LinkedList {
public:
    /// @brief Node definition for the linked list.
    struct Node {
        T data;
        Node *next;
        Node *prev;

        /// @brief Default constructor
        Node() : data(), next(nullptr), prev(nullptr) {}
    };

    /// @brief Constructs an empty linked list.
    LinkedList()
        : m_head(nullptr),
        m_tail(nullptr),
        m_size(0) {}

    /**
     * @brief Constructs a linked list from an array.
     *
     * @param arr Pointer to the array.
     * @param size Number of elements in the array.
     */
    LinkedList(const T *arr, size_t size)
        : m_head(nullptr),
        m_tail(nullptr),
        m_size(0) {
        for (int i = 0; i < size; i++) {
            append(*(arr + i));
        }
    }

    /**
     * @brief Copy constructor.
     *
     * @param src Reference to the linked list to copy from.
     */
    LinkedList(const LinkedList &src)
        : m_head(nullptr),
        m_tail(nullptr),
        m_size(0) {
        Node *src_curr = src.m_head;
        while (src_curr) {
            append(src_curr->data);
            src_curr = src_curr->next;
        }
    }

    /**
     * @brief Move constructor.
     *
     * @param src R-value reference to the linked list to move from.
     */
    LinkedList(LinkedList &&src)
        : m_head(src.m_head),
        m_tail(src.m_tail),
        m_size(src.m_size) {
        src.m_head = nullptr;
        src.m_tail = nullptr;
        src.m_size = 0;
    }

    /**
     * @brief Destructor.
     */
    ~LinkedList() {
        while (m_head) erase(m_head);
    }

    /**
     * @brief Remove an element from the linked list.
     *
     * @param node Pointer to a valid node in this list. If nullptr, does nothing.
     */
    void erase(Node *node) {
        if (!node || m_size <= 0) return;

        if (m_size == 1) {
            m_tail = nullptr;
            m_head = nullptr;
        } else if (node == m_head) {
            m_head = node->next;
            node->next->prev = nullptr;
        } else if (node == m_tail) {
            node->prev->next = nullptr;
            m_tail = node->prev;
        } else {
            node->next->prev = node->prev;
            node->prev->next = node->next;
        }

        delete node;
        m_size--;
    }

    /**
     * @brief Appends a new node after the specified node.
     *
     * @param data Data to store in the new node.
     * @param node Pointer to a valid node in the list to append after. If nullptr, appends at end.
     *
     * @return Pointer to the newly created node.
     */
    Node* append(T data, Node *node = nullptr) {
        Node *new_node = new Node();
        new_node->data = data;

        if (m_size == 0) {
            m_tail = new_node;
            m_head = new_node;
        } else if (node == m_tail || !node) {
            m_tail->next = new_node;
            new_node->prev = m_tail;
            m_tail = new_node;
        } else {
            new_node->prev = node;
            node->next->prev = new_node;
            new_node->next = node->next;
            node->next = new_node;
        }

        m_size++;
        return new_node;
    }

    /**
      * @brief Inserts a new node before the specified node.
      *
      * @param data Data to store in the new node.
      * @param node Pointer to a valid node in the list to insert before. If nullptr, inserts at the beginning.
      * @return Pointer to the newly created node.
      */
    Node* insert(T data, Node *node = nullptr) {
        Node *new_node = new Node();
        new_node->data = data;

        if (m_size == 0) {
            m_head = new_node;
            m_tail = new_node;
        } else if (node == m_head || !node) {
            m_head->prev = new_node;
            new_node->next = m_head;
            m_head = new_node;
        } else {
            new_node->next = node;
            new_node->prev = node->prev;
            node->prev->next = new_node;
            node->prev = new_node;
        }

        m_size++;
        return new_node;
    }

    /**
     * @brief Searches for the first node containing given data.
     *
     * @param data Data to search for in the list.
     * @return Pointer to the first node found with @p data. If not found, returns nullptr.
     */
    Node* search(T data) const {
        Node *scout = m_head;
        while (scout) {
            if (scout->data == data) return scout;
            scout = scout->next;
        }
        return nullptr;
    }

    /**
     * @brief Accesses element at the given index.
     *
     * @param index Zero-based index of a node.
     * @return Pointer to the node. If index is out of bounds, returns nullptr.
     */
    Node* at(unsigned int index) const {
        if (index >= m_size) return nullptr;

        Node *curr;
        if (index > m_size / 2) {
            curr = m_tail;
            for (int i = m_size - 1; i > index; i--) {
                curr = curr->prev;
            }
        } else {
            curr = m_head;
            for (int i = 0; i < index; i++) {
                curr = curr->next;
            }
        }

        return curr;
    }

    /**
     * @brief Returns number of nodes in the list.
     *
     * @return Current size of list.
     */
    size_t get_size() const { return m_size; }

    /**
     * @brief Returns equality between two linked lists
     *
     * @return true if all elements in linked list are equal to each other in order and value
     */
    bool operator==(const LinkedList &other) const {
        if (m_size != other.m_size) return false;

        Node *self_curr = m_head;
        Node *other_curr = other.m_head;

        while (self_curr && other_curr) {
            if (self_curr->data != other_curr->data) return false;
            self_curr = self_curr->next;
            other_curr = other_curr->next;
        }

        return true;
    }

    /**
     * @brief Returns non-equality between two linked lists
     *
     * @return false if all elements in linked list are equal to each other in order and value
     */
    bool operator!=(const LinkedList &other) const {
        return !(*this == other);
    }

private:
    Node *m_head; ///< Pointer to the first node.
    Node *m_tail; ///< Pointer to the last node.
    size_t m_size; ///< Number of elements in the list.

    FRIEND_TEST(BasicLinkedListTest, DefaultConstructor);
    FRIEND_TEST(BasicLinkedListTest, GetSizeWithMutating);
    FRIEND_TEST(BasicLinkedListTest, HeadTailMutation);
    FRIEND_TEST(BasicLinkedListTest, MoveConstructor);
    FRIEND_TEST(LinkedListTest, Erase);
};
}
