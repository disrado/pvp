cmake_minimum_required(VERSION 3.10)

project(app LANGUAGES CXX)

include(cotire)

set(${PROJECT_NAME}_HEADERS
    include/app/Game.hpp
)

set(${PROJECT_NAME}_SOURCES
    src/Game.cpp
    src/main.cpp
)

set(${PROJECT_NAME}_MISC
    src/pch.hpp
)

add_executable(${PROJECT_NAME}
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

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ${CONAN_LIBS}
        graphics
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CONAN_LIBS}
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/src
)

set(COTIRE_MINIMUM_NUMBER_OF_TARGET_SOURCES 1)
set_target_properties(${PROJECT_NAME} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "src/pch.hpp")
cotire(${PROJECT_NAME})
