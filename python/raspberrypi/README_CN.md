# DFRobot_BosonADCModule
* [English Version](./README.md)

Why？BOSON主控板所用芯片ESP32-WROVE-32 模拟量读取误差比较大，无法准确读取BOSON 的ph计，温湿度，距离等传感器的等值。所以需要通过另外一块专门用于模拟数值数据处理的模块作为数据转换模块。
What？通过单片机采集模拟数据，转换为I2C信号输出。

![产品实物图](../../resources/images/BosonAdcModule.png)


## 产品链接 (https://www.dfrobot.com/)
    SKU: BOS0063


## 目录

* [概述](#概述)
* [库安装](#库安装)
* [方法](#方法)
* [兼容性](#兼容性)
* [历史](#历史)
* [创作者](#创作者)


## 概述

* I2C数据输出。<br>
* 两路adc采集, 模拟量范围0-1023。<br>


## 库安装

使用库，首先下载库文件，将其粘贴到指定的目录中，然后打开example文件夹并在该文件夹中运行演示。


## 方法

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


## 兼容性

* RaspberryPi 版本

| Board        | Work Well | Work Wrong | Untested | Remarks |
| ------------ | :-------: | :--------: | :------: | ------- |
| RaspberryPi2 |           |            |    √     |         |
| RaspberryPi3 |           |            |    √     |         |
| RaspberryPi4 |     √     |            |          |         |

* Python 版本

| Python  | Work Well | Work Wrong | Untested | Remarks |
| ------- | :-------: | :--------: | :------: | ------- |
| Python2 |     √     |            |          |         |
| Python3 |     √     |            |          |         |


## 历史

- 2021/10/12 - 1.0.0 版本


## 创作者

Written by qsjhyy(yihuan.huang@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))
