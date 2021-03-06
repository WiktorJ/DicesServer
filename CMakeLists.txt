cmake_minimum_required(VERSION 3.2)
project(DicesServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(/usr/lib/jvm/java-8-oracle/include/)
include_directories(/usr/lib/jvm/java-8-oracle/include/linux/)
set(MISCELLANOUS Miscellanous/DateTime/Time/LocalTime.cpp Miscellanous/DateTime/Time/LocalTime.h Miscellanous/DateTime/Date/LocalDate.cpp Miscellanous/DateTime/Date/LocalDate.h Miscellanous/DateTime/LocalDateTime.cpp Miscellanous/DateTime/LocalDateTime.h)

set(SOURCE_FILES main.cpp Server/ConnectionServer/ClientServer/Exception/ClientNotFoundException.cpp Server/ConnectionServer/ClientServer/Exception/ClientNotFoundException.h Server/ConnectionServer/ClientServer/Exception/ConnectorNotFoundException.cpp Server/ConnectionServer/ClientServer/Exception/ConnectorNotFoundException.h)
find_package(Boost 1.54.0 COMPONENTS system filesystem thread REQUIRED)
find_package(JNI REQUIRED)

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

set(MISCELLANOUS Miscellanous/DateTime/Time/LocalTime.cpp Miscellanous/DateTime/Time/LocalTime.h Miscellanous/DateTime/Date/LocalDate.cpp Miscellanous/DateTime/Date/LocalDate.h Miscellanous/DateTime/LocalDateTime.cpp Miscellanous/DateTime/LocalDateTime.h)
set(JAVA_SOURCE_FILES Server/GameServer/Java/Instance/JNIInstance.cpp Server/GameServer/Java/Instance/JNIInstance.h
        Server/GameServer/Java/Object/Observer/JObserver.cpp Server/GameServer/Java/Object/Observer/JObserver.h
        Server/GameServer/Java/Object/Factory/JFactory.cpp Server/GameServer/Java/Object/Factory/JFactory.h
        Server/GameServer/Java/Object/Controller/JController.cpp Server/GameServer/Java/Object/Controller/JController.h
        Server/GameServer/Java/Exception/Env/JNIEnvException.cpp Server/GameServer/Java/Exception/Env/JNIEnvException.h
        Server/GameServer/Java/Exception/JNIException.cpp Server/GameServer/Java/Exception/JNIException.h
        Server/GameServer/Java/Exception/Loader/JClassException.cpp Server/GameServer/Java/Exception/Loader/JClassException.h
        Server/ConnectionServer/ClientServer/Deserializer/MessageHandle.cpp Server/ConnectionServer/ClientServer/Deserializer/MessageHandle.h Server/ConnectionServer/ClientServer/Deserializer/Command.cpp Server/ConnectionServer/ClientServer/Deserializer/Command.h Server/ConnectionServer/ClientServer/Deserializer/Exception/ConnMessageException.cpp Server/ConnectionServer/ClientServer/Deserializer/Exception/ConnMessageException.h Server/ConnectionServer/ClientServer/Deserializer/Exception/ClientMessageException.cpp Server/ConnectionServer/ClientServer/Deserializer/Exception/ClientMessageException.h)

add_executable(DicesServer ${SOURCE_FILES} ${MISCELLANOUS} ${JAVA_SOURCE_FILES} JNI-test/SimpleInstanceJNI.cpp
        JNI-test/SimpleInstanceJNI.h Server/ConnectionServer/Connector/Network/Sender.cpp
        Server/ConnectionServer/Connector/Network/Sender.h
        Server/ConnectionServer/ClientServer/Client/Client.cpp Server/ConnectionServer/ClientServer/Client/Client.h
        Server/GameServer/Instance/Client/ClientGroup.cpp Server/GameServer/Instance/Client/ClientGroup.h
        Server/GameServer/Instance/Client/ClientMovement.cpp Server/GameServer/Instance/Client/ClientMovement.h
        Server/GameServer/Server/Client/WaitingRoom.cpp Server/GameServer/Server/Client/WaitingRoom.h
        Server/GameServer/Instance/Reader/GameCmdDeseriallizer.cpp Server/GameServer/Instance/Reader/GameCmdDeseriallizer.h
        Server/GameServer/Instance/Observer/GameCmdSeriallizer.cpp Server/GameServer/Instance/Observer/GameCmdSeriallizer.h
        Server/GameServer/Instance/Controller/GameController.cpp Server/GameServer/Instance/Controller/GameController.h
        Server/GameServer/Instance/Reader/GameReader.cpp Server/GameServer/Instance/Reader/GameReader.h
        Server/GameServer/Instance/Observer/Observer.cpp Server/GameServer/Instance/Observer/Observer.h
        Server/GameServer/Instance/GameInstance.cpp Server/GameServer/Instance/GameInstance.h
        Server/GameServer/Server/Factory/GameFactory.cpp Server/GameServer/Server/Factory/GameFactory.h
        Server/GameServer/Server/GameHolder.cpp Server/GameServer/Server/GameHolder.h Server/GameServer/Server/GameServer.cpp
        Server/GameServer/Server/GameServer.h Server/GameServer/Server/Serializer/CmdDeseriallizer.cpp Server/GameServer/Server/Serializer/CmdDeseriallizer.h
        Server/GameServer/Server/Serializer/GamesSerializer.cpp Server/GameServer/Server/Serializer/GamesSerializer.h
        Server/GameServer/Event/RequestQueue.cpp Server/GameServer/Event/RequestQueue.h
        Server/StartUp/MainServer.cpp Server/StartUp/MainServer.h
        Server/Logger/Logger.cpp Server/Logger/Logger.h Server/Logger/LogParser.cpp Server/Logger/LogParser.h Server/GameServer/Instance/Observer/ObsCmdDeserializer.cpp
        Server/GameServer/Instance/Observer/ObsCmdDeserializer.h Server/GameServer/Java/Instance/JConfig.cpp Server/GameServer/Java/Instance/JConfig.h
        Server/GameServer/Event/RequestQueue.cpp Server/GameServer/Event/RequestQueue.h Server/StartUp/MainServer.cpp Server/StartUp/MainServer.h
        Server/Logger/Logger.cpp Server/Logger/Logger.h Server/Logger/LogParser.cpp Server/Logger/LogParser.h
        Server/ConnectionServer/ClientServer/ConnectionServer.cpp Server/ConnectionServer/ClientServer/ConnectionServer.h
        Server/ConnectionServer/ClientServer/ClientServer.h Server/ConnectionServer/ClientServer/ClientServer.cpp
        Server/ConnectionServer/ClientServer/Client/Serializer/ClientSerializer.cpp Server/ConnectionServer/ClientServer/Client/Serializer/ClientSerializer.h
        Server/GameServer/Instance/Client/GameResponseSerializer.cpp Server/GameServer/Instance/Client/GameResponseSerializer.h
        Server/ConnectionServer/ClientServer/Serializer/ConnectorResponseSerializer.cpp Server/ConnectionServer/ClientServer/Serializer/ConnectorResponseSerializer.h
        Server/ConnectionServer/ClientServer/Exception/NameTakenException.cpp Server/ConnectionServer/ClientServer/Exception/NameTakenException.h
        Server/ConnectionServer/ClientServer/Serializer/ConnectorDeserializer.cpp Server/ConnectionServer/ClientServer/Serializer/ConnectorDeserializer.h
        Server/ConnectionServer/ClientServer/ClientHandler.cpp Server/ConnectionServer/ClientServer/ClientHandler.h)


if(Boost_FOUND)

    target_link_libraries(DicesServer ${Boost_LIBRARIES})

endif()

if(JNI_FOUND)
    target_link_libraries(DicesServer ${JNI_LIBRARIES} )

endif()