#pragma once
#include <cmath>
#include <limits>

#ifndef __BYTE_ORDER__
#error Please define __BYTE_ORDER__ to be __ORDER_LITTLE_ENDIAN__ or __ORDER_BIG_ENDIAN__
#endif

namespace rnumeric {

union IEEE754 {
  unsigned int word[2];
  double value;
};

template <typename T>
class RNT;

template <>
class RNT<double> {
public:
  static const bool has_NA{true};
  static const double NA() {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    static const IEEE754 rna{{ 1954, 0x7ff00000 }};
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
    static const IEEE754 rna{{0x7ff00000, 1954}};
#endif

    return rna.value;
  }

  static inline bool ISNA(double x) { return std::isnan(x); }
};

template <>
class RNT<int> {
public:
  static const bool has_NA{true};
  static const int NA() { return std::numeric_limits<int>::min(); }
  static inline bool ISNA(int x) { return x == std::numeric_limits<int>::min() ? true : false; }
};
} // namespace rnumeric
