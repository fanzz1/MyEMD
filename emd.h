//
// File: emd.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 26-Feb-2024 09:41:51
//

#ifndef EMD_H
#define EMD_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
void binary_expand_op(coder::array<double, 1U> &in1, int in2,
                      const coder::array<double, 1U> &in3,
                      const coder::array<double, 1U> &in4);

void binary_expand_op(coder::array<double, 2U> &in1,
                      const coder::array<double, 1U> &in2);

double binary_expand_op(const coder::array<double, 1U> &in1,
                        const coder::array<double, 2U> &in2, double in3);

void binary_expand_op(coder::array<double, 2U> &in1,
                      const coder::array<double, 2U> &in2, int in3);

namespace coder {
void localEMD_anonFcn3(const ::coder::array<double, 2U> &x,
                       ::coder::array<double, 1U> &varargout_1,
                       ::coder::array<double, 1U> &varargout_2);

}

#endif
//
// File trailer for emd.h
//
// [EOF]
//
