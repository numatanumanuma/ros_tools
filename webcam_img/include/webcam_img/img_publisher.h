#ifndef IMG_PUBLISHER_H
#define IMG_PUBLISHER_H

#include "ros/ros.h"
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
   
class ImgPublisher{
public:
    ImgPublisher();
    ~ImgPublisher();
    void captureImg(int device_num, cv::Size image_size);
    void timerCallback(const ros::TimerEvent&);
    
   
private:
    ros::Timer timer;
    ros::NodeHandle nh;
    image_transport::ImageTransport it;
    image_transport::Publisher img_pub;

    cv::Mat image;
    cv::Size image_size;

};

#endif
