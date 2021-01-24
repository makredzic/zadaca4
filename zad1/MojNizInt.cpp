#include "MojNizInt.hpp"
#include <stdexcept>
#include <vector>

int MojNizInt::at(const int &i) const {
  if (i < 0 || i > int(n_)-1) throw std::out_of_range("Pokusaj pristupa kontejneru van granica");
  return *(p_+i);
}

int& MojNizInt::at(const int &i) {
  if (i < 0 || i > int(n_)-1) throw std::out_of_range("Pokusaj pristupa kontejneru van granica");
  return *(p_+i);
}

MojNizInt::MojNizInt(const MojNizInt &drugi) : n_{drugi.n_}, p_{new int[n_]} {
  std::copy(drugi.p_, drugi.p_ + drugi.n_, p_);
}

MojNizInt::MojNizInt(MojNizInt&& drugi) : n_{drugi.n_}, p_{drugi.p_} {
  drugi.p_ = nullptr; 
  //drugi.p_ pokazuje na svoje clanove na heapu kao i novi p_
  //okidanjem destruktora od rvalue MojNizInt-a koji je proslijedjen ovdje
  //uzrokovat ce da se izbrise memorija na koju pokazuje drugi.p_
  //zato se ovdje drugi.p_ seta na nullptr
  drugi.n_ = 0; //ovo je possibly bespotrebno
}

MojNizInt& MojNizInt::operator=(const MojNizInt& drugi) {
  if (this == &drugi) return *this;

  delete [] p_;
  n_ = drugi.n_; 
  p_ = new int[n_];
  std::copy(drugi.p_, drugi.p_ + drugi.n_, p_);
  return *this;
}

MojNizInt& MojNizInt::operator=(MojNizInt&& drugi) { 
  delete [] p_;

  n_ = drugi.n_;
  p_ = drugi.p_;
  
  drugi.p_ = nullptr;
  drugi.n_ = 0; //mozda potpuno bespotrebno

  return *this;
}

MojNizInt operator*(MojNizInt a, const int& i) {
  a*=i; 
  return a; 
}

MojNizInt operator*(const int& i, MojNizInt a) {
  a*=i;
  return a;
}

MojNizInt& MojNizInt::operator+=(const MojNizInt& drugi) {
  if (n_ != drugi.n_) throw std::invalid_argument("Nizovi koji ucestvuju u operacij sabiranja moraju biti iste duzine");
  for (size_t i = 0; i < n_; i++) p_[i] += drugi.p_[i]; 
  return *this;
}

MojNizInt operator+(MojNizInt a, const MojNizInt& drugi) {
  try {
    a+=drugi;
  } catch(const std::invalid_argument& e) {
    throw e; //ne znam sad ni sta cu s ovim ali mislim da nije ni bitno trenutno
  }
  return a;
}

MojNizInt MojNizInt::operator++(int) {
  MojNizInt drugi{*this};
  for (size_t i = 0; i<n_; i++) p_[i] += 1;
  return drugi;
}

MojNizInt& MojNizInt::operator++() {
  for (size_t i = 0; i < n_; i++) p_[i]+=1;
  return *this;
}

void MojNizInt::push_back(const int& k) {

  int* p2 = new int[size()+1];
  if(n_ != 0) std::copy(p_, p_+n_, p2);

  delete[] p_; 
  p_ = p2; 
  p2 = nullptr; 
  p_[n_++] = k; 
}

