/**
 * @file hash_table_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#pragma once
#include <cassert>

#include "hash_table.hpp"


template<class K, class V, class KeyToInt, class Hash>
HashTable<K, V, KeyToInt, Hash>::HashTable(size_t m,
                                           typename KeyToInt::Ref key_to_int,
                                           typename Hash::Ref hash)
{
    //TODO:
    //table_t.size()=m;
    //key_to_int_=key_to_int;
    //hash_=hash;
    //curr_=table_[0].begin();
    //used_entries_=0
    //
    assert(!is_valid());
    assert(size()==m);
}

template<class K, class V, class KeyToInt, class Hash>
typename HashTable<K, V, KeyToInt, Hash>::Ref
HashTable<K, V, KeyToInt, Hash>::create(size_t m,
                                        typename KeyToInt::Ref key_to_int,
                                        typename Hash::Ref hash)
{
    return std::make_shared<HashTable<K, V, KeyToInt, Hash>>(m, key_to_int,
                                                            hash);
}

template<class K, class V, class KeyToInt, class Hash>
size_t
HashTable<K, V, KeyToInt, Hash>::size() const
{
    size_t ret_v = 0;
    //TODO:
    //ret_v=table_t.size();
    //
    return ret_v;
}

template<class K, class V, class KeyToInt, class Hash>
float
HashTable<K, V, KeyToInt, Hash>::load_factor() const
{
    float ret_v = 0.0f;
    //TODO:
    //ret_v=used_entries_/table_t.size();
    //
    return ret_v;
}


template<class K, class V, class KeyToInt, class Hash>
bool
HashTable<K, V, KeyToInt, Hash>::has(K const& k) const
{
    bool ret_v = false;
    //TODO:
    //hint: use the find method.

    //
    return ret_v;
}

template<class K, class V, class KeyToInt, class Hash>
bool
HashTable<K, V, KeyToInt, Hash>::is_valid() const
{
    bool ret_v = false;
    //TODO:

    //
    return ret_v;
}


template<class K, class V, class KeyToInt, class Hash>
K
HashTable<K, V, KeyToInt, Hash>::get_key() const
{
    assert(is_valid());
    K ret_v;
    //TODO:

    //
    return ret_v;
}

template<class K, class V, class KeyToInt, class Hash>
V
HashTable<K, V, KeyToInt, Hash>::get_value() const
{
    assert(is_valid());
    V ret_v = V();
    //TODO:

    //
    return ret_v;
}

template<class K, class V, class KeyToInt, class Hash>
bool
HashTable<K, V, KeyToInt, Hash>::find(K const& k)
{
    assert(load_factor()<1.0f);
    bool is_found=false;
    //TODO:

    //
    assert(!is_valid() || get_key()==k);
    return is_found;
}

template<class K, class V, class KeyToInt, class Hash>
void
HashTable<K, V, KeyToInt, Hash>::insert(K const& k, V const& v)
{
    assert(load_factor()<1.0f);

    //TODO:

    //

    rehash();

    assert(load_factor()<1.0f);
    assert(is_valid());
    assert(get_key()==k);
    assert(get_value()==v);
}

template<class K, class V, class KeyToInt, class Hash>
void
HashTable<K, V, KeyToInt, Hash>::remove()
{
#ifndef NDEBUG
    assert(is_valid());    
    K old_k = get_key();
#endif
    //TODO:
    //Remenber: we are using a mark to sign "deleted".


    //
    assert(!is_valid());
    assert(!has(old_k));
}

template<class K, class V, class KeyToInt, class Hash>
void
HashTable<K, V, KeyToInt, Hash>::set_value(const V& v)
{
    assert(is_valid());
    //TODO:

    //
    assert(get_value()==v);
}

template<class K, class V, class KeyToInt, class Hash>
void
HashTable<K, V, KeyToInt, Hash>::rehash()
{
    assert(is_valid()); //We assume to be call after inserting.
    auto old_curr_key = get_key();
    //TODO:
    //Remenber: you must restore the cursor to point at the same <key,value>.
    //Remenber: rehash when load_factor > 0.5
    //Remenber: we use a 2 factor to grown the current size.
    //Remenber: a new hash function will be picked at from the Universal Family.
    //Hint: use the assign operator = to switch the new table with "this".

    //
    assert(load_factor()<=0.5);
    assert(is_valid() && get_key()==old_curr_key);
}

template<class K, class V, class KeyToInt, class Hash>
void
HashTable<K, V, KeyToInt, Hash>::goto_begin()
{
    //TODO:
    //Remeber: move cursor to the first (from position 0) valid entry
    //         if there is.

    //
}

template<class K, class V, class KeyToInt, class Hash>
void
HashTable<K, V, KeyToInt, Hash>::goto_next()
{
    assert(is_valid());
    //TODO:
    //Remeber: move cursor to the next valid position if there is.

    //
}
