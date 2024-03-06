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
    void set(int i,uint8_t data)
    {
      if(i<4)
        velocity.left_wheel.byte[i]=data;
      else if(i<8)
        velocity.right_wheel.byte[i-4]=data;
      else if(i<12)
        rpy.roll.byte[i-8]=data;
      else if(i<16)
        rpy.pitch.byte[i-12]=data;
      else if(i<20)
        rpy.yaw.byte[i-16]=data;
      else if(i<26)
        sensor_data.light[i-20]=data;
      else if(i<28)
        sensor_data.sw[i-26]=data;
      else if(i<29)
        ems=(bool)data;
      else
        battery_voltage.byte[i-29]=data;
    }
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
    void set(int i,uint8_t data)
    {
      if(i<4)
        liner_x.byte[i]=data;
      else
        angular_z.byte[i-4]=data;
    }
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
