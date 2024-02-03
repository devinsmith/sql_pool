cmake_minimum_required(VERSION 3.10)
project(sql_pool)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/)

find_package(Threads REQUIRED)
find_package(FreeTDS REQUIRED)

set(SOURCES
  src/SqlClient.cpp
  src/SqlConnection.cpp
  src/SqlConnectionFactory.cpp
  src/SqlParams.cpp)

set(HEADERS
  include/SqlClient.h
  include/SqlConnection.h
  include/SqlConnectionFactory.h
  include/SqlParams.h)

# Define library
add_library(sql_pool STATIC ${SOURCES} ${HEADERS})

target_include_directories(sql_pool PUBLIC ${PROJECT_SOURCE_DIR}/include ${FreeTDS_INCLUDE_DIR})
target_link_libraries(sql_pool PRIVATE ${FreeTDS_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
