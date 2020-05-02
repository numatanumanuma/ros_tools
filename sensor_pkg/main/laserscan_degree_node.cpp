/*
動作確認用
*/


#include "ros/ros.h"
#include "sensor_pkg/laserscan_degree.h"

#include <tuple>

class sensorTest{
  public:
    sensorTest();
    ~sensorTest();
    void timerCallback(const ros::TimerEvent&);
    laserScanDegree scan;
    // 宣言
  private:
    ros::NodeHandle nh;
    ros::Timer timer;
};

sensorTest::sensorTest(){
  timer = nh.createTimer(ros::Duration(0.1), &sensorTest::timerCallback, this);
}

sensorTest::~sensorTest(){

}

void sensorTest::timerCallback(const ros::TimerEvent&){
    float d = scan.getScanDistance(0);
    int degree;
    float distance;
    std::tie(degree, distance) = scan.findObstacleDegree(-90, 0);
    ROS_INFO("%f %d %f", d, degree, distance);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "sensor_test");
  //ノード名の初期化

  sensorTest sensorTest;

  ros::spin();

  return 0;
}