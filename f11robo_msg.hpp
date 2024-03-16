#pragma once
#include <cmath>
#include <iostream>
#include <numeric>
#include <ratio>
#include <vector>

namespace f11robo
{
  namespace param
  {
    constexpr double R = 33.35 * 0.001f; // [m]
    constexpr double L = 105.0f * 0.001f; // [m]
  }
  //
  constexpr uint8_t DATA_HEADER = 0x01;
  constexpr uint8_t PARAM_HEADER = 0x02;
  constexpr uint8_t END = 0x04;
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
  struct vector3_t
  {
    float32_t x; //4byte
    float32_t y; //4byte
    float32_t z; //4byte
  };//12byte
  struct pid_gain_t
  {
    float32_t kp; //4byte
    float32_t ki; //4byte
    float32_t kd; //4byte
  };//12byte
  struct sensor_data_t
  {
    uint8_t light[5];//5byte
    bool sw[2];//2byte
  };//7byte
  //union
  struct sensor_msg_t
  {
    constexpr static size_t size = 57;
    velocity_t velocity;//8byte
    rpy_t rpy;//12byte
    vector3_t acc;//12byte
    vector3_t gyro;//12byte
    sensor_data_t sensor_data;//7byte
    bool ems;//1byte
    float32_t battery_voltage;//4byte
    bool button;//1byte
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
      else if(i<24)
        acc.x.byte[i-20]=data;
      else if(i<28)
        acc.y.byte[i-24]=data;
      else if(i<32)
        acc.z.byte[i-28]=data;
      else if(i<36)
        gyro.x.byte[i-32]=data;
      else if(i<40)
        gyro.y.byte[i-36]=data;
      else if(i<44)
        gyro.z.byte[i-40]=data;
      else if(i<49)
        sensor_data.light[i-44]=data;
      else if(i<51)
        sensor_data.sw[i-49]=data;
      else if(i<52)
        ems=data;
      else if(i<56)
        battery_voltage.byte[i-52]=data;
      else
        button=data;
    }
    std::vector<uint8_t> get_data()
    {
      std::vector<uint8_t> data;
      for (const auto byte : velocity.left_wheel.byte)
        data.push_back(byte);
      for (const auto byte : velocity.right_wheel.byte)
        data.push_back(byte);
      for (const auto byte : rpy.roll.byte)
        data.push_back(byte);
      for (const auto byte : rpy.pitch.byte)
        data.push_back(byte);
      for (const auto byte : rpy.yaw.byte)
        data.push_back(byte);
      for (const auto byte : acc.x.byte)
        data.push_back(byte);
      for (const auto byte : acc.y.byte)
        data.push_back(byte);
      for (const auto byte : acc.z.byte)
        data.push_back(byte);
      for (const auto byte : gyro.x.byte)
        data.push_back(byte);
      for (const auto byte : gyro.y.byte)
        data.push_back(byte);
      for (const auto byte : gyro.z.byte)
        data.push_back(byte);
      for (const auto byte : sensor_data.light)
        data.push_back(byte);
      for (const auto byte : sensor_data.sw)
        data.push_back((uint8_t)byte);
      data.push_back((uint8_t)ems);
      for (const auto byte : battery_voltage.byte)
        data.push_back(byte);
      data.push_back((uint8_t)button);
      return data;
    }
  };
  struct command_msg_t
  {
    constexpr static size_t size = 8;
    velocity_t velocity;//8byte
    void set(int i,uint8_t data)
    {
      if(i<4)
        velocity.left_wheel.byte[i]=data;
      else
        velocity.right_wheel.byte[i-4]=data;
    }
    std::vector<uint8_t> get_data()
    {
      std::vector<uint8_t> data;
      for (const auto byte : velocity.left_wheel.byte)
        data.push_back(byte);
      for (const auto byte : velocity.right_wheel.byte)
        data.push_back(byte);
      return data;
    }
  };

  struct param_msg_t
  {
    constexpr static size_t size = 24;
    pid_gain_t left_md_pid_gain;//12byte
    pid_gain_t right_md_pid_gain;//12byte
    void set(int i,uint8_t data)
    {
      if(i<4)
        left_md_pid_gain.kp.byte[i]=data;
      else if(i<8)
        left_md_pid_gain.ki.byte[i-4]=data;
      else if(i<12)
        left_md_pid_gain.kd.byte[i-8]=data;
      else if(i<16)
        right_md_pid_gain.kp.byte[i-12]=data;
      else if(i<20)
        right_md_pid_gain.ki.byte[i-16]=data;
      else
        right_md_pid_gain.kd.byte[i-20]=data;
    }
    std::vector<uint8_t> get_data()
    {
      std::vector<uint8_t> data;
      for (const auto byte : left_md_pid_gain.kp.byte)
        data.push_back(byte);
      for (const auto byte : left_md_pid_gain.ki.byte)
        data.push_back(byte);
      for (const auto byte : left_md_pid_gain.kd.byte)
        data.push_back(byte);
      for (const auto byte : right_md_pid_gain.kp.byte)
        data.push_back(byte);
      for (const auto byte : right_md_pid_gain.ki.byte)
        data.push_back(byte);
      for (const auto byte : right_md_pid_gain.kd.byte)
        data.push_back(byte);
      return data;
    }
  };
} // namespace f11robo
