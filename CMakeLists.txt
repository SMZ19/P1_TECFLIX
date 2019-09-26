cmake_minimum_required(VERSION 3.14)
project(P1_TECFLIX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp windowGUI.cpp windowGUI.h movie.cpp movie.h Page.cpp Page.h linkedList.cpp linkedList.h)
# Include a library search using find_package()
# via REQUIRED, specify that libraries are required
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

add_executable(P1_TECFLIX ${SOURCE_FILES})

# specify which libraries to connect
target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(P1_TECFLIX Qt5::Widgets)