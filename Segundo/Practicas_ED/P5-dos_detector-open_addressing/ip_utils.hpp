/**
 * @file ip_utils.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#pragma once

#include <cstdint>
#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <memory>

/**
 * @brief Represent a IPv4 address.
 */
struct IP
{
    /**
     * @brief Default constructor.
     */
    IP():
        bytes({0, 0, 0, 0})
    {}
    /**
     * @brief Constructor.
     */
    IP(std::uint8_t a, std::uint8_t b, std::uint8_t c, std::uint8_t d)
    {
        bytes = {a, b, c, d};
    }

    /**
     * @brief Is b ip address b equal to this?.
     */
    bool operator == (IP const& b) const
    {
        return bytes == b.bytes;
    }

    /**
     * @brief Is b ip address b less than this?
     * A lexicographical order is check.
     */
    bool operator < (IP const& b) const
    {
        return bytes < b.bytes;
    }

    /**
     * The ip bytes so 150.214.110.3 are
     * bytes[0]=150, bytes[1]=214, bytes[2]=110, bytes[3]=3
     */
    std::array<std::uint8_t, 4> bytes;
};

/**
 * @brief output a ip in text format.
 */
std::ostream& operator<< (std::ostream& out, const IP& ip);

/**
 * @brief load an IPv4 address from a text input stream.
 * @throw std::runtime_error("Ip: wrong input format.") in case of input error.
 */
std::istream& operator>> (std::istream& in, IP& ip) noexcept(false);

/**
 * @brief Functional class to convert a ipaddress into a std::uint64_t.
 */
class IpToInt
{
public:
    /** @brief A shared reference to a IpToInt conversor.*/
    typedef std::shared_ptr<IpToInt> Ref;

    /**
     * @brief Virtual constructor.
     * @return a reference to the conversor.
     */
    static Ref create();

    /**
     * @brief Transform IPv4 addresses into std::uint64_t.
     * We apply a modified PolyHash with x=2^8 without using module operation
     * that means using a p>2^32.
     * i.e. 150.214.117.3 -> 150*2^24+214*2^16+2^8*117+3
     * @return The corresponding std::uint64_t.
     */
    std::uint64_t operator() (const IP& ip) const;
};
