//
// File: main.cpp
//
// MATLAB Coder version            : 5.5
// C/C++ source code generated on  : 26-Feb-2024 09:41:51
//

/*************************************************************************/
/* This automatically generated example C++ main file shows how to call  */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

// Include Files
#define _USE_MATH_DEFINES  // 导入 M_PI 常量
#include <cmath>           // 导入数学函数库
#define M_PI (4 * atan(1)) // 定义圆周率常量
#include "main.h"
#include "MyEMD.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
using namespace std;
#include <iostream>
#include <fstream>
#include <string>
// Function Declarations
static coder::array<double, 2U> argInit_UnboundedxUnbounded_real_T();

static double argInit_real_T();

// Function Definitions
//
// Arguments    : void
// Return Type  : coder::array<double, 2U>
//
static coder::array<double, 2U> argInit_UnboundedxUnbounded_real_T()
{
  coder::array<double, 2U> result;
  // Set the size of the array.
  // Change this size to the value that the application requires.
  result.set_size(2, 2);
  // Loop over the array to initialize each element.
  for (int idx0{0}; idx0 < result.size(0); idx0++) {
    for (int idx1{0}; idx1 < result.size(1); idx1++) {
      // Set the value of the array element.
      // Change this value to the value that the application requires.
      result[idx0 + result.size(0) * idx1] = argInit_real_T();
    }
  }
  return result;
}

//
// Arguments    : void
// Return Type  : double
//
static double argInit_real_T()
{
  return 0.0;
}

//
// Arguments    : int argc
//                char **argv
// Return Type  : int
//
int main(int, char **)
{


  coder::array<double, 2U> data;
  coder::array<double, 2U> imf;
  coder::array<double, 2U> residual;

  // 生成仿真信号，假设您的仿真信号是一个包含多个频率分量的正弦波
  double f1 = 12.0;
  double f2 = 4.0;
  double f3 = 10.0;
  double fs = 30.0; // 假设采样率为100 Hz
  double t = 0.0;
  double dt = 1.0 / fs;
  int N = fs * 60; // 信号长度

  // 初始化 data 的大小
  data.set_size(1, N);

  // 将信号数据赋值给 data
  for (int i = 0; i < N; ++i) {
    data[i] = 5.0 * sin(2.0 * M_PI * f1 * t) + 15.0 * sin(2.0 * M_PI * f2 * t) +
              8.0 * sin(2.0 * M_PI * f3 * t);
    t += dt;
  }
  MyEMD EMD;
  EMD.MyEmd(data, imf, residual);
  std::cout << "Size of IMFS: " << data.size(0) << " x " << data.size(1)
            << std::endl;
  // std::cout << "Size of numimfs: " << info.NumIMF.size << std::endl;
  //  输出每个 IMF 的数据
  int numRows = imf.size(0); // 获取行数
  int numCols = imf.size(1); // 获取列数

  int numTotalElements = numRows * numCols; // 获取总元素数
  int subImfNumber = 1;
  // 计算起始索引和结束索引
  int startIdx = (subImfNumber - 1) * numRows; // 子集的起始索引
  int endIdx = subImfNumber * numRows;         // 子集的结束索引

  // 确保结束索引不超过总元素数
  if (endIdx > numTotalElements) {
    endIdx = numTotalElements;
  }

    // 输出子集数据
    for (int i = startIdx; i < endIdx; ++i) {
      std::cout << imf[i] << " ";
    }

  //for (int i = 0; i < N; ++i) {
  //  std::cout << residual[i] << " ";
  //}


      // 将数据写入 CSV 文件
    std::ofstream outputFile("imf_subset_data.csv");
     if (!outputFile.is_open()) {
       std::cerr << "Error: Unable to open file for writing." << std::endl;
      return 0 ;
     }

     for (int i = startIdx; i < endIdx; ++i) {
       outputFile << imf[i];
       if (i != endIdx - 1) {
         outputFile << ",";
       }
     }
     outputFile.close();
  return 0;
}

//
// Arguments    : MyEMD *instancePtr
// Return Type  : void
//

//
// File trailer for main.cpp
//
// [EOF]
//
