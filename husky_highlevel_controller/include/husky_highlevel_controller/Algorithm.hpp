/**
 * @file Algorithm.hpp
 * @author Tom Georgi (Tom.Georgi@htwg-konstanz.de)
 * @author Christian Schmeisser (Christian.Schmeißer@htwg-konstanz.de)
 * @brief Contains algorithms
 * @version 0.1
 * @date 2021-04-16
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include <geometry_msgs/Pose.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/ColorRGBA.h>
#include <tf/tf.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <tf2_ros/transform_listener.h>
#include <visualization_msgs/Marker.h>

#include <tuple>

namespace husky_highlevel_controller
{
  /**
   * @brief Class containing the algorithms of the package.
   *
   */
  class Algorithm
  {
  private:
    // TF2 Buffer
    tf2_ros::Buffer tf_buffer_;

    // TF2 Transform Listener
    tf2_ros::TransformListener tf_listener_;

  public:
    /**
     * @brief Construct a new Algorithm object
     *
     */
    Algorithm();

    /**
     * @brief Destroy the Algorithm object
     *
     */
    virtual ~Algorithm();

    /**
     * @brief Get the Minimal Distance value and index from a LaserScan message.
     *
     * @param scan LaserScan Message
     * @return std::tuple<int, double> index of closest point, Minimal Distance
     */
    std::tuple<int, double> getMinimalDistance(const sensor_msgs::LaserScan &scan);

    /**
     * @brief Create a New Laser Scan message around the minimal distance.
     * 
     * @param old_scan Old Laser Scan Message
     * @param new_scan New Laser Scan Message
     * @param closest_index index of closest point in the laser scan message.
     * @param min_val value of the minimal distance in the laser scan message.
     * @param range_size range size around the minimal distance point.
     * @return bool, true for success false for fail
     */
    bool createLaserScanAroundMD(const sensor_msgs::LaserScan &old_scan, sensor_msgs::LaserScan &new_scan, int closest_index, double min_val, int range_size);

    /**
     * @brief Calculate the P-Ratio for a new cmd vel msg
     * 
     * @param old_cmd_vel old cmd vel message
     * @param kp Factor of the P-Ratio
     * @param new_cmd_vel new cmd vel message
     */
    void calculatePRatio(const geometry_msgs::Twist &old_cmd_vel, const double kp, double angle, geometry_msgs::Twist &new_cmd_vel);

    /**
     * @brief Create a Marker object
     * 
     * @param x x position
     * @param y y poistion
     * @param frame_id frame_id of marker
     * @param marker_id marker_id
     * @param marker_color color of marker
     * @return visualization_msgs::Marker marker object
     */
    visualization_msgs::Marker createMarker(const double x, const double y,
                                            const std::string frame_id,
                                            const int marker_id,
                                            const std_msgs::ColorRGBA marker_color);

    /**
     * @brief Transform Pose
     * 
     * @param src source pose
     * @param dest destination pose
     * @param src_frame_id source frame id
     * @param dest_frame_id destination frame id
     * @return true success
     * @return false failed
     */
    bool transformPose(const geometry_msgs::Pose src,
                       geometry_msgs::Pose dest,
                       const std::string src_frame_id,
                       const std::string dest_frame_id);
  };
} // namespace husky_highlevel_controller
