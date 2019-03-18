cmake_minimum_required(VERSION 3.10)

project(database LANGUAGES CXX)

include(cotire)

set(${PROJECT_NAME}_HEADERS
	include/db/models/Account.hpp
	include/db/models/Filter.hpp
	include/db/AccountWorker.hpp
	include/db/Aliases.hpp
	include/db/Pager.hpp
	include/db/TypeConversion.hpp
)

set(${PROJECT_NAME}_SOURCES
	src/models/Account.cpp
	src/models/Filter.inl
	src/models/Filter.cpp
	src/AccountWorker.cpp
	src/Pager.cpp
	src/TypeConversion.cpp
)

set(${PROJECT_NAME}_MISC
	src/pch.hpp
)

add_library(${PROJECT_NAME} SHARED
	${${PROJECT_NAME}_HEADERS}
	${${PROJECT_NAME}_SOURCES}
	${${PROJECT_NAME}_MISC}
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_compile_options(${PROJECT_NAME}
	PRIVATE
		$<$<CXX_COMPILER_ID:MSVC>:
			/MP /W3 /Zf
			$<$<CONFIG:Debug>:/MTd>
			$<$<CONFIG:Release>:/MT>>
		$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
			-Wall -Wextra -Werror -Wpedantic -pedantic-errors -pipe>
)

add_library(pvp::database ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		flame::db
		logger
		pvp::utilities
	PRIVATE
		${CONAN_LIBS}
)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		include
	PRIVATE
		src
)

set(COTIRE_MINIMUM_NUMBER_OF_TARGET_SOURCES 1)
set_target_properties(${PROJECT_NAME} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "src/pch.hpp")
cotire(${PROJECT_NAME})
