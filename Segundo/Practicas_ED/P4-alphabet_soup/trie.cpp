/**
 * @file trie.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include <cassert>
#include "trie.hpp"

Trie::Trie()
{
    //TODO:
    root_=nullptr;
    prefix_="";
    //
    assert(is_empty());
}

Trie::Ref Trie::create()
{    
    return std::make_shared<Trie>();
}

Trie::Trie(TrieNode::Ref root_node, std::string const& pref)
{
    //TODO:
    root_=root_node;
    prefix_=pref;
    //
    assert(prefix() == pref);
}

Trie::Ref Trie::create(TrieNode::Ref root_node, std::string const& prefix)
{
    //We cannot use std::make_shared here
    //because the constructor is protected.
    typename Trie::Ref trie ( new Trie(root_node, prefix));
    return trie;
}

Trie::Ref Trie::create(std::istream& in) noexcept(false)
{
    Trie::Ref trie = nullptr;
    //TODO:
    std::string token;
    in >> token;
    if(token!="["){
        throw std::runtime_error("Wrong input format");
    }
    else{
        auto i=TrieNode::create(in);
        trie=Trie::create(i,"");
        in >> token;
    }
    //
    return trie;
}

bool
Trie::is_empty() const
{
    bool ret_v=true;
    //TODO:
    if(root_!=nullptr){
        ret_v=false;
    }
    //
    return ret_v;
}

std::string
Trie::prefix() const
{
    std::string ret_val = "";
    //TODO:
    ret_val=prefix_;
    //
    return ret_val;
}

bool
Trie::is_key() const
{
    assert(!is_empty());
    bool ret_val = true;
    //TODO:
    ret_val=root_->is_key();
    //
    return ret_val;
}


TrieNode::Ref
Trie::root() const
{
    TrieNode::Ref node = nullptr;
    //TODO:
    node=root_;
    //
    return node;
}

bool
Trie::has(std::string const& k) const
{
    assert(!is_empty());
    bool found = false;
    //TODO:
    //Hint: use find_node() to do this.
    //Remember: The Trie can have a prefix==k but does not store the key k.    
    auto auxNode=find_node(k);
    if(auxNode!=nullptr && auxNode->is_key()){
        found=true;
    }
    //
    return found;
}

static void
preorder_traversal(TrieNode::Ref node, std::string prefix,
                   std::vector<std::string> & keys)
{
    //TODO:
    //Remeber: node->is_key() means the prefix is a key too.
    if(node->is_key()){
        keys.push_back(prefix);
    }
    node->goto_first_child();
    while(node->current_exists()){
        preorder_traversal(node->current_node(),prefix+node->current_symbol(),keys);
        node->goto_next_child();
    }
    //
}


void
Trie::retrieve(std::vector<std::string>& keys) const
{
    assert(!is_empty());
    //TODO:
    //Remenber add the subtrie's prefix to the retrieve keys.
    preorder_traversal(root_,prefix(),keys);
    //
}

Trie::Ref
Trie::child(std::string const& pref) const
{
    assert(!is_empty());
    Trie::Ref ret_v = Trie::create();
    //TODO:
    //Hint: use find_node() to do this.
    auto aux=root_;
    for(auto aux2:pref){
        if(!aux->find_child(aux2)){
            return ret_v;
        }
        aux=aux->child(aux2);
    }
    ret_v->root_=aux;
    ret_v->prefix_=prefix_+pref;
    //
    assert(ret_v != nullptr);
    return ret_v;
}

bool
Trie::current_exists() const
{
    assert(!is_empty());
    bool ret_val = false;
    //TODO:
    ret_val=root_->current_exists();
    //
    return ret_val;
}

Trie::Ref
Trie::current() const
{
    assert(current_exists());
    Trie::Ref trie = nullptr;
    //TODO:
    trie=create(root_->current_node(), prefix_+current_symbol());
    //
    return trie;
}

char
Trie::current_symbol() const
{
    assert(current_exists());
    char symbol = 0;
    //TODO:
    if(root_->current_exists()){
        return root_->current_symbol();
    }
    else{
        return '\0';
    }
    //
    return symbol;
}

void
Trie::insert(std::string const& k)
{
    assert(k != "");
    //TODO:
    if(root_==nullptr){
        root_=TrieNode::create(false);
    }
    auto auxNode=root_;
    for(size_t i=0;i<k.size();i++){
        if(auxNode->has(k[i])){
            auxNode=auxNode->child(k[i]);
        }
        else{
            auto newNode=TrieNode::create(false);
            auxNode->set_child(k[i],newNode);
            auxNode=newNode;    
        }
    }
    auxNode->set_is_key_state(true);
    //
    assert(!is_empty());
    assert(has(k));
}

TrieNode::Ref
Trie::find_node(std::string const& pref) const
{
    assert(!is_empty());
    TrieNode::Ref node;
    //TODO:
    //Remenber: the prefix "" must return the trie's root node.
    node=root_;
    size_t i=0;
    while(i<pref.size() && node!=nullptr){
        if(node->has(pref[i])){
            node=node->child(pref[i]);
            i=i+1;
        }
        else{
            node=nullptr;
        }
    }
    //
    return node;
}

std::ostream&
Trie::fold(std::ostream& out) const
{
    //TODO:
    out << "[ ";
    if(root_!=nullptr){
        root_->fold(out);
    }
    out << " ]";
    //
    return out;
}

bool
Trie::find_symbol(char symbol)
{
    assert(!is_empty());
    bool found = false;
    //TODO:
    found=root_->find_child(symbol);
    //
    assert(!found || current_exists());
    assert(found || !current_exists());
    assert(!current_exists() || current_symbol()==symbol);
    return found;
}

void
Trie::goto_first_symbol()
{
    assert(!is_empty());
    //TODO:
    root_->goto_first_child();
    //
    assert(!current_exists() ||
           current()->prefix()==prefix()+current_symbol());
}

void
Trie::goto_next_symbol()
{
    assert(current_exists());
    //TODO:
    root_->goto_next_child();
    //
}
