/**
 * @file test_traversals.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <exception>
#include <vector>

#include "item.hpp"
#include "wgraph.hpp"
#include "graph_traversals.hpp"


int Verbose_level=0;

template <class T>
int
do_the_work(std::istream& input_file)
{
    auto g = create_wgraph<T>(input_file);
    if (!g)
    {
        std::cerr << "Error: could not load a valid wgraph." << std::endl;
        return EXIT_FAILURE;
    }

    typename T::key_t start_node_key;
    if (!(input_file >> start_node_key))
    {
        std::cerr << "Error: could not read the start node key."
                  << std::endl;
        return EXIT_FAILURE;
    }
    auto start_node = g->find_node(start_node_key);
    if (!start_node)
    {
        std::cerr << "Error: could not find the start node." << std::endl;
        return EXIT_FAILURE;
    }
    using Tuple = std::tuple<typename WNode<T>::Ref, typename WNode<T>::Ref>; //(v,u)->Reached v arriving from u.
    std::vector<Tuple> nodes;
    auto p = [&nodes](Tuple edge) -> bool {
        nodes.push_back(edge);
        return true;
    };
    if (!depth_first_scan<T>(g, p))
    {
        std::cerr << "Error: could not do a depth first search." << std::endl;
        return  EXIT_FAILURE;
    }
    std::cout << "DF scan from node '"<< start_node->item() << "': ";
    for(auto k: nodes)
        std::cout << std::get<0>(k)->item().key() << ' ';
    std::cout << std::endl;
    std::cout << "DF spanning tree edges: ";
    for(auto k: nodes)
    {
        auto v = std::get<0>(k);
        auto u = std::get<1>(k);
        if (u != v)
            std::cout << u->item().key() << ':'
                      << v->item().key() << ' ';
    }
    std::cout << std::endl;
    //Re-start the graph.
    g->goto_node(start_node);
    g->set_visited(false);
    nodes.resize(0);
    if (!breadth_first_scan<T>(g, p))
    {
        std::cerr << "Error: could wide traverse the graph." << std::endl;
        return  EXIT_FAILURE;
    }
    std::cout << "BF scan from node '"<< start_node->item() << "': ";
    for(auto k: nodes)
        std::cout << std::get<0>(k)->item().key() << ' ';
    std::cout << std::endl;
    std::cout << "BF spanning tree edges: ";
    for(auto k: nodes)
    {
        auto v = std::get<0>(k);
        auto u = std::get<1>(k);
        if (u != v)
            std::cout << u->item().key() << ':'
                      << v->item().key() << ' ';
    }
    std::cout << std::endl;
    return EXIT_SUCCESS;
}

int
main(int argc, const char* argv[])
{
    int exit_code = EXIT_SUCCESS;
    try
    {
        if (argc < 2 || argc > 3)
        {
            std::cerr << "Usage: " << argv[0] << " [-v] filename" << std::endl;
            return EXIT_FAILURE;
        }
        std::ifstream input_file;
        if (std::string(argv[1])==std::string("-v"))
        {
            Verbose_level=1;
            input_file.open(argv[2]);
        }
        else
            input_file.open(argv[1]);
        if (!input_file)
        {
            std::cerr << "Error: could not open input filename '" << argv[1] << "'." << std::endl;
            return EXIT_FAILURE;
        }
        std::string type;
        if (!(input_file>>type))
        {
            std::cerr << "Error: could not read the type signature."
                      << std::endl;
            return EXIT_FAILURE;
        }
        if (type=="INT")
            exit_code = do_the_work<Int>(input_file);
        else if (type=="STRING")
            exit_code = do_the_work<String>(input_file);
        else
        {
            std::cerr << "Error: unknown graph type." << std::endl;
            return EXIT_FAILURE;
        }
    }
    catch(std::runtime_error &e)
    {
        std::cerr << "Run time exception: " << e.what() << std::endl;
        exit_code = EXIT_FAILURE;
    }
    catch(...)
    {
        std::cerr << "Catched unknown exception!." << std::endl;
        exit_code = EXIT_FAILURE;
    }
    return exit_code;
}

