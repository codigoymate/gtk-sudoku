cmake_minimum_required(VERSION 3.16.3)

project(Sudoku DESCRIPTION "Sudoku Game" LANGUAGES CXX)

set(EXECUTABLE sudoku)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(INC_DIR ${PROJECT_SOURCE_DIR}/include)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
pkg_check_modules(XML REQUIRED libxml-2.0)

file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.cpp)

add_executable(${EXECUTABLE} ${SOURCES})
target_include_directories(${EXECUTABLE} PUBLIC ${INC_DIR})
include_directories(${XML_INCLUDE_DIRS} ${GTKMM_INCLUDE_DIRS})
target_link_libraries(${EXECUTABLE} ${XML_LIBRARIES} ${GTKMM_LIBRARIES})

# Install
install(TARGETS ${EXECUTABLE} RUNTIME DESTINATION bin)
install(DIRECTORY ui/ DESTINATION share/Sudoku/ui)
