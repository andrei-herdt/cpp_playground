cmake_minimum_required(VERSION 3.5)
project(boost_msm_visitor
  LANGUAGES CXX
)

find_package(Boost 1.58 REQUIRED COMPONENTS system)

add_executable(${PROJECT_NAME}
    ./src/msm_main.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        utils::utils
)
