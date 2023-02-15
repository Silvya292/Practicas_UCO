/**
 * @file hash.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#pragma once
#include <cstddef> //for size_t
#include <cstdint> //for uint64_t
#include <memory>
#include <vector>

/**
 * @brief Generate an uniform random number in [0.0, 1.0) interval.
 * @return the random number.
 * @post ret_v in [0.0, 1.0)
 */
double uniform();

/**
 * @brief pick at random a value from the integer range [a,b).
 * @param a is lower bound of the range (inclusive).
 * @param b is upper bound of the range (exclusive).
 * @return the picked up value.
 * @prec a<b
 * @post ret_v in [a,b)
 */
std::uint64_t pick_at_random(std::uint64_t const& a, std::uint64_t const& b);

/**
 * @brief Models an Universal Family hash function using
 *        linear probing to resolve collisions.
 */
class LPHash
{
public:

    /**
     * @brief A reference to a hash function.
     */
    typedef std::shared_ptr<LPHash> Ref;
    /** @name Life cicle. */
    /** @{ */

    /**
     * @brief Create a hash function picked at random from Universal Family.
     * The p parameter used is 4294967311
     * @param m is the table size.
     * @pre m is power of two greater than 1.
     */
    LPHash(size_t m);

    /**
     * @brief Create a hash function picked at random from Universal Family.
     * The p parameter used is 4294967311
     * @param m is the table size.
     * @return a reference to the function.
     * @pre m is power of two greater than 1.
     */
    static Ref create(size_t m);

    /**
     * @brief Create a hash function.
     * @param m is the table size.
     * @param p ,
     * @param a ,
     * @param b are the parameters of the Universal hash function.
     * @pre m is power of two greater than 1.
     * @pre m<p
     * @pre p is prime number.
     * @pre 1<=a<p
     * @pre 0<=b<p
     */
    LPHash(size_t m, std::uint64_t p, std::uint64_t a, std::uint64_t b);

    /**
     * @brief Create a hash function.
     * @param m is the table size.
     * @param p ,
     * @param a ,
     * @param b are the parameters of the Universal hash function.
     * @pre m is power of two greater than 1.
     * @pre m<p
     * @pre p is prime number.
     * @pre 1<=a<p-1
     * @pre 0<=b<p-1
     */
    static Ref create(std::uint64_t m, std::uint64_t p, std::uint64_t a,
                      std::uint64_t b);



    /** @} */

    /** @name Observers. */
    /** @} */

    /**
     * @brief Create a new hash function pick up at random from de Universal
     *        Familiy.
     * @param m is the new table size.
     * @return a reference a to the new hash function.
     * @pre m is power of two greater than 1.
     */
    Ref pick_at_new(std::uint64_t const& m) const;


    /**
     * @brief hash a key value k.
     * Hash the key to get a table index.
     * @param k is the key to be hashed.
     * @param iter is the number of conflicts generates upto now.
     * @return the table index.
     * @post iter==0 implies ret_v is the universal hash function for integers.
     * @post iter>0 and ret_v is the next value of the collision resolution
     *       algorithm.
    */
    size_t operator()(std::uint64_t const& k, size_t iter=0) const;

    /** @} */
protected:

    std::uint64_t m_;
    std::uint64_t p_;
    std::uint64_t a_;
    std::uint64_t b_;
};


/**
 * @brief Models an Universal Family hash function using
 *        quadratic probing to resolve collisions.
 *
 *        This function assume that the table sizie is two power and
 *        the parameters c1=c2=0.5
 */
class QPHash
{
public:

    /**
     * @brief A reference to a hash function.
     */
    typedef std::shared_ptr<QPHash> Ref;
    /** @name Life cicle. */
    /** @{ */

    /**
     * @brief Create a hash function picked at random from Universal Family.
     * The p parameter used is 4294967311
     * @param m is the table size.
     * @pre m is power of two greater than 1.
     */
    QPHash(size_t m);

    /**
     * @brief Create a hash function picked at random from Universal Family.
     * The p parameter used is 4294967311
     * @param m is the table size.
     * @return a reference to the function.
     * @pre m is power of two greater than 1.
     */
    static Ref create(size_t m);

    /**
     * @brief Create a hash function.
     * @param m is the table size.
     * @param p ,
     * @param a ,
     * @param b are the parameters of the Universal hash function.
     * @pre m is power of two greater than 1.
     * @pre m<p
     * @pre p is prime number.
     * @pre 1<=a<p
     * @pre 0<=b<p
     * @pre m is two power.
     */
    QPHash(size_t m, std::uint64_t p, std::uint64_t a, std::uint64_t b);

    /**
     * @brief Create a hash function.
     * @param m is the table size.
     * @param p ,
     * @param a ,
     * @param b are the parameters of the Universal hash function.
     * @pre m is power of two greater than 1.
     * @pre m<p
     * @pre p is prime number.
     * @pre 1<=a<p-1
     * @pre 0<=b<p-1
     * @pre m is two power.
     */
    static Ref create(std::uint64_t m, std::uint64_t p, std::uint64_t a,
                      std::uint64_t b);



    /** @} */

    /** @name Observers. */
    /** @} */

    /**
     * @brief Create a new hash function pick up at random from de Universal
     *        Familiy.
     * @param m is the new table size.
     * @return a reference a to the new hash function.
     * @pre m is power of two greater than 1.
     */
    Ref pick_at_new(std::uint64_t const& m) const;


    /**
     * @brief hash a key value k.
     * Hash the key to get a table index.
     * @param k is the key to be hashed.
     * @param iter is the number of conflicts generates upto now.
     * @return the table index.
     * @post iter==0 implies ret_v is the universal hash function for integers.
     * @post iter>0 and ret_v is the next value of the collision resolution
     *       algorithm.
    */
    size_t operator()(std::uint64_t const& k, size_t iter=0) const;

    /** @} */
protected:

    std::uint64_t m_;
    std::uint64_t p_;
    std::uint64_t a_;
    std::uint64_t b_;
};

/**
 * @brief Models an Universal Family hash function using
 *        random probing to resolve collisions.
 */
class RPHash
{
public:

    /**
     * @brief A reference to a hash function.
     */
    typedef std::shared_ptr<RPHash> Ref;
    /** @name Life cicle. */
    /** @{ */

    /**
     * @brief Create a hash function picked at random from Universal Family.
     * The p parameter used is 4294967311
     * @param m is the table size.
     */
    RPHash(size_t m);

    /**
     * @brief Create a hash function picked at random from Universal Family.
     * The p parameter used is 4294967311
     * @param m is the table size.
     * @return a reference to the function.
     * @pre m is power of two greater than 1.
     */
    static Ref create(size_t m);

    /**
     * @brief Create a hash function.
     * @param m is the table size.
     * @param p ,
     * @param a ,
     * @param b ,
     * @param c are the parameters of the Universal hash function.
     * @pre m is power of two greater than 1.
     * @pre m<p
     * @pre p is prime number.
     * @pre 1<=a<p
     * @pre 0<=b<p
     * @pre c and m are relative primes.
     */
    RPHash(size_t m, std::uint64_t p, std::uint64_t a, std::uint64_t b,
           std::uint64_t c);

    /**
     * @brief Create a hash function.
     * @param m is the table size.
     * @param p ,
     * @param a ,
     * @param b ,
     * @param c are the parameters of the Universal hash function.
     * @pre m is power of two greater than 1.
     * @pre m<p
     * @pre p is prime number.
     * @pre 1<=a<p-1
     * @pre 0<=b<p-1
     * @pre c and m are relative primes.
     */
    static Ref create(std::uint64_t m, std::uint64_t p, std::uint64_t a,
                      std::uint64_t b, std::uint64_t c);



    /** @} */

    /** @name Observers. */
    /** @} */

    /**
     * @brief Create a new hash function pick up at random from de Universal
     *        Familiy.
     * @param m is the new table size.
     * @return a reference a to the new hash function.
     * @pre m is power of two greater than 1.
     */
    Ref pick_at_new(std::uint64_t const& m) const;


    /**
     * @brief hash a key value k.
     * Hash the key to get a table index.
     * @param k is the key to be hashed.
     * @param iter is the number of conflicts generates upto now.
     * @return the table index.
     * @post iter==0 implies ret_v is the universal hash function for integers.
     * @post iter>0 and ret_v is the next value of the collision resolution
     *       algorithm.
    */
    size_t operator()(std::uint64_t const& k, size_t iter=0) const;

    /** @} */
protected:

    std::uint64_t m_;
    std::uint64_t p_;
    std::uint64_t a_;
    std::uint64_t b_;
    std::uint64_t c_;
};


/**
 * @brief Models an Universal Family hash function using
 *        rehashing to resolve collisions.
 *
 * @warning The linear probing will be used if the last hash function collides.
 */
class RHash
{
public:

    /**
     * @brief A reference to a hash function.
     */
    typedef std::shared_ptr<RHash> Ref;
    /** @name Life cicle. */
    /** @{ */

    /**
     * @brief Create a hash function picked at random from Universal Family.
     * The p parameter used is 4294967311
     * @param m is the table size.
     * @param n is the number of hash functions created to rehashing.
     * @pre m is power of two greater than 1.
     */
    RHash(size_t m, size_t n);

    /**
     * @brief Create a hash function picked at random from Universal Family.
     * The p parameter used is 4294967311
     * @param m is the table size.
     * @param n is the number of hash functions created to rehashing.
     * @return a reference to the function.
     * @pre m is power of two greater than 1.
     */
    static Ref create(size_t m, size_t n);

    /**
     * @brief Create a hash function.
     * @param m is the table size.
     * @param p ,
     * @param a ,
     * @param b are the parameters of the Universal hash functions.
     * @pre a.size()>1 && a.size()==b.size()
     * @pre m is power of two greater than 1.
     * @pre m<p
     * @pre p is prime number.
     * @pre 1<=a[i]<p, for each i.
     * @pre 0<=b[i]<p, for each i.
     */
    RHash(size_t m, std::uint64_t p, std::vector<std::uint64_t> const& a,
          std::vector<std::uint64_t>const& b);

    /**
     * @brief Create a hash function.
     * @param m is the table size.
     * @param p ,
     * @param a ,
     * @param b are the parameters of the Universal hash functions.
     * @pre m is power of two greater than 1.
     * @pre a.size()>1 && a.size()==b.size()
     * @pre m<p
     * @pre p is prime number.
     * @pre 1<=a[i]<p, for each i.
     * @pre 0<=b[i]<p, for each i.
     */
    static Ref create(size_t m, std::uint64_t p,
                      std::vector<std::uint64_t> const& a,
                      std::vector<std::uint64_t>const& b);



    /** @} */

    /** @name Observers. */
    /** @} */

    /**
     * @brief Create a new hash function pick up at random from de Universal
     *        Familiy.
     * @param m is the new table size.
     * @return a reference a to the new hash function.
     * @pre m is power of two greater than 1.
     */
    Ref pick_at_new(std::uint64_t const& m) const;


    /**
     * @brief hash a key value k.
     * Hash the key to get a table index.
     * @param k is the key to be hashed.
     * @param iter is the number of conflicts generates upto now.
     * @return the table index.
     * @post iter==0 implies ret_v is the universal hash function for integers.
     * @post iter>0 and ret_v is the next value of the collision resolution
     *       algorithm.
    */
    size_t operator()(std::uint64_t const& k, size_t iter=0) const;

    /** @} */
protected:

    std::uint64_t m_;
    std::uint64_t p_;
    std::vector<std::uint64_t> a_;
    std::vector<std::uint64_t> b_;
};


/**
 * @brief Models an Universal Family hash function using
 *        double hashing to resolve collisions.
 *
 */
class DHash
{
public:

    /**
     * @brief A reference to a hash function.
     */
    typedef std::shared_ptr<DHash> Ref;
    /** @name Life cicle. */
    /** @{ */

    /**
     * @brief Create a hash function picked at random from Universal Family.
     * The p parameter used is 4294967311
     * @param m is the table size.
     * @pre m is power of two greater than 1.
     */
    DHash(size_t m);

    /**
     * @brief Create a hash function picked at random from Universal Family.
     * The p parameter used is 4294967311
     * @param m is the table size.
     * @return a reference to the function.
     * @pre m is power of two greater than 1.
     */
    static Ref create(size_t m);

    /**
     * @brief Create a hash function.
     * @param m is the table size.
     * @param p ,
     * @param a ,
     * @param b are the parameters of the Universal hash functions.
     * @pre a.size()==2 && a.size()==b.size()
     * @pre m<p
     * @pre m is power of two greater than 1.
     * @pre p is prime number.
     * @pre 1<=a[i]<p, for each i.
     * @pre 0<=b[i]<p, for each i.
     */
    DHash(size_t m, std::uint64_t p, std::vector<std::uint64_t> const& a,
          std::vector<std::uint64_t>const& b);

    /**
     * @brief Create a hash function.
     * @param m is the table size.
     * @param p ,
     * @param a ,
     * @param b are the parameters of the Universal hash functions.
     * @pre a.size()==2 && a.size()==b.size()
     * @pre m<p
     * @pre m is power of two greater than 1.
     * @pre p is prime number.
     * @pre 1<=a[i]<p, for each i.
     * @pre 0<=b[i]<p, for each i.
     */
    static Ref create(size_t m, std::uint64_t p,
                      std::vector<std::uint64_t> const& a,
                      std::vector<std::uint64_t>const& b);



    /** @} */

    /** @name Observers. */
    /** @} */

    /**
     * @brief Create a new hash function pick up at random from de Universal
     *        Familiy.
     * @param m is the new table size.
     * @return a reference a to the new hash function.
     * @pre m is power of two greater than 1.
     */
    Ref pick_at_new(std::uint64_t const& m) const;


    /**
     * @brief hash a key value k.
     * Hash the key to get a table index.
     * @param k is the key to be hashed.
     * @param iter is the number of conflicts generates upto now.
     * @return the table index.
     * @post iter==0 implies ret_v is the universal hash function for integers.
     * @post iter>0 and ret_v is the next value of the collision resolution
     *       algorithm.
    */
    size_t operator()(std::uint64_t const& k, size_t iter=0) const;

    /** @} */
protected:

    std::uint64_t m_;
    std::uint64_t p_;
    std::vector<std::uint64_t> a_;
    std::vector<std::uint64_t> b_;
};
