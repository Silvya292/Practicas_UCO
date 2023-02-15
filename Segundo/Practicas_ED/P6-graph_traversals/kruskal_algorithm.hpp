/**
 * @file kruskal_algorithm.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <exception>
#include <limits>
#include <memory>
#include <vector>
#include <algorithm>

#include "wgraph.hpp"
#include "disjointsets.hpp"

/**
 * @brief Kruskal edge weight:(u, v)
 * @see https://en.cppreference.com/w/cpp/utility/tuple
 *
 */
using KEdge = std::tuple<float, size_t, size_t>;

/**
 * @brief Compute the list of edges.
 * @param g is the graph.
 * @param edge_list is used to save the list.
 */
template <class T>
void compute_list_of_edges(typename WGraph<T>::Ref g,
                           std::vector<KEdge>& edge_list)
{
    edge_list.resize(0);
    //TODO:
    //Remenber: the graph is undirected so we only need to find (u,v) edges
    //          with u.label<v.label and weight<inf
    g -> goto_first_node();
    while(g -> has_current_node()){
        g -> goto_first_edge();
        while (g  ->  has_current_edge()){
            auto u = g -> current_edge() -> first() -> label();
            auto v = g -> current_edge() -> second() -> label();
            auto w = g -> current_edge() -> weight();
            edge_list.push_back(KEdge(w, u, v));
            g -> goto_next_edge();
        }
        g -> goto_next_node();
    }
    //
}

template<class T>
struct KruskalEdgeCompare
{
  bool operator()(KEdge & a, KEdge & b) const
  {
    //TODO: replace for a better check.
    auto w1 = std::get<0>(a);
    auto w2 = std::get<0>(b);
    auto it1 = std::get<1>(a);
    auto it2 = std::get<1>(b);
    auto it12 = std::get<2>(a);
    auto it22 = std::get<2>(b);  
    if(w1 < w2){
        return true;
    }
    if(w1 == w2 && it1 < it2){
        return true;
    }
    if(w1 == w2 && it1 == it2 && it12 < it22){
        return true;
    }
    return false;
  }  
};

/**
 * @brief Execute the kruskal algorithm.
 * Compute the minimum spannig tree.
 * @arg[in] g is the graph.
 * @arg[out] mst is the list of edges of g that forms the minium spanning tree.
 * @return the total weigth of the mininum spanning tree.
 * @pre g is an undirected connected graph. 
 * @throw std::runtime_error("It is a unconnected graph.") if the input graph
 *        is an unconnected one.
 */
template <class T>
float
kruskal_algorithm(typename WGraph<T>::Ref g,
                  std::vector<KEdge>& mst) noexcept(false)
{
    float total_distance = 0.0;

    DisjointSets sets (g->size());
    //Generate a set for each node.
    for (size_t i=0; i < g->size(); ++i)
        sets.make_set(i);

    //TODO:
    //Remenber: use disjoint sets to find the "color" of a node label and
    //          joint two sub-sets.
    //Hint: use std::sort to sort the edge list.
    std::vector<KEdge> edges;        
    compute_list_of_edges<T>(g, edges);
    std::sort(edges.begin(), edges.end(), KruskalEdgeCompare<T>());  
    g -> goto_first_node();
    while(g -> has_current_node()){
        sets.make_set(g -> current_node() -> label());
        g -> goto_next_node();
    }
    for(size_t i = 0; i < edges.size(); i++){
        if(sets.find(std::get<1>(edges[i])) != sets.find(std::get<2>(edges[i]))){
            mst.push_back(edges[i]);
            sets.joint(std::get<1>(edges[i]), std::get<2>(edges[i]));
            total_distance += std::get<0>(edges[i]);
        }
    }
    if(mst.size() != g -> size() - 1){
        throw std::runtime_error("It is a non-connected graph.");
    }

    //

    return total_distance;
}
