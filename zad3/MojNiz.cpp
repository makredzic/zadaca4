#include "MojNiz.hpp"

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
template<typename U>
MojNiz<T>::MojNiz(const MojNiz<U> &drugi) 
  : c_{drugi.capacity()}, n_{drugi.size()}, p_{new T[c_]} {

  for (size_t i = 0; i < drugi.size(); i++) p_[i] = T(drugi[i]);
}

template<typename T>
MojNiz<T>::MojNiz(MojNiz&& drugi) 
  : c_{drugi.c_},  n_{drugi.n_}, p_{drugi.p_} {
  drugi.p_ = nullptr; 
  drugi.n_ = 0; 
  drugi.c_ = 0;
}

template<typename T>
template<typename U>
MojNiz<T>& MojNiz<T>::operator=(const MojNiz<U>& drugi) {
  if (std::is_same<T, U>::value && this == (MojNiz<T>*) &drugi) return *this;

  delete [] p_;

  n_ = drugi.size(); 
  c_ = drugi.capacity();
  p_ = new T[c_];

  for (size_t i = 0; i < drugi.size(); i++) p_[i] = T(drugi[i]);
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
template<typename U>
MojNiz<T>& MojNiz<T>::operator+=(const MojNiz<U>& drugi) {
  if (n_ != drugi.n_) throw std::invalid_argument("Nizovi koji ucestvuju u operacij sabiranja moraju biti iste duzine");

  for (size_t i = 0; i < n_; i++) p_[i] += drugi.p_[i]; 
  return *this;

}

template <typename T, typename U>
auto operator+(const MojNiz<T>& a, const MojNiz<U>& drugi) {
  if (a.size() != drugi.size()) throw std::invalid_argument("Nizovi koji ucestvuju u operacij sabiranja moraju biti iste duzine");

  MojNiz<decltype(a.front() + drugi.front())> rezultat(a.size()); 

  for (size_t i = 0; i < a.size(); i++) rezultat[i] = a[i] + drugi[i]; 
  return rezultat;
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
    T* p2 = new T[size()*2];
    c_ *= 2;

    std::copy(p_, p_+n_, p2);
    delete[] p_; 

    p_ = p2; 
    p2 = nullptr;  
  } 

  p_[n_++] = k; 

}
