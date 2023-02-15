/**
 * @file graph_utils_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <string>

#include "wgraph.hpp"

/** GraphNode implementation **/

template<class T>
WNode<T>::WNode(size_t label, T const& v)
{
    //TODO:
    _visited=false;
    _label=label;
    _item=v;
    //
    assert(item()==v);
    assert(!is_visited());
}

template<class T>
T WNode<T>::item() const
{
    T ret_v;
    //TODO:
    ret_v=_item;
    //
    return ret_v;
}

template<class T>
size_t  WNode<T>::label() const
{
    size_t ret_v = 0;
    //TODO:
    ret_v=_label;
    //
    return ret_v;
}

template<class T>
bool  WNode<T>::is_visited() const
{
    bool ret_v = false;
    //TODO:
    if(_visited==true){
        ret_v=true;
    }
    //
    return ret_v;
}

template<class T>
void WNode<T>::set_item(T const& v)
{
    //TODO:
    _item=v;
    //
    assert(item()==v);
}


template<class T>
void WNode<T>::set_visited(bool new_st)
{
    //TODO:
    _visited=new_st;
    //
    assert(new_st || !is_visited());
    assert(!new_st || is_visited());
}

/** GraphEdge implementation **/

template<class T, class E>
WEdge<T,E>::WEdge(NodeRef u, NodeRef v, FMatrix::Ref wmat)
{
    //TODO:
    _u=u;
    _v=v;
    _wmat=wmat;
    //
}

template<class T, class E>
E WEdge<T,E>::weight() const
{
    E ret_val=std::numeric_limits<float>::infinity();
    //TODO:
    ret_val=_wmat->get(_u->label(), _v->label());
    //
    return ret_val;
}

template<class T, class E>
bool WEdge<T,E>::has(NodeRef const& n) const
{
    bool ret_val = false;
    //TODO:
    if(n==_u||n==_v){
        ret_val=true;
    }
    //
    return ret_val;
}

template<class T, class E>
typename WEdge<T,E>::NodeRef WEdge<T,E>::other(NodeRef const& n) const
{
    assert(has(n));
    NodeRef ret_val;
    //TODO:
    if(n==_u){
        ret_val=_v;
    }
    else{
        ret_val=_u;
    }
    //
    return ret_val;
}

template<class T, class E>
typename WEdge<T,E>::NodeRef WEdge<T,E>::first() const
{
    NodeRef ret_val;
    //TODO:
    ret_val=_u;
    //
    return ret_val;
}

template<class T, class E>
typename WEdge<T,E>::NodeRef WEdge<T,E>::second() const
{
    NodeRef ret_val;
    //TODO:
    ret_val=_v;
    //
    return ret_val;
}

template<class T, class E>
void WEdge<T,E>::set_weight(E const& v)
{
    //TODO:
    _wmat->set(_u->label(), _v->label());
    //
    assert(weight()==v);
}


/** WGraph implementation **/
template<class T>
WGraph<T>::WGraph (size_t capacity, float default_weight)
{
    assert(capacity>0);

    //TODO:
    //Remenber: this a weighted graph, so all the nodes are connected with
    //          inifite weight by default.
    _nodes=std::vector<NodeRef>(capacity);
    _a_mat=FMatrix::create(capacity, capacity, default_weight);
    _size=0;
    _curr_edge=capacity+1;
    _curr_node=capacity+1;
    //

    assert(is_empty());
    assert(!has_current_node());
    assert(!has_current_edge());
}

template<class T>
bool WGraph<T>::is_empty() const
{
    bool ret_v = false;
    //TODO:
    if(_size==0){
        ret_v=true;
    }
    //
    return ret_v;
}

template<class T>
bool WGraph<T>::is_full() const
{
    bool ret_v = false;
    //TODO:
    if(_size==_nodes.capacity()){
        ret_v=true;
    }
    //
    return ret_v;
}

template<class T>
size_t WGraph<T>::size() const
{
    size_t ret_v = 0;
    //TODO:
    ret_v=_size;
    //
    return ret_v;
}

template<class T>
size_t WGraph<T>::capacity() const
{
    size_t ret_v = 0;
    //TODO:
    ret_v=_nodes.capacity();
    //
    return ret_v;
}

template<class T>
bool WGraph<T>::has(NodeRef u) const
{
    assert (u != nullptr);
    bool ret_v = true;
    //TODO:
    ret_v=(u->label()<capacity() && _nodes[u->label()]==u);
    //
    return ret_v;
}

template<class T>
bool WGraph<T>::are_adjacent (NodeRef u, NodeRef v) const
{
    assert( has(u) && has(v) );
    bool ret_v = false;
    //TODO:
    //Remenber: this a Weighted graph so a node u is adjacent to v if the
    //          edge's weigth is less than infinite.
    ret_v=(_a_mat[u->label()][v->label()]<std::numeric_limits<float>::infinity());
    //
    return ret_v;
}

template<class T>
bool WGraph<T>::has_current_node () const
{
    bool ret_v = false;
    //TODO:
    //Hint: use attribute _size to mark "end".
    ret_v=(_curr_node<_size);
    //
    return ret_v;
}

template<class T>
typename WGraph<T>::NodeRef WGraph<T>::current_node () const
{
    assert(has_current_node());
    NodeRef ret_v;
    //TODO:
    ret_v=_nodes[_curr_node];
    //
    return ret_v;
}

template<class T>
bool WGraph<T>::has_current_edge () const
{
    bool ret_v = false;
    //TODO:
    //Remenber: first it must exist a current node.
    //Hint: use attribute _size to mark "end".
    if(has_current_node()){
        ret_v=_curr_edge<_size;
    }
    //
    assert(!ret_v || has_current_node());
    return ret_v;
}

template<class T>
float WGraph<T>::current_weight () const
{
    assert(has_current_edge());
    float ret_v = 0.0;
    //TODO:
    ret_v=weight(_nodes[_curr_node], _nodes[_curr_edge]);
    //
    assert(ret_v<std::numeric_limits<float>::infinity());
    return ret_v;
}

template<class T>
FMatrix::Ref WGraph<T>::weight_matrix() const
{
    FMatrix::Ref mat;
    //TODO:
    mat=_a_mat;
    //
    return mat;
}

template<class T>
float WGraph<T>::weight(size_t u_label, size_t v_label) const
{
    assert(u_label<size());
    assert(v_label<size());
    float ret_v = 0.0;
    //TODO:
    ret_v=_a_mat->get(u_label, v_label);
    //
    assert(ret_v == weight(node(u_label), node(v_label)));
    return ret_v;
}

template<class T>
float WGraph<T>::weight (NodeRef u, NodeRef v) const
{
    assert(has(u));
    assert(has(v));
    float ret_v = 0.0;
    //TODO:
    ret_v=_a_mat->get(u->label(), v->label());
    //
    return ret_v;
}

template<class T>
typename WGraph<T>::EdgeRef WGraph<T>::edge(NodeRef u, NodeRef v) const
{
    assert(has(u));
    assert(has(v));
    EdgeRef ret_v=nullptr;
    //TODO:
    ret_v=std::shared_ptr<WEdge<T, float>>(new WEdge<T, float>(u, v, _a_mat));
    //
    assert(ret_v->first()==u);
    assert(ret_v->second()==v);
    assert(ret_v->weight()==weight(u, v));
    return ret_v;
}

template<class T>
typename WGraph<T>::EdgeRef WGraph<T>::edge(size_t u_label, size_t v_label) const
{
    assert(u_label<size());
    assert(v_label<size());
    EdgeRef ret_v=nullptr;
    //TODO:
    //Hint: use the static method WEdge::create().
    ret_v=std::shared_ptr<WEdge<T, float>>(new WEdge<T, float>(node(u_label), node(v_label), _a_mat));
    //
    assert(ret_v->first()->label()==u_label);
    assert(ret_v->second()->label()==v_label);
    assert(ret_v->weight()==weight(u_label, v_label));
    return ret_v;
}

template<class T>
typename WGraph<T>::EdgeRef WGraph<T>::current_edge() const
{
    assert(has_current_edge());
    EdgeRef ret_v = nullptr;
    //TODO:
    //Hint: use the static method WEdge::create().
    ret_v=std::shared_ptr<WEdge<T, float>>(new WEdge<T, float>(node(_curr_node), node(_curr_edge), _a_mat));
    //
    ret_v->first()==current_node();
    return ret_v;
}

template<class T>
typename WGraph<T>::NodeRef WGraph<T>::node(size_t label) const
{
    assert(label<size());
    NodeRef n;
    //TODO:
    n=_nodes[label];
    //
    return n;
}

template<class T>
void WGraph<T>::set_visited(bool state)
{
    //TODO:
    for(size_t i=0; i<_size;i++){
        _nodes[i]->set_visited(state);
    }
    //
}

template<class T>
void WGraph<T>::goto_first_node()
{
    assert(!is_empty());
    //TODO:
    //Remenber: the edge's cursor must be initialized too.
    _curr_node=0;
    if(has_current_node()){
        goto_first_edge();
    }
    //
    assert(!has_current_edge()||current_edge()->first() == current_node());
    assert(!has_current_edge() ||
           current_weight()<std::numeric_limits<float>::infinity());
}

template<class T>
void WGraph<T>::goto_first_edge()
{
    assert(has_current_node());
    //TODO:
    //Remenber: the cursor moves to the first edge with weight<inf.
    _curr_edge=0;
    while(_curr_edge<_size and weight(_curr_node, _curr_edge)==std::numeric_limits<float>::infinity()){
        _curr_edge++;
    }
    //
    assert(!has_current_edge()||current_edge()->first() == current_node());
    assert(!has_current_edge() ||
           current_weight()<std::numeric_limits<float>::infinity());
}

template<class T>
void WGraph<T>::goto_next_node()
{
    assert(has_current_node());
    //TODO:
    //Remenber: the edge's cursor must be initialized too.
    _curr_node++;
    if(has_current_node()){
        goto_first_edge();
    }

    //
    assert(!has_current_edge() || (current_edge()->first() == current_node()));
    assert(!has_current_edge() ||
           current_weight()<std::numeric_limits<float>::infinity());
}

template<class T>
void WGraph<T>::goto_next_edge()
{
    assert(has_current_edge());
    //TODO:
    //Remenber: the edge cursor must iterate on edges with weight<inf
    do{
        _curr_edge++;
    }while(_curr_edge<_size and _a_mat->get(_curr_node, _curr_edge)==std::numeric_limits<float>::infinity());

    //
    assert(!has_current_edge() || current_edge()->first() == current_node());
    assert(!has_current_edge() ||
           current_weight()<std::numeric_limits<float>::infinity());
}

template<class T>
void WGraph<T>::goto_node(NodeRef u)
{
    assert(has(u));
    //TODO:
    //Remenber: the edge's cursor must be initialized too.
    _curr_node=u->label();
    goto_first_edge();
    //
    assert(!has_current_edge() || current_edge()->first()==u);
    assert(!has_current_edge() ||
           current_weight()<std::numeric_limits<float>::infinity());
}

template<class T>
void WGraph<T>::goto_edge(NodeRef u, NodeRef v)
{
    assert(has(u));
    assert(has(v));
    assert(weight(u, v) < std::numeric_limits<float>::infinity());
    //TODO:
    //Remenber: the node's cursor must be initialized too.
    _curr_node=u->label();
    _curr_edge=v->label();
    //
    assert(current_node()==u);
    assert(current_edge()->first()==u);
    assert(current_edge()->second()==v);
    assert(current_weight()==weight(u,v));
}

template<class T>
void WGraph<T>::goto_edge(EdgeRef e)
{
    assert(has(e->first()));
    assert(has(e->second()));
    assert(e->weight() < std::numeric_limits<float>::infinity());
    //TODO:
    //Remenber: the node's cursor must be initialized too.
    goto_edge(e->first(), e->second());
    //
    assert(current_node()==e->first());
    assert(current_edge()->second()==e->second());
    assert(current_weight()==e->weight());
}

template<class T>
typename WGraph<T>::NodeRef WGraph<T>::find_node(typename T::key_t const& key)
{
    assert(!is_empty());
    NodeRef ret_v = nullptr;
    //TODO:
    //Remenber: The item.key() is used to look for.
    //Remenber: the edge's cursor must be initialized too if a node was found.
    goto_first_node();
    while(has_current_node()){
        if(current_node()->item()==key){
            ret_v=current_node();
            break;
        }
        goto_next_node();
    }
    //
    assert((ret_v==nullptr) || (has_current_node() && current_node()==ret_v));
    assert(!has_current_node() || current_node()->item()==key);
    assert(!has_current_edge() || current_edge()->first()==current_node());
    return ret_v;
}

template<class T>
typename WGraph<T>::NodeRef WGraph<T>::find_next_node(typename T::key_t const& key)
{
    assert(!is_empty());
    NodeRef ret_v = nullptr;
    //TODO:
    //Remenber: The item.key() is used to look for.
    //Remenber: the edge's cursor must be initialized too if a node was found.
    for(size_t i=_curr_node;i<_size;i++){
        if(_nodes[i]->item()==key){
            ret_v=_nodes[i];
            goto_node(ret_v);
            break;
        }
    }
    //
    assert((ret_v==nullptr) || (has_current_node() && current_node()==ret_v));
    assert(!has_current_node() || current_node()->item()==key);
    assert(!has_current_edge() || current_edge()->first()==current_node());
    return ret_v;
}

template<class T>
void WGraph<T>::set_current_weight(float new_w)
{
    assert(has_current_edge());
    //TODO:
    _a_mat->set(_curr_node, _curr_edge, new_w);
    //
    assert(current_weight()==new_w);
}

template<class T>
float WGraph<T>::set_weight(size_t u_label, size_t v_label, float new_weight)
{
    assert(u_label<size());
    assert(v_label<size());
    //TODO:
    _a_mat->set(u_label, v_label, new_weight);
    //
    assert(new_weight == weight(u_label, v_label));
}

template<class T>
void WGraph<T>::set_weight(NodeRef u, NodeRef v, float new_w)
{
    assert(has(u));
    assert(has(v));
    //TODO:
    _a_mat->set(u->label(), v->label(), new_w);
    //
    assert(weight(u, v)==new_w);
}

template<class T>
void WGraph<T>::add_node(T const& v)
{
    assert(! is_full());
    //TODO:
    _nodes[_size]=WNode<T>::create(_size, v);
    _curr_node=_size;
    _curr_edge=_size+1;
    _size++;
    //
    assert(has_current_node());
    assert(!has_current_edge());
}

template <class T>
std::ostream&
WGraph<T>::fold(std::ostream& out) const
{
    //TODO:
    //Hint: the Matrix template has a fold method.
    out<<"[ ";
    out<<capacity()<<" ";
    out<<size()<<" ";
    for(size_t i=0;i<size();i++){
        out<<node(i)->item()<<" ";
    }
    std::vector<typename WGraph<T>::EdgeRef>edges;
    weight_matrix()->fold(out);
    out<<" ]";
    //
    return out;
}

template <class T>
WGraph<T>::WGraph (std::istream& input) noexcept(false)
{
    //TODO:
    //Remenber: capacity is the max number of nodes that the graph could have.
    //          size is the current number of nodes (size <= capacity).
    //Hint: The Matrix template has a unfold method.

    //
    assert(!has_current_node());
    assert(!has_current_edge());
}

template <class T>
typename WGraph<T>::Ref WGraph<T>::create (std::istream & input)
{
    return std::make_shared<WGraph<T>>(input);

}

template<class T>
typename WGraph<T>::Ref create_wgraph(std::istream &in) noexcept(false)
{
    assert(in);
    typename WGraph<T>::Ref graph = nullptr; //The returned graph.

    //TODO:    
    //Remenber: Throw std::runtime_error("Wrong graph") when dectecting wrong
    //          input format.
    //Remenber: key_t type is used to give the edge's ends.

    //TODO:
    //First: Determine if it is directed or undirected.
    std::string type;
    if(!in){
        return nullptr;
    }
    in>>type;
    //

    //TODO:
    //Second: get the number of nodes and create a wgraph with this capacity.
    size_t nodes;
    if(!in){
        return nullptr;
    }
    in>>nodes;
    //

    //TODO:
    //Third: load the N T data items and adding the nodes.
    graph.reset(new WGraph<T>(nodes));
    for(size_t i=0;i<nodes;i++){
        T item;
        if(!in){
            return nullptr;
        }
        in>>item;
        graph->add_node(item);
    }
    //

    //TODO:
    //Fourth: load the number of edges.
    size_t edges;
    in>>edges;
    //

    //TODO:
    //Fifth: load the N edges.
    //Remenber: T::key_t type is used to give the edge's ends.
    //Remenber: if the input graph is UNDIRECTED we simulated this with a WGraph
    //          duplicanting each input edge (u,v) making too the (v,u) edge
    //          with the same weight.
    for (size_t i=0; i<edges; i++){
        typename T::key_t u, v;
        float aux;
        in>>u>>v>>aux;
        graph->set_weight(graph->find_node(u), graph->find_node(v), aux);
        if(type!="DIRECTED"){
            graph->set_weight(graph->find_node(v), graph->find_node(u), aux);
        }
    }
    //

    return graph;
}

