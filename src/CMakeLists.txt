cmake_minimum_required(VERSION 3.0.0)
project(ex4 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

add_compile_options(-Wall -Wextra -pedantic -Werror -Wnon-virtual-dtor -Wshadow)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# add the .cpp files of the project
add_executable(ex4.out
                Main.cpp
                Communication/Communication.cpp
                ThreadPool/ThreadPool.cpp
                Factory/ReadCreator.cpp
                Factory/OperateCreator.cpp
                Factory/WaitForReadCreator.cpp
                Factory/WriteCreator.cpp
                Factory/MapCreator.cpp
                Read/Read.cpp
                Write/Write.cpp
                Operations/Operate.cpp
                Operations/Matrix/Matrix.cpp
                Operations/Matrix/MatrixErrorCode.cpp
                Operations/Graph/Graph.cpp
                Operations/DFS.cpp

                )

# add the thread library
target_link_libraries(ex4.out pthread matrix)

# add the folders of the .h files (to be able to include them)
target_include_directories(ex4.out PUBLIC
                            ${CMAKE_SOURCE_DIR}/Communication
                            ${CMAKE_SOURCE_DIR}/Factory
                            ${CMAKE_SOURCE_DIR}/ThreadPool
                            ${CMAKE_SOURCE_DIR}/Read
                            ${CMAKE_SOURCE_DIR}/Write
                            ${CMAKE_SOURCE_DIR}/Operations
                          )

# include the src directory
target_link_directories(ex4.out PUBLIC ${PROJECT_SOURCE_DIR})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)