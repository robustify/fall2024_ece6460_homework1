#include <gtest/gtest.h>
#include <ros/ros.h>
#include <geometry_msgs/TwistStamped.h>
#include <std_msgs/Float64.h>

ros::NodeHandle* node;
geometry_msgs::TwistStamped g_twist;
bool received_twist;

std_msgs::Float64 g_speed;
bool received_speed;

static constexpr double G_TIME_RESOLUTION = 0.01;
static constexpr double G_TOPIC_TIMEOUT = 10.0;
static constexpr double G_TEST_DURATION = 10.0;

bool foundMessages()
{
  return received_twist && received_speed;
}

void runCheck()
{
  ros::Time timeout_t = ros::Time::now() + ros::Duration(G_TEST_DURATION);
  while (!ros::isShuttingDown() && ((timeout_t - ros::Time::now()).toSec() > 0)) {
    if (foundMessages()) {
      received_speed = false;
      received_twist = false;

      ASSERT_DOUBLE_EQ(g_speed.data, g_twist.twist.linear.x) << "Values did not match (twist message speed = " 
                                                             << g_twist.twist.linear.x
                                                             << ", speed topic value = "
                                                             << g_speed.data << ")";
    }
    ros::spinOnce();
    ros::Duration(G_TIME_RESOLUTION).sleep();
  }

  if ((timeout_t - ros::Time::now()).toSec() > 0) {
    FAIL() << "Test was stopped prematurely";
  }
}

void recvTwist(const geometry_msgs::TwistStampedConstPtr& msg)
{
  g_twist = *msg;
  received_twist = true;
}

void recvSpeed(const std_msgs::Float64ConstPtr& msg)
{
  g_speed = *msg;
  received_speed = true;
}

TEST(Homework1, test_speed_republish)
{
  ros::Time timeout_t = ros::Time::now() + ros::Duration(G_TOPIC_TIMEOUT);
  while(!ros::isShuttingDown() && !foundMessages() && ((timeout_t - ros::Time::now()).toSec() > 0.0)) {
    ros::spinOnce();
    ros::Duration(0.02).sleep();
  }

  EXPECT_TRUE(received_speed) << "Test did not receive speed message";
  EXPECT_TRUE(received_twist) << "Test did not receive twist message";
  ASSERT_TRUE(foundMessages()) << "Missing messages";
  runCheck();
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  ros::init(argc, argv, "homework1_tests");

  node = new ros::NodeHandle();

  ros::Subscriber sub_speed = node->subscribe("vehicle_speed", 1, recvSpeed);
  ros::Subscriber sub_twist = node->subscribe("vehicle/twist", 1, recvTwist);

  received_speed = false;
  received_twist = false;

  ros::AsyncSpinner spinner(3);
  spinner.start();

  int result = RUN_ALL_TESTS();

  spinner.stop();
  node->shutdown();
  delete node;

  return 0;
}
