#include <webcam_img/img_subscriber.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "img_subscriber");
    //ノード名の初期化
    ros::NodeHandle nh;
    ImgSubscriber ImgSubscriber;

    ros::spin();

    return 0;
}