cmake_minimum_required(VERSION 3.6)
project(client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_INCLUDE_PATH "/home/alin/Part2Part/shared")
include_directories(/home/alin/Part2Part/shared/include)

set(SOURCE_FILES main.cpp network/ConnectionHandler.h network/Server.h network/Address.h local/storage/Cacher.h local/Publisher.cpp local/Publisher.h local/storage/FileWriter.cpp local/storage/FileWriter.h local/storage/FileDownloader.cpp local/storage/FileDownloader.h local/storage/FileUploader.cpp local/storage/FileUploader.h local/storage/FileReader.cpp local/storage/FileReader.h network/PeerConnection.cpp network/PeerConnection.h local/FileDescriptionBuilder.cpp local/FileDescriptionBuilder.h local/CommandBuilder.cpp local/CommandBuilder.h local/io/ResultsDisplayer.cpp local/io/ResultsDisplayer.h local/io/UserInteractor.cpp local/io/UserInteractor.h)
add_executable(client ${SOURCE_FILES})