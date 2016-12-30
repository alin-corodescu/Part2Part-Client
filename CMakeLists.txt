cmake_minimum_required(VERSION 3.6)
project(client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")
set(CMAKE_INCLUDE_PATH "/home/alin/Part2Part/shared")
include_directories(/home/alin/Part2Part/shared/include)

set(SOURCE_FILES main.cpp network/ConnectionHandler.h network/Server.h
        network/Address.h local/storage/Cacher.h local/Publisher.cpp
        local/Publisher.h local/storage/FileWriter.cpp local/storage/FileWriter.h
        local/storage/FileDownloader.cpp local/storage/FileDownloader.h local/storage/FileUploader.cpp
        local/storage/FileUploader.h local/storage/FileReader.cpp local/storage/FileReader.h network/PeerConnection.cpp
        network/PeerConnection.h local/FileDescriptionBuilder.cpp local/FileDescriptionBuilder.h
        local/io/ResultsDisplayer.cpp local/io/ResultsDisplayer.h local/io/UserInteractor.cpp local/io/UserInteractor.h
        local/io/CLI.cpp local/io/CLI.h local/QueryExecutor.cpp local/QueryExecutor.h
        network/Server.cpp local/CommandParser.cpp local/CommandParser.h
        network/DownloadPeer.cpp network/DownloadPeer.h network/UploadPeer.cpp network/UploadPeer.h
        network/PeerConnector.cpp network/PeerConnector.h network/ConnectionHandler.cpp network/NATTraversalUtils.cpp
        network/NATTraversalUtils.h local/storage/Cacher.cpp network/Address.cpp)

add_executable(client ${SOURCE_FILES})
target_link_libraries(client ${CMAKE_INCLUDE_PATH}/bin/Debug/libIOWrappers.a
        ${CMAKE_INCLUDE_PATH}/bin/Debug/libCommands.a
        ${CMAKE_INCLUDE_PATH}/bin/Debug/libFileDescription.a
        ${CMAKE_INCLUDE_PATH}/bin/Debug/libIntegrityChecker.a
        ${CMAKE_INCLUDE_PATH}/bin/Debug/libNetworkWrappers.a)