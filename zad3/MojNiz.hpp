#pragma once
#include <algorithm>
#include <initializer_list>

template <typename T>
class MojNiz {
  public:

    MojNiz() : c_{1}, n_{0}, p_{new T[1]} {};
    MojNiz(std::initializer_list<T> a) : c_{a.size()}, n_{a.size()}, p_{new T[n_]} {std::copy(std::begin(a), std::end(a), p_);}

    MojNiz(const MojNiz<T>&); //copy konstruktor
    MojNiz(MojNiz<T>&& drugi); //move-copy konstruktor

    MojNiz& operator=(const MojNiz<T>&); //copy jednako
    MojNiz& operator=(MojNiz<T>&&); 

    ~MojNiz() {delete[] p_;}; //destruktor
    size_t size() const {return n_;} 
    size_t capacity() const {return c_;}

    T at(const int& i) const;
    T& at(const int& i); //ovo je potrebno kako bi se moglo promijeniti vrijednost sa at

    T& operator[](const size_t& i) const {return p_[i];};

    MojNiz& operator*=(const T& i) {for(size_t j =0; j<n_; j++) p_[j]*=i; return *this;};
    MojNiz& operator+=(const MojNiz&);

    MojNiz operator++(int); //postfix++ il ti ga sufix
    MojNiz& operator++(); //++prefix

    void push_back(const T&);
    void pop_back() {n_-=1;};

    T& front();
    T& back(); 
  
  private:
    size_t c_;
    size_t n_;
    T* p_;
};

/* OVO nisam siguran jel treba nit kako treba pa cu zakomentarisat za sad
template<typename T>
MojNiz<T> operator*(MojNiz<T>, const T&);

template<typename T>
MojNiz<T> operator*(const T&, MojNiz<T>);

template<typename T>
MojNiz<T> operator+(MojNiz<T>, const MojNiz<T>& drugi);
*/
