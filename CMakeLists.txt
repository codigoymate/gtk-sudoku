cmake_minimum_required(VERSION 3.16.3)

# Versioning #################################
# Extract version from Git
execute_process(
	COMMAND git describe --tags --abbrev=0
	OUTPUT_VARIABLE SUDOKU_VERSION
	OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Configure version on CMake
if(SUDOKU_VERSION)
	message(STATUS "Sudoku version: ${SUDOKU_VERSION}")
else()
	set(SUDOKU_VERSION "1.0.0")
	message(WARNING "Could not determine sudoku version from Git. Defaulting to ${SUDOKU_VERSION}")
endif()

# Generar el archivo version.h a partir de version.h.in
configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/version.h.in
	${CMAKE_CURRENT_BINARY_DIR}/version.h
	@ONLY
)

# Incluir el directorio binario para acceder a version.h
include_directories(${CMAKE_CURRENT_BINARY_DIR})

##############################################

project(Sudoku DESCRIPTION "Sudoku Game" LANGUAGES CXX VERSION ${SUDOKU_VERSION})

set(EXECUTABLE sudoku)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

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

