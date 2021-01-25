#include "MojNiz.hpp"
#include <stdexcept>
#include <vector>

int MojNiz::at(const int &i) const {
  if (i < 0 || i > int(n_)-1) throw std::out_of_range("Pokusaj pristupa kontejneru van granica");
  return *(p_+i);
}

int& MojNiz::at(const int &i) {
  if (i < 0 || i > int(n_)-1) throw std::out_of_range("Pokusaj pristupa kontejneru van granica");
  return *(p_+i);
}

MojNiz::MojNiz(const MojNiz &drugi) 
  : c_{drugi.c_}, n_{drugi.n_}, p_{new int[c_]} {

  std::copy(drugi.p_, drugi.p_ + drugi.n_, p_);

}

MojNiz::MojNiz(MojNiz&& drugi) 
  : c_{drugi.c_},  n_{drugi.n_}, p_{drugi.p_} {
  drugi.p_ = nullptr; 
  drugi.n_ = 0; 
  drugi.c_ = 0;
}

MojNiz& MojNiz::operator=(const MojNiz& drugi) {
  if (this == &drugi) return *this;

  delete [] p_;

  n_ = drugi.n_; 
  c_ = drugi.c_;
  p_ = new int[c_];

  std::copy(drugi.p_, drugi.p_ + drugi.n_, p_);
  return *this;
}

MojNiz& MojNiz::operator=(MojNiz&& drugi) { 
  delete [] p_;

  n_ = drugi.n_;
  p_ = drugi.p_;
  c_ = drugi.c_;
  
  drugi.p_ = nullptr;
  drugi.n_ = 0;
  drugi.c_ = 0;

  return *this;
}

MojNiz operator*(MojNiz a, const int& i) {
  a*=i; 
  return a; 
}

MojNiz operator*(const int& i, MojNiz a) {
  a*=i;
  return a;
}

MojNiz& MojNiz::operator+=(const MojNiz& drugi) {
  if (n_ != drugi.n_) throw std::invalid_argument("Nizovi koji ucestvuju u operacij sabiranja moraju biti iste duzine");
  for (size_t i = 0; i < n_; i++) p_[i] += drugi.p_[i]; 
  return *this;
}

MojNiz operator+(MojNiz a, const MojNiz& drugi) {
  try {
    a+=drugi;
  } catch(const std::invalid_argument& e) {
    throw e; //ne znam sad ni sta cu s ovim ali mislim da nije ni bitno trenutno
  }
  return a;
}

MojNiz MojNiz::operator++(int) {
  MojNiz drugi{*this};
  for (size_t i = 0; i<n_; i++) p_[i] += 1;
  return drugi;
}

MojNiz& MojNiz::operator++() {
  for (size_t i = 0; i < n_; i++) p_[i]+=1;
  return *this;
}

void MojNiz::push_back(const int& k) {

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

int& MojNiz::front() {

  return p_[0];
}

int& MojNiz::back() {

  return p_[n_-1]; //p_[n_] bi vratilo referncu na jedan elemenat van kontejnera
}

