# DFRobot_BosonAdcModule
* [中文版](./README_CN.md)

Why？BOSON主控板所用芯片ESP32-WROVE-32 模拟量读取误差比较大，无法准确读取BOSON 的ph计，温湿度，距离等传感器的等值。所以需要通过另外一块专门用于模拟数值数据处理的模块作为数据转换模块。
What？通过单片机采集模拟数据，转换为I2C信号输出。

![产品实物图](./resources/images/BosonAdcModule.png)


## Product Link (链接到英文商城)
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

要使用这个库，首先下载库文件，将其粘贴到\Arduino\libraries目录中，然后打开示例文件夹并在文件夹中运行演示。


## Methods

```C++

  /**
   * @fn begin
   * @brief 初始化函数
   * @return int类型, 表示返回初始化的状态
   * @retval 0 NO_ERROR
   * @retval -1 ERR_DATA_BUS
   * @retval -2 ERR_IC_VERSION
   */
  int begin(void);

  /**
   * @fn refreshBasicInfo
   * @brief 重新从传感器获取其基本信息, 并缓存到存储信息的结构体basicInfo里面
   * @n     basicInfo结构体的成员: PID, VID, version, iicAddr
   * @return None
   */
  void refreshBasicInfo(void);

  /**
   * @fn getAnalogSignalA1
   * @brief 获取模拟信号A1
   * @return 返回值范围为： 0-1023
   */
  uint16_t getAnalogSignalA1(void);

  /**
   * @fn getAnalogSignalA2
   * @brief 获取模拟信号A2
   * @return 返回值范围为： 0-1023
   */
  uint16_t getAnalogSignalA2(void);

```


## Compatibility

MCU                | Work Well    | Work Wrong   | Untested    | Remarks
------------------ | :----------: | :----------: | :---------: | -----
Arduino Uno        |      √       |              |             | 
Arduino MEGA2560   |      √       |              |             | 
Arduino Leonardo   |      √       |              |             | 
FireBeetle-ESP8266 |      √       |              |             | 
FireBeetle-ESP32   |      √       |              |             | 
FireBeetle-M0      |      √       |              |             | 
Micro:bit          |      √       |              |             | 
Raspberry Pi       |      √       |              |             | 


## History

- 2021/10/12 - Version 1.0.0 released.


## Credits

Written by qsjhyy(yihuan.huang@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))

