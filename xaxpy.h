//
// File: xaxpy.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 26-Feb-2024 09:41:51
//

#ifndef XAXPY_H
#define XAXPY_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace internal {
namespace blas {
void xaxpy(int n, double a, int ix0, ::coder::array<double, 2U> &y, int iy0);

void xaxpy(int n, double a, const ::coder::array<double, 2U> &x, int ix0,
           ::coder::array<double, 1U> &y, int iy0);

void xaxpy(int n, double a, const ::coder::array<double, 1U> &x, int ix0,
           ::coder::array<double, 2U> &y, int iy0);

} // namespace blas
} // namespace internal
} // namespace coder

#endif
//
// File trailer for xaxpy.h
//
// [EOF]
//
