//
// File: interp1.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 26-Feb-2024 09:41:51
//

// Include Files
#include "interp1.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include "omp.h"
#include <cmath>

// Type Definitions
struct struct_T {
  coder::array<double, 2U> breaks;
  coder::array<double, 2U> coefs;
};

// Function Declarations
namespace coder {
static void interp1SplineMakimaOrPCHIP(const ::coder::array<double, 1U> &y,
                                       const ::coder::array<double, 1U> &xi,
                                       ::coder::array<double, 1U> &yi,
                                       const ::coder::array<double, 1U> &x);

}

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &y
//                const ::coder::array<double, 1U> &xi
//                ::coder::array<double, 1U> &yi
//                const ::coder::array<double, 1U> &x
// Return Type  : void
//
namespace coder {
static void interp1SplineMakimaOrPCHIP(const ::coder::array<double, 1U> &y,
                                       const ::coder::array<double, 1U> &xi,
                                       ::coder::array<double, 1U> &yi,
                                       const ::coder::array<double, 1U> &x)
{
  array<double, 2U> del;
  array<double, 2U> h;
  array<double, 2U> slopes;
  struct_T pp;
  double d;
  double d2;
  double dzdxdx;
  double dzzdx;
  double signd1;
  double xloc;
  int high_i;
  int low_i;
  int low_ip1;
  int mid_i;
  int nxm1;
  int nxm2;
  nxm1 = x.size(0) - 2;
  h.set_size(1, x.size(0) - 1);
  del.set_size(1, y.size(0) - 1);
  for (int k{0}; k <= nxm1; k++) {
    d2 = x[k + 1] - x[k];
    h[k] = d2;
    del[k] = (y[k + 1] - y[k]) / d2;
  }
  slopes.set_size(1, y.size(0));
  if (x.size(0) == 2) {
    slopes[0] = del[0];
    slopes[1] = del[0];
  } else {
    nxm2 = x.size(0);
    for (int k{0}; k <= nxm2 - 3; k++) {
      d2 = h[k + 1];
      d = h[k];
      signd1 = 2.0 * d2 + d;
      dzdxdx = d2 + 2.0 * d;
      slopes[k + 1] = 0.0;
      d2 = del[k];
      d = del[k + 1];
      dzzdx = d2 * d;
      if (!std::isnan(dzzdx)) {
        if (dzzdx < 0.0) {
          dzzdx = -1.0;
        } else {
          dzzdx = (dzzdx > 0.0);
        }
      }
      if (dzzdx > 0.0) {
        slopes[k + 1] = (signd1 + dzdxdx) / (signd1 / d2 + dzdxdx / d);
      }
    }
    dzzdx = del[0];
    d2 = del[1];
    dzdxdx = h[0];
    signd1 = h[1];
    dzdxdx =
        ((2.0 * dzdxdx + signd1) * dzzdx - dzdxdx * d2) / (dzdxdx + signd1);
    if (std::isnan(dzzdx)) {
      signd1 = rtNaN;
    } else if (dzzdx < 0.0) {
      signd1 = -1.0;
    } else {
      signd1 = (dzzdx > 0.0);
    }
    if (std::isnan(dzdxdx)) {
      d = rtNaN;
    } else if (dzdxdx < 0.0) {
      d = -1.0;
    } else {
      d = (dzdxdx > 0.0);
    }
    if (d != signd1) {
      dzdxdx = 0.0;
    } else {
      if (std::isnan(d2)) {
        d = rtNaN;
      } else if (d2 < 0.0) {
        d = -1.0;
      } else {
        d = (d2 > 0.0);
      }
      if ((signd1 != d) && (std::abs(dzdxdx) > std::abs(3.0 * dzzdx))) {
        dzdxdx = 3.0 * dzzdx;
      }
    }
    slopes[0] = dzdxdx;
    dzzdx = del[x.size(0) - 2];
    d2 = del[x.size(0) - 3];
    dzdxdx = h[x.size(0) - 2];
    signd1 = h[x.size(0) - 3];
    dzdxdx =
        ((2.0 * dzdxdx + signd1) * dzzdx - dzdxdx * d2) / (dzdxdx + signd1);
    if (std::isnan(dzzdx)) {
      signd1 = rtNaN;
    } else if (dzzdx < 0.0) {
      signd1 = -1.0;
    } else {
      signd1 = (dzzdx > 0.0);
    }
    if (std::isnan(dzdxdx)) {
      d = rtNaN;
    } else if (dzdxdx < 0.0) {
      d = -1.0;
    } else {
      d = (dzdxdx > 0.0);
    }
    if (d != signd1) {
      dzdxdx = 0.0;
    } else {
      if (std::isnan(d2)) {
        d = rtNaN;
      } else if (d2 < 0.0) {
        d = -1.0;
      } else {
        d = (d2 > 0.0);
      }
      if ((signd1 != d) && (std::abs(dzdxdx) > std::abs(3.0 * dzzdx))) {
        dzdxdx = 3.0 * dzzdx;
      }
    }
    slopes[x.size(0) - 1] = dzdxdx;
  }
  nxm1 = x.size(0);
  pp.breaks.set_size(1, x.size(0));
  nxm2 = x.size(0);
  for (int k{0}; k < nxm2; k++) {
    pp.breaks[k] = x[k];
  }
  nxm2 = slopes.size(1) - 1;
  pp.coefs.set_size(slopes.size(1) - 1, 4);
  for (int k{0}; k <= nxm1 - 2; k++) {
    d2 = del[k];
    d = slopes[k];
    signd1 = h[k];
    dzzdx = (d2 - d) / signd1;
    dzdxdx = (slopes[k + 1] - d2) / signd1;
    pp.coefs[k] = (dzdxdx - dzzdx) / signd1;
    pp.coefs[nxm2 + k] = 2.0 * dzzdx - dzdxdx;
    pp.coefs[(nxm2 << 1) + k] = d;
    pp.coefs[3 * nxm2 + k] = y[k];
  }
  nxm2 = xi.size(0) - 1;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
    high_i, xloc, low_i, low_ip1, mid_i)

  for (int b_k = 0; b_k <= nxm2; b_k++) {
    if (std::isnan(xi[b_k])) {
      yi[b_k] = rtNaN;
    } else {
      if (std::isnan(xi[b_k])) {
        xloc = xi[b_k];
      } else {
        high_i = pp.breaks.size(1);
        low_i = 1;
        low_ip1 = 2;
        while (high_i > low_ip1) {
          mid_i = (low_i >> 1) + (high_i >> 1);
          if (((low_i & 1) == 1) && ((high_i & 1) == 1)) {
            mid_i++;
          }
          if (xi[b_k] >= pp.breaks[mid_i - 1]) {
            low_i = mid_i;
            low_ip1 = mid_i + 1;
          } else {
            high_i = mid_i;
          }
        }
        xloc = xi[b_k] - pp.breaks[low_i - 1];
        xloc = xloc * (xloc * (xloc * pp.coefs[low_i - 1] +
                               pp.coefs[(low_i + pp.breaks.size(1)) - 2]) +
                       pp.coefs[(low_i + ((pp.breaks.size(1) - 1) << 1)) - 1]) +
               pp.coefs[(low_i + 3 * (pp.breaks.size(1) - 1)) - 1];
      }
      yi[b_k] = xloc;
    }
  }
}

//
// Arguments    : const ::coder::array<double, 1U> &varargin_1
//                const ::coder::array<double, 1U> &varargin_2
//                const ::coder::array<double, 1U> &varargin_3
//                ::coder::array<double, 1U> &Vq
// Return Type  : void
//
void interp1(const ::coder::array<double, 1U> &varargin_1,
             const ::coder::array<double, 1U> &varargin_2,
             const ::coder::array<double, 1U> &varargin_3,
             ::coder::array<double, 1U> &Vq)
{
  array<double, 1U> x;
  array<double, 1U> y;
  int k;
  int n;
  int nx;
  y.set_size(varargin_2.size(0));
  n = varargin_2.size(0);
  for (k = 0; k < n; k++) {
    y[k] = varargin_2[k];
  }
  x.set_size(varargin_1.size(0));
  n = varargin_1.size(0);
  for (k = 0; k < n; k++) {
    x[k] = varargin_1[k];
  }
  nx = varargin_1.size(0) - 1;
  Vq.set_size(varargin_3.size(0));
  n = varargin_3.size(0);
  for (k = 0; k < n; k++) {
    Vq[k] = 0.0;
  }
  if (varargin_3.size(0) != 0) {
    k = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (k <= nx) {
        if (std::isnan(varargin_1[k])) {
          exitg1 = 1;
        } else {
          k++;
        }
      } else {
        if (varargin_1[1] < varargin_1[0]) {
          double xtmp;
          int b_j1;
          k = (nx + 1) >> 1;
          for (b_j1 = 0; b_j1 < k; b_j1++) {
            xtmp = x[b_j1];
            n = nx - b_j1;
            x[b_j1] = x[n];
            x[n] = xtmp;
          }
          if (varargin_2.size(0) > 1) {
            n = varargin_2.size(0) - 1;
            nx = varargin_2.size(0) >> 1;
            for (k = 0; k < nx; k++) {
              xtmp = y[k];
              b_j1 = n - k;
              y[k] = y[b_j1];
              y[b_j1] = xtmp;
            }
          }
        }
        interp1SplineMakimaOrPCHIP(y, varargin_3, Vq, x);
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
}

} // namespace coder

//
// File trailer for interp1.cpp
//
// [EOF]
//
