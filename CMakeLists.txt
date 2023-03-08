cmake_minimum_required(VERSION 3.13)
project(CocktailPro)

set(CMAKE_CXX_STANDARD 14)

include(ExternalProject)
# Includes the Flags cmake file to simplify adding flags to compiler/linker
include(cmake/Flags.cmake)

find_library(TINYXML2_LIBRARY tinyxml2)
if (TINYXML2_LIBRARY MATCHES "NOTFOUND")
    message(STATUS "Could NOT find TinyXML2 (building TinyXML2 internally)")
    # TinyXML2 is not found. Download, build, and install it in the build directory
    set(TINYXML2_DIR ${CMAKE_BINARY_DIR}/tinyxml2)
    externalproject_add(tinyxml2
            URL https://github.com/leethomason/tinyxml2/archive/7.0.1.tar.gz
            PREFIX ${TINYXML2_DIR}
            CMAKE_ARGS
            -DCMAKE_INSTALL_PREFIX=${TINYXML2_DIR}
            -DCMAKE_MAKE_PROGRAM=${CMAKE_MAKE_PROGRAM}
            -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
            -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
            -DBUILD_SHARED_LIBS=OFF
            -DBUILD_TESTS=OFF)
else ()
    message(STATUS "Found TinyXML2: ${TINYXML2_LIBRARY}")
endif ()

#[[
    Enable coverage for the given targets, if they are either an executable or a library
    coverage(target1 ...)
#]]
function(coverage)
    if (ARGC EQUAL 0)
        message(FATAL_ERROR "No targets were given")
    endif ()
    foreach (target ${ARGN})
        get_target_property(targetType ${target} TYPE)
        if (targetType STREQUAL "EXECUTABLE" OR targetType MATCHES "LIBRARY")
            addCompilerFlags(--coverage TARGETS ${target})
            if (targetType STREQUAL "EXECUTABLE" OR targetType STREQUAL "SHARED_LIBRARY")
                addLinkerFlags(--coverage TARGETS ${target})
            endif ()

            get_target_property(targetName ${target} NAME)
            # Remove all .gcda files of the target prior building to prevent problems with examine old invalid data
            add_custom_command(TARGET ${target} PRE_BUILD COMMAND find ${CMAKE_BINARY_DIR}/CMakeFiles/${targetName}.dir -name *.gcda -delete)
        endif ()
    endforeach ()
endfunction(coverage)

#[[
    Adds a list of compiler warning flags to the specified targets:
        -Wall
        -Wextra
        -pedantic
        -Wfloat-equal
        -Wundef
        -Wcast-align
        -Wwrite-strings
        -Wmissing-declarations
        -Wredundant-decls
        -Wshadow
        -Woverloaded-virtual
        GNU specific: -Wlogical-op
        CLang specific: -Wlogical-op-parentheses
    addCompilerWarningFlags(target1 ...)
#]]
function(addCompilerWarningFlags)
    if (ARGC EQUAL 0)
        message(FATAL_ERROR "No targets were given")
    endif ()
    addCompilerFlags(-Wall -Wextra -pedantic -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual
            GNU -Wlogical-op
            CLANG -Wlogical-op-parentheses
            TARGETS ${ARGN})
endfunction(addCompilerWarningFlags)

#[[
    Links the given target against TinyXML2
    linkTinyXML2(target)
#]]
function(linkTinyXML2 target)
    if (TARGET tinyxml2)
        add_dependencies(${target} tinyxml2)
        target_include_directories(${target} PUBLIC ${TINYXML2_DIR}/include)
        # Add ${CMAKE_FIND_LIBRARY_CUSTOM_LIB_SUFFIX} as suffix to lib, in case the Operating system uses lib32 or lib64 as install directory
        target_link_directories(${target} PUBLIC ${TINYXML2_DIR}/lib64)
        target_link_libraries(${target} 'tinyxml2')
    else ()
        target_link_libraries(${target} ${TINYXML2_LIBRARY})
    endif ()
endfunction(linkTinyXML2)

include(cmake/CocktailProResource.cmake)
include(cmake/CocktailProSource.cmake)

#[[
    Links the given target against CocktailProSource
    linkCocktailProSource(target)
#]]
function(linkCocktailProSource target)
    add_dependencies(${target} CocktailProSource)
    target_include_directories(${target} PUBLIC src/main)
    target_link_libraries(${target} CocktailProSource)
endfunction(linkCocktailProSource)

include(cmake/CocktailProDoxygen.cmake)
include(cmake/CocktailProTest.cmake)
include(cmake/CocktailPro.cmake)
include(cmake/CocktailProCppCheck.cmake)

option(CODE_COVERAGE "Enable code coverage capability" ON)
# If the build type is debug and CODE_COVERAGE is on, enabling code coverage capability for all targets that are capable of
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    get_property(targets DIRECTORY PROPERTY BUILDSYSTEM_TARGETS)
    if (targets AND CODE_COVERAGE)
        coverage(${targets})
    endif ()
endif ()