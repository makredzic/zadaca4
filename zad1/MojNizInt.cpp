#include "MojNizInt.hpp"
#include <stdexcept>
#include <vector>

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

/*
//ovaj operator ne radi trenutno
//Mozda prvo napravit implementaciju operatora *= i onda pomocu nje operator*
MojNizInt MojNizInt::operator*(int&& i) {
  return MojNizInt{}; //vrati novi objekat tipa MojNizInt koji je prazan

  //nije zakomentarisano jer ce se oginuti return gore odmah
  //Kod ispod alocira novi blockmemorije na heapu sa elementima pomnozenim sa i
  //medjutim ne znam kako instancirat novi objekat MojNizInt sa tim novim elementima
  int* temp = p_; 
  std::vector<int> vec;
  
  for (int j = 0; j < n_; j++) {
    int x = *temp;
    vec.push_back(x*i);
    temp++; //incrementira se temp odnosno pointer se pomjeri na sljedeci elemenat u memorij
  }
  
  int* ptr_arr = new int[n_];
  std::copy(vec.begin(), vec.end(), ptr_arr);
  return MojNizInt{};
}
*/

MojNizInt operator*(MojNizInt a, const int& i) {
  a*=i; 
  return a; 
}

MojNizInt& MojNizInt::operator+=(const MojNizInt& drugi) {
  if (n_ != drugi.n_) throw std::invalid_argument("Nizovi koji ucestvuju u operacij sabiranja moraju biti iste duzine");
  for (int i = 0; i < n_; i++) p_[i] += drugi.p_[i]; 
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
  for (int i = 0; i<n_; i++) drugi.p_[i] += 1;
  return drugi;
}

MojNizInt& MojNizInt::operator++() {
  for (int i = 0; i < n_; i++) p_[i]+=1;
  return *this;
}
