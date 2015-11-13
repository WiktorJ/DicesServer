cmake_minimum_required(VERSION 3.2)
project(DicesServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
find_package(Boost 1.57.0 COMPONENTS system filesystem REQUIRED)

if(Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})

else()
    message(WARNING "Boost not found")

endif()


add_executable(DicesServer ${SOURCE_FILES})

if(Boost_FOUND)

    target_link_libraries(DicesServer ${Boost_LIBRARIES})

endif()