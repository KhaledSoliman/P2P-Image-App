cmake_minimum_required(VERSION 3.14)
project(Proj C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(Boost_INCLUDE_DIR /Users/snappy/Desktop/boost_1_70_0)
set(Boost_LIBRARY_DIR /Users/snappy/Desktop/boost_1_70_0/stage/lib)
include_directories(${Boost_INCLUDE_DIR})
find_package(JPEG REQUIRED)
INCLUDE_DIRECTORIES(${JPEG_INCLUDE_DIR})
find_package(Boost REQUIRED COMPONENTS ${BOOST_COMPONENTS} filesystem thread iostreams serialization date_time random system)
add_executable(Proj
        headers/Client.h
        headers/Server.h
        headers/UDPSocket.h
        headers/Message.h
        headers/UDPServerSocket.h
        headers/UDPClientSocket.h
        main.cpp
        sources/Server.cpp
        sources/Message.cpp
        sources/UDPSocket.cpp
        sources/UDPServerSocket.cpp
        sources/UDPClientSocket.cpp
        sources/Client.cpp
        sources/MessageStructures.cpp
        headers/MessageStructures.h
        sources/DirectoryServer.cpp
        headers/DirectoryServer.h
        sources/Peer.cpp
        headers/Peer.h
        headers/Seng.h
        sources/Seng.cpp
        headers/Cache.h
        sources/Cache.cpp
        headers/ImageBody.h
        sources/ImageBody.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${PROJECT_NAME} ${JPEG_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
