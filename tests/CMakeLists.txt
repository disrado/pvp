cmake_minimum_required(VERSION 3.10)

project(tests LANGUAGES CXX)

function(create_test name library)
    add_executable(${name} ${name}.cpp)

    target_include_directories(${name}
        PUBLIC
    )

    target_link_libraries(${name}
        PUBLIC
            ${library}
    )
    
    add_test(NAME ${name} COMMAND $<TARGET_FILE:${name}>)
endfunction()