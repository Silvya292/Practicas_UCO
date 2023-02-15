#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "queue_imp.hpp"

int
main(int argc, const char* argv[])
{
    int exit_code = EXIT_SUCCESS;
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: test_stack test_case" << std::endl;
            return EXIT_FAILURE;
        }
        std::string filename = argv[1];

        std::ifstream input (argv[1]);
        if (!input)
        {
            std::cerr << "Error: could not open input filename '" << argv[1] << "'." << std::endl;
            return EXIT_FAILURE;
        }

        Queue<int> queue;

        while(input)
        {
            std::string operation;
            input >> operation;
            if (input)
            {
                if (operation=="ENQUE")
                {
                    int value;
                    input >> value;
                    std::cout << "Enque " <<value << std::endl;
                    queue.enque(value);
                } else if (operation == "DEQUE")
                {
                    std::cout << "Deque " << queue.front() << std::endl;
                    queue.deque();
                } else if (operation == "FRONT")
                {
                    std::cout << "Front: " << queue.front() << std::endl;
                } else if (operation == "IS_EMPTY")
                {
                    std::cout << "Is it empty?: "
                              << (queue.is_empty() ? "Y" : "N")
                              << std::endl;
                } else if (operation == "BACK")
                {
                    std::cout << "Back: " << queue.back() << std::endl;
                } else if (operation == "SIZE")
                {
                    std::cout << "Size: " << queue.size() << std::endl;
                }
                else
                {
                    std::cerr << "Error: operation not found? '"
                              << operation << "'." << std::endl;
                    return EXIT_FAILURE;
                }
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
