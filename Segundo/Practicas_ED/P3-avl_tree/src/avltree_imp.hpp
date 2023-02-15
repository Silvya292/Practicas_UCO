#pragma once
#include <cassert>

#include "avltree.hpp"

/****
 * AVLTNode class implementation.
 ****/


template <class T>
AVLTNode<T>::AVLTNode (T const& it, AVLTNode<T>::Ref parent,
                       AVLTNode<T>::Ref left, AVLTNode<T>::Ref right)
{
    //TODO:
    item_=it;
    parent_=parent;
    left_=left;
    right_=right;
    compute_height();
    //
    assert(check_height_invariant());
}

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::create(T const& it,
                                              AVLTNode<T>::Ref parent,
                                              AVLTNode<T>::Ref left,
                                              AVLTNode<T>::Ref right)
{
    return std::make_shared< AVLTNode<T> > (it, parent, left, right);
}

template <class T>
T AVLTNode<T>::item() const
{
    T value;
    //TODO:
    value=item_;
    //
    return value;
}

template <class T>
int AVLTNode<T>::height() const
{
    int height=0;
    //TODO:
    (this == nullptr ) ? height=-1 : height=height_;
    //
    return height;
}

template <class T>
int AVLTNode<T>::balance_factor() const
{
    int bf = 0;
    //TODO:
    bf=(right_->height()-(left_->height()));
    //
    return bf;
}

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::parent() const
{
    AVLTNode<T>::Ref node;
    //TODO:
    node=parent_;
    //
    return node;
}

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::left() const
{
    AVLTNode<T>::Ref node;
    //TODO:
    node=left_;
    //
    return node;
}

template <class T>
typename AVLTNode<T>::Ref AVLTNode<T>::right() const
{
    AVLTNode<T>::Ref node;
    //TODO:
    node=right_;
    //
    return node;
}

template <class T>
bool AVLTNode<T>::check_height_invariant () const
{
    bool ret_val = false;
    //TODO:
    int LHeight,RHeight,max;

    LHeight=left_->height();
    RHeight=right_->height();
    
    (RHeight > LHeight) ? max=RHeight : max=LHeight;
    ret_val=( height_ == max+1 );
    //
    return ret_val;
}

template <class T>
void AVLTNode<T>::set_item(const T& new_it)
{
    //TODO:
    item_=new_it;
    //
    assert(item()==new_it);
}

template <class T>
void AVLTNode<T>::set_parent(AVLTNode<T>::Ref new_parent)
{
    //TODO:
    parent_=new_parent;
    //
    assert(parent()==new_parent);
}


template <class T>
void AVLTNode<T>::set_left(AVLTNode<T>::Ref new_child)
{
    //TODO:
    //Remember to update the height property.
    left_=new_child;
    compute_height();
    //
    assert(check_height_invariant());
    assert(left()==new_child);
}

template <class T>
void AVLTNode<T>::set_right(AVLTNode<T>::Ref new_child)
{
    //TODO:
    //Remember to update the height property.
    right_=new_child;
    compute_height();
    //
    assert(check_height_invariant());
    assert(right()==new_child);
}

template <class T>
void AVLTNode<T>::compute_height()
{
    //TODO:
    //Remember: we want O(1) here.
    int LHeight,RHeight,max;
    if(left_!=nullptr){
        left_->compute_height();
    }
    if(right_!=nullptr){
        right_->compute_height();
    }
    LHeight=left_->height();
    RHeight=right_->height();
    (RHeight > LHeight) ? max=RHeight : max=LHeight;
    height_ = max+1;
    //
    assert(check_height_invariant());
}

/***
 * AVLTree class implementation.
 ***/

template <class T>
AVLTree<T>::AVLTree ()
{
    //TODO:
    root_=nullptr;
    parent_=nullptr;
    current_=nullptr;
    //
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
    assert(is_empty());
}

template <class T>
AVLTree<T>::AVLTree (T const& item)
{
    //TODO:
    root_=AVLTNode<T>::create(item);
    //
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
    assert(!is_empty());
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::create ()
{
    return std::make_shared< AVLTree<T> >();
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::create (T const& item)
{
    return std::make_shared<AVLTree<T>> (item);
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::create(std::istream& in) noexcept(false)
{
    auto tree = AVLTree<T>::create();
    std::string token;
    //TODO:
    T data;
    in>>token;
    if(token == "[]"){
        return tree;
    }
    if(token != "["){
        throw std::runtime_error("Wrong input format.");
    }
    
    in>>token;
    std::istringstream my_stream(token);
    my_stream>>data;
    if(my_stream.fail()){
        throw std::runtime_error("Wrong input format.");
    }
    tree= AVLTree<T>::create(data);
    tree->set_left(AVLTree<T>::create(in));
    tree->set_right(AVLTree<T>::create(in));
    in>>token;
    if(token != "]"){
        throw std::runtime_error("Wrong input format.");
    }
    //
    if (! tree->is_a_binary_search_tree())
        throw std::runtime_error("It is not a binary search tree");
    if (! tree->is_a_balanced_tree())
        throw std::runtime_error("It is not an avl bstree");
    return tree;
}

#ifdef __ONLY_BSTREE__
/**
 * @brief Create an perfectly balanced BSTree by inserting the median of
 *        an ordered sub sequence data[begin, end).
 * @param data is the ordered sequence of values.
 * @param begin,
 * @param end specify a [begin, end) indexing interval of array data to use.
 * @pre 0 <= begin <= end <=data.size()
 * @pre begin==end || data[begin]<data[end];
 */
template<class T>
void create_inserting_median(std::vector<T> const& data,
                             size_t begin,
                             size_t end,
                             typename AVLTree<T>::Ref& tree)
{
    assert(begin<=end);
    assert(end<=data.size());
    assert(begin==end || data[begin]<=data[end-1]);

    //TODO:
    //Hint: if (end==begin) none thing must be done (it is an empty sub array)
    // else, insert the median in the tree and (recursively) process
    // the two sub sequences [begin, median_idx) and [median_idx+1, end)
    int dif=end-begin;
    if( dif > 0 ){
        tree->insert(data[begin+((dif)/2)]);
        create_inserting_median(data,begin,begin+((dif)/2),tree);
        create_inserting_median(data,(begin+((dif)/2))+1,end,tree);
    }
    //
}

template<class T>
typename AVLTree<T>::Ref
create_perfectly_balanced_bstree(std::vector<T> & data)
{
    typename AVLTree<T>::Ref tree = AVLTree<T>::create();
    //TODO:
    //Remember: the empty tree is perfectly balanced.
    //Remember: first, an ordered sequence (using < order) of values is needed.
    //Then you should use the above create_inserting_median function
    //on a empty tree to recursively create the perfectly balanced bstree.
    std::sort(data.begin(),data.end());
    create_inserting_median(data,0,data.size(),tree);
    //
    assert(tree != nullptr);
    return tree;    
}
#endif //__ONLY_BSTREE__

template <class T>
bool AVLTree<T>::is_empty () const
{
    bool empty = false;
    //TODO:
    empty=(root_ == nullptr);
    //
    return empty;
}

template <class T>
T AVLTree<T>::item() const
{
    assert(!is_empty());
    T value;
    //TODO:
    value=root_->item();
    //
    return value;
}

template <class T>
std::ostream& AVLTree<T>::fold(std::ostream& out) const
{
    //TODO:
    if(is_empty()){
        out<<"[]";
        return out;
    }
    out<<"["<<" ";
    out<<root_->item();
    out<<" ";
    left()->fold(out);
    out<<" ";
    right()->fold(out);
    out<<" "<<"]";
    //
    return out;
}

template <class T>
bool AVLTree<T>::current_exists() const
{
    bool exists = false;
    //TODO:
    if(current_==nullptr){
        return false;
    }
    auto auxNode=root_;
    while(auxNode!=nullptr){
        if(current_->item()==auxNode->item()){
            return true;
        }
        (current_->item()>auxNode->item()) ? auxNode=auxNode->right() : auxNode=auxNode->left();
    }
    //
    return exists;
}

template <class T>
T AVLTree<T>::current() const
{
    assert(current_exists());
    T value;
    //TODO:
    value=current_->item();
    //
    return value;
}

template <class T>
int AVLTree<T>::current_level() const
{
    assert(current_exists());
    int level = 0;
    //TODO:
    auto auxNode=root_;
    while(auxNode!=current_){
        (auxNode->item()>current_->item()) ? auxNode=auxNode->left() : auxNode=auxNode->right();
        level++;
    }
    //
    return level;
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::left() const
{
    assert(!is_empty());
    typename AVLTree<T>::Ref subtree;
    //TODO:
    subtree=AVLTree<T>::create(root_->left());
    //
    return subtree;
}

template <class T>
typename AVLTree<T>::Ref AVLTree<T>::right() const
{
    assert(!is_empty());
    typename AVLTree<T>::Ref subtree;
    //TODO:
    subtree=AVLTree<T>::create(root_->right());
    //
    return subtree;
}

template <class T>
int AVLTree<T>::size() const
{
    int s = 0;
    //TODO:
    if(is_empty()==false){
        s=1+right()->size()+left()->size();
    }
    //
    return s;
}

template <class T>
int AVLTree<T>::height() const
{
    int h = 0;
    //TODO:
    //Remenber: we want O(1) here.
    h=root_->height();
    //
    return h;
}

template <class T>
int AVLTree<T>::balance_factor() const
{
#ifdef __ONLY_BSTREE__
    return 0;
#else
    int bf = 0;
    //TODO:
    bf=root_->balance_factor();
    //
    return bf;
#endif
}

template <class T>
bool AVLTree<T>::has(const T& k) const
{
#ifndef NDEBUG
  bool old_current_exists = current_exists();
  T old_current;
  if (old_current_exists)
      old_current = current();
#endif

  bool found = true;

  //TODO:
  //Hint: you can reuse the search method for this but in this case you will
  //      need to use "const_cast" to remove constness of "this" and
  //      save/restore the old state of current before returning.
    auto auxNode=root_;
    found=false;
    if(!is_empty()){
        while(auxNode!=nullptr && found==false ){
            if(auxNode->item()==k){
                found=true;
            }
            else if(auxNode->item()>k){
                auxNode=auxNode->left();
            }
            else if (auxNode->item()<k){
                auxNode=auxNode->right();
            }
        }
    }
  //

#ifndef NDEBUG
  assert (!old_current_exists || old_current == current());
#endif
  return found;
}

/**
 * @brief infix process of a node.
 * The Processor must allow to be used as a function with a parameter  (the
 * item to be processed) and returning true if the process must continue or
 * false if not.
 * @param node is the node to be processed.
 * @param p is the Processor.
 * @return true if all the tree was in-fix processed.
 */
template <class T, class Processor>
bool
infix_process(typename AVLTNode<T>::Ref node, Processor& p)
{
    bool retVal = true;
    //TODO:
    //Remember: if node is nullptr return true.
    if(node!=nullptr){
        retVal=retVal && infix_process<T, Processor>(node->left(),p);
        retVal=retVal && p(node->item());
        retVal=retVal && infix_process<T, Processor>(node->right(),p);
    }
    //
    return retVal;
}

template <class T>
bool AVLTree<T>::is_a_binary_search_tree() const
{
    bool is_bst = true;
    //TODO:
    //Remenber: a empty tree is a binary searh tree.
    //
    //Remenber: for a non empty binary search tree, the in-fix traversal from
    //the root node must follow an ordered sequence of items.
    //
    //Remember: use a lambda function with signature '(T v) -> bool' to
    // implement the Processor.
    //
    if(!is_empty()){
        std::vector<T> v;
        auto p=[&v](T const &it)
        {
            v.push_back(it);
            return std::is_sorted(v.begin(),v.end());
        };
        is_bst=infix_process<T>(root_,p);
    }
    //
    return is_bst;
}

template <class T>
bool AVLTree<T>::is_a_balanced_tree() const
{
#ifdef __ONLY_BSTREE__
    return true;
#else
    bool is_balanced = true;
    //TODO:
    //Remenber: a empty tree is balanced.
    //
    //Remenber: A non empty tree is balanced if both children are balanced
    //and the absolute value of the balance factor of the tree is less or
    //equal to one.
    if(is_empty()==false){
        is_balanced=(std::abs(balance_factor())<=1 
        && left()->is_a_balanced_tree() 
        && right()->is_a_balanced_tree());
    }
    //
    return is_balanced;
#endif
}

template <class T>
void AVLTree<T>::create_root(T const& v)
{
    assert(is_empty());
    //TODO:
    root_=AVLTNode<T>::create(v);
    root_->compute_height();
    //
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());
    assert(!is_empty());
    assert(item()==v);

}

template <class T>
bool AVLTree<T>::search(T const& k)
{
    bool found = false;
    //TODO:
    current_=root_;
    while(current_exists()){
        if(current()==k){
            return true;
        }
        parent_=current_;
        (current()>k) ? current_=current_->left() : current_=current_->right();
    }
    //
    assert(!found || current()==k);
    assert(found || !current_exists());
    return found;
}

template <class T>
void AVLTree<T>::insert(T const& k)
{
    //Check invariants.
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());

    if (!search(k))
    {        
        //TODO:
        if(is_empty()){
            root_=AVLTNode<T>::create(k,nullptr,nullptr,nullptr);
            current_=root_;
        }
        else{
            current_=AVLTNode<T>::create(k,parent_,nullptr,nullptr);
            (parent_->item()>k) ? parent_->set_left(current_) : parent_->set_right(current_);
        }
        //
        make_balanced();
    }

    //Check invariants.
    assert(is_a_binary_search_tree());
    assert(is_a_balanced_tree());

    //check postconditions.
    assert(current_exists());
    assert(current()==k);
}

template <class T>
void AVLTree<T>::remove ()
{
    //check preconditions.
    assert(current_exists());

#ifndef NDEBUG
    //the invariants only must be checked for the first recursive call.
    //We use a static variable to count the recursion levels.
    //see section "Static variables in a Function" in
    //ref https://www.geeksforgeeks.org/static-keyword-cpp/ for more info.
    static int recursion_count = 0;
    recursion_count++;
    if (recursion_count==1)
    {
        //Check invariants.
        assert(is_a_binary_search_tree());
        assert(is_a_balanced_tree());
    }
#endif //NDEBUG

    bool replace_with_subtree = true;
    typename AVLTNode<T>::Ref subtree;

    //TODO:
    // Check which of cases 0,1,2,3 we have (see theorical class slides).
    if(current_->right()==nullptr&&current_->left()==nullptr){
        subtree=nullptr;
    }
    else if(current_->left()==nullptr){
        subtree=current_->right();
    }
    else if(current_->right()==nullptr){
        subtree=current_->left();
    }
    else{
        replace_with_subtree=false;
    }
    //

    if (replace_with_subtree)
    {   
        //TODO:
        //Manage cases 0,1,2
        if(parent_==nullptr){
            root_=subtree;
        }
        else if(parent_->right()==current_){
            parent_->set_right(subtree);
        }
        else{
            parent_->set_left(subtree);
        }
        current_=nullptr;
        //
        make_balanced();
    }
    else
    {
        //TODO:
        //Manage case 3.
        auto c=current_;
        find_inorder_sucessor();
        c->set_item(current_->item());
        remove();
        //
    }

#ifndef NDEBUG
    //We come back so the recursion count must be decreased.
    recursion_count--;
    assert(recursion_count>=0);
    if (recursion_count==0)
    {
        //Only check for the last return.
        //Check invariants.
        assert(is_a_binary_search_tree());
        assert(is_a_balanced_tree());

        //Check postconditions.
        assert(! current_exists());
    }
#endif
}

template <class T>
AVLTree<T>::AVLTree (typename AVLTNode<T>::Ref root_node)
{
    //TODO:
    root_=root_node;
    //
    assert(!current_exists());
}

template <class T>
typename AVLTree<T>::Ref  AVLTree<T>::create (typename AVLTNode<T>::Ref root)
{
    AVLTree<T>::Ref ret_v (new AVLTree<T>(root));
    return ret_v;
}

template <class T>
void AVLTree<T>::set_left(Ref subtree)
{
    assert(!is_empty());
    //TODO:
    //Remenber to set parent's link of the subtree root to this.
    if (!subtree->is_empty()){
        auto newtree = AVLTNode<T>::create(subtree->root_->item(), root_, subtree->root_->left(), subtree->root_->right());
        root_->set_left(newtree);
    }
    else{
        root_->set_left(nullptr);
    }
    //
    assert(subtree->is_empty() || left()->item()==subtree->item());
    assert(!subtree->is_empty() || left()->is_empty());
}

template <class T>
void AVLTree<T>::set_right(Ref subtree)
{
    assert(!is_empty());
    //TODO:
    //Remenber to set parent's link of the subtree root to this.
    if (!subtree->is_empty()){
        auto newtree = AVLTNode<T>::create(subtree->root_->item(), root_, subtree->root_->left(), subtree->root_->right());
        root_->set_right(newtree);
    }
    else{
        root_->set_right(nullptr);
    }
    //
    assert(subtree->is_empty()|| right()->item()==subtree->item());
    assert(!subtree->is_empty()|| right()->is_empty());
}

template <class T>
typename AVLTNode<T>::Ref AVLTree<T>::current_node() const
{
    typename AVLTNode<T>::Ref node;
    //TODO:
    node=current_;
    //
    return node;
}

template <class T>
typename AVLTNode<T>::Ref AVLTree<T>::root_node() const
{
    typename AVLTNode<T>::Ref node;
    //TODO:
    node=root_;
    //
    return node;
}

template <class T>
typename AVLTNode<T>::Ref AVLTree<T>::parent_node() const
{
    typename AVLTNode<T>::Ref node;
    //TODO:
    node=current_->parent();
    //
    return node;
}

template <class T>
void AVLTree<T>::find_inorder_sucessor()
{
    assert(current_exists());
    assert(is_a_binary_search_tree());

#ifndef NDEBUG
    T old_curr = current();
#endif
    //TODO:
    parent_=current_;
    current_=current_->right();
    while(current_->left()!=nullptr){
        parent_=current_;
        current_=current_->left();
    }
    //
    assert(current_exists() && current_node()->left()==nullptr);
#ifndef NDEBUG
    assert(current()>old_curr);
#endif
}

template <class T>
void AVLTree<T>::rotate_left(typename AVLTNode<T>::Ref node)
{
    assert(node->left()!=nullptr);
    //TODO:
    //Remenber: when set a node A as child of a node B, also is needed set
    // node B as parent of node A.
    //Remenber: update the node height at the end.
    auto leftValue=node->left();
    if(node->parent()==nullptr){
        root_=leftValue;
    }
    else if(node==node->parent()->right()){
        node->parent()->set_right(leftValue);
    }
    else{
        node->parent()->set_left(leftValue);
    }
    leftValue->set_parent(node->parent());
    if(leftValue->right()!=nullptr){
        node->set_left(leftValue->right());
        leftValue->right()->set_parent(node);
    }

    else{
        node->set_left(nullptr);
    }
    leftValue->set_right(node);
    node->set_parent(leftValue);
    node->compute_height();
    leftValue->compute_height();
    //
}

template <class T>
void AVLTree<T>::rotate_right(typename AVLTNode<T>::Ref node)
{
    assert(node->right()!=nullptr);
    //TODO:
    //Remenber: when set a node A as child of a node B, also is needed set
    // node B as parent of node A.
    //Remenber: update the node height at the end.
    auto rightValue = node->right();
    if(node->parent()==nullptr ){
        root_ = rightValue;
    }
    else if(node->parent()->right() == node){
        node->parent()->set_right(rightValue);
    }
    else{
        node->parent()->set_left(rightValue);
    }
    rightValue->set_parent(node->parent());
    if(rightValue->left()!=nullptr){
        node->set_right(rightValue->left());
        rightValue->left()->set_parent(node);
    }
    else{
        node->set_right(nullptr);
    }
    rightValue->set_left(node);
    node->set_parent(rightValue);
    node->compute_height();
    rightValue->compute_height();
    //
}

template <class T>
void AVLTree<T>::make_balanced()
{
#ifdef __ONLY_BSTREE__
    return;
#else
    //TODO:
    //From current position, go up until root's node is achieved.
    //In each step, check if the current subtree is balanced and balance it
    //   if it is not.
    //Remenber: use parent_ to travel to the root and restore it properly at
    //the end.
    //
    int bf;
    int bfChild;
    while(parent_!=nullptr){
        parent_->compute_height();
        bf=parent_->balance_factor();
        if(bf<-1){
            auto child=parent_->left();
            bfChild=child->balance_factor();
            if(bfChild<=0){
                rotate_left(parent_);
            }
            else{
                rotate_right(child);
                rotate_left(parent_);
            }
        }
        else if(bf>1){
            auto child=parent_->right();
            bfChild=child->balance_factor();
            if(bfChild>=0){
                rotate_right(parent_);
            }
            else{
                rotate_left(child);
                rotate_right(parent_);
            }
        }
        else{
            parent_=parent_->parent();
        }
    }
    if(current_exists()){
        parent_=current_->parent();
    }
    //
    assert(!current_exists() || current_node()->parent()==parent_node());
#endif //__ONLY_BSTREE__
}
