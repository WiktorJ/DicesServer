cmake_minimum_required(VERSION 3.2)
find_package(Boost 1.54.0 COMPONENTS system filesystem REQUIRED)
find_package(JNI REQUIRED)
find_package(Java REQUIRED)
include(UseJava)
project(DicesServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")
set(CMAKE_EXE_LINKER_FLAGS  -I/usr/lib/jvm/java-7-oracle/include/ -I/usr/lib/jvm/java-7-oracle/include/linux/ -L/usr/bin/java -L/usr/lib/jvm/java-7-oracle/jre/lib/amd64/server/ -ljvm)

set(MISCELLANOUS Miscellanous/DateTime/Time/LocalTime.cpp Miscellanous/DateTime/Time/LocalTime.h Miscellanous/DateTime/Date/LocalDate.cpp Miscellanous/DateTime/Date/LocalDate.h Miscellanous/DateTime/LocalDateTime.cpp Miscellanous/DateTime/LocalDateTime.h)

set(SOURCE_FILES main.cpp)

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

if(JNI_FOUND)
    target_link_libraries(DicesServer ${JNI_LIBRARIES})

endif()