/**
 * @file trie.hpp
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
#include <memory>
#include <string>
#include <vector>
#include "trie_node.hpp"


/**
 * @brief Represents a Trie.
 * A Trie is a m-path tree to store keys based on prefixes.
 */
class Trie
{
public:

    /** @brief a reference to a Trie.*/
    typedef std::shared_ptr<Trie> Ref;

    /** @name Life cicle. */
    /** @{*/

    /**
     * @brief Create a empty trie.
     * @post is_empty()
     * @post prefix()=""
     */
    Trie ();

    /**
     * @brief Create a empty trie.
     * @return a shared reference to an empty trie.
     */
    static Ref create();

    /**
     * @brief Create a Trie unfolding from an input stream.
     * @param in is the input stream.
     * @return a shared reference to the tree created.
     * @throw std::runtime_error("Worng input format") when wrong input format
     *        is detected.
     */
    static Ref create(std::istream& in) noexcept(false);

    /** @}*/

    /** @name Observers. */
    /** @{*/

    /**
     * @brief Is the trie empty?
     * @return true if it is empty.
     */
    bool is_empty() const;

    /**
     * @brief Get the prefix of the root node.
     * @return the prefix.     
     */
    std::string prefix() const;

    /**
     * @brief Is the root's prefix a key?
     * @return true if the root's prefix is a stored key too.
     * @pre !is_empty()
     */
    bool is_key() const;

    /**
     * @brief Is the key prefix()+k stored?.
     * @param[i] k the postfix of the key to be found.
     * @return true if the key is stored into the trie.
     * @warning the process must be O(m) with m the length of k postfix.
     * @pre !is_empty()
     */
    bool has(std::string const& k) const;

    /**
     * @brief Retrieve the stored keys.
     * @param[in] keys is the vector where storing the keys.
     * @warning The keys are stored using push_back vector operation.
     * @pre !is_empty()
     */
    void retrieve(std::vector<std::string>& keys) const;

    /**
     * @brief Gets the subtrie for the prefix prefix()+pref
     * @param pref is the prefix of the subtree to be found.
     * @return the subtrie storing the keys with prefix prefix()+pref
     * @pre !is_empty()
     * @post ret_v->is_empty() || ret_v->prefix()==prefix()+pref
     * @post !ret_v->is_empty() || ret_v->prefix()==""
     */
    Trie::Ref child(std::string const& pref) const;

    /**
     * @brief Fold the tree.
     * Output format:
     * [] for empty trie.
     * [ <root node> ]
     * @param out is the output stream
     * @return the output stream
     */
    std::ostream& fold(std::ostream& out) const;

    /**
     * @brief Is current valid?
     * return true is current is valid subtrie.
     * @pre !is_empty()
     */
    bool current_exists() const;

    /**
     * @brief Gets the current subtrie.
     * This subtrie represents the keys with prefix prefix()+current_symbol()
     * @return a reference to the subtrie.
     * @pre current_exists()
     */
    Trie::Ref current() const;

    /**
     * @brief Gets current next symbol.
     * @return the next symbol of the current subtrie.
     * @pre current_exists()
     */
    char current_symbol() const;

    /** @} */

    /** @name Modifiers. */
    /** @{*/

    /**
     * @brief Insert the key prefix()+k into the trie.
     * @param[in] k is the key to be stored.
     * @pre k!=""
     * @post !is_emtpy()
     * @post has(k)
     */
    void insert(std::string const& k);

    /**
     * @brief Move current to the subtree representing the prefix prefix()+symbol
     * @param symbol is the next symbol to be found.
     * @return true if a child was found.
     * @pre !is_empty()
     * @post-c !ret_v || currentExists()
     * @post-c ret_v || !currentExists()
     * @post-c !currentExists() || current()->prefix() == (prefix()+pref)
     */
    bool find_symbol(char symbol);

    /**
     * @brief Move current to the subtree prefix()+’first symbol’
     * @post !currentExists() ||
     *       current()->prefix() ==  (prefix()+current_symbol())
     */
    void goto_first_symbol();

    /**
     * @brief Move current to the next subtree prefix()+’next symbol’
     * @prec current_exists()
     */
    void goto_next_symbol();


    /** @}*/

protected:

    /**
     * @brief Create a subtrie storing keys with prefix pref.
     * @param root_node is the root of the new trie.
     * @param prefix is the prefix represented by this subtrie.
     * @post prefix()==pref
     */
    Trie(TrieNode::Ref root_node, std::string const& pref);

    /**
     * @brief Create a subtrie storing keys with prefix pref.
     * @param root_node is the root of the new trie.
     * @param prefix is the prefix represented by this subtrie.
     * @return a reference to the subtree.
     * @post ret_v->prefix()==pref
     */
    static Ref create(TrieNode::Ref root_node,  std::string const& prefix);

    /**
     * @brief Find the node that represents this prefix.
     * @param[in] P is the prefix to be found.
     * @return a reference to the node or nullptr if that prefix is not stored.
     * @pre !is_empty()
     * @post all the stored keys that match "P*" regular expression are
     * descendants of this node.
     */
    TrieNode::Ref find_node(std::string const& P) const;

    /**
     * @brief Get the root node.
     * The root node represent the empty "" prefix.
     * @return a const reference to the root node.
     */
    TrieNode::Ref root() const;

    //TODO
    TrieNode::Ref root_;
    TrieNode::Ref curr_;
    std::string prefix_;
    //
};

