cmake_minimum_required(VERSION 3.8)
project(audio)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS “${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror”)
#set(CMAKE_CXX_FLAGS “${CMAKE_CXX_FLAGS} -g -g3)

# These directories get symlinked into the build directory after compilation
set(RESOURCE_DIRS
        music
        )


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
        SoundEngine.cpp
        SoundEngine.hpp
        SoundMain.cpp)

# Find OpenGL (for Mac mostly, Linux didn’t need this)
find_package(OpenGL REQUIRED)
find_package(OpenAL REQUIRED)	#> Linux => libopenal-dev
find_package(PkgConfig)


if (NOT PKG_CONFIG_EXECUTABLE)
    installPkg(pkg-config pkg-config)
    find_package(PkgConfig REQUIRED)
endif()

# Find the dependencies for the project						Mac				Linux
pkg_search_module(GLEW		REQUIRED	glew)			#>	glew			libglew-dev
pkg_search_module(GLM		REQUIRED	glm)			#>	glm				Install from source (https://github.com/g-truc/glm)
#pkg_search_module(GLFW3		REQUIRED	glfw3)		#>	glfw3			libglfw3-dev
#pkg_search_module(SNDFILE	REQUIRED	sndfile)		#>	libsndfile		libsndfile1-dev
#pkg_search_module(FT		REQUIRED	freetype2)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/~/.brew/Cellar/freealut/1.1.0/lib/pkgconfig")

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
        ~/.brew/Cellar/sdl/1.2.15/include/SDL
        ~/.brew/opt/sdl/include/SDL
        ~/.brew/Cellar/sdl2/2.0.5/include/SDL2
        ~/.brew/opt/sdl2/include/SDL2
)

# Directories to find the libraries
link_directories(
        ~/.brew/opt/alut/lib
        ~/.brew/Cellar/sdl/1.2.15/lib
        ~/.brew/Cellar/sdl2/2.0.5/lib
        ~/.brew/opt/sdl/lib
        ~/.brew/opt/sdl2/lib
        ${PROJECT_SOURCE_DIR}
        ${GLEW_LIBRARY_DIRS}
        ${GLM_LIBRARY_DIRS}
)

add_executable(audio ${SOURCE_FILES})

# Link executable with libraries
target_link_libraries(${PROJECT_NAME}
        ${OPENGL_LIBRARIES}
        ${OPENAL_LIBRARY}
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
        alut
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
