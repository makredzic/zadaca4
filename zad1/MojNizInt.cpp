#include "MojNizInt.hpp"
#include <stdexcept>
#include <vector>

int MojNizInt::at(const size_t &i) const {
  if (i > int(n_)-1) throw std::invalid_argument("Pokusaj pristupa kontejneru van granica");
  return *(p_+i);
}

int& MojNizInt::at(const size_t &i) {
  if (i > int(n_)-1) throw std::invalid_argument("Pokusaj pristupa kontejneru van granica");
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
  for (size_t i = 0; i<n_; i++) drugi.p_[i] += 1;
  return drugi;
}

MojNizInt& MojNizInt::operator++() {
  for (size_t i = 0; i < n_; i++) p_[i]+=1;
  return *this;
}

void MojNizInt::push_back(const int& k) {

  int* p2 = new int[size()+1]; //novi pointer koji pokazuje na novi prosireni block memorije
  std::copy(p_, p_+n_, p2); //u novi block se kopiraju vrijednosti iz starog p_

  n_++; //de ba

  delete[] p_; //posto p2 pokazuje na novokopirane vrijednosti, izbrisat stari block p_
  p_ = p2; //sad p_ pokazuje na novi prosireni block koji ima iste vrijednosti samo vise prostora
  p2 = nullptr; //posto je p2 beskorisno i pokazuje na isto sto i p_, stavit da p2 ne pokazuje ni na sta

  p_[n_] = k; //p_ pokazuje na novi block koji ima mjesta na kraju za jos jedan int i sad se postavi taj zadnji int na vrijednost k
}

