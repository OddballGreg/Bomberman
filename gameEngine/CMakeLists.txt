cmake_minimum_required(VERSION 3.8)
project(gameEngine)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS “${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror”)
set(CMAKE_CXX_FLAGS “${CMAKE_CXX_FLAGS} -g -g3)

# These directories get symlinked into the build directory after compilation
set(RESOURCE_DIRS
        Shaders
        Textures
        )

#include(ExternalProject)
#set(BOMBERMAN_DIR ${CMAKE_CURRENT_SOURCE_DIR})
#set(NANOGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/.nanogui)

if (NOT IS_DIRECTORY “$ENV{HOME}/.brew”)
    message(“ERROR: Please make sure brew is installed.“)
#    execute_process(COMMAND sh -c “$(curl -fsSL https://raw.githubusercontent.com/Tolsadus/42homebrewfix/master/install.sh)”)
endif()

if (NOT IS_DIRECTORY “$ENV{HOME}/.brew/Cellar/glew”)
    execute_process(COMMAND brew install glew)
endif()

if (NOT IS_DIRECTORY “${CMAKE_CURRENT_SOURCE_DIR}/dependencies/nanogui/build”)
    message(INFO “The Bomberman dependency repositories (NanoGUI) are missing! ”
            “You probably did not clone the project with --recursive.\n”
            “Automatically cloning submodules...“)
    execute_process(COMMAND git submodule update --init --recursive)
    message(INFO “Build NanoGUI”)
    execute_process(COMMAND /bin/sh ${PROJECT_SOURCE_DIR}/install_dependencies.sh
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/dependencies/nanogui/)
endif ()

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
        gameEngine/gameEngine/Engine/Makefile
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/AngryCloud.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/Background.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/BrokenLandPiece_Beige.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/BrokenLandPiece_Blue.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/BrokenLandPiece_Gray.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/BrokenLandPiece_Green.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/BrokenLandPiece_Multicolored.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/BrokenLandPiece_Pink.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/Bubble_Big.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/Bubble_Small.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/Bullet.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/CharacterLeft_Jump.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/CharacterLeft_Standing.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/CharacterLeft_Walk1.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/CharacterLeft_Walk2.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/CharacterRight_Jump.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/CharacterRight_Standing.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/CharacterRight_Walk1.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/CharacterRight_Walk2.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/CloudWind.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/Coin.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/HalfLandPiece_Left_Beige.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/HalfLandPiece_Left_Blue.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/HalfLandPiece_Left_Gray.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/HalfLandPiece_Left_Green.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/HalfLandPiece_Left_Multicolored.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/HalfLandPiece_Left_Pink.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/HalfLandPiece_Right_Beige.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/HalfLandPiece_Right_Blue.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/HalfLandPiece_Right_Gray.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/HalfLandPiece_Right_Green.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/HalfLandPiece_Right_Multicolored.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/HalfLandPiece_Right_Pink.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/HappyCloud.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/HearthEnemy1.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/HearthEnemy2.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/JetFire1.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/JetFire2.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/Jetpack_Big.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/Jetpack_Small.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/LandPiece_DarkBeige.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/LandPiece_DarkBlue.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/LandPiece_DarkGray.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/LandPiece_DarkGreen.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/LandPiece_DarkMulticolored.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/LandPiece_DarkPing.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/LandPiece_LightBeige.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/LandPiece_LightBlue.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/LandPiece_LightGray.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/LandPiece_LightGreen.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/LandPiece_LightMulticolored.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/LandPiece_LightPing.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/Lightning1.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/Lightning2.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/Mushroom.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/Number_0.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/Number_1.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/Number_2.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/Number_3.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/Number_4.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/Number_5.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/Number_6.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/Number_7.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/Number_8.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/Number_9.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/Number_Point.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/Pistol.png
        gameEngine/gameEngine/textures/jimmyJump_pack/PNG/Spring.png
        gameEngine/gameEngine/textures/jimmyJump_pack/license.txt
        gameEngine/gameEngine/Bomb.cpp
        gameEngine/gameEngine/Bomb.hpp
        gameEngine/gameEngine/bomberman_log.txt
        gameEngine/gameEngine/BulletOld.cpp
        gameEngine/gameEngine/BulletOld.hpp
        gameEngine/gameEngine/Camera2D.cpp
        gameEngine/gameEngine/Camera2D.hpp
        gameEngine/gameEngine/colourshading.frag
        gameEngine/gameEngine/colourshading.vert
        gameEngine/gameEngine/FatalError.cpp
        gameEngine/gameEngine/FatalError.hpp
        gameEngine/gameEngine/game
        gameEngine/gameEngine/gameEngine.cpp
        gameEngine/gameEngine/gameEngine.hpp
        gameEngine/gameEngine/GLSLProgram.cpp
        gameEngine/gameEngine/GLSLProgram.hpp
        gameEngine/gameEngine/GLTexture.hpp
        gameEngine/gameEngine/ImageLoader.cpp
        gameEngine/gameEngine/ImageLoader.hpp
        gameEngine/gameEngine/InputManager.cpp
        gameEngine/gameEngine/InputManager.hpp
        gameEngine/gameEngine/IOManager.cpp
        gameEngine/gameEngine/IOManager.hpp
        gameEngine/gameEngine/Log.cpp
        gameEngine/gameEngine/Log.hpp
        gameEngine/gameEngine/Logger.cpp
        gameEngine/gameEngine/Logger.hpp
        gameEngine/gameEngine/main.cpp
        gameEngine/gameEngine/mainGame.cpp
        gameEngine/gameEngine/mainGame.hpp
        gameEngine/gameEngine/Makefile
        gameEngine/gameEngine/picoPNG.cpp
        gameEngine/gameEngine/picoPNG.hpp
        gameEngine/gameEngine/ResourceManager.cpp
        gameEngine/gameEngine/ResourceManager.hpp
        gameEngine/gameEngine/Sprite.cpp
        gameEngine/gameEngine/Sprite.hpp
        gameEngine/gameEngine/SpriteBatch.cpp
        gameEngine/gameEngine/SpriteBatch.hpp
        gameEngine/gameEngine/TextureCache.cpp
        gameEngine/gameEngine/TextureCache.hpp
        gameEngine/gameEngine/Timing.cpp
        gameEngine/gameEngine/Timing.hpp
        gameEngine/gameEngine/Vertex.cpp
        gameEngine/gameEngine/Vertex.hpp
        gameEngine/gameEngine/Window.cpp
        gameEngine/gameEngine/Window.hpp
        gameEngine/Levels/level1.txt
        gameEngine/Shaders/textureShading.frag
        gameEngine/Shaders/textureShading.vert
        gameEngine/Textures/circle.png
        gameEngine/Textures/credits.txt
        gameEngine/Textures/glass.png
        gameEngine/Textures/light_bricks.png
        gameEngine/Textures/red_bricks.png
        gameEngine/Agent.cpp
        gameEngine/Agent.hpp
        gameEngine/author
        gameEngine/Bomb.cpp
        gameEngine/Bomb.hpp
        gameEngine/Bullet.cpp
        gameEngine/Bullet.hpp
        gameEngine/colourshading.frag
        gameEngine/colourshading.vert
        gameEngine/Gun.cpp
        gameEngine/Gun.hpp
        gameEngine/Human.cpp
        gameEngine/Human.hpp
        gameEngine/Level.cpp
        gameEngine/Level.hpp
        gameEngine/main.cpp
        gameEngine/mainGame.cpp
        gameEngine/mainGame.h
        gameEngine/Makefile
        gameEngine/Player.cpp
        gameEngine/Player.hpp
        gameEngine/Zombie.cpp
        gameEngine/Zombie.hpp)

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
pkg_search_module(SNDFILE	REQUIRED	sndfile)		#>	libsndfile		libsndfile1-dev
pkg_search_module(FT		REQUIRED	freetype2)

if (NOT GLEW_FOUND)
    installPkg(glew libglew-dev)
endif()

if (NOT GLM_FOUND)
    installPkg(glm FALSE)
endif()

if (NOT SNDFILE_FOUND)
    installPkg(libsndfile libsndfile1-dev)
endif()

if (NOT FT_FOUND)
    installPkg(freetype FALSE)
endif()


# Directories to find the header files
include_directories(
        includes
        ${PROJECT_SOURCE_DIR}/dependencies/nanogui/include
        ${PROJECT_SOURCE_DIR}/dependencies/nanogui/ext
        ${PROJECT_SOURCE_DIR}/dependencies/nanogui/ext/nanovg/src
        ${PROJECT_SOURCE_DIR}/dependencies/nanogui/ext/eigen
        ${PROJECT_SOURCE_DIR}/dependencies/nanogui/ext/glfw/include
        ${GLEW_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS}
        ${FT_INCLUDE_DIRS}
        ${OPENAL_INCLUDE_DIR}
        ${SNDFILE_INCLUDE_DIRS}
)

# Directories to find the libraries
link_directories(
        ${PROJECT_SOURCE_DIR}/dependencies/nanogui/build
        ${GLEW_LIBRARY_DIRS}
        ${GLM_LIBRARY_DIRS}
        ${FT_LIBRARY_DIRS}
        ${SNDFILE_LIBRARY_DIRS}
)

add_executable(gameEngine ${SOURCE_FILES})

# Link executable with libraries
target_link_libraries(${PROJECT_NAME}
        ${OPENGL_LIBRARIES}
        ${OPENAL_LIBRARY}
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
        ${SNDFILE_LIBRARIES}
        ${FT_LIBRARIES}
        nanogui
        )

# Function to symbolically link the resources into the build directory
#	Won’t work on Windows
foreach(RESOURCE_DIR ${RESOURCE_DIRS})
    add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_SOURCE_DIR}/${RESOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${RESOURCE_DIR}
            DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${RESOURCE_DIR}
    )
endforeach()