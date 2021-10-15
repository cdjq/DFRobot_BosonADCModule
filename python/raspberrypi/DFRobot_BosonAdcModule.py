# -*- coding: utf-8 -*
'''!
  @file  DFRobot_BosonAdcModule.py
  @brief  Define the infrastructure of DFRobot_BosonAdcModule class.
  @details  获取模块基本信息, 获取模拟量A1和A2
  @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license  The MIT License (MIT)
  @author  [qsjhyy](yihuan.huang@dfrobot.com)
  @version  V1.0
  @date  2021-10-12
  @url  https://github.com/DFRobot/DFRobot_BosonAdcModule
'''
import sys
import time
import smbus
import logging
from ctypes import *

logger = logging.getLogger()
#logger.setLevel(logging.INFO)   # Display all print information
logger.setLevel(logging.FATAL)   # If you don’t want to display too many prints, only print errors, please use this option
ph = logging.StreamHandler()
formatter = logging.Formatter("%(asctime)s - [%(filename)s %(funcName)s]:%(lineno)d - %(levelname)s: %(message)s")
ph.setFormatter(formatter) 
logger.addHandler(ph)

## 默认的IIC通信地址
BOSON_ADC_MODULE_DEFAULT_IIC_ADDR = 0x06
## 模块的PID (BOS0063)(最高两位作为种类判断00:SEN、01:DFR、10:TEL、11:BOS, 后面14位作为num)
BOSON_ADC_MODULE_PID              = 0xC03F

# BOSON_ADC_MODULE register address
## 模块的PID存储寄存器, 默认值0xC03F (最高两位作为种类判断00：SEN、01：DFR、10：TEL、11:BOS, 后面14位作为num)
BOSON_ADC_MODULE_PID_MSB_REG      = 0x00
BOSON_ADC_MODULE_PID_LSB_REG      = 0x01
## 模块的VID存储寄存器，默认值0x3343（代表厂商为DFRobot）
BOSON_ADC_MODULE_VID_MSB_REG      = 0x02
BOSON_ADC_MODULE_VID_LSB_REG      = 0x03
## 固件版本号存储寄存器：0x0100代表V0.1.0.0
BOSON_ADC_MODULE_VERSION_MSB_REG  = 0x04
BOSON_ADC_MODULE_VERSION_LSB_REG  = 0x05
## 模块的通信地址存储寄存器，默认值0x06
BOSON_ADC_MODULE_ADDR_REG         = 0x07
## 模拟信号A1
BOSON_ADC_MODULE_ADC1_MSB_REG     = 0x08
BOSON_ADC_MODULE_ADC1_LSB_REG     = 0x09
## 模拟信号A2
BOSON_ADC_MODULE_ADC2_MSB_REG     = 0x0A
BOSON_ADC_MODULE_ADC2_LSB_REG     = 0x0B

class DFRobot_BosonAdcModule(object):
    '''!
      @brief 定义DFRobot_BosonAdcModule类
      @details 用于驱动adc采集模块
    '''

    PID = 0
    VID = 0
    version = 0
    IIC_addr = 0

    def __init__(self, i2c_addr=BOSON_ADC_MODULE_DEFAULT_IIC_ADDR, bus=1):
        '''!
          @brief Module init
          @param i2c_addr IIC通信地址
          @param bus IIC通信总线
        '''
        '''初始化配置参数'''
        self._iic_addr = i2c_addr
        self._i2c = smbus.SMBus(bus)

    def begin(self):
        '''!
          @brief Initialize sensor
          @return  返回初始化状态
          @retval True indicate initialization succeed
          @retval False indicate initialization failed
        '''
        ret = True
        chip_id = self._read_reg(BOSON_ADC_MODULE_PID_MSB_REG, 2)
        logger.info((chip_id[0] << 8) | chip_id[1])
        if BOSON_ADC_MODULE_PID != (chip_id[0] << 8) | chip_id[1]:
            ret = False
        return ret

    def read_basic_info(self):
        '''!
          @brief 读取模块基本信息
          @n     重新从传感器获取其基本信息, 并缓存到存储信息的变量里面:
          @n     PID, VID, version, IIC_addr
        '''
        data = self._read_reg(BOSON_ADC_MODULE_PID_MSB_REG, 8)

        self.PID = (data[0] << 8) | data[1]   # PID
        self.VID = (data[2] << 8) | data[3]   # VID
        self.version = (data[4] << 8) | data[5]   # version
        self.IIC_addr = data[7]   # IIC addr

    def get_analog_signal_A1(self):
        '''!
          @brief 获取模拟信号A1
          @return 返回值范围为： 0-1023
        '''
        data = self._read_reg(BOSON_ADC_MODULE_ADC1_MSB_REG, 2)
        return (data[0] << 8) | data[1]

    def get_analog_signal_A2(self):
        '''!
          @brief 获取模拟信号A2
          @return 返回值范围为： 0-1023
        '''
        data = self._read_reg(BOSON_ADC_MODULE_ADC2_MSB_REG, 2)
        return (data[0] << 8) | data[1]

    def _write_reg(self, reg, data):
        '''!
          @brief writes data to a register
          @param reg register address
          @param data written data
        '''
        if isinstance(data, int):
            data = [data]
            #logger.info(data)
        self._i2c.write_i2c_block_data(self._iic_addr, reg, data)

    def _read_reg(self, reg, length):
        '''!
          @brief read the data from the register
          @param reg register address
          @param length read data length
        '''
        return self._i2c.read_i2c_block_data(self._iic_addr, reg, length)
