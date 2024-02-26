//
// File: norm.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 26-Feb-2024 09:41:51
//

// Include Files
#include "norm.h"
#include "rt_nonfinite.h"
#include "xzsvdc.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &x
// Return Type  : double
//
namespace coder {
double b_norm(const ::coder::array<double, 2U> &x)
{
  array<double, 2U> b_x;
  array<double, 1U> r;
  double y;
  boolean_T MATRIX_INPUT_AND_P_IS_TWO;
  boolean_T VECTOR_INPUT_AND_P_IS_NUMERIC;
  VECTOR_INPUT_AND_P_IS_NUMERIC = false;
  MATRIX_INPUT_AND_P_IS_TWO = false;
  if ((x.size(0) == 1) || (x.size(1) == 1)) {
    VECTOR_INPUT_AND_P_IS_NUMERIC = true;
  } else {
    MATRIX_INPUT_AND_P_IS_TWO = true;
  }
  if ((x.size(0) == 0) || (x.size(1) == 0)) {
    y = 0.0;
  } else if (MATRIX_INPUT_AND_P_IS_TWO) {
    int m;
    int n;
    m = x.size(0);
    n = x.size(1);
    y = 0.0;
    for (int j{0}; j < n; j++) {
      for (int i{0}; i < m; i++) {
        double scale;
        scale = std::abs(x[i + x.size(0) * j]);
        if (std::isnan(scale) || (scale > y)) {
          y = scale;
        }
      }
    }
    if ((!std::isinf(y)) && (!std::isnan(y))) {
      b_x.set_size(x.size(0), x.size(1));
      m = x.size(0) * x.size(1) - 1;
      for (n = 0; n <= m; n++) {
        b_x[n] = x[n];
      }
      internal::reflapack::xzsvdc(b_x, r);
      y = r[0];
    }
  } else if (VECTOR_INPUT_AND_P_IS_NUMERIC) {
    int n;
    n = x.size(0) * x.size(1);
    y = 0.0;
    if (n >= 1) {
      if (n == 1) {
        y = std::abs(x[0]);
      } else {
        double scale;
        scale = 3.3121686421112381E-170;
        for (int m{0}; m < n; m++) {
          double absxk;
          absxk = std::abs(x[m]);
          if (absxk > scale) {
            double t;
            t = scale / absxk;
            y = y * t * t + 1.0;
            scale = absxk;
          } else {
            double t;
            t = absxk / scale;
            y += t * t;
          }
        }
        y = scale * std::sqrt(y);
      }
    }
  } else {
    y = rtNaN;
  }
  return y;
}

} // namespace coder

//
// File trailer for norm.cpp
//
// [EOF]
//
