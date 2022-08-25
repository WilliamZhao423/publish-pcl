#include <ros/ros.h>
#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl/io/pcd_io.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;


main(int argc, char **argv)
{
    ros::init (argc, argv, "pcl_read"); 

    ros::NodeHandle nh;
    ros::Publisher pcl_pub = nh.advertise<sensor_msgs::PointCloud2> ("pcl_output", 10);
    
    sensor_msgs::PointCloud2 output;
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    

	
	pcl::io::loadPCDFile<pcl::PointXYZ> ("/home/yimin/cloud.pcd", *cloud);

    cout << "Read Data" << endl;    
    pcl::toROSMsg(*cloud, output);
    
    output.header.frame_id = "odom";
    ros::Rate loop_rate(1);
    while (ros::ok())
    {
        pcl_pub.publish(output);
        ros::spinOnce();
        loop_rate.sleep();
        //ros::shutdown();
    }

    return 0;
}

