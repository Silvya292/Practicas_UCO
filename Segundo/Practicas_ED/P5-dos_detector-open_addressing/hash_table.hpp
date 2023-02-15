/**
 * @file hash_table.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#pragma once

#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <vector>
#include <list>
#include <utility>
#include <memory>

#include "hash.hpp"
#include "hash_table_entry.hpp"

/**
 * @brief Implement the HashTable[K,V] ADT.
 *
 * The template parameter keyToInt is a functional to transform
 * values of type K into size_t. It must implement the interface:
 * std::uint64_t operator()(K const&k)
 *
 * The template parameter Hash is a functional (the hash function) to
 * transform from keys (std::uint64_t) to table indices (size_t). It must
 * implement the interfaces:
 *    - static Hash::Ref create(size_t table_size); pick at random
 *      a new hash function from the Universal Family using the given
 *      table size.
 *    - size_t operator()(std::uint64_t k, size_t iter=0); where
 *      iter indicates the current collision resolution iteration.
 *
 * @invariant load_factor() <= 0.5
 */
template<class K, class V, class KeyToInt, class Hash>
class HashTable
{
public:

    /** @brief A reference to a hash table.*/
    typedef std::shared_ptr<HashTable<K,V,KeyToInt,Hash>> Ref;

    /** @name Life cicle.*/
    /** @{*/

    /**
      * @brief Create a new HashTable.
      * @param m is the table size.
      * @param key_to_int is the conversor from key values to int value.
      * @param hash is the hash function.
      * @post not is_valid()
      * @post size()==m
      */
    HashTable(size_t m, typename KeyToInt::Ref key_to_int,
              typename Hash::Ref hash);

    /**
      * @brief Virtual constructor.
      * @param m is the table size.
      * @param key_to_int is the conversor from key values to int value.
      * @param hash is a reference to the hash function.
      * @post is_empty()
      * @post not is_valid()
      * @post size()==m
      */
    static Ref create(size_t m, typename KeyToInt::Ref key_to_int,
                      typename Hash::Ref hash);

    /** @}*/

    /** @name Observers*/
    /** @{*/

    /**
     * @brief Get the table size.
     * @return the size of the table.
     */
    size_t size() const;

    /**
     * @brief Return the load factor of the table.
     * @return the load factor.
     */
    float load_factor() const;

    /**
     * @brief Has the table this key?
     * @param k the key to find.
     * @return true if the key is saved into the table.
     * @warning The cursor is not affected by this operation.
     */
    bool has(K const& k) const;

    /**
     * @brief is the cursor at a valid position?
     * @return true if the cursor is at a valid position.
     */
    bool is_valid() const;

    /**
     * @brief Get the key at cursor.
     * @return return the key of the cursor.
     * @pre is_valid()
     */
    K get_key() const;

    /**
     * @brief Get tha value at cursor.
     * @return return the value of the cursor.
     * @pre is_valid()
     */
    V get_value() const;

    /** @}*/

    /** @name Modifiers*/
    /** @{*/

    /**
     * @brief Find a key value.
     * @return true if the key is found.
     * @post !is_valid() or get_key()==k
     */
    bool find(K const& k);

    /**
     * @brief Insert a new entry.
     *
     * If the key is currently in the table, the value is updated.
     *
     * @post is_valid()
     * @post get_key()==k
     * @post get_value()==v;
     * @post not old(has(k)) -> num_of_valid_keys() = old(num_of_valid_keys())+1
     */
    void insert(K const& k, V const& v);

    /**
     * @brief Remove the entry at the cursor position.
     * @pre is_valid()
     * @post !is_valid()
     * @post !has(old.get_key())
     */
    void remove();

    /**
     * @brief Set the value of the entry at the cursor position.
     */
    void set_value(const V& v);

    /**
     * @brief Move the cursor to the first valid entry if there is.
     */
    void goto_begin();

    /**
     * @brief Move the cursor to next valid position if there is.
     * @prec is_valid()
     */
    void goto_next();

    /** @} */

protected:

    /**
     * @brief Generate a new table with doble size when load factor > 0.5
     * @post load_factor()<=0.5
     */
    void rehash();

    //Alias for the table type.
    typedef std::vector<HashTableEntry<K,V>> table_t;

    typename KeyToInt::Ref key_to_int_; //Convert key values to int.
    typename Hash::Ref hash_; //The hash function.
    std::shared_ptr<table_t> table_; //The table.
    size_t curr_; //Cursor.
    size_t used_entries_; //Counter of used entries (valid and deleted).

};

#include "hash_table_entry_imp.hpp"
