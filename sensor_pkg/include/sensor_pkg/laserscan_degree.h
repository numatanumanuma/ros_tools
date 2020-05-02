#ifndef LASERSCAN_DEGREE_H
#define LASERSCAN_DEGREE_H

#include <math.h>
#include <tuple>
#include "ros/ros.h"
#include <sensor_msgs/LaserScan.h>

class laserScanDegree{
public:
    laserScanDegree();
    ~laserScanDegree();
    void msgsCallback(const sensor_msgs::LaserScan::ConstPtr& msgs);
    void timerCallback(const ros::TimerEvent&);
    float getScanDistance(int degree);
    std::tuple<int, float> findObstacleDegree(int dmin, int dmax);
   
private:
    ros::Subscriber scan_sub;
    ros::Timer timer;
    ros::NodeHandle nh;

    sensor_msgs::LaserScan latest_scan;
};

#endif
