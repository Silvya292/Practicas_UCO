/**
 * @file hash.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include "hash.hpp"
#include <cassert>
#include <cstdlib>


double
uniform()
{
    double ret_v = 0.0;
    //TODO:
    //Hint: Use std::rand() trying to use all the random bits.
    ret_v=(double)rand()/(double)RAND_MAX;
    //
    assert(0.0<=ret_v && ret_v <1.0);
    return ret_v;
}


std::uint64_t
pick_at_random(std::uint64_t const& a, std::uint64_t const& b)
{
    assert(a<b);
    std::uint64_t ret_v = 0;
    //TODO:
    //Hint: use uniform()
    ret_v=(std::uint64_t)((b-a)*uniform())+a;
    //
    assert(a<=ret_v && ret_v<b);
    return  ret_v;
}

/**
 * @brief The universal hash function.
 * @param key is the value to hash.
 * @param m ,
 * @param p ,
 * @param a ,
 * @param b are the hashing parameters.
 * @return the hashed value.
 * @pre key<p
 * @post ret_v<m
 */
static inline size_t
universal_hash(std::uint64_t const& key, std::uint64_t const& m,
               std::uint64_t const& p, std::uint64_t const& a,
               std::uint64_t const& b)
{
    assert(key < p);
    size_t ret_v=0;
    //TODO:
    //Hint: use static_cast to static type conversions.
    ret_v=(size_t)((a*key+b)%p)%m;
    ret_v=(((key*a)+b)%p)%m;
    //
    assert(ret_v<m);
    return ret_v;
}

//////////////////////////////////////////////////////////////
// Linear Probing hash function.
//////////////////////////////////////////////////////////////

LPHash::LPHash(size_t m)
{
    assert(m>1 && (m & (m-1))==0);
    m_ = m;
    p_ = 4294967311l;
    a_ = pick_at_random(std::uint64_t(1), p_);
    b_ = pick_at_random(std::uint64_t(0), p_);
}

LPHash::Ref LPHash::create(size_t m)
{
    return std::make_shared<LPHash>(m);
}


LPHash::LPHash(size_t m, std::uint64_t p, std::uint64_t a,
               std::uint64_t b)
{
    assert(m>1 && (m & (m-1))==0);
    assert(0<a && a<p);
    assert(0<=b && b<p);
    assert(m<p);
    m_ = m;
    p_ = p;
    a_ = a;
    b_ = b;
}

LPHash::Ref LPHash::create(size_t m, std::uint64_t p, std::uint64_t a,
                  std::uint64_t b)
{
    return std::make_shared<LPHash>(m, p, a, b);
}

LPHash::Ref LPHash::pick_at_new(std::uint64_t const& m) const
{
    assert(m>1 && (m & (m-1))==0);
    LPHash::Ref new_f;
    new_f = LPHash::create(m, p_, pick_at_random(std::uint64_t(1), p_),
                           pick_at_random(std::uint64_t(0), p_));
    return new_f;
}



size_t
LPHash::operator()(const uint64_t &k, size_t iter) const
{
    size_t ret_v=0;
    //TODO:
    //Remeber: if iter == 0 (first attempt), compute the hash value.
    //         iter>0 means a collision happened so get the next proper value
    //         regarding the collision algorithm.
    //Hint: you could save the first value to avoid recompute it when
    //      a collision happened.
    ret_v=(universal_hash(k, m_, p_, a_, b_)+iter)%m_;
    //
    return ret_v;
}

//////////////////////////////////////////////////////////////
// Quadratic Probing hash function.
//////////////////////////////////////////////////////////////

QPHash::QPHash(size_t m)
{
    assert(m>1 && (m & (m-1))==0);
    m_ = m;
    p_ = 4294967311l;
    a_ = pick_at_random(std::uint64_t(1), p_);
    b_ = pick_at_random(std::uint64_t(0), p_);
}

QPHash::Ref QPHash::create(size_t m)
{
    return std::make_shared<QPHash>(m);
}


QPHash::QPHash(size_t m, std::uint64_t p, std::uint64_t a,
               std::uint64_t b)
{
    assert(m>1 && (m & (m-1))==0);
    assert(0<a && a<p);
    assert(0<=b && b<p);
    assert(m<p);
    m_ = m;
    p_ = p;
    a_ = a;
    b_ = b;
}

QPHash::Ref QPHash::create(size_t m, std::uint64_t p, std::uint64_t a,
                  std::uint64_t b)
{
    return std::make_shared<QPHash>(m, p, a, b);
}

QPHash::Ref QPHash::pick_at_new(std::uint64_t const& m) const
{
    assert(m>1 && (m & (m-1))==0);
    QPHash::Ref new_f;
    new_f = QPHash::create(m, p_, pick_at_random(std::uint64_t(1), p_),
                           pick_at_random(std::uint64_t(0), p_));
    return new_f;
}



size_t
QPHash::operator()(const uint64_t &k, size_t iter) const
{
    size_t ret_v=0;
    //TODO:
    //Remeber: if iter == 0 (first attempt), compute the hash value.
    //         iter>0 means a collision happened so get the next proper value
    //         regarding the collision algorithm.
    //Hint: you could save the first value to avoid recompute it when
    //      a collision happened.
    //Remember: m is two power and c1= c2 = 1/2.
    if(iter==0){
        ret_v=universal_hash(k, m_, p_, a_, b_);
    }
    else{
        ret_v=(size_t)(universal_hash(k, m_, p_, a_, b_)+(0.5*iter)+(0.5*iter*iter))%m_;
    }
    //
    return ret_v;
}

//////////////////////////////////////////////////////////////
// Random Probing hash function.
//////////////////////////////////////////////////////////////

#ifndef NDEBUG
/**
 * @brief Compute the greatest common divisor.
 * @param u and
 * @param v are the numbers to check.
 * @return the greatest common divisor.
 */
static std::uint64_t GCD(std::uint64_t u, std::uint64_t v)
{
    while (v != 0)
    {
        std::uint64_t r = u % v;
        u = v;
        v = r;
    }
    return u;
}
#endif

RPHash::RPHash(size_t m)
{
    assert(m>1 && (m & (m-1))==0);
    m_ = m;
    p_ = 4294967311l;
    a_ = pick_at_random(std::uint64_t(1), p_);
    b_ = pick_at_random(std::uint64_t(0), p_);
    c_ = m_/2-1;
}

RPHash::Ref RPHash::create(size_t m)
{
    return std::make_shared<RPHash>(m);
}


RPHash::RPHash(size_t m, std::uint64_t p, std::uint64_t a,
               std::uint64_t b, std::uint64_t c)
{
    assert(m>1 && (m & (m-1))==0);
    assert(m<p);
    assert(0<a && a<p);
    assert(0<=b && b<p);    
    assert(GCD(c, m)==1);
    m_ = m;
    p_ = p;
    a_ = a;
    b_ = b;
    c_ = c;
}

RPHash::Ref RPHash::create(size_t m, std::uint64_t p, std::uint64_t a,
                  std::uint64_t b, std::uint64_t c)
{
    return std::make_shared<RPHash>(m, p, a, b, c);
}

RPHash::Ref RPHash::pick_at_new(std::uint64_t const& m) const
{
    assert(m>1 && (m & (m-1))==0);
    RPHash::Ref new_f;
    new_f = RPHash::create(m, p_, pick_at_random(std::uint64_t(1), p_),
                           pick_at_random(std::uint64_t(0), p_), m/2-1);
    return new_f;
}

size_t
RPHash::operator()(const uint64_t &k, size_t iter) const
{
    size_t ret_v=0;
    //TODO:
    //Remeber: if iter == 0 (first attempt), compute the hash value.
    //         iter>0 means a collision happened so get the next proper value
    //         regarding the collision algorithm.
    //Hint: you could save the first value to avoid recompute it when
    //      a collision happened.
    if (iter == 0){
        ret_v = universal_hash(k, m_, p_, a_, b_);
    }
    else{
        ret_v = (universal_hash(k, m_, p_, a_, b_) + iter * c_) % m_;
    }
    //
    return ret_v;
}


//////////////////////////////////////////////////////////////
// Rehashing hash function.
//////////////////////////////////////////////////////////////

RHash::RHash(size_t m, size_t n)
{
    assert(m>1 && (m & (m-1))==0);
    p_ = 4294967311l;
    std::vector<std::uint64_t> a_(n);
    std::vector<std::uint64_t> b_(n);
    for (size_t i=0; i<n; ++i)
    {
        a_[i]=pick_at_random(std::uint64_t(1), p_);
        b_[i]=pick_at_random(std::uint64_t(0), p_);
    }
}

RHash::Ref RHash::create(size_t m, size_t n)
{
    return std::make_shared<RHash>(m, n);
}


RHash::RHash(size_t m, std::uint64_t p,
             std::vector<std::uint64_t> const& a,
               std::vector<std::uint64_t> const& b)
{
#ifndef NDEBUG
    assert(m>1 && (m & (m-1))==0);
    assert(a.size()>1 && a.size()==b.size());
    assert(m<p);
    for (size_t i = 0; i<a.size();++i)
    {
        assert(0<a[i] && a[i]<p);
        assert(0<=b[i] && b[i]<p);
    }
#endif
    m_ = m;
    p_ = p;
    a_ = a;
    b_ = b;    
}

RHash::Ref
RHash::create(size_t m, std::uint64_t p,
              std::vector<std::uint64_t> const& a,
                std::vector<std::uint64_t> const& b)
{
    return std::make_shared<RHash>(m, p, a, b);
}

RHash::Ref RHash::pick_at_new(std::uint64_t const& m) const
{
    assert(m>1 && (m & (m-1))==0);
    RHash::Ref new_f;
    std::vector<std::uint64_t> new_a(a_.size());
    std::vector<std::uint64_t> new_b(b_.size());
    for (size_t i=0; i<a_.size(); ++i)
    {
        new_a[i]=pick_at_random(std::uint64_t(1), p_);
        new_b[i]=pick_at_random(std::uint64_t(0), p_);
    }
    new_f = RHash::create(m, p_, new_a, new_b);
    return new_f;
}



size_t
RHash::operator()(const uint64_t &k, size_t iter) const
{
    size_t ret_v=0;
    //TODO:
    //Remeber: if iter == 0 (first attempt), compute the hash value.
    //         iter>0 means a collision happened so get the next proper value
    //         regarding the collision algorithm.
    //Rember: we use n hash fucntions to resolve the colisión or continue with
    //        linear probing from the last computed value if it is needed.
    if (iter == 0){
        ret_v = universal_hash(k, m_, p_, a_[0], b_[0]);
    }
    else if (iter < a_.size()){
        ret_v = (universal_hash(k, m_, p_, a_[iter], b_[iter])) % m_;
    }
    else{
        ret_v = (universal_hash(k, m_, p_, a_[a_.size() - 1], b_[b_.size() - 1]) + iter - a_.size() + 1) % m_;
    }
    //
    return ret_v;
}

//////////////////////////////////////////////////////////////
// Double hashing hash function.
//////////////////////////////////////////////////////////////

DHash::DHash(size_t m)
{
    assert(m>1 && (m & (m-1))==0);
    p_ = 4294967311l;
    std::vector<std::uint64_t> a_(2);
    std::vector<std::uint64_t> b_(2);
    for (size_t i=0; i<2; ++i)
    {
        a_[i]=pick_at_random(std::uint64_t(1), p_);
        b_[i]=pick_at_random(std::uint64_t(0), p_);
    }
}

DHash::Ref DHash::create(size_t m)
{
    return std::make_shared<DHash>(m);
}


DHash::DHash(size_t m, std::uint64_t p,
             std::vector<std::uint64_t> const& a,
               std::vector<std::uint64_t> const& b)
{
#ifndef NDEBUG
    assert(m>1 && (m & (m-1))==0);
    assert(a.size()==2 && a.size()==b.size());
    assert(m<p);
    for (size_t i = 0; i<a.size();++i)
    {
        assert(0<a[i] && a[i]<p);
        assert(0<=b[i] && b[i]<p);
    }
#endif
    m_ = m;
    p_ = p;
    a_ = a;
    b_ = b;
}

DHash::Ref
DHash::create(size_t m, std::uint64_t p,
              std::vector<std::uint64_t> const& a,
                std::vector<std::uint64_t> const& b)
{
    return std::make_shared<DHash>(m, p, a, b);
}

DHash::Ref DHash::pick_at_new(std::uint64_t const& m) const
{
    assert(m>1 && (m & (m-1))==0);
    DHash::Ref new_f;
    std::vector<std::uint64_t> new_a(a_.size());
    std::vector<std::uint64_t> new_b(b_.size());
    for (size_t i=0; i<a_.size(); ++i)
    {
        new_a[i]=pick_at_random(std::uint64_t(1), p_);
        new_b[i]=pick_at_random(std::uint64_t(0), p_);
    }
    new_f = DHash::create(m, p_, new_a, new_b);
    return new_f;
}



size_t
DHash::operator()(const uint64_t &k, size_t iter) const
{
    size_t ret_v=0;
    //TODO:
    //Remenber: if iter == 0 (first attempt), compute the hash value.
    //         iter>0 means a collision happened so get the next proper value
    //         regarding the collision algorithm.
    //Remenber: we use n hash fucntions to resolve the colisión or continue with
    //        linear probing from the last computed value if it is needed.
    if (iter == 0){
        ret_v = universal_hash(k, m_, p_, a_[0], b_[0]);
    }
    else{
        ret_v = (universal_hash(k, m_, p_, a_[0], b_[0]) + iter * universal_hash(k, m_, p_, a_[1], b_[1])) % m_;
    }
    //
    return ret_v;
}

