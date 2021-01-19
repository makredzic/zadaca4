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

    ~MojNizInt() {delete []p_;}; //destruktor
    size_t size() const {return n_;} 
    int at(const size_t& i) const;

    int& operator[](size_t&& i) const {return p_[i];};

  private:
    size_t n_{0};
    int* p_{nullptr};
};
