# MyEMD
**基于C++的经验模态分解（Empirical Mode Decomposition，EMD）类**

本项目基于 MATLAB Coder将MATLAB EMD函数 代码转换为C/C++代码


**1.定义matlab函数如下：**
```
function [imf,residual]=MyEmd(data)
[imf,residual] = emd(data,Interpolation="pchip");% name一定要有双引号
end
```

根据matlab官方的EMD说明文档：https://ww2.mathworks.cn/help/signal/ref/emd.html?searchHighlight=EMD&s_tid=srchtitle_support_results_1_EMD

本项目采用"pchip"插值方式，使用分段三次 Hermite 插值多项式，多用于处理非平滑数据。

**2.定义测试函数：**
```
f1=15;                        	   % 信号1的频率
f2=12;                              % 信号2的频率
f3=10;                      	   % 信号3的频率
fs=30;                             % 采样率
N=fs*60;
t = 0 : 1/fs : (N-1)/fs;
y1=5*sin(2*pi*f1*t)+15*sin(2*pi*f2*t)+8*sin(2*pi*f3*t); 
plot(t,y1)
xlabel('Time(s)')
[myimfs,canCha]=MyEmd(y1);
emd(y1,"Interpolation","pchip")
```
**3.采用MATLAB coder转换为C++函数**

![image](https://github.com/fanzz1/MyEMD/assets/95949202/5dc83190-b9b2-4d07-b5b5-41b0aeb53ec1)



**4.Interface style选择 Fuctions 则生成的EMD为函数形式，选择Methods则为类的形式，本项目选择类的形式生成。**

![image](https://github.com/fanzz1/MyEMD/assets/95949202/c22a351e-eb3a-4c5e-aade-909a8fb75025)



**5.生成后采用分别采用matlab和C++用相同的仿真信号进行测试：**

*C++*

```
 // 生成仿真信号，假设您的仿真信号是一个包含多个频率分量的正弦波
  double f1 = 15.0;
  double f2 = 12.0;
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
```


*MATLAB*
```
f1=15;                        	   % 信号1的频率
f2=12;                              % 信号2的频率
f3=10;                      	   % 信号3的频率
fs=30;                             % 采样率
N=fs*60;
t = 0 : 1/fs : (N-1)/fs;
y1=5*sin(2*pi*f1*t)+15*sin(2*pi*f2*t)+8*sin(2*pi*f3*t);
```
结果如下：
**MATLAB:**
IMFS个数：
![image](https://github.com/fanzz1/MyEMD/assets/95949202/fb754f0f-d6ef-4dab-8bca-2cdf84d3f577)

残差值：

![image](https://github.com/fanzz1/MyEMD/assets/95949202/cb761f5f-5ddf-4713-bf9e-f65bedad7e9a)


**C++**
计算残差值：

![image](https://github.com/fanzz1/MyEMD/assets/95949202/7786d58f-e8b4-48f9-9b91-dec1ef0cef0d)

基本一致!

**6.未解决的问题：**

上述测试函数由于刚好分解成3个IMFS，所以分解结果相同，当我换成其他函数时，C++的结果与MATLAB结果会出现差异:其一，分解的本征模态函数个数不同，其二分解的IMFS前三个的结果基本一致，从第四个开始出现偏差（因此导致分解结果不同）



