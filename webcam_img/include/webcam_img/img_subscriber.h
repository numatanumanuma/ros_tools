#ifndef IMG_SUBSCRIBE_H
#define IMG_SUBSCRIBE_H

#include "ros/ros.h"
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
   
class ImgSubscriber{
public:
    ImgSubscriber();
    ~ImgSubscriber();
    void imageCallback(const sensor_msgs::ImageConstPtr& msgs);
    void timerCallback(const ros::TimerEvent&);
    
   
private:
    ros::Timer timer;
    ros::NodeHandle nh;
    image_transport::ImageTransport it;
    image_transport::Subscriber img_sub;

    cv::Mat image;
    cv::Size image_size;

};

#endif
