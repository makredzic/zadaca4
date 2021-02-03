#pragma once
#include <iostream>
#include <type_traits>
#include <initializer_list>
#include <stdexcept>

template<typename T>
class Matrica {
public:
  Matrica() = delete; 
  Matrica(size_t m, size_t n) : m_{m}, n_{n}, p_{new T[m*n]} {}  
  Matrica(std::initializer_list<T> a) 
    : m_{*std::begin(a)}, n_{*(std::begin(a)+1)}, p_{new T[m_*n_]} {
    if (m_*n_ < a.size()-2) throw std::domain_error("Previse elemenata proslijedjeno za te dimenzije");
    std::copy(std::begin(a)+2, std::end(a), p_); 
  }

  Matrica(const Matrica& drugi) : m_{drugi.m_}, n_{drugi.n_}, p_{new T[m_*n_]} {
    std::copy(drugi.p_, drugi.p_ + drugi.rows() + drugi.columns(), p_);
  }

  T operator()(const size_t&, const size_t&) const;
  T& operator()(const size_t&, const size_t&);

  template<typename U>
  Matrica& operator+=(const Matrica<U>&);

  template<typename U>
  Matrica& operator-=(const Matrica<U>&);
  
  template<typename U>
  Matrica& operator*=(const U&);

  template<typename U>
  Matrica& operator/=(const U&);

  size_t rows() const {return m_;};
  size_t columns() const {return n_;}

  ~Matrica() {delete [] p_;};

private:
  size_t m_;
  size_t n_;
  T* p_{nullptr};
};
