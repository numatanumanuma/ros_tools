#include "webcam_img/img_subscriber.h"
   
ImgSubscriber::ImgSubscriber():it(nh){
    ros::NodeHandle nh_private("~");
    img_sub = it.subscribe("/img_publisher/image", 1, &ImgSubscriber::imageCallback, this);
    timer = nh.createTimer(ros::Duration(0.05), &ImgSubscriber::timerCallback, this);
    image_size.width = 1920;
    image_size.height = 1080;
}

ImgSubscriber::~ImgSubscriber(){

}

void ImgSubscriber::imageCallback(const sensor_msgs::ImageConstPtr& msg){
	try {
		image = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8)->image;
		ROS_INFO("image subscribed.");
	}
	catch (cv_bridge::Exception& e) {
		ROS_ERROR("cv_bridge exception: %s", e.what());
	}

	cv::imshow("image", image);
	cv::waitKey(3);
}

void ImgSubscriber::timerCallback(const ros::TimerEvent&){

}
