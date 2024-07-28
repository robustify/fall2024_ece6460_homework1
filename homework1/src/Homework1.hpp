// Prevent multiple declarations caused by including
//     this header file from multiple locations
#pragma once

// ROS header
#include <ros/ros.h>

// Namespace matches ROS package name
namespace homework1 {

  class Homework1 {
    public:
      Homework1(ros::NodeHandle& n, ros::NodeHandle& pn);

    private:
      // Node-specific stuff here
  };

}
