/**
 * @file test_kruskal.cpp
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
#include "city.hpp"
#include "wgraph.hpp"
#include "kruskal_algorithm.hpp"

template<class T>
int
do_the_work(std::istream& input_file)
{
    auto g = create_wgraph<T>(input_file);
    if (! g)
    {
        std::cerr << "Error: could not load a valid wgraph for integers." << std::endl;
        return EXIT_FAILURE;
    }
    std::vector<KEdge> MST;

    float total_weight  = 0.0;
    std::cout << "Minimum Spanning tree :";

    try
    {
        total_weight = kruskal_algorithm<T>(g, MST);
    }
    catch (std::runtime_error &e)
    {
        std::cout << " !!Error: The input graph is unconnected." << std::endl;
        return EXIT_SUCCESS;
    }

    for (size_t i=0; i<MST.size(); ++i)
    {
        auto w = std::get<0>(MST[i]);
        auto u = g->node(std::get<1>(MST[i]))->item().key();
        auto v = g->node(std::get<2>(MST[i]))->item().key();
        if (v<u)
            std::swap(u, v);
        std::cout << ' ' << w << ":(" << u << ',' << v << ')';
    }
    std::cout << std::endl;
    std::cout << "Total weight: " << total_weight << std::endl;
    return EXIT_SUCCESS;
}

int
main(int argc, const char* argv[])
{
    int exit_code = EXIT_SUCCESS;
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
            return EXIT_FAILURE;
        }
        std::ifstream input_file (argv[1]);
        if (!input_file)
        {
            std::cerr << "Error: could not open input filename '" << argv[1] << "'." << std::endl;
            return EXIT_FAILURE;
        }
        std::string type;
        input_file >> type;
        input_file.ignore();
        if (type=="INT")
            exit_code = do_the_work<Int>(input_file);
        else if (type=="STRING")
            exit_code = do_the_work<String>(input_file);
        else if(type=="CITY")
            exit_code = do_the_work<City>(input_file);
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

