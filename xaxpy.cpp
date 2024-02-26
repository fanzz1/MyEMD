//
// File: xaxpy.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 26-Feb-2024 09:41:51
//

// Include Files
#include "xaxpy.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : int n
//                double a
//                int ix0
//                ::coder::array<double, 2U> &y
//                int iy0
// Return Type  : void
//
namespace coder {
namespace internal {
namespace blas {
void xaxpy(int n, double a, int ix0, ::coder::array<double, 2U> &y, int iy0)
{
  if ((n >= 1) && (!(a == 0.0))) {
    int i;
    i = n - 1;
    for (int k{0}; k <= i; k++) {
      int i1;
      i1 = (iy0 + k) - 1;
      y[i1] = y[i1] + a * y[(ix0 + k) - 1];
    }
  }
}

//
// Arguments    : int n
//                double a
//                const ::coder::array<double, 2U> &x
//                int ix0
//                ::coder::array<double, 1U> &y
//                int iy0
// Return Type  : void
//
void xaxpy(int n, double a, const ::coder::array<double, 2U> &x, int ix0,
           ::coder::array<double, 1U> &y, int iy0)
{
  if ((n >= 1) && (!(a == 0.0))) {
    int i;
    i = n - 1;
    for (int k{0}; k <= i; k++) {
      int i1;
      i1 = (iy0 + k) - 1;
      y[i1] = y[i1] + a * x[(ix0 + k) - 1];
    }
  }
}

//
// Arguments    : int n
//                double a
//                const ::coder::array<double, 1U> &x
//                int ix0
//                ::coder::array<double, 2U> &y
//                int iy0
// Return Type  : void
//
void xaxpy(int n, double a, const ::coder::array<double, 1U> &x, int ix0,
           ::coder::array<double, 2U> &y, int iy0)
{
  if ((n >= 1) && (!(a == 0.0))) {
    int i;
    i = n - 1;
    for (int k{0}; k <= i; k++) {
      int i1;
      i1 = (iy0 + k) - 1;
      y[i1] = y[i1] + a * x[(ix0 + k) - 1];
    }
  }
}

} // namespace blas
} // namespace internal
} // namespace coder

//
// File trailer for xaxpy.cpp
//
// [EOF]
//
