/**
 * @file main.cpp
 * @author Mckenzie Crandall
 * @brief Assignment2: A Triple-Sensor System (generator and processor)
 * @version 1.0
 * @date 09-30-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "sensor_types.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <cmath>

int main() {
  // Storage for all sensor data across timestamps
  std::vector<TimestampData> sensor_readings;

  // Quality tracking variables
  const std::unordered_map<std::string, int> initial_counts{{"LIDAR", 0},
                                                            {"Camera", 0},
                                                            {"IMU", 0}};
  std::unordered_map<std::string, int> valid_readings{initial_counts};
  std::unordered_map<std::string, int> total_readings{initial_counts};

  // Variables for calculating summary statistics
  double total_lidar_avg_distance{0.0};
  double total_camera_brightness{0.0};
  double total_imu_avg_rotation{0.0};
  int total_obstacles_detected{0};
  int day_mode_count{0};
  int night_mode_count{0};
  int stable_count{0};
  int unstable_count{0};

  std::cout << std::fixed << std::setprecision(2);

  std::cout << "=== ROBOT DUAL-SENSOR SYSTEM ===\n\n";

  // ========================================================================
  // Step 1: Data Generation and Storage
  // ========================================================================
  std::cout << "Generating sensor data for 5 timestamps...\n\n";

  // Part A: random number generator set up
  std::random_device rd;
  std::mt19937 gen{rd()};
  std::uniform_real_distribution<> lidar_dist(lidar_min_range, lidar_max_range);
  std::uniform_real_distribution<> imu_dist(imu_min_rotation, imu_max_rotation);
  std::uniform_int_distribution<> camera_dist(rgb_min, rgb_max);

  // Part B: create main storage container
  sensor_readings.reserve(5);

  // Part C: Data Generation Loop
  for (int i{0}; i <= 4; i++) {
    std::vector<double> lidar_data{};
    lidar_data.reserve(8);
    for (int n{0}; n <= 7; n++) {
      lidar_data.push_back(lidar_dist(gen));
    }
    std::tuple<int, int, int> camera_data(camera_dist(gen), camera_dist(gen), camera_dist(gen));
    std::tuple<double, double, double> imu_data(imu_dist(gen), imu_dist(gen), imu_dist(gen));

    TimestampData newTimestamp;
    for (double val : lidar_data) {
      newTimestamp.lidar_readings.push_back(val);
    }
    newTimestamp.imu_readings = imu_data;
    newTimestamp.camera_readings = camera_data;
    newTimestamp.timestamp = i;
    sensor_readings.push_back(newTimestamp);
  }

  // ========================================================================
  // Step 2: Data Processing Loop
  // ========================================================================

  // Initialize required vectors
  std::vector<double> avg_lidar_readings;
  std::vector<int> obstacle_tracker;
  std::vector<double> avg_camera_brightness;
  std::vector<std::string> camera_mode_tracker;
  std::vector<double> avg_imu_rotation;
  std::vector<std::string> imu_stable_tracker;

  for (const auto& data : sensor_readings) {
    std::cout << "Processing Timestamp: " << data.timestamp << "*************************************" << '\n';

  // ========================================================================
  // Step 3: Sensor-Specific Processing
  // ========================================================================  
  
  // steps 3 and 4 are happening concurrently below

  // ========================================================================
  // Step 4: Quality Assessment and Status Determination
  // ========================================================================
    
    // LiDAR processing ********************
    // Initialize required variables
    int obstacle_count{0};
    bool poor_lidar_reading = false;
    std::string lidar_status;

    // Calculate average for one timestamp instance and add to lidar average vector
    double lidar_sum = std::accumulate(data.lidar_readings.begin(), data.lidar_readings.end(), 0.0);
    double lidar_average = lidar_sum / data.lidar_readings.size();
    avg_lidar_readings.push_back(lidar_average);
    
    // Check if there was an obstacle and if the reading was valid
    for (double lidar_output : data.lidar_readings) {
      if (lidar_output < obstacle_threshold && lidar_output > lidar_min_valid) {
        ++obstacle_count;
      } else if (lidar_output < lidar_min_valid) {
        poor_lidar_reading = true;
      }
    }

    // Add obstacle to counter vector
    obstacle_tracker.push_back(obstacle_count);

    // Add timestamp count to total readings count
    ++total_readings["LIDAR"];

    // Add reading status to counter vector
    if (!poor_lidar_reading) {
      ++valid_readings["LIDAR"];
      lidar_status = "GOOD";
    } else {
      lidar_status = "POOR";
    }
    
    // Print out LIDAR readings
    std::cout << "- LIDAR: [" << data.lidar_readings[0] << ", " << data.lidar_readings[1] << ", " << data.lidar_readings[2] << 
                  ", " << data.lidar_readings[3] << ", " << data.lidar_readings[4] << ", " << data.lidar_readings[5] << ", " <<
                  data.lidar_readings[6] << ", " << data.lidar_readings[7] << "]" << '\n';
    std::cout << "     Avg = " << lidar_average << "m, " << "Obstacles = " << obstacle_count << ", Status = " << lidar_status << '\n';


    // Camera Processing ***************
    // Initialize variables
    const auto [r, g, b] = data.camera_readings;
    double brightness = (r + g + b) / 3.0;
    std::string day_night_mode;
    std::string camera_status;

    // Calculate average brightness
    avg_camera_brightness.push_back(brightness);
    
    // Check whether day/night and quality status
    if (brightness > day_night_threshold) {
      day_night_mode = "DAY";
      ++valid_readings["Camera"];
      ++total_readings["Camera"];
      camera_status = "GOOD";
    } else {
      day_night_mode = "NIGHT";
      ++total_readings["Camera"];
      camera_status = "POOR";
    }

    // Add mode to tracker vector
    camera_mode_tracker.push_back(day_night_mode);

    // Print out camera stats
    std::cout << "- Camera: RGB(" << r << ", " << g << ", " << b << "), Brightness = " << brightness << ", Mode = " << day_night_mode <<
                ", Status = " << camera_status << '\n';


    // IMU Processing ***************
    // Initialize variables
    const auto [roll, pitch, yaw] = data.imu_readings;
    std::string imu_mode;
    std::string imu_status;

    // Calculate rotation and add it to vector
    const auto rotation_mag = std::sqrt(std::pow(roll, 2) + std::pow(pitch, 2) + std::pow(yaw, 2));
    avg_imu_rotation.push_back(rotation_mag);
    
    // Check stability
    if (abs(roll) < imu_stability_threshold && abs(pitch) < imu_stability_threshold && abs(yaw) < imu_stability_threshold) {
      imu_mode = "STABLE";
    } else {
      imu_mode = "UNSTABLE";
    }

    // Add stability status to vector
    imu_stable_tracker.push_back(imu_mode);

    // Check if reading was valid and add total count and valid count to trackers
    if (roll < imu_max_rotation && pitch < imu_max_rotation && yaw < imu_max_rotation && roll > imu_min_rotation && pitch > imu_min_rotation && yaw > imu_min_rotation) {
      ++valid_readings["IMU"];
      ++total_readings["IMU"];
      imu_status = "GOOD";
    } else {
      ++total_readings["IMU"];
      imu_status = "POOR";
    }

    // Print IMU stats
    std::cout << "- IMU: RPY(" << abs(roll) << ", " << abs(pitch) << ", " << abs(yaw) << ", Total Rotation = " << rotation_mag << ", Mode = " <<
    imu_mode << ", Status = " << imu_status << "\n\n";
  }

  // ========================================================================
  // STEP 5: Summary Statistics and Display
  // ========================================================================
  std::cout << "=== SUMMARY STATISTICS ===\n";

  std::cout << std::fixed << std::setprecision(1);

  // Initialize required variables
  int sum_total_readings{0};
  int sum_valid_readings{0};
  double valid_percent{0.0};
  double lidar_percent{0.0};
  double camera_percent{0.0};
  double imu_percent{0.0};
  std::string target_camera_string = "DAY";
  std::string target_imu_string = "STABLE";

  // Get total readings
  for (const auto& total : total_readings) {
    sum_total_readings += total.second;
  }

  // Get total valid readings
  for (const auto& valids : valid_readings) {
    sum_valid_readings += valids.second;
  }

  // Calculate overall summary statistics
  valid_percent = (static_cast<double>(sum_valid_readings) / sum_total_readings) * 100;

  // Calculate LIDAR summary statistics
  lidar_percent = (static_cast<double>(valid_readings["LIDAR"]) / total_readings["LIDAR"]) * 100;
  double total_lidar_distance = std::accumulate(avg_lidar_readings.begin(), avg_lidar_readings.end(), 0.0);
  total_lidar_avg_distance = total_lidar_distance / avg_lidar_readings.size();
  total_obstacles_detected = std::accumulate(obstacle_tracker.begin(), obstacle_tracker.end(), 0.0);

  // Calculate Camera summary statistics
  camera_percent = (static_cast<double>(valid_readings["Camera"]) / total_readings["Camera"]) * 100;
  double sum_camera_brightness = std::accumulate(avg_camera_brightness.begin(), avg_camera_brightness.end(), 0.0);
  total_camera_brightness = sum_camera_brightness / avg_camera_brightness.size();
  day_mode_count = std::count(camera_mode_tracker.begin(), camera_mode_tracker.end(), target_camera_string);
  night_mode_count = camera_mode_tracker.size() - day_mode_count;

  // Calculate IMU summary statistics
  imu_percent = (static_cast<double>(valid_readings["IMU"]) / total_readings["IMU"]) * 100;
  double sum_imu_rotation = std::accumulate(avg_imu_rotation.begin(), avg_imu_rotation.end(), 0.0);
  total_imu_avg_rotation = sum_imu_rotation / avg_imu_rotation.size();
  stable_count = std::count(imu_stable_tracker.begin(), imu_stable_tracker.end(), target_imu_string);
  unstable_count = imu_stable_tracker.size() - stable_count;

  // Print summary statistics
  std::cout << "Total Readings Processed = " << sum_total_readings << "\n";
  std::cout << "Valid Readings = " << sum_valid_readings << "(" << valid_percent << "%)" << "\n\n";

  std::cout << "Sensor Reliability Report:\n";
  std::cout << "LIDAR = " << valid_readings["LIDAR"] << "/" << total_readings["LIDAR"] << " (" << lidar_percent << "%)\n";
  std::cout << "Camera = " << valid_readings["Camera"] << "/" << total_readings["Camera"] << " (" << camera_percent << "%)\n";
  std::cout << "IMU = " << valid_readings["IMU"] << "/" << total_readings["IMU"] << " (" << imu_percent << "%)\n\n";

  std::cout << "Operational Statistics:\n";
  std::cout << "  - Average LIDAR Distance = " << total_lidar_avg_distance << "m\n";
  std::cout << "   - Total Obstacles Detected = " << total_obstacles_detected << "\n";
  std::cout << "  - Average Camera Brightness = " << total_camera_brightness << "\n";
  std::cout << "   - Total Day Mode Detections = " << day_mode_count << "\n";
  std::cout << "   - Total Night Mode Detections = " << night_mode_count << "\n";
  std::cout << "  - Average IMU Total Rotation = " << total_imu_avg_rotation << " deg\n";
  std::cout << "   - Total Stable Detections = " << stable_count << "\n";
  std::cout << "   - Total Unstable Detections = " << unstable_count << "\n";

}