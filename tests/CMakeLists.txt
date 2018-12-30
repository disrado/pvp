cmake_minimum_required(VERSION 3.10)

project(UnitTests LANGUAGES CXX)

set(${PROJECT_NAME}_HEADERS
)

set(${PROJECT_NAME}_SOURCES
	Init.cpp
	AccountWork.cpp
)

set(${PROJECT_NAME}_MISC
	pch.hpp
)

include_directories(.)
add_definitions(-DASSETS_ROOT="${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(unittests
	${${PROJECT_NAME}_HEADERS}
	${${PROJECT_NAME}_SOURCES}
	${${PROJECT_NAME}_MISC}
)
gtest_discover_tests(unittests)

target_link_libraries(unittests
	CONAN_PKG::gtest,
	pvp::database,
	pvp::utilities
)

# Precompiled header.
set(COTIRE_MINIMUM_NUMBER_OF_TARGET_SOURCES 1)
set_target_properties(unittests PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "pch.hpp")
cotire(unittests)