cmake_minimum_required(VERSION 2.6)

project(passhash)
file(GLOB_RECURSE SOURCES src/*.h src/*.c)
add_executable(${PROJECT_NAME} ${SOURCES})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(PkgConfig REQUIRED)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})
target_Link_libraries(${PROJECT_NAME} ${GTK3_LIBRARIES})

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${OPENSSL_LIBRARIES})

find_package(sodium REQUIRED)
include_directories(${sodium_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${sodium_LIBRARY_RELEASE})
