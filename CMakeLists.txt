cmake_minimum_required(VERSION 3.2)
project(DicesServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(MISCELLANOUS Miscellanous/DateTime/Time/LocalTime.cpp Miscellanous/DateTime/Time/LocalTime.h Miscellanous/DateTime/Date/LocalDate.cpp Miscellanous/DateTime/Date/LocalDate.h Miscellanous/DateTime/LocalDateTime.cpp Miscellanous/DateTime/LocalDateTime.h)

set(SOURCE_FILES main.cpp)
find_package(Boost 1.54.0 COMPONENTS system filesystem REQUIRED)
find_package(JNI)

if (JNI_FOUND)
    message (STATUS "JNI_INCLUDE_DIRS=${JNI_INCLUDE_DIRS}")
    message (STATUS "JNI_LIBRARIES=${JNI_LIBRARIES}")

    include_directories(${JNI_INCLUDE_DIRS})
else()
    message(WARNING "JNI Not found")
endif()

if(Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})

else()
    message(WARNING "Boost not found")

endif()


add_executable(DicesServer ${SOURCE_FILES} ${MISCELLANOUS} JNI-test/SimpleInstanceJNI.cpp JNI-test/SimpleInstanceJNI.h)

if(Boost_FOUND)

    target_link_libraries(DicesServer ${Boost_LIBRARIES})

endif()