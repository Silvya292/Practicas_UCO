#pragma once
#include <cassert>
#include "stack.hpp"


template<class T>
Stack<T>::Stack ()
{
    //TODO:
    l_=SList<T>::create();
    //
    assert(is_empty());
}

template<class T>
typename Stack<T>::Ref Stack<T>::create()
{
    return std::make_shared<Stack<T>>();
}

template<class T>
typename Stack<T>::Ref Stack<T>::create(std::istream & in) noexcept(false)
{
    auto stack = Stack<T>::create();
    //TODO:
    //Hint: unfold the list used as implementation.
    stack=SList<T>::create(in);
    //
    return stack;
}

template<class T>
bool Stack<T>::is_empty () const
{
    bool ret_val = true;
    //TODO:
    if(l_->is_empty()==false){
        ret_val=false;
    }
    //
    return ret_val;
}

template<class T>
size_t Stack<T>::size () const
{
    size_t ret_val = 0;
    //TODO:
    ret_val=l_->size();
    //
    return ret_val;
}

template<class T>
T Stack<T>::top() const
{
    assert(! is_empty());
    T it;
    //TODO:
    it=l_->front();
    //
    return it;
}

template<class T>
void Stack<T>::fold(std::ostream& out) const
{
    //TODO:
    //Hint: fold the list used as implementation.
    l_->fold(out);
    //
}
template<class T>
void Stack<T>::push(const T& new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    //TODO:
    l_->push_front(new_it);
    //
    assert(top()==new_it);
    assert(size()==(old_size+1));
}

template<class T>
void Stack<T>::pop()
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    assert(! is_empty());
    //TODO:
    l_->pop_front();
    //
    assert(size()==(old_size-1));
}
