/*
北陽電機の2DLiDARの使用を想定
tupleを使用するためc++11以降のコンパイラで
*/

#include "sensor_pkg/LaserScan_degree.h"
   
laserScanDegree::laserScanDegree(){
    ros::NodeHandle nh_private("~");
    scan_sub = nh.subscribe("/base_scan", 1, &laserScanDegree::msgsCallback, this);
    // stageは/base_scanトピック
    timer = nh.createTimer(ros::Duration(0.05), &laserScanDegree::timerCallback, this);

    ROS_INFO("%f %f", latest_scan.angle_min, latest_scan.angle_max);
}

laserScanDegree::~laserScanDegree(){

}

void laserScanDegree::msgsCallback(const sensor_msgs::LaserScan::ConstPtr& msgs){
    latest_scan = *msgs;
}

void laserScanDegree::timerCallback(const ros::TimerEvent&){
    
}

/*
引数に角度を受け取りその方向のセンサで得た距離を返す
ロボットの前方を0度とし上から見て半時計回りが正方向
angle_minはセンサが認識する最小のラジアンだが、0radのとき
それがロボットの真正面を指しているかは不明（調べる）
ここでは真正面であるとしている
*/
float laserScanDegree::getScanDistance(int degree){
    int i = (- latest_scan.angle_min + degree * M_PI / 180) / latest_scan.angle_increment;
    if (i >= 0 && i < latest_scan.ranges.size()){
        if (latest_scan.ranges[i] >= latest_scan.range_min &&
        latest_scan.ranges[i] <= latest_scan.range_max &&
        ! std::isnan(latest_scan.ranges[i])){
            return latest_scan.ranges[i];
        }
    }
    return -1;
}

/*
一番近い障害物のロボットからの方向と距離を返す
(角度, 距離)
引数に見てほしい範囲を与える
ロボットは後方は認識できないが、180度等を受け取ったらセンサが
認識するスタート地点またはゴール地点に変換する
とりあえずセンサで見れる範囲すべてを確認して欲しいのなら
-180, 180と与えればいい
すべての方向が無限遠などの場合は (-1, -1)を返す
*/
std::tuple<int, float> laserScanDegree::findObstacleDegree(int dmin, int dmax){
    int index_min = (- latest_scan.angle_min + dmin * M_PI / 180) / latest_scan.angle_increment;
    int index_max = (- latest_scan.angle_min + dmax * M_PI / 180) / latest_scan.angle_increment;
    if (index_min > index_max){
        int tmp = index_min;
        index_min = index_max;
        index_max = tmp;
    }
    index_min = std::max(index_min, 0);
    index_max = std::min(index_max, (int)latest_scan.ranges.size());
    int index;
    int degree;
    float distance = 1000;
    for (int i = index_min; i <= index_max; i++){
        if (latest_scan.ranges[i] < distance){
            distance = latest_scan.ranges[i];
            index = i;
        }
    }
    if (distance == 1000){
        distance = -1;
        degree = -1;
    }
    degree = (index * latest_scan.angle_increment + latest_scan.angle_min) * 180 / M_PI; 
    return std::forward_as_tuple(degree, distance);
}
