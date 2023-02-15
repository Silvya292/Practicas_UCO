/**
 * @file test_graph.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <exception>
#include <vector>

#include "wgraph.hpp"
#include "item.hpp"

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
        WGraph<Char>::Ref graph;

        std::cout << std::unitbuf;

        std::string buffer;
        std::istringstream input;
        while(std::getline(input_file, buffer))
        {
            input.str(buffer);
            input.clear();
            std::string command;

            input >> command;
            if (!input || command=="" || command[0]=='#')
                continue;

            if (command == "CREATE")
            {
                size_t cap;
                if (!(input>>cap))
                    throw std::runtime_error("Wrong command");
                graph = WGraph<Char>::create(cap);
                std::cout << "Created a graph with capacity = "
                          << graph->capacity() << " and size="
                          << graph->size() << std::endl;
            }
            else if (command == "ADD_NODE")
            {
                Char data;
                if (!(input >> data))
                    throw std::runtime_error("Wrong command");
                graph->add_node(data);
                std::cout << "Added node with data '" << data
                          << "'. Graph size =" << graph->size() << std::endl;
            }
            else if (command == "SET_WEIGHT")
            {
                char u_d, v_d;
                float weight;
                if (!(input >> u_d >> v_d >> weight))
                    throw std::runtime_error("Wrong command");
                auto u = graph->find_node(u_d);
                auto v = graph->find_node(v_d);
                graph->set_weight(u, v, weight);
                std::cout << "Set weight of edge (" << u_d << "," << v_d
                          << ") to " << graph->weight(u, v) << std::endl;
            }
            else if (command == "PRINT_EDGES")
            {
                std::cout << "Graph's edges:" << std::endl;
                graph->goto_first_node();
                while(graph->has_current_node())
                {
                    while(graph->has_current_edge())
                    {
                        auto u = graph->current_node();
                        auto v = graph->current_edge()->other(u);
                        auto w = graph->current_weight();
                        std::cout << u->item() << " -- "
                                  << w << " --> " << v->item() << std::endl;
                        graph->goto_next_edge();
                    }
                    graph->goto_next_node();
                }
            }
            else if (command == "PRINT_INCIDENT_EDGES")
            {
                char key;
                if (!(input >> key))
                    throw std::runtime_error("Wrong command");
                auto u = graph->find_node(key);
                if (u==nullptr)
                    throw std::runtime_error("Wrong command");

                std::cout << "Incident edges on vertex '" << u->item()
                          << "' :" << std::endl;
                while(graph->has_current_edge())
                {
                    auto v = graph->current_edge()->other(u);
                    auto w = graph->current_weight();
                    std::cout << u->item() << " -- "
                              << w << " --> " << v->item() << std::endl;
                    graph->goto_next_edge();
                }
            }
            else if (command == "PRINT_EDGE")
            {
                char u_key, v_key;
                if (!(input >> u_key >> v_key))
                    throw std::runtime_error("Wrong command");
                auto u=graph->find_node(u_key);
                if (u==nullptr)
                    throw std::runtime_error("Wrong command");
                auto v=graph->find_node(v_key);
                if (v==nullptr)
                    throw std::runtime_error("Wrong command");
                auto edge = graph->edge(u, v);
                std::cout << "Edge '" << u->item() << "' to '"
                          << v->item() << "' has weight="
                          << edge->weight() << std::endl;

            }
            else if (command == "PRINT_WMATRIX")
            {
                std::cout << "WMatrix:" << std::endl;
                for(size_t r = 0 ; r<graph->size(); ++r)
                {
                    auto u = graph->node(r);
                    for(size_t c = 0 ; c<graph->size(); ++c)
                    {
                        auto v = graph->node(c);
                        std::cout << std::setw(6) << graph->weight(u, v) << ' ';
                    }
                    std::cout << std::endl;
                }
            }
            else if (command == "FOLD")
            {
                std::cout << "Folding graph: " << std::endl;
                graph->fold(std::cout);
                std::cout << std::endl;
            }
            else if (command == "UNFOLD")
            {
                std::cout << "Unfolding graph ...";
                graph = WGraph<Char>::create(input);
                std::cout << " ok." << std::endl;
            }
            else
            {
                std::cerr << "Error: command unknown '"<< command << "'." << std::endl;
                return EXIT_FAILURE;
            }

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

