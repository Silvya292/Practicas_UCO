/**
 * @file hash_table_entry.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#pragma once
#include <utility>
#include <memory>

/**
 * @brief Models an entry of a hash table.
 *
 * An entry has three states: empty, valid, deleted.
 * The entry data is a <Key,Value> pair.
 *
 * The template parameters K and V must have
 * default constructors.
 */
template<class K, class V>
class HashTableEntry
{
public:
    /** @name Life cicle.*/
    /** @{*/
    /**
     * @brief Create an empty entry.
     * @post is_empty()
     */
    HashTableEntry();

    /**
     * @brief Create a valid entry.
     * @param k is the key data of the pair.
     * @param v is the value data of the pair.
     * @post is_valid()
     * @post get_key()==k
     * @post get_value()==v
     */
    HashTableEntry(const K& k, const V& v);
    /** @}*/

    /** @name Observers.*/
    /** @{ */
    /**
     * @brief Check if the entry's state is Empty.
     * @return true if the entry's state is empty.
     */
    bool is_empty() const;
    /**
     * @brief Check if the entry's state is Deleted.
     * @return true if the entry's state is Deleted.
     */
    bool is_deleted() const;
    /**
     * @brief Check if the entry's state is Valid.
     * @return true if the entry's state is Valid.
     */
    bool is_valid() const;

    /**
     * @brief Get the key value of the entry.
     * @return the key value.
     * @pre !is_empty()
     */
    K get_key() const;
    /**
     * @brief Get the value data of the entry.
     * @return the value.
     * @pre !is_empty()
     */
    V get_value() const;
    /** @} */

    /** @name Modifiers.*/
    /** @{ */
    /**
     * @brief Set the pair <key,value>.
     * @post is_valid()
     * @post get_key()==k
     * @post get_value()==v
     */
    void set(const K& k, const V& v);
    /**
     * @brief Set the value data.
     * @pre is_valid()
     * @post is_valid()
     * @post old.get_key()==get_key()
     * @post get_value()==v
     */
    void set_value(const V& v);
    /**
     * @brief Set the state of the entry to Deleted.
     * @pre is_valid()
     * @post is_deleted()
     */
    void set_deleted();
    /** @} */
protected:
    /**
     * @brief The entry's states.
     */
    enum EntryState
    {
        EMPTY=0,
        VALID=1,
        DELETED=2
    };
    //TODO:
    //Hint: you could use std::pair<> to represent the pair Key,Value.
    //      @see https://en.cppreference.com/w/cpp/utility/pair
    //Hint: To save space, you can use an unique_ptr<"pair k,v"> to reference
    //      the entry's data  so in this way empty entries don't use memory
    //      (note that the the load factor < 0.5, so half table could be in an
    //      empty state during most time).
    //      @see https://en.cppreference.com/w/cpp/memory/unique_ptr


    //
};

#include "hash_table_entry_imp.hpp"
