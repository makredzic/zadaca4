#include "Matrica.cpp"
#include <iostream>

int main() {
  Matrica<int> a(2, 2);
  a(0, 0) = 1;
  a(0, 1) = 34;
  a(1, 0) = 5;
  a(1, 1) = 100;
  Matrica<int> b(a);
  std::cout << "Matrica b:" << std::endl << b << std::endl;

  //test1 i test2 ispisi dodani da se pokaze gdje program prestaje raditi
  std::cout << "Test1" << std::endl;

  Matrica<int> c{2, 2, 1, 4, 2, 10};

  std::cout<< "Test2" << std::endl;
  c *= 3;

  std::cout << "Matrica c:" << std::endl << c << std::endl;
  try {
    a += b - c;
    std::cout << "Matrica a:" << std::endl<< a << std::endl;
  } catch (std::domain_error e) {
    std::cout << e.what();
  }
  return 0;
}
