#include <iostream>
#include <array>
#include <vector>
#include <limits>
#include "dainty_named.h"

using namespace dainty;

///////////////////////////////////////////////////////////////////////////////

void set_point(unsigned short x, unsigned short y) {
  std::cout << "1. x:" << x << ", y:" << y << std::endl;
}

///////////////////////////////////////////////////////////////////////////////
// step1. create explicit types

enum t_x_ {};
using t_xaxis = named::t_explicit<named::t_ushort, t_x_>;

enum t_y_ {};
using t_yaxis = named::t_explicit<named::t_ushort, t_y_>;

// step2. overload operators for new types
constexpr t_xaxis operator "" _xaxis(unsigned long long int value) {
  // can throw if out of bounds - don't use braced initialization.
  return t_xaxis(value);
}

constexpr t_yaxis operator "" _yaxis(unsigned long long int value) {
  // can throw if out of bounds - don't use braced initialization.
  return t_yaxis(value);
}

inline std::ostream& operator<<(std::ostream& out, const t_xaxis& xaxis) {
  return (out << "x:" << get(xaxis));
}

inline std::ostream& operator<<(std::ostream& out, const t_yaxis& yaxis) {
  return (out << "y:" << get(yaxis));
}

// step3. rewrite set_point with new types
void set_point(t_xaxis x, t_yaxis y) {
  std::cout << "2. " << x << ", " << y << std::endl;
}

///////////////////////////////////////////////////////////////////////////////

using named::t_uint;
using named::t_ix;
using named::t_bix;
using named::t_eix;
using named::t_n;
using named::to_ix;
using named::to_bix;
using named::to_eix;
using named::to_n;

constexpr t_ix maxix{10};
constexpr t_ix minix{0};

using t_arr = std::array<int, get(to_n(maxix))>;

///////////////////////////////////////////////////////////////////////////////
// difference between indexing and number of elemen

template<typename T>
void print(t_bix begin, t_eix end, const T& arr) {
  for (auto ix = get(begin), eix = get(end); ix != eix; ++ix)
    std::cout << arr[ix];
  std::cout << std::endl;
}

template<typename T>
inline void print(t_ix pos, t_n n, const T& arr) {
  print(to_bix(pos), t_eix{get(pos) + get(n)}, arr);
}

///////////////////////////////////////////////////////////////////////////////

int main() {
  set_point(1,2);
  set_point(t_xaxis(1), t_yaxis(2));
  set_point(1_xaxis, 2_yaxis);

  std::cout << 7_xaxis << std::endl;

  //set_point(t_xaxis{-1}, t_yaxis{2}); // can detect narrowing
  set_point(t_xaxis{1}, t_yaxis{2});

  auto three = t_n{3};

  t_arr arr = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  print(t_ix{1}, three, arr);

  std::vector<t_uint> vect{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  print(t_ix{0}, three, vect);

  t_ix ix = to_ix(three);

  return 0;
}
