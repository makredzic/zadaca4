#pragma once
#include <algorithm>
#include <initializer_list>
#include <stdexcept>
#include <vector>
#include <type_traits>

template <typename T>
class MojNiz {
  public:

    MojNiz(size_t cap = 1) : c_{cap}, n_{0}, p_{new T[cap]} {};
    MojNiz(std::initializer_list<T> a) : c_{a.size()}, n_{a.size()}, p_{new T[n_]} {std::copy(std::begin(a), std::end(a), p_);}

    template<typename U>
    MojNiz(const MojNiz<U>&); //copy konstruktor
    MojNiz(MojNiz<T>&& drugi); //move-copy konstruktor

    template<typename U>
    MojNiz& operator=(const MojNiz<U>&); //copy jednako
    MojNiz& operator=(MojNiz<T>&&); 

    ~MojNiz() {delete[] p_;}; //destruktor
    size_t size() const {return n_;} 
    size_t capacity() const {return c_;}

    T at(const int& i) const;
    T& at(const int& i); //ovo je potrebno kako bi se moglo promijeniti vrijednost sa at

    T& operator[](const size_t& i) const {return p_[i];};

    MojNiz& operator*=(const T& i) {for(size_t j =0; j<n_; j++) p_[j]*=i; return *this;};
    
    template<typename U>
    MojNiz& operator+=(const MojNiz<U>&);

    MojNiz operator++(int); //postfix++ il ti ga sufix
    MojNiz& operator++(); //++prefix

    void push_back(const T&);
    void pop_back() {n_-=1;};

    T& front() {return p_[0];};
    T& back() {return p_[n_-1];}; 
    T& front() const {return p_[0];};
    T& back() const {return p_[n_-1];}; 
  
    size_t c_;
    size_t n_;
    T* p_;
};
