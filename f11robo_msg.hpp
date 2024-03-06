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
  union float32_t
  {
    float data;
    uint8_t byte[4];
  };
  //struct
  struct velocity_t
  {
    float32_t right_wheel; //4byte
    float32_t left_wheel; //4byte
  };//8byte
  struct rpy_t
  {
    float32_t roll; //4byte
    float32_t pitch; //4byte
    float32_t yaw; //4byte
  };//12byte
  struct sensor_data_t
  {
    uint8_t light[6];//6byte
    bool sw[2];//2byte
  };//8byte
  //union
  struct sensor_msg_t
  {
    velocity_t velocity;//8byte
    rpy_t rpy;//12byte
    sensor_data_t sensor_data;//8byte
    bool ems;//1byte
    float32_t battery_voltage;//4byte
    std::vector<uint8_t> get_data()
    {
      std::vector<uint8_t> data;
      for (const auto byte : velocity.left_wheel.byte)
        data.push_back(byte);
      for (const auto byte : velocity.right_wheel.byte)
        data.push_back(byte);
      for (const auto byte : sensor_data.light)
        data.push_back(byte);
      for (const auto byte : sensor_data.sw)
        data.push_back((uint8_t)byte);
      data.push_back((uint8_t)ems);
      for (const auto byte : battery_voltage.byte)
        data.push_back(byte);
      return data;
    }
  };
  struct command_msg_t
  {
    float32_t liner_x; //4byte
    float32_t angular_z; //4byte
    std::vector<uint8_t> get_data()
    {
      std::vector<uint8_t> data;
      for (const auto byte : liner_x.byte)
        data.push_back(byte);
      for (const auto byte : angular_z.byte)
        data.push_back(byte);
      return data;
    }
  };
} // namespace f11robo
