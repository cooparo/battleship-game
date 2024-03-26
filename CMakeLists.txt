cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE "Release")

project(finalproject_charizard)
set(BIN_NAME charizard)

include_directories(include)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")
set(main_src "${CMAKE_SOURCE_DIR}/entrypoints/charizard.cpp")
add_executable("charizard" ${SOURCES} ${main_src})

set(battaglia_navale_src "${CMAKE_SOURCE_DIR}/entrypoints/battaglia_navale.cpp")
add_executable("battaglia_navale" ${SOURCES} ${battaglia_navale_src})
set(replay_src "${CMAKE_SOURCE_DIR}/entrypoints/replay.cpp")
add_executable("replay" ${SOURCES} ${replay_src})