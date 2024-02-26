//
// File: MyEMD.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 26-Feb-2024 09:41:51
//

// Include Files
#include "MyEMD.h"
#include "MyEmd_data.h"
#include "emd.h"
#include "interp1.h"
#include "norm.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
MyEMD::MyEMD()
{
  omp_init_nest_lock(&MyEmd_nestLockGlobal);
}

//
// Arguments    : void
// Return Type  : void
//
MyEMD::~MyEMD()
{
  omp_destroy_nest_lock(&MyEmd_nestLockGlobal);
}

//
// Arguments    : const coder::array<double, 2U> &data
//                coder::array<double, 2U> &imf
//                coder::array<double, 2U> &residual
// Return Type  : void
//
void MyEMD::MyEmd(const coder::array<double, 2U> &data,
                  coder::array<double, 2U> &imf,
                  coder::array<double, 2U> &residual)
{
  coder::array<double, 2U> b_rsigL;
  coder::array<double, 2U> rsigL;
  coder::array<double, 2U> x;
  coder::array<double, 1U> bottomsIdx;
  coder::array<double, 1U> extpksLoc_tmp;
  coder::array<double, 1U> extpksVal;
  coder::array<double, 1U> mVal;
  coder::array<double, 1U> peaksIdx;
  coder::array<double, 1U> r;
  coder::array<double, 1U> rsigPrev;
  coder::array<double, 1U> t;
  coder::array<unsigned int, 2U> y;
  int b_i;
  int i;
  int kpks;
  int loop_ub;
  int partialTrueCount;
  int u1;
  boolean_T exitg1;
  x.set_size(data.size(0), data.size(1));
  loop_ub = data.size(0) * data.size(1);
  for (i = 0; i < loop_ub; i++) {
    x[i] = data[i];
  }
  if ((data.size(0) == 0) || (data.size(1) == 0)) {
    y.set_size(1, 0);
  } else {
    kpks = data.size(0);
    u1 = data.size(1);
    if (kpks >= u1) {
      u1 = kpks;
    }
    y.set_size(1, u1);
    loop_ub = u1 - 1;
    for (i = 0; i <= loop_ub; i++) {
      y[i] = static_cast<unsigned int>(i) + 1U;
    }
  }
  t.set_size(y.size(1));
  loop_ub = y.size(1);
  for (i = 0; i < loop_ub; i++) {
    t[i] = y[i];
  }
  if (data.size(0) == 1) {
    x.set_size(data.size(1), 1);
    loop_ub = data.size(1);
    for (i = 0; i < loop_ub; i++) {
      x[i] = data[i];
    }
  }
  residual.set_size(x.size(0), x.size(1));
  loop_ub = x.size(0) * x.size(1);
  for (i = 0; i < loop_ub; i++) {
    residual[i] = x[i];
  }
  if ((x.size(0) == 0) || (x.size(1) == 0)) {
    u1 = 0;
  } else {
    kpks = x.size(0);
    u1 = x.size(1);
    if (kpks >= u1) {
      u1 = kpks;
    }
  }
  imf.set_size(u1, 10);
  loop_ub = u1 * 10;
  for (i = 0; i < loop_ub; i++) {
    imf[i] = 0.0;
  }
  rsigPrev.set_size(u1);
  mVal.set_size(u1);
  for (i = 0; i < u1; i++) {
    rsigPrev[i] = 0.0;
    mVal[i] = 0.0;
  }
  b_i = 0;
  exitg1 = false;
  while ((!exitg1) && (b_i < 10)) {
    coder::localEMD_anonFcn3(residual, peaksIdx, bottomsIdx);
    if ((10.0 * std::log10(coder::b_norm(x) / coder::b_norm(residual)) >
         20.0) ||
        (static_cast<unsigned int>(peaksIdx.size(0)) +
             static_cast<unsigned int>(bottomsIdx.size(0)) <
         1U)) {
      exitg1 = true;
    } else {
      double rtol;
      int endLoc;
      int k;
      rsigL.set_size(residual.size(0), residual.size(1));
      loop_ub = residual.size(0) * residual.size(1);
      for (i = 0; i < loop_ub; i++) {
        rsigL[i] = residual[i];
      }
      rtol = 1.0;
      k = 0;
      while ((k < 100) && (!(rtol < 0.2))) {
        double A;
        double b_t;
        double scale;
        if (u1 < 1) {
          loop_ub = 0;
        } else {
          loop_ub = u1;
        }
        for (i = 0; i < loop_ub; i++) {
          rsigPrev[i] = rsigL[i];
        }
        coder::localEMD_anonFcn3(rsigL, peaksIdx, bottomsIdx);
        if (static_cast<unsigned int>(peaksIdx.size(0)) +
                static_cast<unsigned int>(bottomsIdx.size(0)) >
            0U) {
          double b_extbtmVal_data[3];
          double b_extpksLoc_tmp_data[3];
          double b_extpksVal_data[3];
          double extbtmVal_data[3];
          double extpksLoc_tmp_data[3];
          double extpksVal_data[3];
          double lbtmLoc_data[3];
          double rbtmLoc_data[3];
          double m;
          unsigned int P;
          int b_extpksVal_size;
          int b_trueCount;
          int c_trueCount;
          int d_trueCount;
          int extbtmVal_size;
          int extpksVal_size;
          int trueCount;
          if (peaksIdx.size(0) == 0) {
            peaksIdx.set_size(2);
            peaksIdx[0] = 1.0;
            peaksIdx[1] = t.size(0);
          }
          if (bottomsIdx.size(0) == 0) {
            bottomsIdx.set_size(2);
            bottomsIdx[0] = 1.0;
            bottomsIdx[1] = t.size(0);
          }
          A = std::abs(rsigL[static_cast<int>(peaksIdx[0]) - 1] -
                       rsigL[static_cast<int>(bottomsIdx[0]) - 1]) /
              2.0;
          scale = t[static_cast<int>(peaksIdx[0]) - 1];
          b_t = t[static_cast<int>(bottomsIdx[0]) - 1];
          P = static_cast<unsigned int>(std::abs(scale - b_t)) << 1;
          if (P != 0U) {
            rtol = t[0] - scale;
            m = rsigL[0] - A * std::sin(6.2831853071795862 /
                                            static_cast<double>(P) * rtol +
                                        1.5707963267948966);
            kpks = static_cast<int>(std::floor(rtol / static_cast<double>(P)));
            kpks += (kpks < 0);
            trueCount = 0;
            rtol = (static_cast<double>(kpks) - 1.0) * static_cast<double>(P) +
                   scale;
            extpksLoc_tmp_data[0] = rtol;
            if (rtol != static_cast<int>(t[0])) {
              trueCount = 1;
            }
            rtol = (static_cast<double>(kpks) - 2.0) * static_cast<double>(P) +
                   scale;
            extpksLoc_tmp_data[1] = rtol;
            if (rtol != static_cast<int>(t[0])) {
              trueCount++;
            }
            rtol = (static_cast<double>(kpks) - 3.0) * static_cast<double>(P) +
                   scale;
            extpksLoc_tmp_data[2] = rtol;
            if (rtol != static_cast<int>(t[0])) {
              trueCount++;
            }
            partialTrueCount = 0;
            if (extpksLoc_tmp_data[0] != static_cast<int>(t[0])) {
              partialTrueCount = 1;
            }
            if (extpksLoc_tmp_data[1] != static_cast<int>(t[0])) {
              extpksLoc_tmp_data[partialTrueCount] = extpksLoc_tmp_data[1];
              partialTrueCount++;
            }
            if (extpksLoc_tmp_data[2] != static_cast<int>(t[0])) {
              extpksLoc_tmp_data[partialTrueCount] = extpksLoc_tmp_data[2];
            }
            rtol = m + A;
            extpksVal_size = trueCount;
            for (i = 0; i < trueCount; i++) {
              extpksVal_data[i] = rtol;
            }
            kpks = static_cast<int>(
                std::floor((t[0] - b_t) / static_cast<double>(P)));
            kpks += (kpks < 0);
            b_trueCount = 0;
            rtol = (static_cast<double>(kpks) - 1.0) * static_cast<double>(P) +
                   b_t;
            lbtmLoc_data[0] = rtol;
            if (rtol != static_cast<int>(t[0])) {
              b_trueCount = 1;
            }
            rtol = (static_cast<double>(kpks) - 2.0) * static_cast<double>(P) +
                   b_t;
            lbtmLoc_data[1] = rtol;
            if (rtol != static_cast<int>(t[0])) {
              b_trueCount++;
            }
            rtol = (static_cast<double>(kpks) - 3.0) * static_cast<double>(P) +
                   b_t;
            lbtmLoc_data[2] = rtol;
            if (rtol != static_cast<int>(t[0])) {
              b_trueCount++;
            }
            partialTrueCount = 0;
            if (lbtmLoc_data[0] != static_cast<int>(t[0])) {
              partialTrueCount = 1;
            }
            if (lbtmLoc_data[1] != static_cast<int>(t[0])) {
              lbtmLoc_data[partialTrueCount] = lbtmLoc_data[1];
              partialTrueCount++;
            }
            if (lbtmLoc_data[2] != static_cast<int>(t[0])) {
              lbtmLoc_data[partialTrueCount] = lbtmLoc_data[2];
            }
            rtol = m - A;
            extbtmVal_size = b_trueCount;
            for (i = 0; i < b_trueCount; i++) {
              extbtmVal_data[i] = rtol;
            }
            i = trueCount >> 1;
            for (kpks = 0; kpks < i; kpks++) {
              rtol = extpksLoc_tmp_data[0];
              extpksLoc_tmp_data[0] = extpksLoc_tmp_data[trueCount - 1];
              extpksLoc_tmp_data[trueCount - 1] = rtol;
            }
            i = b_trueCount >> 1;
            for (kpks = 0; kpks < i; kpks++) {
              rtol = lbtmLoc_data[0];
              lbtmLoc_data[0] = lbtmLoc_data[b_trueCount - 1];
              lbtmLoc_data[b_trueCount - 1] = rtol;
            }
          } else {
            trueCount = 0;
            extpksVal_size = 0;
            b_trueCount = 0;
            extbtmVal_size = 0;
          }
          endLoc = static_cast<int>(t[t.size(0) - 1]);
          A = std::abs(
                  rsigL[static_cast<int>(peaksIdx[peaksIdx.size(0) - 1]) - 1] -
                  rsigL[static_cast<int>(bottomsIdx[bottomsIdx.size(0) - 1]) -
                        1]) /
              2.0;
          P = static_cast<unsigned int>(std::abs(
                  t[static_cast<int>(peaksIdx[peaksIdx.size(0) - 1]) - 1] -
                  t[static_cast<int>(bottomsIdx[bottomsIdx.size(0) - 1]) - 1]))
              << 1;
          if (P != 0U) {
            m = rsigL[rsigL.size(0) * rsigL.size(1) - 1] -
                A * std::sin(6.2831853071795862 / static_cast<double>(P) *
                                 (t[t.size(0) - 1] -
                                  t[static_cast<int>(
                                        peaksIdx[peaksIdx.size(0) - 1]) -
                                    1]) +
                             1.5707963267948966);
            kpks = static_cast<int>(std::floor(
                (t[t.size(0) - 1] -
                 t[static_cast<int>(peaksIdx[peaksIdx.size(0) - 1]) - 1]) /
                static_cast<double>(P)));
            kpks += (kpks < 0);
            c_trueCount = 0;
            rtol = (static_cast<double>(kpks) + 1.0) * static_cast<double>(P) +
                   t[static_cast<int>(peaksIdx[peaksIdx.size(0) - 1]) - 1];
            b_extpksLoc_tmp_data[0] = rtol;
            if (rtol != endLoc) {
              c_trueCount = 1;
            }
            rtol = (static_cast<double>(kpks) + 2.0) * static_cast<double>(P) +
                   t[static_cast<int>(peaksIdx[peaksIdx.size(0) - 1]) - 1];
            b_extpksLoc_tmp_data[1] = rtol;
            if (rtol != endLoc) {
              c_trueCount++;
            }
            rtol = (static_cast<double>(kpks) + 3.0) * static_cast<double>(P) +
                   t[static_cast<int>(peaksIdx[peaksIdx.size(0) - 1]) - 1];
            b_extpksLoc_tmp_data[2] = rtol;
            if (rtol != endLoc) {
              c_trueCount++;
            }
            partialTrueCount = 0;
            if (b_extpksLoc_tmp_data[0] != endLoc) {
              partialTrueCount = 1;
            }
            if (b_extpksLoc_tmp_data[1] != endLoc) {
              b_extpksLoc_tmp_data[partialTrueCount] = b_extpksLoc_tmp_data[1];
              partialTrueCount++;
            }
            if (b_extpksLoc_tmp_data[2] != endLoc) {
              b_extpksLoc_tmp_data[partialTrueCount] = b_extpksLoc_tmp_data[2];
            }
            rtol = m + A;
            b_extpksVal_size = c_trueCount;
            for (i = 0; i < c_trueCount; i++) {
              b_extpksVal_data[i] = rtol;
            }
            kpks = static_cast<int>(std::floor(
                (t[t.size(0) - 1] -
                 t[static_cast<int>(bottomsIdx[bottomsIdx.size(0) - 1]) - 1]) /
                static_cast<double>(P)));
            kpks += (kpks < 0);
            d_trueCount = 0;
            rtol = (static_cast<double>(kpks) + 1.0) * static_cast<double>(P) +
                   t[static_cast<int>(bottomsIdx[bottomsIdx.size(0) - 1]) - 1];
            rbtmLoc_data[0] = rtol;
            if (rtol != endLoc) {
              d_trueCount = 1;
            }
            rtol = (static_cast<double>(kpks) + 2.0) * static_cast<double>(P) +
                   t[static_cast<int>(bottomsIdx[bottomsIdx.size(0) - 1]) - 1];
            rbtmLoc_data[1] = rtol;
            if (rtol != endLoc) {
              d_trueCount++;
            }
            rtol = (static_cast<double>(kpks) + 3.0) * static_cast<double>(P) +
                   t[static_cast<int>(bottomsIdx[bottomsIdx.size(0) - 1]) - 1];
            rbtmLoc_data[2] = rtol;
            if (rtol != endLoc) {
              d_trueCount++;
            }
            partialTrueCount = 0;
            if (rbtmLoc_data[0] != endLoc) {
              partialTrueCount = 1;
            }
            if (rbtmLoc_data[1] != endLoc) {
              rbtmLoc_data[partialTrueCount] = rbtmLoc_data[1];
              partialTrueCount++;
            }
            if (rbtmLoc_data[2] != endLoc) {
              rbtmLoc_data[partialTrueCount] = rbtmLoc_data[2];
            }
            rtol = m - A;
            kpks = d_trueCount;
            for (i = 0; i < d_trueCount; i++) {
              b_extbtmVal_data[i] = rtol;
            }
          } else {
            c_trueCount = 0;
            b_extpksVal_size = 0;
            d_trueCount = 0;
            kpks = 0;
          }
          if (u1 < 1) {
            loop_ub = 0;
          } else {
            loop_ub = u1;
          }
          extpksLoc_tmp.set_size((trueCount + peaksIdx.size(0)) + c_trueCount);
          for (i = 0; i < trueCount; i++) {
            extpksLoc_tmp[i] = extpksLoc_tmp_data[i];
          }
          endLoc = peaksIdx.size(0);
          for (i = 0; i < endLoc; i++) {
            extpksLoc_tmp[i + trueCount] = t[static_cast<int>(peaksIdx[i]) - 1];
          }
          for (i = 0; i < c_trueCount; i++) {
            extpksLoc_tmp[(i + trueCount) + peaksIdx.size(0)] =
                b_extpksLoc_tmp_data[i];
          }
          extpksVal.set_size((extpksVal_size + peaksIdx.size(0)) +
                             b_extpksVal_size);
          for (i = 0; i < extpksVal_size; i++) {
            extpksVal[i] = extpksVal_data[i];
          }
          endLoc = peaksIdx.size(0);
          for (i = 0; i < endLoc; i++) {
            extpksVal[i + extpksVal_size] =
                rsigL[static_cast<int>(peaksIdx[i]) - 1];
          }
          for (i = 0; i < b_extpksVal_size; i++) {
            extpksVal[(i + extpksVal_size) + peaksIdx.size(0)] =
                b_extpksVal_data[i];
          }
          coder::interp1(extpksLoc_tmp, extpksVal, t, r);
          extpksLoc_tmp.set_size((b_trueCount + bottomsIdx.size(0)) +
                                 d_trueCount);
          for (i = 0; i < b_trueCount; i++) {
            extpksLoc_tmp[i] = lbtmLoc_data[i];
          }
          endLoc = bottomsIdx.size(0);
          for (i = 0; i < endLoc; i++) {
            extpksLoc_tmp[i + b_trueCount] =
                t[static_cast<int>(bottomsIdx[i]) - 1];
          }
          for (i = 0; i < d_trueCount; i++) {
            extpksLoc_tmp[(i + b_trueCount) + bottomsIdx.size(0)] =
                rbtmLoc_data[i];
          }
          extpksVal.set_size((extbtmVal_size + bottomsIdx.size(0)) + kpks);
          for (i = 0; i < extbtmVal_size; i++) {
            extpksVal[i] = extbtmVal_data[i];
          }
          endLoc = bottomsIdx.size(0);
          for (i = 0; i < endLoc; i++) {
            extpksVal[i + extbtmVal_size] =
                rsigL[static_cast<int>(bottomsIdx[i]) - 1];
          }
          for (i = 0; i < kpks; i++) {
            extpksVal[(i + extbtmVal_size) + bottomsIdx.size(0)] =
                b_extbtmVal_data[i];
          }
          coder::interp1(extpksLoc_tmp, extpksVal, t, peaksIdx);
          if (r.size(0) == peaksIdx.size(0)) {
            for (i = 0; i < loop_ub; i++) {
              mVal[i] = (r[i] + peaksIdx[i]) / 2.0;
            }
          } else {
            binary_expand_op(mVal, loop_ub, r, peaksIdx);
          }
        } else {
          if (u1 < 1) {
            loop_ub = 0;
          } else {
            loop_ub = u1;
          }
          for (i = 0; i < loop_ub; i++) {
            mVal[i] = 0.0;
          }
        }
        if (rsigL.size(0) == mVal.size(0)) {
          b_rsigL.set_size(rsigL.size(0), rsigL.size(1));
          loop_ub = rsigL.size(1);
          for (i = 0; i < loop_ub; i++) {
            endLoc = rsigL.size(0);
            for (partialTrueCount = 0; partialTrueCount < endLoc;
                 partialTrueCount++) {
              b_rsigL[partialTrueCount + b_rsigL.size(0) * i] =
                  rsigL[partialTrueCount + rsigL.size(0) * i] -
                  mVal[partialTrueCount];
            }
          }
          rsigL.set_size(b_rsigL.size(0), b_rsigL.size(1));
          loop_ub = b_rsigL.size(0) * b_rsigL.size(1);
          for (i = 0; i < loop_ub; i++) {
            rsigL[i] = b_rsigL[i];
          }
        } else {
          binary_expand_op(rsigL, mVal);
        }
        if (rsigPrev.size(0) == 0) {
          rtol = 0.0;
        } else {
          rtol = 0.0;
          if (rsigPrev.size(0) == 1) {
            rtol = std::abs(rsigPrev[0]);
          } else {
            scale = 3.3121686421112381E-170;
            kpks = rsigPrev.size(0);
            for (partialTrueCount = 0; partialTrueCount < kpks;
                 partialTrueCount++) {
              A = std::abs(rsigPrev[partialTrueCount]);
              if (A > scale) {
                b_t = scale / A;
                rtol = rtol * b_t * b_t + 1.0;
                scale = A;
              } else {
                b_t = A / scale;
                rtol += b_t * b_t;
              }
            }
            rtol = scale * std::sqrt(rtol);
          }
        }
        if (rsigPrev.size(0) == rsigL.size(0)) {
          b_rsigL.set_size(rsigPrev.size(0), rsigL.size(1));
          loop_ub = rsigL.size(1);
          for (i = 0; i < loop_ub; i++) {
            endLoc = rsigPrev.size(0);
            for (partialTrueCount = 0; partialTrueCount < endLoc;
                 partialTrueCount++) {
              b_rsigL[partialTrueCount + b_rsigL.size(0) * i] =
                  rsigPrev[partialTrueCount] -
                  rsigL[partialTrueCount + rsigL.size(0) * i];
            }
          }
          rtol = coder::b_norm(b_rsigL) / rtol;
        } else {
          rtol = binary_expand_op(rsigPrev, rsigL, rtol);
        }
        rtol *= rtol;
        k++;
      }
      loop_ub = imf.size(0);
      for (i = 0; i < loop_ub; i++) {
        imf[i + imf.size(0) * b_i] = rsigL[i];
      }
      if (residual.size(0) == imf.size(0)) {
        b_rsigL.set_size(residual.size(0), residual.size(1));
        loop_ub = residual.size(1);
        for (i = 0; i < loop_ub; i++) {
          endLoc = residual.size(0);
          for (partialTrueCount = 0; partialTrueCount < endLoc;
               partialTrueCount++) {
            b_rsigL[partialTrueCount + b_rsigL.size(0) * i] =
                residual[partialTrueCount + residual.size(0) * i] -
                imf[partialTrueCount + imf.size(0) * b_i];
          }
        }
        residual.set_size(b_rsigL.size(0), b_rsigL.size(1));
        loop_ub = b_rsigL.size(0) * b_rsigL.size(1);
        for (i = 0; i < loop_ub; i++) {
          residual[i] = b_rsigL[i];
        }
      } else {
        binary_expand_op(residual, imf, b_i);
      }
      b_i++;
    }
  }
  if (b_i < 1) {
    loop_ub = 0;
  } else {
    loop_ub = b_i;
  }
  kpks = imf.size(0);
  for (i = 0; i < loop_ub; i++) {
    for (partialTrueCount = 0; partialTrueCount < kpks; partialTrueCount++) {
      imf[partialTrueCount + kpks * i] =
          imf[partialTrueCount + imf.size(0) * i];
    }
  }
  imf.set_size(imf.size(0), loop_ub);
  //  name一定要有双引号
}

//
// File trailer for MyEMD.cpp
//
// [EOF]
//
