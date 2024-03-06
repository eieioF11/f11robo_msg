#pragma once
#include <cmath>
#include <iostream>
#include <numeric>
#include <ratio>
#include <vector>

namespace f11robo
{
  const static uint8_t HEADER = 0x01;
  const static uint8_t END = 0x04;
  //struct
  struct velocity_t
  {
    float right_wheel; //4byte
    float left_wheel; //4byte
  };//8byte
  struct rpy_t
  {
    float roll; //4byte
    float pitch; //4byte
    float yaw; //4byte
  };//12byte
  struct sensor_data_t
  {
    uint8_t light[6];//6byte
    bool sw[2];//2byte
  };//8byte
  //union
  union sensor_msg_t
  {
    velocity_t velocity;//8byte
    rpy_t rpy;//12byte
    sensor_data_t sensor_data;//8byte
    bool ems;//1byte
    float battery_voltage;//4byte
    uint8_t data[33];
  };
  union command_msg_t
  {
    float liner_x; //4byte
    float angular_z; //4byte
    uint8_t data[8];
  };
} // namespace f11robo
