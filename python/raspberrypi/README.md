# DFRobot_BosonADCModule
* [中文版](./README_CN.md)

Why？BOSON主控板所用芯片ESP32-WROVE-32 模拟量读取误差比较大，无法准确读取BOSON 的ph计，温湿度，距离等传感器的等值。所以需要通过另外一块专门用于模拟数值数据处理的模块作为数据转换模块。
What？通过单片机采集模拟数据，转换为I2C信号输出。

![产品实物图](../../resources/images/BosonAdcModule.png)


## Product Link (https://www.dfrobot.com/)
    SKU: BOS0063


## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)
* [Compatibility](#compatibility)
* [History](#history)
* [Credits](#credits)


## Summary

* I2C数据输出。<br>
* 两路adc采集, 模拟量范围0-1023。<br>


## Installation

使用库，首先下载库文件，将其粘贴到指定的目录中，然后打开example文件夹并在该文件夹中运行演示。


## Methods

```python

    '''!
      @brief Initialize sensor
      @return  返回初始化状态
      @retval True indicate initialization succeed
      @retval False indicate failed
    '''
    def begin(self):

    '''!
      @brief 读取模块基本信息
      @n     重新从传感器获取其基本信息, 并缓存到存储信息的变量里面:
      @n     PID, VID, version, IIC_addr
    '''
    def read_basic_info(self):

    '''!
      @brief 获取模拟信号A1
      @return 返回值范围为： 0-1023
    '''
    def get_analog_signal_A1(self):

    '''!
      @brief 获取模拟信号A2
      @return 返回值范围为： 0-1023
    '''
    def get_analog_signal_A2(self):

```


## Compatibility

* RaspberryPi Version

| Board        | Work Well | Work Wrong | Untested | Remarks |
| ------------ | :-------: | :--------: | :------: | ------- |
| RaspberryPi2 |           |            |    √     |         |
| RaspberryPi3 |           |            |    √     |         |
| RaspberryPi4 |     √     |            |          |         |

* Python Version

| Python  | Work Well | Work Wrong | Untested | Remarks |
| ------- | :-------: | :--------: | :------: | ------- |
| Python2 |     √     |            |          |         |
| Python3 |     √     |            |          |         |


## History

- 2021/10/12 - Version 1.0.0 released.


## Credits

Written by qsjhyy(yihuan.huang@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))
