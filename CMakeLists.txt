cmake_minimum_required(VERSION 3.5)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set (CMAKE_CXX_STANDARD 11)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIR}
                    ${SDL2_IMAGE_INCLUDE_DIR}
			${SDL2_TTF_INCLUDE_DIR}
                    )

add_executable(
welcome
main.cpp
Environment.h
Environment.cpp
)
target_link_libraries(welcome ${SDL2_LIBRARY}
                             ${SDL2_IMAGE_LIBRARIES} "/usr/lib/x86_64-linux-gnu/libSDL2_ttf.so;-lpthread")

