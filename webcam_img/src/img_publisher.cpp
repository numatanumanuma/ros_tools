#include "webcam_img/img_publisher.h"
   
ImgPublisher::ImgPublisher():it(nh){
    ros::NodeHandle nh_private("~");
    img_pub = it.advertise("img_publisher/image", 10);
    timer = nh.createTimer(ros::Duration(0.05), &ImgPublisher::timerCallback, this);
    image_size.width = 1920;
    image_size.height = 1080;
    ImgPublisher::captureImg(1, image_size);
}

ImgPublisher::~ImgPublisher(){

}

void ImgPublisher::captureImg(int device_num, cv::Size image_size){
    cv::VideoCapture capture;
    capture.open(device_num);
    if (!capture.isOpened()) {
        ROS_INFO("failed to open camera.");
        return;
    }
    ROS_INFO("Start");
    ros::Rate looprate (10); // capture image at 10Hz
    while(ros::ok()){
        capture >> image;
        // cv::imshow("imge", image);
        // cv::waitKey(1);
        sensor_msgs::ImagePtr cam_msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();
        img_pub.publish(cam_msg);
        looprate.sleep();
    }
}

void ImgPublisher::timerCallback(const ros::TimerEvent&){

}
