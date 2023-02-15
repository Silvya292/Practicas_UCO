/**
 * @file trie_node.hpp
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
#include <map>


/**
 * @brief Models a node of a Trie.
 *
 * The path from the root node to this node represents a prefix and
 * the this node represents a key equal to this prefix and all the following
 * possible next prefixs where a new symbol was added.
 *
 * For example: if we have the keys '123', '1231', '1232, '1233' a node
 * will represent the key '123' and the prefix '123' with three child nodes
 * for symbols '1', '2' and '3' respectively.
 *
 */
class TrieNode
{
public:
    /** @brief a reference to a trie node.*/
    typedef std::shared_ptr<TrieNode> Ref;

    /** @name Life cicle.*/
    /** @{*/

    /**
     * @brief Constructor.
     * @param is_key is true when the node represents a key.
     * @post is_key() == is_key_state
     * @post !current_exisits()
     */
    TrieNode (bool is_key_state=false);

    /**
     * @brief Create a TrieNode.
     * @return a shared reference to the node created.
     * @post ret_val->is_key() == is_key_state
     */
    static Ref create(bool is_key_state=false);

    /**
     * @brief Create a TrieNode unfolding from an input stream.
     * @see fold() for the expected input format.
     * @param in is the input stream.
     * @return a shared reference to the node created.
     * @throw std::runtime_error("Worng input format") when wrong input format
     *        is detected.
     */
    static Ref create(std::istream& in) noexcept(false);

    /**
      * Destroy a Trie.
      */
    ~TrieNode ();
    /** @}*/

    /** @name Observers. */
    /** @{*/

    /**
     * @brief Does the node represent a key value?
     * @return true if this node represents a key value.
     */
    bool is_key() const;

    /**
     * @brief Has it the node a child for the symbol k?
     */
    bool has(char k) const;

    /**
     * @brief The child for the symbol k?
     * @return a reference to the node.
     * @pre has(k)
     */
    Ref child(char k) const;

    /**
     * @brief Does current exist?
     * @return true if current is valid.
     */
    bool current_exists() const;

    /**
     * @brief Get the current child node.
     * @return a reference to the current child node.
     * @pre current_exist()
     */
    Ref current_node() const;

    /**
     * @brief Get the current child next symbol.
     * @return the current next symbol.
     * @pre current_exist()
     */
    char current_symbol() const;

    /**
     * @brief Fold the node and childs.
     * Format:
     * node: '[' <is_key_state> {<symbol> <node>}* ']'
     * Where:
     * <is_key_state>: 'T'|'F'
     * <symbol>: ASCII code of the symbol coded as a hexadecimal unsigned
     *           int value.
     * @param out is the output stream.
     * @return the modified stream.
     */
    std::ostream& fold(std::ostream& out) const ;

    /** @} */

    /** @name Modifiers. */
    /** @{*/

    /**
     * @brief Mark this node as a node representing (or not) a key.     
     * @post is_key() == new_state
     */
    void set_is_key_state(bool new_state);

    /**
     * @brief Set a child node for a given symbol.
     * If none previuos child was associated with the given symbol, a new child
     *    is create.
     * if a previous child existed for the given symbol, the child node is updated.
     * @arg[in] s is the symbol.
     * @arg[in] node is the new child node.
     * @pre node != nullptr
     * @post current_symbol()==s
     * @post current_node()==node
     */
    void set_child(char s, Ref node);

    /**
     * @brief Move current to first child.     
     */
    void goto_first_child();

    /**
     * @brief Move current to the next child.
     * @pre current_exist()
     */
    void goto_next_child();

    /**
     * @brief Move current to the child associated with a symbol.
     * @return true if a child was found.
     * @post ret_val || !current_exists()
     * @post !ret_val || current_symbol()==s
     */
    bool find_child(char s);

    /** @}*/

protected:

    //TODO:
    //Hint: use std::map to implement the dictionary for next symbols.
    bool isKey_;
    std::map<char,Ref> dict_;
    Ref curr_;
    //
};


