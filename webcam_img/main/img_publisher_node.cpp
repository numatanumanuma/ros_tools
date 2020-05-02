#include <webcam_img/img_publisher.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "img_publisher");
    //ノード名の初期化
    ros::NodeHandle nh;
    ImgPublisher ImgPublisher;

    ros::spin();

    return 0;
}