#include <iostream>
#include <cmath>

// write a read me that explains initial position of the robot is pointed to the right at 0,0

int main() {

  // Initialize necessary variables
  double robot_x_position{0.0};
  double robot_y_position{0.0};
  double robot_orientation_deg{0.0};
  const double pi{3.14159265};
  double robot_orientation_rad{};
  int user_select{};
  double forward_move{};
  double left_deg{};
  double right_deg{};

  // Put this outside the main loop so it only appears in the beginning.
  std::cout << "Welcome to the Robot Simulator!\n\n";

  while (true) {

    // Main Menu display (always come back to this after each selection except 'Exit')
    std::cout << "--- Robot Menu ---\n";
    std::cout << "1. Move Forward\n";
    std::cout << "2. Turn Left\n";
    std::cout << "3. Turn Right\n";
    std::cout << "4. Get Robot Status\n";
    std::cout << "5. Exit\n";
    std::cout << "------------------\n";
    std::cout << "Enter your choice: ";
    std::cin >> user_select;

    // Check if user_input is not an integer
    if (std::cin.fail()) {
      std::cout << "\n\n************You must enter an integer!************\n\n\n";
      std::cin.clear();
      std::cin.ignore(1000, '\n');
    }

    // Check if user_input is not between 1 and 5
    if (user_select > 5) {
      std::cout << "\n\n************You must enter an value from 1-5!************\n\n\n";
      std::cin.clear();
      std::cin.ignore(1000, '\n');
    }

    // Exit scenario
    if (user_select == 5) {
      std::cout << "Exiting the Robot Simulator. Goodbye\n\n";
      break;
    }

    switch (user_select){
      case 1:
      // Move Forward scenario
        while (true) {
          std::cout << "Input a distance to move forward: ";
          std::cin >> forward_move;

          // Check if user_input is valid
          if (std::cin.fail() || forward_move < 0) {
            std::cout << "************You must input a positive decimal number to move forward!************\n\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
          } else { 
            robot_orientation_rad = robot_orientation_deg * (pi/180);
            robot_x_position = robot_x_position + forward_move * cos(robot_orientation_rad);
            robot_y_position = robot_y_position + forward_move * sin(robot_orientation_rad);
            std::cout << "Robot moved forward " << forward_move << ". New Robot Position = (" << 
              std::trunc(robot_x_position * 100) / 100 << ", " << std::trunc(robot_y_position * 100) / 100 << ")\n\n";
            std::cout << "------------------\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            break;
          }
          break;
        }
        break;
      case 2:
        while (true) {
          std::cout << "Input an angle (in degrees) to turn left: ";
          std::cin >> left_deg;
          if (std::cin.fail() || left_deg < 0) {
            std::cout << "************You must input a positive decimal number to turn!************\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
          }
          robot_orientation_deg += left_deg;
          if (robot_orientation_deg > 360) {
            while (robot_orientation_deg > 360) {
              robot_orientation_deg = robot_orientation_deg - 360;
            }
            robot_orientation_rad = robot_orientation_deg * (pi/180);
            std::cout << "Robot turned " << left_deg << " degrees. New Robot Orientation = " << 
              robot_orientation_deg << " degrees" "\n\n";
            std::cout << "------------------\n";
            break;
          } 
          else {
              robot_orientation_rad = robot_orientation_deg * (pi/180);
              std::cout << "Robot turned " << left_deg << " degrees. New Robot Orientation = " << 
              robot_orientation_deg << " degrees" "\n\n";
              std::cout << "------------------\n";
              std::cout << "degrees: " << robot_orientation_deg << ", " << "radians: " << robot_orientation_rad << "\n"; //***get rid of
              break;
          }
        }
        break;
      case 3:
        while (true) {
          std::cout << "Input an angle (in degrees) to turn right: ";
          std::cin >> right_deg;
          if (std::cin.fail() || right_deg < 0) {
            std::cout << "************You must input a positive decimal number to turn!************\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
          }
          robot_orientation_deg -= right_deg;
          if (robot_orientation_deg < 0) {
            while (robot_orientation_deg < 0) {
              robot_orientation_deg = robot_orientation_deg + 360;
            }
            robot_orientation_rad = robot_orientation_deg * (pi/180);
            std::cout << "Robot turned " << right_deg << " degrees. New Robot Orientation = " << 
              robot_orientation_deg << " degrees" "\n\n";
            std::cout << "------------------\n";
            std::cout << "degrees: " << robot_orientation_deg << ", " << "radians: " << robot_orientation_rad << "\n"; //***get rid of
            break;
          } 
          else {
            robot_orientation_rad = robot_orientation_deg * (pi/180);
            std::cout << "Robot turned " << left_deg << " degrees. New Robot Orientation = " << 
              robot_orientation_deg << " degrees" "\n\n";
            std::cout << "------------------\n";
            std::cout << "degrees: " << robot_orientation_deg << ", " << "radians: " << robot_orientation_rad << "\n"; //***get rid of
            break;
          }
        }
        break;
      case 4:
        std::cout << "Robot Status Report:\n";
        std::cout << "Robot Position = (" << std::trunc(robot_x_position * 100) / 100 << ", " << std::trunc(robot_y_position * 100) / 100 << ")\n";
        std::cout << "Robot Orientation = " << std::trunc(robot_orientation_deg *100) / 100 << "\n\n";
        std::cout << "------------------\n";
        break;
    }
  }
}