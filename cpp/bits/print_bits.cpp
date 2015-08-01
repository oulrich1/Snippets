#include <string.h>
#include <iostream>

using namespace std;

typedef unsigned char BYTE;
typedef BYTE* PTRBYTE;

template <typename T>
void print_bits (T v) {
  const char zero = '0';
  const char one = '1';
  const int BITS_IN_BYTE = 8;
  BYTE* bits = reinterpret_cast<BYTE*>(&v); // reinterpret values as if it had the type. (no cast)
  const int numBytes = sizeof(T);
  const int numBits = numBytes * BITS_IN_BYTE;
  for (int i = numBytes-1; i >= 0; --i) { // reverse byte order since least sig is first in array
    for (int b = BITS_IN_BYTE-1; b >= 0; --b) { // read bits in order from left to right
      if (bits[i] & (1 << b)) { // print one or zero if bit is one or zero.
        cout << one;
      } else {
        cout << zero;
      }
    }
  }
  cout << endl;
}

int main () {
  cout << "Ints: " << endl;
  print_bits<int>(0);
  print_bits<int>(1);
  print_bits<int>(2);
  print_bits<int>(3);
  print_bits<int>(4);
  print_bits<int>(5);
  print_bits<int>(6);

  cout << "Floats: " << endl;
  print_bits<float>(0);
  print_bits<float>(1);
  print_bits<float>(2);
  print_bits<float>(3);
  print_bits<float>(4);
  print_bits<float>(5);
  print_bits<float>(5.834);
  print_bits<float>(6.25);

  cout << "Doubles: " << endl;
  print_bits<double>(0);
  print_bits<double>(1);
  print_bits<double>(2);
  print_bits<double>(3);
  print_bits<double>(4);
  print_bits<double>(5);
  print_bits<double>(5.834);
  print_bits<double>(6.25);
  return 0;
}
