cmake_minimum_required(VERSION 3.10)

project(NeoTitanicML)

# == Version
set(VERSION "0.0.1")

# == Output
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/output)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/output)


# == Dependencies
set(DEPS
    cxxopts GTest NeoML nlohmann_json
)

foreach(deps ${DEPS})
    find_package(${deps})
    if (NOT ${deps}_FOUND)
        message(FATAL_ERROR "ERROR: ${deps} library not found")
    endif()
endforeach()

# == Project
add_subdirectory(NeoTitanicML)
