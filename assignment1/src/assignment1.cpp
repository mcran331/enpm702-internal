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

    // Exit scenario
    if (user_select == 5) {
      std::cout << "Exiting the Robot Simulator. Goodbye\n\n";
      break;
    }

    switch (user_select)
    {
      case 1: // Move Forward scenario
        while (true) {
          std::cout << "Input a distance to move forward: ";
          std::cin >> forward_move;

          // Check if user_input is valid
          if (std::cin.fail()) {
            std::cout << "\n*********ROAR ERROR MONSTER HAS BEEN AWOKEN*********\n";
            std::cout << "************You must input a decimal number to move forward and silence the error monster!************\n\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;

          } else if (forward_move < 0) { // Check if user wants to move backwards
            while (true) {
              std::cout << "**You must input a positive number to move forward, would you like to move backwards instead? (y/n): ";
              char backwards_select{};
              std::cin >> backwards_select;

              // If yes, move the robot backwards
              if (backwards_select == 'y') {
                robot_orientation_rad = robot_orientation_deg * (pi/180);
                robot_x_position = robot_x_position + forward_move * cos(robot_orientation_rad);
                robot_y_position = robot_y_position + forward_move * sin(robot_orientation_rad);
                std::cout << "Robot moved forward " << forward_move << ". New Robot Position = (" << 
                std::trunc(robot_x_position * 100) / 100 << ", " << std::trunc(robot_y_position * 100) / 100 << ")\n\n";
                std::cout << "------------------\n";
                break;
              } else if (backwards_select == 'n') { // If no, return to the Robot Main Menu
                std::cout << "*****Returning to Robot Main Menu*****\n\n";
                break;
              } else { // Error state, ask the user for input again
                std::cout << "***Please Enter 'y' or 'n'***\n\n";
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                continue;
              }
            }
          } else { // If no errors and user_input is > 0, move the robot forwards, report status, and return to main menu
            robot_orientation_rad = robot_orientation_deg * (pi/180);
            robot_x_position = robot_x_position + forward_move * cos(robot_orientation_rad);
            robot_y_position = robot_y_position + forward_move * sin(robot_orientation_rad);
            std::cout << "Robot moved forward " << forward_move << ". New Robot Position = (" << 
            std::trunc(robot_x_position * 100) / 100 << ", " << std::trunc(robot_y_position * 100) / 100 << ")\n\n";
            std::cout << "------------------\n";
            break;
          }
          break;
        }
        break;
      case 2: // Turn Left scenario
        while (true) {
          std::cout << "Input an angle (in degrees) to turn left: ";
          std::cin >> left_deg;

          // Check if user_input is valid
          if (std::cin.fail() || left_deg < 0) {
            std::cout << "\n*********ROAR ERROR MONSTER HAS BEEN AWOKEN*********\n";
            std::cout << "************You must input a positive decimal number to turn and silence the error monster!************\n\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
          }

          robot_orientation_deg += left_deg; // turn the robot left

          // Keep robot_orientation < 360 degrees and report status
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
          else { // Report status if robot_orientation already < 360
              robot_orientation_rad = robot_orientation_deg * (pi/180);
              std::cout << "Robot turned " << left_deg << " degrees. New Robot Orientation = " << 
              robot_orientation_deg << " degrees" "\n\n";
              std::cout << "------------------\n";
              break;
          }
        }
        break;
      case 3: // Turn Right scenario
        while (true) {
          std::cout << "Input an angle (in degrees) to turn right: ";
          std::cin >> right_deg;

          // Check if user_input is valid
          if (std::cin.fail() || right_deg < 0) {
            std::cout << "\n*********ROAR ERROR MONSTER HAS BEEN AWOKEN*********\n";
            std::cout << "************You must input a positive decimal number to turn and silence the error monster!************\n\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
          }

          robot_orientation_deg -= right_deg; // Turn the robot right

          // Keep robot_orientation > 0 and report status
          if (robot_orientation_deg < 0) {
            while (robot_orientation_deg < 0) {
              robot_orientation_deg = robot_orientation_deg + 360;
            }
            robot_orientation_rad = robot_orientation_deg * (pi/180);
            std::cout << "Robot turned " << right_deg << " degrees. New Robot Orientation = " << robot_orientation_deg << " degrees" "\n\n";
            std::cout << "------------------\n";
            break;
          } 
          else { // Report status if robot_orientation already > 0
            robot_orientation_rad = robot_orientation_deg * (pi/180);
            std::cout << "Robot turned " << left_deg << " degrees. New Robot Orientation = " << robot_orientation_deg << " degrees" "\n\n";
            std::cout << "------------------\n";
            break;
          }
        }
        break;
      case 4: // Report Status scenario
        std::cout << "Robot Status Report:\n";
        std::cout << "Robot Position = (" << std::trunc(robot_x_position * 100) / 100 << ", " << std::trunc(robot_y_position * 100) / 100 << ")\n";
        std::cout << "Robot Orientation = " << std::trunc(robot_orientation_deg *100) / 100 << "\n\n";
        std::cout << "------------------\n";
        break;
      default:
        // Check if user_input is not an integer
        try {
        // Check if user_input is not an integer or between 1 and 5
          if (user_select <= 0 || user_select > 5 || std::cin.fail()) {
            throw 404;
          }
        }
        catch (int err) { // Report there has been an error and return to main menu
          std::cout << "\nERROR MONSTER " << err << "\n";
          std::cout << "\n************You must enter an integer from 1-5 to silence the error monster!************\n\n\n";
          std::cin.clear();
          std::cin.ignore(1000, '\n');
        }
        break;
    }
  }
}