# -*- coding: utf-8 -*
'''!
  @file      get_data.py
  @brief     这个demo演示了如何获取模块基本信息, 获取模拟量A1和A2
  @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license   The MIT License (MIT)
  @author    [qsjhyy](yihuan.huang@dfrobot.com)
  @version   V1.0
  @date      2021-10-12
  @url       https://github.com/DFRobot/DFRobot_BosonADCModule
'''
from __future__ import print_function
import sys
sys.path.append('../')
from DFRobot_BosonADCModule import *

'''
  实例化一个对象，来驱动我们的传感器;
  IIC地址根据模块当前选择的设置即可，默认为0x06
'''
sensor = DFRobot_BosonADCModule(i2c_addr = 0x06, bus = 1)


def setup():
  while (sensor.begin() == False):
    print ('Please check that the device is properly connected')
    time.sleep(3)
  print("sensor begin successfully!!!\n")

  '''
    读取模块基本信息
    重新从传感器获取其基本信息, 并缓存到存储信息的变量里面:
    PID, VID, version, IIC_addr
  '''
  sensor.read_basic_info()

  # 模块的PID存储寄存器, 默认值0xC03F (BOS0063)(最高两位作为种类判断00：SEN、01：DFR、10：TEL、11:BOS, 后面14位作为num)
  print("PID: %#x" %sensor.PID)

  # 模块的VID，默认值0x3343（代表厂商为DFRobot）
  print("VID: %#x" %sensor.VID)

  # 固件版本号：0x0100代表V0.1.0.0
  print("version: %#x" %sensor.version)

  # 模块的通信地址, 默认值0x06
  print("mailing address: %#x" %sensor.IIC_addr)

  time.sleep(2)


def loop():
  '''
    获取模拟信号A1
    返回值范围为： 0-1023
  '''
  analog_signal_A1 = sensor.get_analog_signal_A1()
  print("Module current analog signal A1: %d" %analog_signal_A1)

  '''
    获取模拟信号A2
    返回值范围为： 0-1023
  '''
  analog_signal_A2 = sensor.get_analog_signal_A2()
  print("Module current analog signal A2: %d\n" %analog_signal_A2)

  time.sleep(1)


if __name__ == "__main__":
  setup()
  while True:
    loop()