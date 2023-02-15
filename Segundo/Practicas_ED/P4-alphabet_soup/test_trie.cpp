/**
 * @file test_trie.cpp
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
#include <vector>
#include <exception>
#include <string>
#include <algorithm>

#include "trie.hpp"

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
            std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
            return EXIT_FAILURE;
        }
        Trie::Ref trie = Trie::create();
        std::string command;
        while(input_file >> command)
        {
            if (command == "IS_EMPTY")
            {
                std::cout << "Is it empty? " <<
                             (trie->is_empty() ? "yes." : "no.") << std::endl;
            }
            else if (command == "PREFIX")
            {
                std::cout << "Trie's prefix: '" << trie->prefix()
                          << "'." << std::endl;
            }
            else if (command == "IS_KEY")
            {
                std::cout << "Is trie's prefix a key? " <<
                             (trie->is_key() ? "yes." : "no.") << std::endl;
            }
            else if (command == "INSERT")
            {
                std::string new_key;
                input_file.ignore(); //remove blank.
                std::getline(input_file, new_key);
                trie->insert(new_key);
                std::cout << "Inserted key: '" << new_key << "'." << std::endl;
            }
            else if (command == "HAS")
            {
                std::string key;
                input_file.ignore(); //remove blank.
                std::getline(input_file, key);
                if (!input_file)
                {
                    std::cerr << "Error: worng input format." << std::endl;
                    return  EXIT_FAILURE;
                }
                std::cout << "Has '" << key << "' key?: "
                          << (trie->has(key) ? "yes." : "no.") << std::endl;
            }
            else if (command == "SUBTRIE")
            {
                std::string prefix;
                input_file.ignore(); //remove blank.
                std::getline(input_file, prefix);
                if (!input_file)
                {
                    std::cerr << "Error: worng input format." << std::endl;
                    return  EXIT_FAILURE;
                }
                std::cout << "Finding subtrie for prefix '"
                          << prefix << "' ... ";
                trie = trie->child(prefix);
                std::cout << (trie->is_empty() ? "(not found)" : "(found)")
                          << std::endl;
            }
            else if (command == "CURRENT_EXISTS")
            {
                std::cout << "Current exist? "
                          << (trie->current_exists() ? "yes." : "no.")
                          << std::endl;
            }
            else if (command == "CURRENT_SYMBOL")
            {
                std::cout << "Current symbol '"
                          << trie->current_symbol() << "'." << std::endl;
            }
            else if (command == "CURRENT_PREFIX")
            {
                std::cout << "Current trie's prefix '" <<
                    trie->current()->prefix() << "'." << std::endl;
            }
            else if (command == "GOTO_FIRST_SYMBOL")
            {
                std::cout << "Going to first symbol ... ";
                trie->goto_first_symbol();
                std::cout << " ok." << std::endl;
            }
            else if (command == "GOTO_NEXT_SYMBOL")
            {
                std::cout << "Going to next symbol ... ";
                trie->goto_next_symbol();
                std::cout << " ok." << std::endl;
            }
            else if (command == "FIND_SYMBOL")
            {
                char symbol;
                input_file >> symbol;
                std::cout << "Finding symbol '" << symbol << "' ... ";
                std::cout << (trie->find_symbol(symbol) ? "found." :
                                                          "not found.");
                std::cout << std::endl;
            }
            else if (command == "RETRIEVE")
            {                
                std::cout << "Rerieving keys with prefix '" << trie->prefix()
                          << "' :";
                std::vector<std::string> keys;
                trie->retrieve(keys);
                std::sort(std::begin(keys), std::end(keys));
                for(size_t i=0;i<keys.size();++i)
                    std::cout << " '" << keys[i] << "'";
                std::cout << std::endl;
            }
            else if (command == "FOLD")
            {
                std::cout << "Fold trie: ";
                trie->fold(std::cout) << std::endl;
            }
            else if (command == "UNFOLD")
            {
                std::cout << "Unfolding ... ";
                try
                {
                    trie = Trie::create(input_file);
                    std::cout << " ok." << std::endl;
                }
                catch (std::runtime_error& e)
                {
                    std::string buffer;
                    std::getline(input_file, buffer);
                    std::cout << "wrong input format. Decoded upto '"
                              << buffer << "'." << std::endl;
                }
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

