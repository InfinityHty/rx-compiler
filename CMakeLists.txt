cmake_minimum_required(VERSION 3.16)
project(rx CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# src/ 下的全部 .cpp：main.cpp + ANTLR 生成的 6 个文件。
# BUILD 每次都会重新跑 cmake 配置，所以新增文件会被自动收集。
file(GLOB SOURCES src/*.cpp)

find_package(Threads REQUIRED)

add_executable(rx ${SOURCES})

# 头文件用仓库 vendored 的 4.13.2（src/include），
# 不要用 /usr/include/antlr4-runtime（apt 装的是 4.10）。
target_include_directories(rx PRIVATE src src/include)

# 链接 /usr/local/lib 下的 4.13.2 运行时，与生成代码版本一致；
# apt 的 4.10（/lib/x86_64-linux-gnu）不能链接。
target_link_directories(rx PRIVATE /usr/local/lib)
target_link_libraries(rx antlr4-runtime Threads::Threads)
set_target_properties(rx PROPERTIES BUILD_RPATH /usr/local/lib)
