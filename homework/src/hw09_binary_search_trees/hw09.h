#pragma once

#include <algorithm> // for std::sort
#include <iomanip> // for std::setw
#include <iostream> // for std::cout
#include <vector> // for std::vector
#include <cstddef> // for size_t

namespace cppclass {
template <typename T> class BinarySearchTree {
public:
    struct Node {
        T data;
        Node *right;
        Node *left;

        /**
         * @brief Constructs an empty Node.
         *
         * @param val Data for the Node to hold.
         */
        Node(T val) : data(val), left(nullptr), right(nullptr) {}
    };

    /// @brief An empty BinarySearchTree will be created.
    BinarySearchTree() : m_root(nullptr), m_size(0) {}

    /**
     * @brief Constructor that initializes the tree with an array of values.
     *
     * @param arr Pointer to an array of values.
     * @param size Size of the array.
     */
    BinarySearchTree(const T *arr, size_t size)
            : m_root(nullptr), m_size(0) {
        std::vector<T> local_arr(arr, arr + size);
        std::sort(local_arr.begin(), local_arr.end());
        bisection_insert(local_arr, 0, size);
    }

    /**
     * @brief Copy constructor for BinarySearchTree.
     *
     * @param other Reference to BinarySearchTree to copy from.
     */
    BinarySearchTree(const BinarySearchTree& other)
            : m_root(nullptr), m_size(0) {
        prefix_insert(other.m_root);
    }

    /**
     * @brief Move constructor for BinarySearchTree.
     *
     * @param other R-value reference to another BinarySearchTree object.
     */
    BinarySearchTree(BinarySearchTree&& other)
            : m_root(other.m_root), m_size(other.m_size) {
        other.m_root = nullptr;
        other.m_size = 0;
    }

    /// @brief Destructor for BinarySearchTree.
    ~BinarySearchTree() {
        postfix_del(m_root);
    }

    /**
     * @brief Inserts a value into the binary search tree.
     *
     * @param value The value to insert. Cannot be a duplicate.
     * @return True if the value was inserted successfully, false if it already exists.
     */
    bool insert(const T &value) {
        auto current = m_root;

        if (m_size == 0) {
            m_root = new Node(value);
            m_size++;
            return true;
        }

        while (current) {
            if (value > current->data) {
                if (!current->right) {
                    current->right = new Node(value);
                    m_size++;
                    return true;
                }
                current = current->right;

            } else if (value < current->data) {
                if (!current->left) {
                    current->left = new Node(value);
                    m_size++;
                    return true;
                }
                current = current->left;

            } else {
                return false;
            }
        }

        return false;
    }

    /**
     * @brief Removes a value from the binary search tree.
     *
     * @param value The value to remove. Must be present in the tree.
     * @return True if the value was removed successfully, false if it was not found.
     */
    bool remove(const T &value) {
        Node *target = m_root;
        while (target) {
            if (target->data > value) {
                target = target->left;
            } else if (target->data < value) {
                target = target->right;
            } else {
                break;
            }
        }

        if (!target) {
            return false;
        }

        if (target->right) {
            auto current = target->right;
            if (!current->left) {
                target->data = current->data;
                target->right = current->right;
                delete current;
                m_size--;
                return true;
            }

            while (current->left->left) {
                current = current->left;
            }

            target->data = current->left->data;
            if (current->left->right) {
                Node *tmp = current->left->right;
                delete current->left;
                m_size--;
                current->left = tmp;
            } else {
                delete current->left;
                m_size--;
            }

        } else if (target->left) {
            auto current = target->left;
            if (!current->right) {
                target->data = current->data;
                target->left = current->left;
                delete current;
                m_size--;
                return true;
            }

            while (current->right->right) {
                current = current->right;
            }

            target->data = current->right->data;
            if (current->right->left) {
                Node *tmp = current->right->left;
                delete current->right;
                m_size--;
                current->right = tmp;
            } else {
                delete current->right;
                m_size--;
            }

        } else {
            delete target;
            m_size--;
        }

        return true;
    }

    /**
     * @brief Checks if a value is contained in the binary search tree.
     *
     * @param value The value to check.
     * @return True if the value is found, false otherwise.
     */
    bool contains(T value) const {
        Node *current = m_root;
        while (current) {
            if (current->data > value) {
                current = current->left;
            } else if (current->data < value) {
                current = current->right;
            } else {
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Returns the size of the binary search tree.
     *
     * @return The number of nodes in the tree.
     */
    size_t size() const { return m_size; }

    /**
     * @brief Checks if two binary search trees are equal.
     *
     * @param other The other binary search tree to compare with.
     * @return True if the trees are equal, false otherwise.
     */
    bool operator==(const BinarySearchTree& other) const {
        return prefix_comp(m_root, other.m_root);
    }

    /**
     * @brief Checks if the binary search tree is not equal to another tree.
     *
     * @param other The other binary search tree to compare with.
     * @return True if the trees are not equal, false otherwise.
     */
    bool operator!=(const BinarySearchTree& other) const {
        return !(*this == other);
    }

private:
    /// @brief Prints the binary search tree in-order.
    void print() const {
        print_helper(m_root, 0);
    }

    /**
     * @brief Checks if the binary search tree is valid.
     *
     * @return True if the tree is valid, false otherwise.
     */
    bool isValid() const {
        return isValid_helper(m_root, nullptr, nullptr);
    }

    bool isValid_helper(Node *node, const T *min, const T *max) const {
        if (!node) return true;

        if ((min && node->data <= *min) || (max && node->data >= *max))
            return false;

        return isValid_helper(node->left, min, node->data) &&
               isValid_helper(node->right, node->data, max);
    }

    void print_helper(Node *current, size_t level) const {
        if (!current) return;

        print_helper(current->right, level + 2);
        std::cout << std::setw(level * 2) << current->data << std::endl;
        print_helper(current->left, level + 2);
    }

    void postfix_del(Node *current) {
        if (!current) return;

        postfix_del(current->left);
        postfix_del(current->right);
        delete current;
    }

    void prefix_insert(Node *current) {
        if (!current) return;

        this->insert(current->data);
        prefix_insert(current->left);
        prefix_insert(current->right);
    }

    void bisection_insert(std::vector<T> &arr, size_t lower, size_t upper) {
        if (lower >= upper) return;

        size_t midpoint = (lower + upper) / 2;
        this->insert(arr[midpoint]);
        bisection_insert(arr, lower, midpoint);
        bisection_insert(arr, midpoint + 1, upper);
    }

    bool prefix_comp(Node *self_curr, Node *other_curr) const {
        if (!self_curr && !other_curr)
            return true;

        if (!self_curr || !other_curr)
            return false;

        if (self_curr->data != other_curr->data)
            return false;

        return prefix_comp(self_curr->left, other_curr->left) &&
               prefix_comp(self_curr->right, other_curr->right);
    }

    Node *m_root;
    size_t m_size;
};
} // namespace cppclass
