//
// File: MyEMD.h
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 26-Feb-2024 09:41:51
//

#ifndef MYEMD_H
#define MYEMD_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
class MyEMD {
public:
  MyEMD();
  ~MyEMD();
  void MyEmd(const coder::array<double, 2U> &data,
             coder::array<double, 2U> &imf, coder::array<double, 2U> &residual);
};

#endif
//
// File trailer for MyEMD.h
//
// [EOF]
//
