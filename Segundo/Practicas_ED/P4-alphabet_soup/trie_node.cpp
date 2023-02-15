/**
 * @file trie_node.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include <cassert>
#include <sstream>
#include <cstdint>

#include "trie_node.hpp"

TrieNode::TrieNode (bool is_key_state)
{
    //TODO:
    isKey_=is_key_state;
    curr_=nullptr;
    //
    assert(is_key()==is_key_state);
    assert(!current_exists());
};

TrieNode::Ref TrieNode::create(bool is_key_state)
{
    return std::make_shared<TrieNode>(is_key_state);
}

TrieNode::~TrieNode()
{}

bool TrieNode::is_key() const
{
    bool ret_val = true;
    //TODO:
    ret_val=isKey_;
    //
    return ret_val;
}

bool
TrieNode::has(char k) const
{
    bool ret_v = false;
    //TODO:
    if(dict_.find(k)!=dict_.end()){
        ret_v=true;
    }
    //
    return ret_v;
}

TrieNode::Ref
TrieNode::child(char k) const
{
    assert(has(k));
    TrieNode::Ref node = nullptr;
    //TODO:
    auto auxChild=dict_;
    node=auxChild[k];
    //
    return node;
}

bool
TrieNode::current_exists() const
{
    bool ret_val = true;
    //TODO:
    if(curr_==nullptr){
        ret_val=false;
    }
    else{
        bool found;
        for(auto i=dict_.begin();i!=dict_.end();i++){
            if(i->second==curr_){
                found=true;
                break;
            }
        }
        ret_val=found;
    }
    //
    return ret_val;
}

TrieNode::Ref
TrieNode::current_node() const
{
    assert(current_exists());
    TrieNode::Ref node = nullptr;
    //TODO:
    node=curr_;
    //
    return node;
}

char
TrieNode::current_symbol() const
{
    assert(current_exists());
    char symbol = 0;
    //TODO:
    for(auto i=dict_.begin();i!=dict_.end();i++){
            if(i->second==curr_){
                symbol=i->first;
                break;
            }
        }
    //
    return symbol;
}

void
TrieNode::set_is_key_state(bool new_state)
{
    //TODO:
    isKey_=new_state;
    //
    assert(is_key()==new_state);
}

bool
TrieNode::find_child(char s)
{
    bool found = false;
    //TODO:
    auto i=dict_.find(s);
    if(i!=dict_.end()){
        curr_=i->second;
        found=true;
    }
    else{
        curr_=nullptr;
    }
    //
    assert(found || !current_exists());
    assert(!found || current_symbol()==s);
    return found;
}

void
TrieNode::goto_first_child()
{
    //TODO:
    curr_=dict_.begin()->second;
    //
}

void
TrieNode::goto_next_child()
{
    assert(current_exists());
    //TODO:
    for(auto i=dict_.begin();i!=dict_.end();i++){
        if(i->second==curr_){
            i++;
            if(i==dict_.end()){
                curr_=nullptr;
            }
            else{
                curr_=i->second;
            }
            break;
        }
    }
    //
}

void
TrieNode::set_child(char k, Ref node)
{
    assert(node != nullptr);
    //TODO:
    dict_[k]=node;
    curr_=node;
    //
    assert(current_symbol()==k);
    assert(current_node()==node);
}

std::ostream&
TrieNode::fold(std::ostream& out) const
{
    //TODO:
    //Hint: review c++ input/output manipulators at
    //      https://en.cppreference.com/w/cpp/io/manip
    out << "[ ";
    if(is_key()){
        out << "T";
    }
    else{
        out << "F";
    }

    for(auto i=dict_.begin();i!=dict_.end();i++){
        out << " " << std::hex << (uint16_t)i->first << " ";
        i->second->fold(out);
    }
    out << " ]";
    //
    return out;
}

TrieNode::Ref TrieNode::create(std::istream& in) noexcept(false)
{
    TrieNode::Ref node = nullptr;
    //TODO:
    std::string token;
    in >> token;
    if(token!="["){
        throw std::runtime_error("Wrong input format");
    }
    in >> token;
    if(token=="T"){
        node=TrieNode::create(true);
    }
    else if(token=="F"){
        node=TrieNode::create(false);
    }
    else{
        throw std::runtime_error("Wrong input format");
    }

    while(in >> token && token!="]"){
        node->set_child(char(std::stoi(token, nullptr, 16)), TrieNode::create(in));
    }

    if(token!="]"){
        throw std::runtime_error("Wrong input format");
    }
    //
    return node;
}
