cmake_minimum_required(VERSION 3.10)

project(UnitTests LANGUAGES CXX)

set(${PROJECT_NAME}_HEADERS
)

set(${PROJECT_NAME}_SOURCES
	src/TAccountWork.cpp
	src/Init.cpp
)

set(${PROJECT_NAME}_MISC
	src/pch.hpp
)

include_directories(.)

add_executable(${PROJECT_NAME}
	${${PROJECT_NAME}_HEADERS}
	${${PROJECT_NAME}_SOURCES}
	${${PROJECT_NAME}_MISC}
)
gtest_discover_tests(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		pvp::database
		CONAN_PKG::gtest
		pvp::utilities
)

