/**
 * @file test_hash_function.cpp
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
#include <vector>
#include <exception>

#include "hash.hpp"

std::istream&
operator>>(std::istream& in, std::vector<int>& v)
{
    size_t size;
    in >> size;
    if (in)
    {
        v.resize(size);
        for (size_t i=0;i<size && in; ++i)
            in >> v[i];
    }
    return in;
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
            std::cerr << "Usage: " << argv[0] << " filename" << std::endl;
            return EXIT_FAILURE;
        }
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

            if (command=="GEN_UNIFORM")
            {
                size_t n;
                if (!(input >> n))
                    throw std::runtime_error("Wrong command format.");
                std::cout << "Generating " << n << " uniform [0,1] numbers: "
                          << std::setprecision(3);
                for (size_t i=0;i<n; ++i)
                    std::cout << ' ' << uniform();
                std::cout << std::endl;
            }
            else if (command=="GEN_UNIFORM_INT")
            {
                size_t n, a, b;
                if (!(input >> n >> a >> b))
                    throw std::runtime_error("Wrong command format.");
                std::cout << "Generating " << n << " uniform [" << a << ','
                          << b-1 << "] int numbers: ";
                for (size_t i=0;i<n; ++i)
                    std::cout << ' ' << pick_at_random(a, b);
                std::cout << std::endl;
            }
            else if (command=="LP_HASH")
            {
                std::uint64_t m, p, a, b, k;
                input >> m >> p >> a >> b >> k;
                if (!input)
                    throw std::runtime_error("Wrong command format.");
                LPHash hash (m, p, a, b);
                std::cout << "Hashing key " << k << " (linear probing):";
                for (size_t i=0;i<m; ++i)
                    std::cout << ' ' << hash(k, i);
                std::cout << std::endl;
            }
            else if (command=="QP_HASH")
            {
                std::uint64_t m, p, a, b, k;
                input >> m >> p >> a >> b >> k;
                if (!input)
                    throw std::runtime_error("Wrong command format.");
                QPHash hash (m, p, a, b);
                std::cout << "Hashing key " << k << " (quadratic probing):";
                for (size_t i=0;i<m; ++i)
                    std::cout << ' ' << hash(k, i);
                std::cout << std::endl;
            }
            else if (command=="RP_HASH")
            {
                std::uint64_t m, p, a, b, c, k;
                input >> m >> p >> a >> b >> c >> k;
                if (!input)
                    throw std::runtime_error("Wrong command format.");
                RPHash hash (m, p, a, b, c);
                std::cout << "Hashing key " << k << " (random probing):";
                for (size_t i=0;i<m; ++i)
                    std::cout << ' ' << hash(k, i);
                std::cout << std::endl;
            }
            else if (command=="R_HASH")
            {
                std::uint64_t m, p, k, n;
                input >> m >> p >> n;
                std::vector<std::uint64_t> a(n);
                std::vector<std::uint64_t> b(n);
                for (size_t i=0; i<n; ++i)
                    input >> a[i] >> b[i];
                input >> k;
                if (!input)
                    throw std::runtime_error("Wrong command format.");
                RHash hash (m, p, a, b);
                std::cout << "Hashing key " << k << " (rehasing probing):";
                for (size_t i=0;i<m; ++i)
                    std::cout << ' ' << hash(k, i);
                std::cout << std::endl;
            }
            else if (command=="D_HASH")
            {
                std::uint64_t m, p, k;
                input >> m >> p;
                std::vector<std::uint64_t> a(2);
                std::vector<std::uint64_t> b(2);
                for (size_t i=0; i<2; ++i)
                    input >> a[i] >> b[i];
                input >> k;
                if (!input)
                    throw std::runtime_error("Wrong command format.");
                DHash hash (m, p, a, b);
                std::cout << "Hashing key " << k << " (double hasing probing):";
                for (size_t i=0;i<m; ++i)
                    std::cout << ' ' << hash(k, i);
                std::cout << std::endl;
            }
            else
            {
                std::cerr << "Error: unkown command '" << command << "'." << std::endl;
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

