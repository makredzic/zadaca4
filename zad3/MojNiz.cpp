#include "MojNiz.hpp"
#include <stdexcept>
#include <vector>

template <typename T>
T MojNiz<T>::at(const int &i) const {
  if (i < 0 || i > int(n_)-1) throw std::out_of_range("Pokusaj pristupa kontejneru van granica");
  return *(p_+i);
}

template<typename T>
T& MojNiz<T>::at(const int &i) {
  if (i < 0 || i > int(n_)-1) throw std::out_of_range("Pokusaj pristupa kontejneru van granica");
  return *(p_+i);
}

template<typename T>
MojNiz<T>::MojNiz(const MojNiz &drugi) 
  : c_{drugi.c_}, n_{drugi.n_}, p_{new int[c_]} {

  std::copy(drugi.p_, drugi.p_ + drugi.n_, p_);

}

template<typename T>
MojNiz<T>::MojNiz(MojNiz&& drugi) 
  : c_{drugi.c_},  n_{drugi.n_}, p_{drugi.p_} {
  drugi.p_ = nullptr; 
  drugi.n_ = 0; 
  drugi.c_ = 0;
}

template<typename T>
MojNiz<T>& MojNiz<T>::operator=(const MojNiz& drugi) {
  if (this == &drugi) return *this;

  delete [] p_;

  n_ = drugi.n_; 
  c_ = drugi.c_;
  p_ = new int[c_];

  std::copy(drugi.p_, drugi.p_ + drugi.n_, p_);
  return *this;
}

template<typename T>
MojNiz<T>& MojNiz<T>::operator=(MojNiz&& drugi) { 
  delete [] p_;

  n_ = drugi.n_;
  p_ = drugi.p_;
  c_ = drugi.c_;
  
  drugi.p_ = nullptr;
  drugi.n_ = 0;
  drugi.c_ = 0;

  return *this;
}

template<typename T>
MojNiz<T> operator*(MojNiz<T> a, const int& i) {
  a*=i; 
  return a; 
}

template<typename T>
MojNiz<T> operator*(const int& i, MojNiz<T> a) {
  a*=i;
  return a;
}

template<typename T>
MojNiz<T>& MojNiz<T>::operator+=(const MojNiz& drugi) {
  if (n_ != drugi.n_) throw std::invalid_argument("Nizovi koji ucestvuju u operacij sabiranja moraju biti iste duzine");
  for (size_t i = 0; i < n_; i++) p_[i] += drugi.p_[i]; 
  return *this;
}

template <typename T>
MojNiz<T> operator+(MojNiz<T> a, const MojNiz<T>& drugi) {
  try {
    a+=drugi;
  } catch(const std::invalid_argument& e) {
    throw e; //ne znam sad ni sta cu s ovim ali mislim da nije ni bitno trenutno
  }
  return a;
}

template<typename T>
MojNiz<T> MojNiz<T>::operator++(int) {
  MojNiz drugi{*this};
  for (size_t i = 0; i<n_; i++) p_[i] += 1;
  return drugi;
}

template<typename T>
MojNiz<T>& MojNiz<T>::operator++() {
  for (size_t i = 0; i < n_; i++) p_[i]+=1;
  return *this;
}

template<typename T>
void MojNiz<T>::push_back(const T& k) {

  if (capacity() < size()+1) {//ako se predje preko kapaciteta dodavanjem 1 novog elementa
    int* p2 = new int[size()*2];
    c_ *= 2;

    std::copy(p_, p_+n_, p2);
    delete[] p_; 

    p_ = p2; 
    p2 = nullptr;  
  } 

  p_[n_++] = k; 

}

template<typename T>
T& MojNiz<T>::front() {
  return p_[0];
}

template<typename T>
T& MojNiz<T>::back() {
  return p_[n_-1]; //p_[n_] bi vratilo referncu na jedan elemenat van kontejnera
}

