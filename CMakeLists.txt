cmake_minimum_required(VERSION 3.24)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
# for now, the project name is used as the executable name
project(oop)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)

# disable sanitizers when releasing executables without explicitly requested debug info
# use generator expressions to set flags correctly in both single and multi config generators
set(is_debug "$<CONFIG:Debug>")
set(is_rel_with_deb "$<CONFIG:RelWithDebInfo>")
set(debug_mode "$<OR:${is_debug},${is_rel_with_deb}>")

###############################################################################

# custom functions

function(set_custom_stdlib_and_sanitizers target add_apple_asan)
    if(MSVC)
        target_compile_options(${target} PRIVATE "$<${debug_mode}:/fsanitize=address>")
        return()
    endif()

    if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
        target_compile_options(${target} PRIVATE -stdlib=libc++)
        target_link_options(${target} PRIVATE -stdlib=libc++)
    endif()

    if(APPLE)
        # first check Apple since Apple is also a kind of Unix
        if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang" AND add_apple_asan MATCHES true)
            target_compile_options(${target} PRIVATE "$<${debug_mode}:-fsanitize=address,undefined>")
            target_link_options(${target} PRIVATE "$<${debug_mode}:-fsanitize=address,undefined>")
        endif()
    elseif(UNIX)
        if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
            if("${CMAKE_CXX_COMPILER_VERSION}" MATCHES "12.")
                # check leaks on Linux since macOS does not support the leaks sanitizer yet
                # leaks sanitizer is enabled by default on Linux, so we do not need to enable it explicitly
                target_compile_options(${target} PRIVATE "$<${debug_mode}:-fsanitize=address,undefined>")
                target_link_options(${target} PRIVATE "$<${debug_mode}:-fsanitize=address,undefined>")
            elseif("${CMAKE_CXX_COMPILER_VERSION}" MATCHES "13.")
                # use semi-colons instead of spaces to separate arguments
                # it is recommended to quote generator expressions in order to avoid unintentional splitting
                target_compile_options(${target} PRIVATE "$<${debug_mode}:-fsanitize=memory,undefined;-fsanitize-recover=memory,undefined;-fsanitize-memory-track-origins>")
                target_link_options(${target} PRIVATE "$<${debug_mode}:-fsanitize=memory,undefined;-fsanitize-recover=memory,undefined;-fsanitize-memory-track-origins;-Wl,-rpath,tools/llvm-project/build/lib>")
            else()
                message("No matching Clang version to add sanitizer flags!")
            endif()
        endif()
    endif()
endfunction()

#find_package(OpenGL REQUIRED)
#
#if(NOT OPENGL_FOUND)
#    message("OpenGL not found. Installing...")
#    include(FetchContent)
#    FetchContent_Declare(
#            OpenGL
#            URL "https://github.com/opencv/opencv/archive/4.1.0.zip"
#            URL_HASH SHA256=4d2ba9ad0b6c74a17779962b6a0a0a87a6e1787f010042b78ef19d9819b9c931
#            SOURCE_DIR "${CMAKE_BINARY_DIR}/OpenGL-src"
#            BINARY_DIR "${CMAKE_BINARY_DIR}/OpenGL-build"
#    )
#    FetchContent_MakeAvailable(OpenGL)
#endif()
#
## Use the OpenGL library and headers
#target_link_libraries(${PROJECT_NAME} OpenGL::GL)

include(FetchContent)

# NOTE: Also update SFML_VERSION env var in .github/workflows/cmake.yml:122
FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG        863fef024619da7f59b6404087b454337a172ac1 # 2.6.x as of 2022-08-30
        # GIT_TAG        72d88033e2f24be0fb1e9df614a56f3d5274154c # master as of 2022-08-30
        # GIT_TAG        f7c88ee7ef4e1c705531cd614efb7dcff1f873cb # last commit merged in master before API breakage (2022-04-21)
        # GIT_TAG        origin/master
        # GIT_TAG        origin/2.6.x
        # GIT_SHALLOW    1  # works only with branches or tags, not with arbitrary commit hashes
)


FetchContent_MakeAvailable(SFML)

set_custom_stdlib_and_sanitizers(sfml-system false)
set_custom_stdlib_and_sanitizers(sfml-window false)
set_custom_stdlib_and_sanitizers(sfml-graphics false)

#FetchContent_Declare(
#        OpenGL
#        URL "https://github.com/opencv/opencv/archive/4.1.0.zip"
#        URL_HASH SHA256=4d2ba9ad0b6c74a17779962b6a0a0a87a6e1787f010042b78ef19d9819b9c931
#        SOURCE_DIR "${CMAKE_BINARY_DIR}/OpenGL-src"
#        BINARY_DIR "${CMAKE_BINARY_DIR}/OpenGL-build"
#)
#FetchContent_MakeAvailable(OpenGL)

###############################################################################

# external dependencies with FetchContent
#include(FetchContent)
#
# NOTE: Also update env vars used for caching in .github/workflows/cmake.yml
#FetchContent_Declare(
#        SomeLib
#        GIT_REPOSITORY https://github.com/<SomeUser>/<SomeLib>.git
#        GIT_TAG        <some_git_hash> # <which tag/branch @ <some_date>>
#        GIT_SHALLOW    1  # works only with branches or tags, not with arbitrary commit hashes
#)
#
#FetchContent_MakeAvailable(SomeLib)

###############################################################################

# external dependencies with find_package

# find_package(Threads REQUIRED)

###############################################################################

#include font
# Add font file

install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets
        DESTINATION bin
        FILES_MATCHING
        PATTERN "*.ttf")


#add_custom_command(
#        OUTPUT "${CMAKE_BINARY_DIR}/assets/RobotoMono-Regular.ttf"
#        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/assets/RobotoMono-Regular.ttf" "${CMAKE_BINARY_DIR}/assets/RobotoMono-Regular.ttf"
#        DEPENDS "${CMAKE_SOURCE_DIR}/assets/RobotoMono-Regular.ttf"
#)
#add_custom_target(FontCopy ALL DEPENDS "${CMAKE_BINARY_DIR}/assets/RobotoMono-Regular.ttf")
#add_dependencies(${PROJECT_NAME} FontCopy)
#target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR})

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing name here
add_executable(${PROJECT_NAME} main.cpp Game.cpp Utils.cpp Individual.cpp Individual.h Food.cpp Food.h Cell.h RedBull.h Clairvoyant.h Keystone.h ${CMAKE_SOURCE_DIR}/assets/RobotoMono-Regular.ttf Ascendant.cpp Ascendant.h Suitor.cpp Suitor.h CellFactory.cpp CellFactory.h)

### INCLUDE SFML LIBRARY ###
#find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
#target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)
###############################################################################

# target definitions

if(GITHUB_ACTIONS)
  message("NOTE: GITHUB_ACTIONS defined")
  target_compile_definitions(${PROJECT_NAME} PRIVATE GITHUB_ACTIONS)
endif()

###############################################################################

if(WARNINGS_AS_ERRORS)
    set_property(TARGET ${PROJECT_NAME} PROPERTY COMPILE_WARNING_AS_ERROR ON)
endif()

# custom compiler flags
message("Compiler: ${CMAKE_CXX_COMPILER_ID} version ${CMAKE_CXX_COMPILER_VERSION}")
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive- /wd4244 /wd4267 /wd4996 /external:anglebrackets /external:W0)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

###############################################################################

# sanitizers
set_custom_stdlib_and_sanitizers(${PROJECT_NAME} true)

###############################################################################

# use SYSTEM so clang-tidy does not report warnings from these directories
#target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ext/<SomeHppLib>/include)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${SFML_SOURCE_DIR}/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${SFML_BINARY_DIR}/lib)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)
#
#target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${OPENGL_SOURCE_DIR}/include)
#target_link_directories(${PROJECT_NAME} PRIVATE ${OPENGL_BINARY_DIR}/lib)
#target_link_libraries(${PROJECT_NAME} OpenGL::GL)

###############################################################################

# copy binaries to "bin" folder; these are uploaded as artifacts on each release
# update name in .github/workflows/cmake.yml:29 when changing "bin" name here
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
# install(DIRECTORY some_dir1 some_dir2 DESTINATION bin)
# install(FILES some_file1.txt some_file2.md DESTINATION bin)


find_package(Threads REQUIRED)
if(APPLE)
elseif(UNIX)
    find_package(X11)
endif()

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${SFML_SOURCE_DIR}/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${SFML_BINARY_DIR}/lib)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system Threads::Threads)

if(APPLE)
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} X11)
endif()