cmake_minimum_required(VERSION 3.28)
project(assignment1 VERSION 1.0 LANGUAGES C CXX)



include_directories(include)
add_executable(assignment1_cpp src/assignment1.cpp)

# Set C++17 standard for the targets
set_property(TARGET assignment1_cpp PROPERTY CXX_STANDARD 17)
set_property(TARGET assignment1_cpp PROPERTY CXX_STANDARD_REQUIRED ON)

# --- Add this section to integrate Valgrind ---
# Find the valgrind executable on the system
find_program(VALGRIND_EXECUTABLE valgrind)

# Only create the targets if valgrind is found
if(VALGRIND_EXECUTABLE)

    # --- Target for Memory Leak Checking (memcheck) ---
    add_custom_target(memcheck)

    add_custom_command(
        TARGET memcheck
        COMMAND ${VALGRIND_EXECUTABLE} --leak-check=full --track-origins=yes $<TARGET_FILE:assignment1_cpp>
        COMMENT "Running Valgrind Memcheck on assignment1_cpp"
    )

    # Ensure executables are built before any tool runs
    add_dependencies(memcheck assignment1_cpp)

endif()
