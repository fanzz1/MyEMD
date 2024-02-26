//
// File: emd.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 26-Feb-2024 09:41:51
//

// Include Files
#include "emd.h"
#include "norm.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : coder::array<double, 1U> &in1
//                int in2
//                const coder::array<double, 1U> &in3
//                const coder::array<double, 1U> &in4
// Return Type  : void
//
void binary_expand_op(coder::array<double, 1U> &in1, int in2,
                      const coder::array<double, 1U> &in3,
                      const coder::array<double, 1U> &in4)
{
  int stride_0_1;
  int stride_1_1;
  stride_0_1 = (in3.size(0) != 1);
  stride_1_1 = (in4.size(0) != 1);
  for (int i{0}; i < in2; i++) {
    in1[i] = (in3[i * stride_0_1] + in4[i * stride_1_1]) / 2.0;
  }
}

//
// Arguments    : coder::array<double, 2U> &in1
//                const coder::array<double, 1U> &in2
// Return Type  : void
//
void binary_expand_op(coder::array<double, 2U> &in1,
                      const coder::array<double, 1U> &in2)
{
  coder::array<double, 2U> b_in1;
  int b_loop_ub;
  int i;
  int in2_idx_0;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  in2_idx_0 = in2.size(0);
  if (in2_idx_0 == 1) {
    i = in1.size(0);
  } else {
    i = in2_idx_0;
  }
  b_in1.set_size(i, in1.size(1));
  stride_0_0 = (in1.size(0) != 1);
  stride_1_0 = (in2_idx_0 != 1);
  loop_ub = in1.size(1);
  for (i = 0; i < loop_ub; i++) {
    if (in2_idx_0 == 1) {
      b_loop_ub = in1.size(0);
    } else {
      b_loop_ub = in2_idx_0;
    }
    for (int i1{0}; i1 < b_loop_ub; i1++) {
      b_in1[i1 + b_in1.size(0) * i] =
          in1[i1 * stride_0_0 + in1.size(0) * i] - in2[i1 * stride_1_0];
    }
  }
  in1.set_size(b_in1.size(0), b_in1.size(1));
  loop_ub = b_in1.size(1);
  for (i = 0; i < loop_ub; i++) {
    b_loop_ub = b_in1.size(0);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
      in1[i1 + in1.size(0) * i] = b_in1[i1 + b_in1.size(0) * i];
    }
  }
}

//
// Arguments    : const coder::array<double, 1U> &in1
//                const coder::array<double, 2U> &in2
//                double in3
// Return Type  : double
//
double binary_expand_op(const coder::array<double, 1U> &in1,
                        const coder::array<double, 2U> &in2, double in3)
{
  coder::array<double, 2U> b_in1;
  int i;
  int in1_idx_0;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  in1_idx_0 = in1.size(0);
  if (in2.size(0) == 1) {
    i = in1_idx_0;
  } else {
    i = in2.size(0);
  }
  b_in1.set_size(i, in2.size(1));
  stride_0_0 = (in1_idx_0 != 1);
  stride_1_0 = (in2.size(0) != 1);
  loop_ub = in2.size(1);
  for (i = 0; i < loop_ub; i++) {
    int b_loop_ub;
    int i1;
    i1 = in2.size(0);
    if (i1 == 1) {
      b_loop_ub = in1_idx_0;
    } else {
      b_loop_ub = i1;
    }
    for (i1 = 0; i1 < b_loop_ub; i1++) {
      b_in1[i1 + b_in1.size(0) * i] =
          in1[i1 * stride_0_0] - in2[i1 * stride_1_0 + in2.size(0) * i];
    }
  }
  return coder::b_norm(b_in1) / in3;
}

//
// Arguments    : coder::array<double, 2U> &in1
//                const coder::array<double, 2U> &in2
//                int in3
// Return Type  : void
//
void binary_expand_op(coder::array<double, 2U> &in1,
                      const coder::array<double, 2U> &in2, int in3)
{
  coder::array<double, 2U> b_in1;
  int b_loop_ub;
  int i;
  int in2_idx_0;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  in2_idx_0 = in2.size(0);
  if (in2_idx_0 == 1) {
    i = in1.size(0);
  } else {
    i = in2_idx_0;
  }
  b_in1.set_size(i, in1.size(1));
  stride_0_0 = (in1.size(0) != 1);
  stride_1_0 = (in2_idx_0 != 1);
  loop_ub = in1.size(1);
  for (i = 0; i < loop_ub; i++) {
    if (in2_idx_0 == 1) {
      b_loop_ub = in1.size(0);
    } else {
      b_loop_ub = in2_idx_0;
    }
    for (int i1{0}; i1 < b_loop_ub; i1++) {
      b_in1[i1 + b_in1.size(0) * i] = in1[i1 * stride_0_0 + in1.size(0) * i] -
                                      in2[i1 * stride_1_0 + in2.size(0) * in3];
    }
  }
  in1.set_size(b_in1.size(0), b_in1.size(1));
  loop_ub = b_in1.size(1);
  for (i = 0; i < loop_ub; i++) {
    b_loop_ub = b_in1.size(0);
    for (int i1{0}; i1 < b_loop_ub; i1++) {
      in1[i1 + in1.size(0) * i] = b_in1[i1 + b_in1.size(0) * i];
    }
  }
}

//
// Arguments    : const ::coder::array<double, 2U> &x
//                ::coder::array<double, 1U> &varargout_1
//                ::coder::array<double, 1U> &varargout_2
// Return Type  : void
//
namespace coder {
void localEMD_anonFcn3(const ::coder::array<double, 2U> &x,
                       ::coder::array<double, 1U> &varargout_1,
                       ::coder::array<double, 1U> &varargout_2)
{
  unsigned int nmax;
  unsigned int nmin;
  int u0;
  int u1;
  if ((x.size(0) == 0) || (x.size(1) == 0)) {
    u1 = 0;
  } else {
    u0 = x.size(0);
    u1 = x.size(1);
    if (u0 >= u1) {
      u1 = u0;
    }
  }
  nmax = 0U;
  nmin = 0U;
  varargout_1.set_size(u1);
  varargout_2.set_size(u1);
  for (u0 = 0; u0 < u1; u0++) {
    varargout_1[u0] = 0.0;
    varargout_2[u0] = 0.0;
  }
  if (u1 >= 3) {
    double dright;
    dright = x[1] - x[0];
    for (u0 = 0; u0 <= u1 - 3; u0++) {
      double dleft;
      dleft = dright;
      dright = x[u0 + 2] - x[u0 + 1];
      if ((dleft > 0.0) && (dright <= 0.0)) {
        nmax++;
        varargout_1[static_cast<int>(nmax) - 1] = static_cast<double>(u0) + 2.0;
      } else if ((dleft < 0.0) && (dright >= 0.0)) {
        nmin++;
        varargout_2[static_cast<int>(nmin) - 1] = static_cast<double>(u0) + 2.0;
      }
    }
  }
  if (static_cast<int>(nmax) < 1) {
    u1 = 0;
  } else {
    u1 = static_cast<int>(nmax);
  }
  varargout_1.set_size(u1);
  if (static_cast<int>(nmin) < 1) {
    u1 = 0;
  } else {
    u1 = static_cast<int>(nmin);
  }
  varargout_2.set_size(u1);
}

} // namespace coder

//
// File trailer for emd.cpp
//
// [EOF]
//
