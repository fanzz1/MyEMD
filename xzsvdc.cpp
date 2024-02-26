//
// File: xzsvdc.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 26-Feb-2024 09:41:51
//

// Include Files
#include "xzsvdc.h"
#include "rt_nonfinite.h"
#include "xaxpy.h"
#include "xnrm2.h"
#include "xrotg.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &A
//                ::coder::array<double, 1U> &S
// Return Type  : void
//
namespace coder {
namespace internal {
namespace reflapack {
void xzsvdc(::coder::array<double, 2U> &A, ::coder::array<double, 1U> &S)
{
  array<double, 1U> e;
  array<double, 1U> s;
  array<double, 1U> work;
  double nrm;
  double rt;
  double sm;
  double sqds;
  int i;
  int minnp;
  int n;
  int ns;
  int p;
  int qq;
  n = A.size(0);
  p = A.size(1);
  qq = A.size(0) + 1;
  ns = A.size(1);
  if (qq <= ns) {
    ns = qq;
  }
  qq = A.size(0);
  minnp = A.size(1);
  if (qq <= minnp) {
    minnp = qq;
  }
  s.set_size(ns);
  for (i = 0; i < ns; i++) {
    s[i] = 0.0;
  }
  e.set_size(A.size(1));
  ns = A.size(1);
  for (i = 0; i < ns; i++) {
    e[i] = 0.0;
  }
  work.set_size(A.size(0));
  ns = A.size(0);
  for (i = 0; i < ns; i++) {
    work[i] = 0.0;
  }
  if ((A.size(0) != 0) && (A.size(1) != 0)) {
    double r;
    double snorm;
    int ii;
    int jj;
    int nct;
    int nmq;
    int nrt;
    int qp1;
    if (A.size(1) >= 2) {
      qq = A.size(1) - 2;
    } else {
      qq = 0;
    }
    nrt = A.size(0);
    if (qq <= nrt) {
      nrt = qq;
    }
    qq = A.size(0) - 1;
    nct = A.size(1);
    if (qq <= nct) {
      nct = qq;
    }
    if (nct >= nrt) {
      i = nct;
    } else {
      i = nrt;
    }
    for (int q{0}; q < i; q++) {
      boolean_T apply_transform;
      qp1 = q + 2;
      qq = (q + n * q) + 1;
      nmq = (n - q) - 1;
      apply_transform = false;
      if (q + 1 <= nct) {
        nrm = blas::xnrm2(nmq + 1, A, qq);
        if (nrm > 0.0) {
          apply_transform = true;
          if (A[qq - 1] < 0.0) {
            nrm = -nrm;
          }
          s[q] = nrm;
          if (std::abs(nrm) >= 1.0020841800044864E-292) {
            nrm = 1.0 / nrm;
            ns = qq + nmq;
            for (int k{qq}; k <= ns; k++) {
              A[k - 1] = nrm * A[k - 1];
            }
          } else {
            ns = qq + nmq;
            for (int k{qq}; k <= ns; k++) {
              A[k - 1] = A[k - 1] / s[q];
            }
          }
          A[qq - 1] = A[qq - 1] + 1.0;
          s[q] = -s[q];
        } else {
          s[q] = 0.0;
        }
      }
      for (jj = qp1; jj <= p; jj++) {
        ns = q + n * (jj - 1);
        if (apply_transform) {
          nrm = 0.0;
          if (nmq + 1 >= 1) {
            for (int k{0}; k <= nmq; k++) {
              nrm += A[(qq + k) - 1] * A[ns + k];
            }
          }
          nrm = -(nrm / A[q + A.size(0) * q]);
          blas::xaxpy(nmq + 1, nrm, qq, A, ns + 1);
        }
        e[jj - 1] = A[ns];
      }
      if (q + 1 <= nrt) {
        ns = p - q;
        nrm = blas::xnrm2(ns - 1, e, q + 2);
        if (nrm == 0.0) {
          e[q] = 0.0;
        } else {
          if (e[q + 1] < 0.0) {
            e[q] = -nrm;
          } else {
            e[q] = nrm;
          }
          nrm = e[q];
          if (std::abs(e[q]) >= 1.0020841800044864E-292) {
            nrm = 1.0 / e[q];
            ns += q;
            for (int k{qp1}; k <= ns; k++) {
              e[k - 1] = nrm * e[k - 1];
            }
          } else {
            ns += q;
            for (int k{qp1}; k <= ns; k++) {
              e[k - 1] = e[k - 1] / nrm;
            }
          }
          e[q + 1] = e[q + 1] + 1.0;
          e[q] = -e[q];
          if (q + 2 <= n) {
            for (ii = qp1; ii <= n; ii++) {
              work[ii - 1] = 0.0;
            }
            for (jj = qp1; jj <= p; jj++) {
              blas::xaxpy(nmq, e[jj - 1], A, (q + n * (jj - 1)) + 2, work,
                          q + 2);
            }
            for (jj = qp1; jj <= p; jj++) {
              blas::xaxpy(nmq, -e[jj - 1] / e[q + 1], work, q + 2, A,
                          (q + n * (jj - 1)) + 2);
            }
          }
        }
      }
    }
    qq = A.size(1);
    n = A.size(0) + 1;
    if (qq <= n) {
      n = qq;
    }
    if (nct < A.size(1)) {
      s[nct] = A[nct + A.size(0) * nct];
    }
    if (A.size(0) < n) {
      s[n - 1] = 0.0;
    }
    if (nrt + 1 < n) {
      e[nrt] = A[nrt + A.size(0) * (n - 1)];
    }
    e[n - 1] = 0.0;
    nrt = n;
    nmq = 0;
    snorm = 0.0;
    for (int q{0}; q < n; q++) {
      nrm = s[q];
      if (s[q] != 0.0) {
        rt = std::abs(s[q]);
        r = s[q] / rt;
        nrm = rt;
        s[q] = rt;
        if (q + 1 < n) {
          e[q] = e[q] / r;
        }
      }
      if ((q + 1 < n) && (e[q] != 0.0)) {
        rt = std::abs(e[q]);
        r = rt / e[q];
        e[q] = rt;
        s[q + 1] = s[q + 1] * r;
      }
      snorm = std::fmax(snorm, std::fmax(std::abs(nrm), std::abs(e[q])));
    }
    while ((n > 0) && (nmq < 75)) {
      boolean_T exitg1;
      jj = n - 1;
      ii = n - 1;
      exitg1 = false;
      while (!(exitg1 || (ii == 0))) {
        nrm = std::abs(e[ii - 1]);
        if ((nrm <= 2.2204460492503131E-16 *
                        (std::abs(s[ii - 1]) + std::abs(s[ii]))) ||
            (nrm <= 1.0020841800044864E-292) ||
            ((nmq > 20) && (nrm <= 2.2204460492503131E-16 * snorm))) {
          e[ii - 1] = 0.0;
          exitg1 = true;
        } else {
          ii--;
        }
      }
      if (ii == n - 1) {
        ns = 4;
      } else {
        qq = n;
        ns = n;
        exitg1 = false;
        while ((!exitg1) && (ns >= ii)) {
          qq = ns;
          if (ns == ii) {
            exitg1 = true;
          } else {
            nrm = 0.0;
            if (ns < n) {
              nrm = std::abs(e[ns - 1]);
            }
            if (ns > ii + 1) {
              nrm += std::abs(e[ns - 2]);
            }
            rt = std::abs(s[ns - 1]);
            if ((rt <= 2.2204460492503131E-16 * nrm) ||
                (rt <= 1.0020841800044864E-292)) {
              s[ns - 1] = 0.0;
              exitg1 = true;
            } else {
              ns--;
            }
          }
        }
        if (qq == ii) {
          ns = 3;
        } else if (qq == n) {
          ns = 1;
        } else {
          ns = 2;
          ii = qq;
        }
      }
      switch (ns) {
      case 1:
        rt = e[n - 2];
        e[n - 2] = 0.0;
        for (int k{jj}; k >= ii + 1; k--) {
          blas::xrotg(&s[k - 1], &rt, &sqds, &sm);
          if (k > ii + 1) {
            r = e[k - 2];
            rt = -sm * r;
            e[k - 2] = r * sqds;
          }
        }
        break;
      case 2:
        rt = e[ii - 1];
        e[ii - 1] = 0.0;
        for (int k{ii + 1}; k <= n; k++) {
          blas::xrotg(&s[k - 1], &rt, &sqds, &sm);
          r = e[k - 1];
          rt = -sm * r;
          e[k - 1] = r * sqds;
        }
        break;
      case 3: {
        double scale;
        nrm = s[n - 1];
        rt = s[n - 2];
        r = e[n - 2];
        scale = std::fmax(
            std::fmax(
                std::fmax(std::fmax(std::abs(nrm), std::abs(rt)), std::abs(r)),
                std::abs(s[ii])),
            std::abs(e[ii]));
        sm = nrm / scale;
        nrm = rt / scale;
        rt = r / scale;
        sqds = s[ii] / scale;
        r = ((nrm + sm) * (nrm - sm) + rt * rt) / 2.0;
        nrm = sm * rt;
        nrm *= nrm;
        if ((r != 0.0) || (nrm != 0.0)) {
          rt = std::sqrt(r * r + nrm);
          if (r < 0.0) {
            rt = -rt;
          }
          rt = nrm / (r + rt);
        } else {
          rt = 0.0;
        }
        rt += (sqds + sm) * (sqds - sm);
        nrm = sqds * (e[ii] / scale);
        for (int k{ii + 1}; k <= jj; k++) {
          blas::xrotg(&rt, &nrm, &sqds, &sm);
          if (k > ii + 1) {
            e[k - 2] = rt;
          }
          r = e[k - 1];
          nrm = s[k - 1];
          e[k - 1] = sqds * r - sm * nrm;
          rt = sm * s[k];
          s[k] = s[k] * sqds;
          s[k - 1] = sqds * nrm + sm * r;
          blas::xrotg(&s[k - 1], &rt, &sqds, &sm);
          rt = sqds * e[k - 1] + sm * s[k];
          s[k] = -sm * e[k - 1] + sqds * s[k];
          nrm = sm * e[k];
          e[k] = e[k] * sqds;
        }
        e[n - 2] = rt;
        nmq++;
      } break;
      default:
        if (s[ii] < 0.0) {
          s[ii] = -s[ii];
        }
        qp1 = ii + 1;
        while ((ii + 1 < nrt) && (s[ii] < s[qp1])) {
          rt = s[ii];
          s[ii] = s[qp1];
          s[qp1] = rt;
          ii = qp1;
          qp1++;
        }
        nmq = 0;
        n--;
        break;
      }
    }
  }
  S.set_size(minnp);
  for (int k{0}; k < minnp; k++) {
    S[k] = s[k];
  }
}

} // namespace reflapack
} // namespace internal
} // namespace coder

//
// File trailer for xzsvdc.cpp
//
// [EOF]
//
