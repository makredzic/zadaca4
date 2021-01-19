#include "MojNizInt.hpp"
#include <stdexcept>

int MojNizInt::at(const size_t &i) const {
  if (i > n_-1) throw std::invalid_argument("Pokusaj pristupa kontejneru van granica");
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



