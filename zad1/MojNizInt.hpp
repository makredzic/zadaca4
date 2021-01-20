#pragma once
#include <algorithm>
#include <initializer_list>

class MojNizInt {
  public:

    MojNizInt() = default;
    MojNizInt(std::initializer_list<int> a) : n_{a.size()}, p_{new int[n_]} {std::copy(std::begin(a), std::end(a), p_);}

    MojNizInt(const MojNizInt&); //copy konstruktor
    MojNizInt(MojNizInt&& drugi); //move-copy konstruktor

    MojNizInt& operator=(const MojNizInt&); //copy jednako
    MojNizInt& operator=(MojNizInt&&); 

    ~MojNizInt() {delete[] p_;}; //destruktor
    size_t size() const {return n_;} 

    int at(const size_t& i) const;
    int& at(const size_t& i); //ovo je potrebno kako bi se moglo promijeniti vrijednost sa at

    int& operator[](const size_t& i) const {return p_[i];};

    //MojNizInt operator*(int&&); //ovo slobodno ignorisi
    MojNizInt& operator*=(const int& i) {for(int j =0; j<n_; j++) p_[j]*=i; return *this;};
    MojNizInt& operator+=(const MojNizInt&);

    MojNizInt operator++(int); //postfix++ il ti ga sufix
    MojNizInt& operator++(); //++prefix

    void push_back(const int&);

  private:
    size_t n_{0};
    int* p_{nullptr};
};

MojNizInt operator*(MojNizInt, const int&);
MojNizInt operator*(const int&, MojNizInt);
MojNizInt operator+(MojNizInt, const MojNizInt& drugi);

