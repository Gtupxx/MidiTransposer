cmake_minimum_required(VERSION 3.8.0)
project(MidiTransposer VERSION 0.1.0 LANGUAGES CXX)

# 添加可执行文件
file(GLOB SOURCES 
    "src/*.cpp"
    "main.cpp"
)

# 添加头文件搜索路径
include_directories(src)

# 生成可执行文件
add_executable(MidiTransposer ${SOURCES})

find_package(rtmidi CONFIG REQUIRED)
target_link_libraries(MidiTransposer PRIVATE RtMidi::rtmidi)