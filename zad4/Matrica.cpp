#include "Matrica.h"

template<typename T>
T& Matrica<T>::operator()(const size_t& m, const size_t& n) {
  // m1n1 m1n2 m1n3 m1n4
  // m2n1 m2n2 m2n3 m2n4
  // m3n1 m3n2 m3n3 m3n4
//p_={m1n1, m1n2, m1n3, m1n4m m2n1, m2n2, m2n3, m2n4, m3n1, m3n2, m3n3, m3n4}
  
  if (m >= m_ || n >= n_) throw std::invalid_argument("Invalidne dimenzije matrice");

  const size_t index = m * columns() + n;
  return p_[index]; 
}

template<typename T>
T Matrica<T>::operator()(const size_t& m, const size_t& n) const { 
  if (m >= m_ || n >= n_) throw std::invalid_argument("Invalidne dimenzije matrice");

  const size_t index = m * columns() + n; 
  return p_[index]; 
}

template<typename T>
template<typename U>
Matrica<T>& Matrica<T>::operator+=(const Matrica<U>& drugi) {
  if (rows() != drugi.rows() || columns() != drugi.columns()) throw std::domain_error("Matrice moraju bit istih dimenzija kako bi se sabirale."); 

  size_t index = 0;
  for (size_t i = 0; i < rows(); i++) {
    for (size_t j =0; j < columns(); j++) p_[index++] += drugi(i,j);
  }
  return *this;
}

template<typename T>
template<typename U>
Matrica<T>& Matrica<T>::operator-=(const Matrica<U>& drugi) {
  if (rows() != drugi.rows() || columns() != drugi.columns()) throw std::domain_error("Matrice moraju bit istih dimenzija kako bi se sabirale."); 
  
  size_t index = 0;
  for (size_t i = 0; i < rows(); i++) {
    for (size_t j =0; j < columns(); j++) p_[index++] -= drugi(i,j);
  }
  return *this;
}

template<typename T, typename U>
Matrica<T> operator+(Matrica<T> prva, const Matrica<U>& druga) {
  try {
    prva += druga;
  } catch (const std::domain_error& e) {
    throw e;
  }
  return prva;
}

template<typename T, typename U>
Matrica<T> operator-(Matrica<T> prva, const Matrica<U>& druga) {
  try {
    prva -= druga;
  } catch (const std::domain_error& e) {
    throw e;
  }
  return prva;
}

template<typename T>
template<typename U>
Matrica<T>& Matrica<T>::operator*=(const U& br) { 
  for (size_t i = 0; i < rows()*columns(); i++) p_[i] *= br;
  return *this;
}

template<typename T>
template<typename U>
Matrica<T>& Matrica<T>::operator/=(const U& br) { 
  for (size_t i = 0; i < rows()*columns(); i++) p_[i] /= br;
  return *this;
}

template<typename T, typename U>
Matrica<T> operator*(Matrica<T> prva, const U& br) {
  try {
    prva += br;
  } catch (const std::domain_error& e) {
    throw e;
  }
  return prva;
}

template<typename T, typename U>
Matrica<T> operator/(Matrica<T> prva, const U& br) {
  try {
    prva -= br;
  } catch (const std::domain_error& e) {
    throw e;
  }
  return prva;
}

template<typename T>
std::ostream& operator<<(std::ostream& o, const Matrica<T>& mat) {
  for (size_t i = 0; i < mat.rows(); i++) {
    for (size_t j = 0; j < mat.columns(); j++) {
      o << mat(i,j) << "\t"; 
    }
    o << std::endl;
  }
}
