/**
 * @file graph.hpp
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
#include <cstdlib>
#include <memory>
#include <vector>
#include <limits>

#include "matrix.hpp"

template<class T> class WGraph;

/**
 * @brief Class to model the Node of a Graph ADT.
 * @ingroup graph
 */
template <class T>
class WNode
{
public:
    /** @brief Models a reference to a Node.*/
    typedef std::shared_ptr< WNode<T> > Ref;

    ~WNode() {}

  /** @name Observers*/
  /**@{*/

  /** @brief Get data saved.
      @return a reference to the data saved in the node.
   */
  T item() const;

  /** @brief get the label of the node.
   * @return the node's label.
   * @post no other node in the graph has this label.
   */
   size_t label() const;

   /** @brief Has been the node visited?
    * return true if the node was visited.
    */
   bool is_visited() const;

  /**@}*/

  /** @name Modifiers*/
  /** @{*/

   /**@brief Set data saved in the node.
   * @arg[in] item is the data to save in.
   * @post item()==item
   */
   void set_item(T const& new_item);

   /**
    *  @brief Set the flag visited
    *  @param new_state is the state to set.
    *  @post new_state || !is_visited()
    *  @post !new_state || is_visited()
    */
   void set_visited(bool new_state);
  /** @} */

protected:

   /** @name Makers*/
   /** @{*/

     /** @brief Makes a new node.
      * @args label is the label of the new node.
      * @args item is the item saved in the node.
      * @pre no othe node in the graph has the same label.
      * @post not isVisited()
      */
      WNode(size_t label, T const& item);

      /** @brief Makes a new node.
      * @args label is the label of the new node.
      * @args item is the item saved in the node.
      * @pre no othe node in the graph has the same label.
      * @post not isVisited()
      */
      static typename WNode<T>::Ref create(size_t label, const T& item)
      {
          return std::shared_ptr<WNode<T>> ( new WNode<T>(label, item) );
      }

   /** @}*/

   friend class WGraph<T>;

   //TODO:
   size_t _label;
   T _item;
   bool _visited;
   //
};

/**
 * @brief Class to model the WEdge of a WGraph ADT.
 * A weighted edge is a directed link u -> v with a weight (float).
 * @ingroup wgraph
 */
template <class T, class E>
class WEdge
{
public:

  /** @brief a referece to a node.*/
  typedef typename WNode<T>::Ref NodeRef;

  /** @brief Models a reference to an Edge.*/
  typedef std::shared_ptr< WEdge <T, E> > Ref;

    ~WEdge() {}

  /** @name Observers*/
  /** @{*/

  /**
   *  @brief Get data item.
   */
  E weight() const;

  /**
   *  @brief Is node u an end of this edge.
  * @args[in] u is a node to test.
  * @return true is u is one of the edge's ends.
  */
  bool has(NodeRef const& u) const;

  /**
   *  @brief The other end node that is not u.
  * @args[in] u is a end node.
  * @return the other end node that is not u.
  * @pre has(u)
  * @post has(retVal) and other(retVal)=u
  */
  NodeRef other(NodeRef const& u) const;

  /** @brief the start node when a directed edge.
  * @return the start node.
  */
  NodeRef first() const;

  /** @brief the end node when a directed edge.
  * @return the end node.
  */
  NodeRef second() const;

  /**@}*/

  /** @name Modifiers*/
  /** @{*/

   /**
    * @brief Set data saved in the node.
   * @arg[in] v is the data to save in.
   * @post item()==v
   */
   void set_weight(E const& v);

  /** @} */

protected:

   /** @name Makers*/
   /** @{*/

     /**
     * @brief Makes a new node.
     * @arg[in] u the first node.
     * @arg[in] v the second node.
     * @arg[in] wmat is the graph's weight matrix.
     * @post first()==u and second()=v
     */
     WEdge(NodeRef u, NodeRef v, FMatrix::Ref wmat);

     /**
     * @brief Makes a new node.
     * @arg[in] u the first node.
     * @arg[in] v the second node.
     * @arg[in] item the data to save.
     * @post first()==u and second()=v
     */
     static Ref create(NodeRef u, NodeRef v, FMatrix::Ref wmat)
     {
         return std::shared_ptr<WEdge<T,E>> ( new WEdge<T,E>(u, v, wmat) );
     }

   /** @}*/

   friend class WGraph<T>;

    //TODO:
    NodeRef _u;
    NodeRef _v;
    FMatrix::Ref _wmat;
    //
};

/**
 * @brief Models the Weighted Graph ADT.
 * A Weighted graph is directed graph where all nodes are connected with all
 * by default with infinity weigth.
 * Two nodes u,v are adjacent if the weight of the edge u->v is less than infinity.
 * @ingroup graph
 *
 * @invariant !is_empty() || size()==0
 * @invariant !is_full() || size()>=capacity()
 *
 */
template <class T>
class WGraph
{
public:

    /** @brief Models a reference to a WGraph.*/
    typedef std::shared_ptr< WGraph<T> > Ref;

    /** @brief a ref to a graph's node. */
    typedef typename WNode<T>::Ref NodeRef;

    /** @brief the type used as node's key. */
    typedef typename T::key_t key_t;

    /** @brief a ref to a graph's edge. */
    typedef typename WEdge<T, float>::Ref EdgeRef;


  /** @name Makers*/
  /** @{*/

    /**
     * @brief Makes a Weighted Graph with capicity nodes.
     * @param capacity is the maximum number of vertices.
     * @param default_weight used to initialice edges' weight.
     * @pre capacity > 0
     * @post is_empty()
     * @post !has_current_node()
     * @post !has_current_edge()
     */
    WGraph (size_t capacity,
            float default_weight=std::numeric_limits<float>::infinity());

    /**
     * @brief Virtual constructor.
     * @param capacity maximun number of vertices.
     * @param default_weight used to initialice edges' weight.
     * @return a reference to the created graph.
     */
    static Ref create (size_t capacity,
                    float default_weight=std::numeric_limits<float>::infinity())
    {
        return std::make_shared<WGraph<T>>(capacity, default_weight);
    }

    /**
     * @brief Makes a Weighted graph from an input stream.
     * FORMAT:
     *
     * 'WGraph'
     * <capacity> <size>
     * <node_item_0>
     * ...
     * <node_item_size-1>
     * <Weight Matrix capacity x capacity>
     *
     * @param input is the input stream.
     * @throw std::runtime_error("Wrong WGraph format.")
     */
    WGraph (std::istream& input) noexcept(false);

    /**
     * @brief Virtual constructor from an input stream.
     * @see fold to the input format.
     * @param input is the input stream.capacity maximun number of vertices.
     * @return a reference to the created graph.
     */
    static Ref create(std::istream & input);

    ~WGraph () {}

  /** @}*/

  /** @name Observers*/
  /**@{*/

    /**
    * @brief is the graph empty?
    * @return true if there is not any node.
    * @pos !is_empty() or size()==0
    */
    bool is_empty() const;

    /**
    * @brief is the graph empty?
    * @return true if there is not any node.
    */
    bool is_full() const;

    /**
     * @brief Get current number of nodes.
     */
    size_t size() const;

    /**
     * @brief Get the max number of nodes to be added.
     * @return return the graph's capacity.
     */
    size_t capacity() const;

    /** @brief is u a node of this graph?
     * @pre u is not nullptr.
     * @return if its true.
     */
    bool has( NodeRef u) const;

    /**
    * @brief Are nodes u and v adjacents?
    * Two nodes are adjacents if the weigth of the edge u->v is less than inf.
    * @arg[in] u ,
    * @arg[in] v are nodes.
    * @return true if the weight of the edge u->v < inf.
    * @pre u and v are nodes of the graph.
    */
    bool are_adjacent (NodeRef u, NodeRef v) const;

    /**
    * @brief Is the node cursor valid?
    * @return true if the node cursor references to a valid node.
    */
    bool has_current_node() const;

    /**
    * @brief Get the current node.
    * @return a reference to the current node.
    * @pre has_current_node()
    */
    NodeRef current_node() const;

    /**
    * @brief Is the edge cursor valid?.
    * @return true if the edge cursor references a valid edge.
    * @post !ret_v || has_current_node();
    */
    bool has_current_edge() const;

    /**
     * @brief Get the weight of current edge.
     * @return the weight of the current edge.
     * @pre has_current_edge()
     * @post ret_v < inf
     */
    float current_weight() const;

    /**
     * @brief Get the weight of current edge.
     * @return a reference to the current edge.
     * @pre has_current_edge()
     * @post ret_v->first()==current_node()
     */
    EdgeRef current_edge() const;

    /**
     * @brief get a node by its label.
     * @pre label< size()
     */
    NodeRef node(size_t label) const;

    /**
     * @brief Get the weight of a u->v edge.
     * @pre has(u) and has(v)
     */
    float weight(NodeRef u, NodeRef v) const;

    /**
     * @brief Get the weight of a u->v edge.
     * @param u_label is the label of the u node.
     * @param v_label is the label of the v node.
     * @pre u_label<size()
     * @pre v_label<size()
     * @post ret_v = weight(node(u_label), node(v_label))
     */
    float weight(size_t u_label, size_t v_label) const;

    /**
     * @brief Get the edge (u,v).
     * @param u is the first vertex.
     * @param v is the second vertex.
     * @return a reference to the edge.
     * @pre has(u)
     * @pre has(v)
     * @post ret_v->first()==u
     * @post ret_v->second()==v
     * @post ret_val->weight()==weight(u, v)
     */
    EdgeRef edge(NodeRef u, NodeRef v) const;

    /**
     * @brief Get the edge (u,v).
     * @param u_label is the label of the first vertex.
     * @param v_label is the label of the second vertex.
     * @return a reference to the edge.
     * @pre u_label < size()
     * @pre v_label < size()
     * @post ret_v->first()->label()==u_label
     * @post ret_v->second()->label()==v_label
     * @post ret_val->weight()==weight(u_label, v_label)
     */
    EdgeRef edge(size_t u_label, size_t v_label) const;

    /**
     * @brief Fold a weighted graph to an output stream.
     * FORMAT:
     *
     * '[ '<capacity>' '<size>{' '<node_item>}*' [ '<rows>' '<cols>'{' 'weight}*' ] ]'
     *
     * @param out is the output stream.
     * @return the output stream.
     */
    std::ostream& fold(std::ostream& out) const;


    /**
     * @brief get the Weight Matrix.
     * @return a reference to the weight matrix.
     */
    FMatrix::Ref weight_matrix() const;

  /** @}*/

  /** @name Modifiers*/
  /** @{*/

    /** @name Cursor Management*/
    /** @{*/
        /**
         * @brief set the visited state for all then nodes.
         */
        void set_visited(bool state);

        /**
        * @brief Goto to the first node.
        * @pre !is_empty().
        * @post !has_current_edge() || current_edge()->first() == current_node()
        * @post !has_current_edge() || current_weight()<inf
        */
        void goto_first_node();

        /**
        * @brief Goto to the first edge (with weight < inf).
        * @pre has_current_node()
        * @post !has_current_edge() || current_edge()->first() == current_node()
        * @post !has_current_edge() || current_weight()<inf
        */
        void goto_first_edge();

        /**
        * @brief Move the cursor to the next node if there is.
        * The edge cursor is also affected.
        * @pre has_current_node().
        * @post !has_current_edge()||current_edge()->first() == current_node()
        * @post !has_current_edge()||current_weight()<inf
        */
        void goto_next_node();

        /**
        * @brief Move the cursor to the next edge with weight < inf.
        * @pre has_current_edge().
        * @post !has_current_edge()||current_edge()->first() == current_node()
        * @post !has_current_edge()||current_weight()<inf
        */
        void goto_next_edge();

        /**
        * @brief Move the cursor to a node.
        * @arg[in] u is a node.
        * @pre has(u)
        * @post current_node()==u.
        * @post !has_current_edge()||current_edge()->first()==u
        * @post !has_current_edge()||current_weight()<inf
        */
        void goto_node(NodeRef u);

        /**
        * @brief Move the node and graph cursors.
        * @arg[in] u,
        * @arg[in] v are nodes.
        * @pre has(u)
        * @pre has(v)
        * @pre weight(u, v) < inf
        * @post current_node()==u
        * @post current_edge()->first()==u
        * @post current_edge()->second()==v
        * @post current_weight()==weight(u,v)
        */
        void goto_edge(NodeRef u, NodeRef v);

        /**
        * @brief Move the node and graph cursors.
        * @arg[in] e is the edget where moving cursors.
        * @pre has(e->fist()) and has(e->second())
        * @pre e->weight()<inf
        * @post current_node()==e->first()
        * @post current_edge()->second()==e->second()
        * @post current_weight()==e->weight()
        */
        void goto_edge(EdgeRef e);

        /**
         * @brief Move cursor to the first node with data item equal to key.
         * @param key is the data item to be found.
         * @return a reference to the node.
         * @pre !is_empty()
         * @post ret_v==nullptr || has_current_node() && current_node()==ret_v
         * @post !has_current_node() || current_node()->item()==key
         * @post !has_current_edge() || current_edge()->first()==current_node()
         */
        NodeRef find_node (typename T::key_t const& key);

        /**
         * @brief Move cursor to next node with data item equal to key.
         * @param key is the data item to be found.
         * @return a reference to the node.
         * @pre has_current_node()
         * @post ret_v==nullptr || has_current_node() && current_node()==ret_v
         * @post !has_current_node() || current_node()->item()==key
         * @post !has_current_edge() || current_edge()->first()==current_node()
         */
        NodeRef find_next_node (typename T::key_t const& key);

    /** @} */

    /** @name Graph editing */
    /** @{ */

        /**
         * @brief Set the weight of current edge.
         * @pre has_current_edge()
         * @post current_weight()==new_w
         */
        void set_current_weight(float new_w);

        /**
         * @brief Set the weight of u->v edge.
         * @param u_label is the label of the u node.
         * @param v_label is the label of the v node.
         * @param new_w is the weight value to set.
         * @pre u_label<size()
         * @pre v_label<size()
         * @post weight(u_label, v_label)==new_w
         */
        float set_weight(size_t u_label, size_t v_label, float new_w);

        /**
         * @brief Set the weight of u->v edge.
         * @param u and
         * @param v are the edge ends.
         * @param new_w is the weight value to set.
         * @pre has(u) and has(v).
         * @post weight(u, v)==new_w
         */
        void set_weight(NodeRef u, NodeRef v, float new_w);

        /**
        * @brief Add a new node.
        * @arg[in] v is the data item to be save in the new node.
        * @pre not is_full()
        * @post has_current_node()
        * @post not has_current_edge()
        */
        void add_node(T const& v);

    /** @} */

  /** @} */
        protected:

    std::vector< NodeRef > _nodes;
    FMatrix::Ref _a_mat;
    size_t _size;
    size_t _curr_node;
    size_t _curr_edge;
};


/**
 * @brief Create a WGraph from a generic Graph format.
 *
 * INPUT FORMAT:
 *
 * 'DIRECTED'|'UNDIRECTED'
 * <NUM. NODES>
 * <NODE_0_ITEM>
 * ...
 * <NODE_N-1_ITEM>
 * <NUM_EDGES>
 * <U_KEY_0> <V_KEY_0> <WEIGHT_0>
 * ...
 * <U_KEY_num_edges-1> <V_KEY_num_edges-1> <WEIGHT_num_edges-1>
 *
 * @warning if the input graph is undirected, the weight of edge (u,v) will be
 *          duplicated to make the edge (v,u).
 * @param in is the input stream.
 * @return a reference to the WGraph.
 * @throw std::runtime_error("Wrong graph")
 */
template<class T>
typename WGraph<T>::Ref create_wgraph(std::istream &in) noexcept(false);

#include "wgraph_imp.hpp"
