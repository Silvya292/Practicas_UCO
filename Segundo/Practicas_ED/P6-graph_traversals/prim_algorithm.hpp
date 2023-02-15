/**
 * @file prim_algorithm.hpp
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
#include <utility>
#include <list>
#include <limits>
#include <memory>
#include <valarray>
#include <vector>

#include "wgraph.hpp"

/**
 * @brief Execute the Prim algorithm.
 * The Prim's algorithm create the minimum spannig tree on an undirected
 * weighted graph.
 * @arg[in] g is the graph.
 * @arg[out] mst is the list of edges of g that forms the minium spanning tree.
 * @return the total weigth of the mininum spanning tree. 
 * @pre g->hash_current()
 * @throw std::runtime_error("It is a unconnected graph.") if the input graph
 *        is an unconnected one.
 */
template <class T>
float
prim_algorithm(typename WGraph<T>::Ref g,
               std::vector<typename WGraph<T>::EdgeRef>& mst) noexcept(false)
{
    assert(g->has_current_node());
    float total_distance = 0.0;
    mst.resize(0);

    //TODO::
    //Remenber: Use three auxiliary vectors A, V and C.
    //Hint: use std::numeric_limits<float> template to represent "infinite".
    std::vector<bool>A;
    std::vector<int>V;
    std::vector<float>C;

    auto u = g -> current_node();
    for(size_t i = 0; i < g -> size(); i++){
        if(u -> label() == i){
            A.push_back(true);
            V.push_back(-1);
        }
        else{
            A.push_back(false);
            V.push_back(u -> label());
        }
        C.push_back(g -> weight(g -> node(i), u));
    }
    size_t p_min = 0;
    float min = C[0];
    for(size_t i = 0; i < g -> size(); i++){
        if(A[i] == false && C[i] < min){
            p_min = i;
            min = C[i];
        }
    }
    A[p_min] = true;
    mst.push_back(g -> edge(g -> node(p_min), g -> node(V[p_min])));
    total_distance += C[p_min];
    C[p_min] = std::numeric_limits<float>::infinity();
    for (size_t i = 1; i < g -> size()-1; i++){
        size_t last = p_min;
        for(size_t i = 0; i<g->size(); i++){
            if(A[i] == false && last != i && g -> weight(g -> node(last), g -> node(i)) < C[i]){
                V[i] = last;
                C[i] = g -> weight(g -> node(last), g -> node(i));
            }
        }
        p_min = 0;
        min = C[0];
        for(size_t i = 0; i < g -> size(); i++){
            if(A[i] == false && C[i] < min){
                p_min = i;
                min = C[i];
            }
        }
        if(min == std::numeric_limits<float>::infinity()){
            throw std::runtime_error("It is a non-connected graph.");
        }
        g -> goto_edge(g -> node(p_min), g -> node(V[p_min]));
        if (!g -> has_current_edge()){
            throw std::runtime_error("It is a non-connected graph.");
        }
        A[p_min] = true;
        mst.push_back(g -> edge(g -> node(p_min), g -> node(V[p_min])));
        total_distance += C[p_min];
        C[p_min] = std::numeric_limits<float>::infinity();
    }

    //

    return total_distance;
}
