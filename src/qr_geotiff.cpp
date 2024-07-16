#include <ros/ros.h>
#include <geometry_msgs/TransformStamped.h>
#include "imax_qrcode/TransformStampedArray.h"
#include "hector_worldmodel_msgs/PosePercept.h"
#include "hector_worldmodel_msgs/PerceptInfo.h"


ros::Publisher pub;
void tfsaCb(const imax_qrcode::TransformStampedArrayConstPtr& msg)
{
  hector_worldmodel_msgs::PosePercept pp;
  for (int i = 0; i < msg->transformStampedArray.size(); i++){
    pp.header.frame_id = msg->transformStampedArray[i].header.frame_id;
    pp.header.stamp = msg->transformStampedArray[i].header.stamp;
    pp.pose.pose.position.x = msg->transformStampedArray[i].transform.translation.x;
    pp.pose.pose.position.y = msg->transformStampedArray[i].transform.translation.y;
    pp.pose.pose.position.z = msg->transformStampedArray[i].transform.translation.z;
    pp.info.class_id = "qrcode";
    pp.info.class_support = 1.0;
    pp.info.object_support = 1.0;
    pp.info.name = msg->transformStampedArray[i].child_frame_id;
    pub.publish(pp);
  }
  
}

void tfhazmatCb(const imax_qrcode::TransformStampedArrayConstPtr& msg)
{
  hector_worldmodel_msgs::PosePercept pp;
  for (int i = 0; i < msg->transformStampedArray.size(); i++){
    pp.header.frame_id = msg->transformStampedArray[i].header.frame_id;
    pp.header.stamp = msg->transformStampedArray[i].header.stamp;
    pp.pose.pose.position.x = msg->transformStampedArray[i].transform.translation.x;
    pp.pose.pose.position.y = msg->transformStampedArray[i].transform.translation.y;
    pp.pose.pose.position.z = msg->transformStampedArray[i].transform.translation.z;
    pp.info.class_id = "hazmat";
    pp.info.class_support = 1.0;
    pp.info.object_support = 1.0;
    pp.info.name = msg->transformStampedArray[i].child_frame_id;
    pub.publish(pp);
  }
}

void tfobjectCb(const imax_qrcode::TransformStampedArrayConstPtr& msg)
{
  hector_worldmodel_msgs::PosePercept pp;
  for (int i = 0; i < msg->transformStampedArray.size(); i++){
    pp.header.frame_id = msg->transformStampedArray[i].header.frame_id;
    pp.header.stamp = msg->transformStampedArray[i].header.stamp;
    pp.pose.pose.position.x = msg->transformStampedArray[i].transform.translation.x;
    pp.pose.pose.position.y = msg->transformStampedArray[i].transform.translation.y;
    pp.pose.pose.position.z = msg->transformStampedArray[i].transform.translation.z;
    pp.info.class_id = msg->transformStampedArray[i].child_frame_id;
    pp.info.class_support = 1.0;
    pp.info.object_support = 1.0;
    pp.info.name = msg->transformStampedArray[i].child_frame_id;
    pub.publish(pp);
  }
}



int main(int argc, char** argv)
{
  ros::init(argc, argv, "qr_geotiff");
  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe("/tfsa", 10, tfsaCb);
  ros::Subscriber sub_hazmat = nh.subscribe("/tf_hazmat", 10, tfhazmatCb);
   ros::Subscriber sub_object = nh.subscribe("/tf_object", 10, tfobjectCb);
  pub = nh.advertise<hector_worldmodel_msgs::PosePercept>("/worldmodel/pose_percept", 10);

  ros::spin();
  return 0;
}