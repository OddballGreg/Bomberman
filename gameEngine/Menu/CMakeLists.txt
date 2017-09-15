cmake_minimum_required(VERSION 3.8)
project(gabe)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS “${CMAKE_CXX_FLAGS} -g -g3)
#set(CMAKE_CXX_FLAGS “${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror”)

# These directories get symlinked into the build directory after compilation
set(RESOURCE_DIRS
        )

include(ExternalProject)
set(NANOGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/.nanogui)


#if (NOT IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/nanogui/build")
#    message(INFO "The Bomberman dependency repositories (NanoGUI) are missing! "
#            "You probably did not clone the project with --recursive.\n"
#            "Automatically cloning submodules...")
#    execute_process(COMMAND git submodule update --init --recursive)
#    message(INFO "Build NanoGUI")
#    execute_process(COMMAND /bin/sh ${PROJECT_SOURCE_DIR}/install_dependencies.sh
#            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/dependencies/nanogui/)
#endif ()

if (NOT IS_DIRECTORY "${NANOGUI_DIR}")
    execute_process(COMMAND git clone https://github.com/wjakob/nanogui.git --recursive .nanogui)
    execute_process(COMMAND sh install_dependencies.sh)
endif()


set(INSTALLED_PACKAGE FALSE)

function(installPkg pkgApple pkgLinux)
    if (APPLE AND pkgApple)
        message(“Installing ” ${pkgApple} “...“)
        execute_process(COMMAND brew install pkg-config) #${pkgApple}
    elseif(LINUX AND pkgLinux)
        execute_process(COMMAND sudo apt install ${pkgLinux})
    endif()

    set(INSTALLED_PACKAGE TRUE)
endfunction()

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

set(SOURCE_FILES
        gabe.cpp
        gabe2.cpp)

# Find OpenGL (for Mac mostly, Linux didn’t need this)
find_package(OpenGL REQUIRED)
find_package(OpenAL REQUIRED)	#> Linux => libopenal-dev
find_package(PkgConfig)

if (NOT PKG_CONFIG_EXECUTABLE)
    installPkg(brew install pkg-config)
    find_package(PkgConfig REQUIRED)
endif()

# Find the dependencies for the project						Mac				Linux
pkg_search_module(GLEW		REQUIRED	glew)			#>	glew			libglew-dev
pkg_search_module(GLM		REQUIRED	glm)			#>	glm				Install from source (https://github.com/g-truc/glm)
#pkg_search_module(GLFW3		REQUIRED	glfw3)		#>	glfw3			libglfw3-dev
#pkg_search_module(SNDFILE	REQUIRED	sndfile)		#>	libsndfile		libsndfile1-dev
#pkg_search_module(FT		REQUIRED	freetype2)

if (NOT GLEW_FOUND)
    installPkg(glew libglew-dev)
endif()

if (NOT GLM_FOUND)
    installPkg(glm FALSE)
endif()


# Directories to find the header files
include_directories(
        ~/.brew/Cellar/freealut/1.1.0/include/AL
        includes
        ${GLEW_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS}
        ${OPENAL_INCLUDE_DIR}
        ~/.brew/opt/alut/include
        ~/.brew/Cellar/sdl2/2.0.5/include/SDL2
        ~/.brew/opt/sdl2/include/SDL2
        ~/.brew/Cellar/glfw/3.2.1/include/
        ${PROJECT_SOURCE_DIR}/.nanogui/include
        ${PROJECT_SOURCE_DIR}/.nanogui/ext
        ${PROJECT_SOURCE_DIR}/.nanogui/ext/nanovg/src
        ${PROJECT_SOURCE_DIR}/.nanogui/ext/eigen
        ${PROJECT_SOURCE_DIR}/.nanogui/ext/glfw/include
)

# Directories to find the libraries
link_directories(
        ~/.brew/opt/alut/lib
        ~/.brew/Cellar/sdl2/2.0.5/lib
        ~/.brew/opt/sdl2/include/SDL2/
        ~/.brew/Cellar/glfw/3.2.1/lib
        ~/.brew/opt/sdl2/lib
        ${PROJECT_SOURCE_DIR}
        ${GLEW_LIBRARY_DIRS}
        ${GLM_LIBRARY_DIRS}
        ${GLFW_LIBRARY_DIRS}
        ${PROJECT_SOURCE_DIR}/.nanogui/cmake-build-debug
#        ${NANOGUI_DIR}
#        ${NANOGUI_DIR}/ext/eigen
#        ${NANOGUI_DIR}/ext/nanovg/src
)


add_executable(gabe gabe.cpp)
add_executable(gabe2 gabe2.cpp)

# Link executable with libraries
#target_link_libraries(gabe nanogui ${NANOGUI_EXTRA_LIBS})
#target_link_libraries(gabe2 nanogui ${NANOGUI_EXTRA_LIBS})
target_link_libraries(${PROJECT_NAME}
        ${OPENGL_LIBRARIES}
        ${OPENAL_LIBRARY}
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
        ${GLFW_LIBRARIES}
        alut
        glfw
        sdl2
        nanogui
        )


if (APPLE)
    target_link_libraries(${PROJECT_NAME}
            "-framework OpenGL")
endif()

# Function to symbolically link the resources into the build directory
#	Won’t work on Windows
foreach(RESOURCE_DIR ${RESOURCE_DIRS})
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/${RESOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${RESOURCE_DIR}
            DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${RESOURCE_DIR}
    )
endforeach()