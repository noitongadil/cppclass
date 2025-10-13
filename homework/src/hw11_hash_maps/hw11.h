#pragma once

#include <vector>

#include "xxhash.h"

namespace cppclass
{
/**
 * @brief A template class for a hash map.
 *
 * @tparam K The type of the key.
 * @tparam T The type of the data.
 */
template <typename K, typename T> class HashMap
{
public:
    /**
     * @brief Constructs an empty hash map.
     */
    HashMap();

    /**
     * @brief Copy constructs a hash map from @p other.
     *
     * @param other Reference to hash map to copy.
     */
    HashMap(const HashMap &other);

    /**
     * @brief Copy constructs a hash map from @p other.
     *
     * @param other Reference to hash map to copy.
     * @return Reference to this object.
     */
    HashMap &operator=(const HashMap &other);

    /**
     * @brief Move constructs a hash map from @p other.
     *
     * @param other R-value reference to hash map to move from.
     */
    HashMap(HashMap &&other);

    /**
     * @brief Copy constructs a hash map from @p other.
     *
     * @param other R-value reference to hash map to copy.
     * @return Reference to this object.
     */
    HashMap &operator=(const HashMap &&other);

    /**
     * @brief Destructor.
     */
    ~HashMap();

    /**
     * @brief Insert an item into the hash map.
     *
     * @param key The identifier of the data.
     * @param data Data to insert.
     * @return True if inserted, otherwise false.
     */
    bool insert(const K &key, const T &data);

    /**
     * @brief Remove an item from the hash map.
     *
     * @param key The identifier of the item to be removed.
     * @return True if removed, otherwise false.
     */
    bool remove(const K &key);

    /**
     * @brief Find an item from the hash map.
     *
     * @param key The indentifier of the item to find.
     * @return Const pointer to the item's data if found, otherwise nullptr.
     */
    const T *find(const K &key) const;

    /**
     * @brief Access the data of a pair with @p key in the hash map if it exists.
     *
     * @param key The identifier of the item to be accessed.
     * @return Pointer to the data if found, otherwise nullptr.
     */
    T *at(const K &key);

    /**
     * @brief Access the data of a pair with @p key in the hash map if it exists.
     *        If it doesn't exist, insert an item with a default-constructed value.
     *
     * @param key The identifier of the item to be accessed.
     * @return Reference to the data.
     */
    T &operator[](const K &key);

    /**
     * @brief Returns the number of items in the hash map.
     *
     * @return Number of items in the hash map.
     */
    size_t size() const;

    /**
     * @brief Returns true if hash map is empty, false if not.
     */
    bool empty() const;

private:
    struct KeyDataPair
    {
        K key; ///< The key for the pair.
        T Data; ///< The data for the pair.

        /**
         * @brief Constructs a new KeyDataPair.
         *
         * @param key The key for the pair.
         * @param data The data for the pair.
         */
        KeyDataPair(const K &key, const T &data);
    };

    std::vector<KeyDataPair *> m_vect; ///< Container to hold data.
    size_t m_size; ///< Number of elements in the hash table.

    /**
     * @brief Hashing method that uses xxhash.
     *
     * @param key The key to hash.
     * @param seed Hash seed (defaults to 0).
     * @return The 64-bit hash value.
     */
    XXH64_hash_t hash(const K &key, const XXH64_hash_t &seed = 0);
};
}
