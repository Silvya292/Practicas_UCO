
#pragma once

#include <cassert>
#include <exception>
#include <memory>
#include <iostream>
#include <queue>

#include "btree_utils.hpp"

template<class T>
int compute_height (typename BTree<T>::Ref t)
{
    assert(t != nullptr);
    int height = 0;
    //TODO:
    height=-1;
    if(!t->is_empty()){
        int LHeight=compute_height<T>(t->left())+1;
        int RHeight=compute_height<T>(t->right())+1;
        if(LHeight>=RHeight){
            height=LHeight;
        }
        else{
            height=RHeight;
        }
    }
    //
    return height;
}

template<class T>
size_t compute_size (typename BTree<T>::Ref t)
{
    assert(t != nullptr);
    size_t ret_val = 0;
    //TODO:
    if(!t->is_empty()){
        ret_val=1+compute_size<T>(t->left())+compute_size<T>(t->right());
    }
    //
    return ret_val;
}

template <class T, typename Processor>
bool
prefix_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool retVal = true;
    //TODO:
    if(!tree->is_empty()){
        retVal=p(tree->item());
        retVal=retVal && prefix_process<T, Processor>(tree->left(),p);
        retVal=retVal && prefix_process<T, Processor>(tree->right(),p);
    }
    //
    return retVal;
}

template <class T, class Processor>
bool
infix_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool retVal = true;
    //TODO:
    if(!tree->is_empty()){
        retVal=infix_process<T, Processor>(tree->left(),p);
        retVal=retVal && p(tree->item());
        retVal=retVal && infix_process<T, Processor>(tree->right(),p);
    }
    //
    return retVal;
}

template <class T, class Processor>
bool
postfix_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool retVal = true;
    //TODO:
    if(!tree->is_empty()){
        retVal=postfix_process<T, Processor>(tree->left(),p);
        retVal=retVal && postfix_process<T, Processor>(tree->right(),p);
        retVal=retVal && p(tree->item());
    }
    //
    return retVal;
}


template <class T, class Processor>
bool
breadth_first_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool go_on = true;
    //TODO:
    std::queue<typename BTree<T>::Ref> q;
    typename BTree<T>::Ref subtree;
    q.push(tree);
    while(!q.empty() && go_on){
        subtree=q.front();
        if(!subtree->is_empty()){
            go_on=p(subtree->item());
            q.push(subtree->left());
            q.push(subtree->right());
        }
        q.pop();
    }
    //
    return go_on;
}

template <class T>
std::ostream&
print_prefix(std::ostream& out, typename BTree<T>::Ref tree)
{
    //TODO:
    //You must create a lambda function with a parameter to be printed and
    //  use a prefix_process to process the tree with this lambda.
    //Remenber: the lambda must return true.
    auto f=[&out](T n) mutable->bool{
        out<<n<<" ";
        return true;
    };
    prefix_process<T>(tree,f);
    //
    return out;
}

template <class T>
std::ostream&
print_infix(std::ostream& out, typename BTree<T>::Ref tree)
{
    //TODO:
    //You must create a lambda function with a parameter to be printed and
    //  use a infix_process to process the tree with this lambda.
    //Remenber: the lambda must return true.
    auto f=[&out](T n) mutable->bool{
        out<<n<<" ";
        return true;
    };
    infix_process<T>(tree,f);
    //
    return out;
}

template <class T>
std::ostream&
print_postfix(std::ostream& out, typename BTree<T>::Ref tree)
{
    //TODO:
    //You must create a lambda function with a parameter to be printed and
    //  use a postfix_process to process the tree with this lambda.
    //Remenber: the lambda must return true.
    auto f=[&out](T n) mutable->bool{
        out<<n<<" ";
        return true;
    };
    postfix_process<T>(tree,f);
    //
    return out;
}

template <class T>
std::ostream&
print_breadth_first(std::ostream& out, typename BTree<T>::Ref tree)
{
    //TODO:
    //You must create a lambda function with a parameter to be printed and
    //  use a breadth_first_process to process the tree with this lambda.
    //Remenber: the lambda must return true.
    auto f=[&out](T n) mutable->bool{
        out<<n<<" ";
        return true;
    };
    breadth_first_process<T>(tree,f);
    //
    return out;
}

template <class T>
bool search_prefix(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //TODO:
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with in the prefix_process.
    //Remenber: Also, the lambda must update the count variable and
    //must return True/False.
    auto f=[&found, it, &count](T item) mutable->bool{
        ++count;
        if(it==item){
            found=true;
        }
        return it!=item;
    };
    prefix_process<T>(tree,f);
    //
    return found;
}

template <class T>
bool search_infix(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //TODO::
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with in the infix_process.
    //Remenber: Also, the lambda must update the count variable and
    //must return True/False.
    auto f=[&found, it, &count](T item) mutable->bool{
        ++count;
        if(it==item){
            found=true;
        }
        return it!=item;
    };
    infix_process<T>(tree,f);
    //
    return found;
}

template <class T>
bool search_postfix(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //TODO:
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with in the postfix_process.
    //Remenber: Also, the lambda must update the count variable and
    //must return True/False.
    auto f=[&found, it, &count](T item) mutable->bool{
        ++count;
        if(it==item){
            found=true;
        }
        return it!=item;
    };
    postfix_process<T>(tree,f);
    //
    return found;
}

template <class T>
bool search_breadth_first(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //TODO:
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with in the breadth_first_process.
    //Remenber: Also, the lambda must update the count variable and
    //must return True/False.
    auto f=[&found, it, &count](T item) mutable->bool{
        ++count;
        if(it==item){
            found=true;
        }
        return it!=item;
    };
    breadth_first_process<T>(tree,f);
    //
    return found;
}


template<class T>
bool check_btree_in_order(typename BTree<T>::Ref const& tree)
{
    bool ret_val = true;
    //TODO:
    if(!tree->is_empty()){
        if(!tree->left()->is_empty()){
            auto maxLeft=tree->left();
            while(!maxLeft->right()->is_empty()){
                maxLeft=maxLeft->right();
            }
            if(maxLeft->item()>=tree->item()){
                ret_val=false;
            }
        }
        if(!tree->right()->is_empty()){
            auto minRight=tree->right();
            while(!minRight->left()->is_empty()){
                minRight=minRight->left();
            }
            if(minRight->item()<=tree->item()){
                ret_val=false;
            }
        }
        if(!check_btree_in_order<T>(tree->left()) || !check_btree_in_order<T>(tree->right())){
            ret_val=false;
        }
    }
    //
    return ret_val;
}

template<class T>
bool has_in_order(typename BTree<T>::Ref tree, T const& v)
{
    assert(check_btree_in_order<T>(tree));    
    bool ret_val = false;
    //TODO:
    if(!tree->is_empty()){
        if(v<tree->item()){
            ret_val=has_in_order(tree->left(),v);
        }
        else if(v>tree->item()){
            ret_val=has_in_order(tree->right(),v);
        }
        else{
            ret_val=true;
        }
    }
    //
    return ret_val;
}

template <class T>
void insert_in_order(typename BTree<T>::Ref tree, T const& v)
{
    assert(check_btree_in_order<T>(tree));
    //TODO:
    if(tree->is_empty()){
        tree->create_root(v);
    }
    else if(v<tree->item()){
        if(tree->left()->is_empty()){
            tree->set_left(BTree<T>::create(v));
        }
        else{
            insert_in_order(tree->left(),v);
        }
    }
    else if(v>tree->item()){
        if(tree->right()->is_empty()){
            tree->set_right(BTree<T>::create(v));
        }
        else{
            insert_in_order(tree->right(),v);
        }
    }
    //
    assert(has_in_order<T>(tree, v));
}
