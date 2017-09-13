cmake_minimum_required(VERSION 3.8)
project(gameEngine)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS “${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror”)
#set(CMAKE_CXX_FLAGS “${CMAKE_CXX_FLAGS} -g -g3)

# These directories get symlinked into the build directory after compilation
set(RESOURCE_DIRS
        Shaders
        Textures
        Art
        Levels
        colourshading.vert
        colourshading.frag
        )

if (NOT IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/nanogui/build")
    message(INFO "The Bomberman dependency repositories (NanoGUI) are missing! "
            "You probably did not clone the project with --recursive.\n"
            "Automatically cloning submodules...")
    execute_process(COMMAND git submodule update --init --recursive)
    message(INFO "Build NanoGUI")
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
        gameEngine/textures/jimmyJump_pack/PNG/AngryCloud.png
        gameEngine/textures/jimmyJump_pack/PNG/Background.png
        gameEngine/textures/jimmyJump_pack/PNG/BrokenLandPiece_Beige.png
        gameEngine/textures/jimmyJump_pack/PNG/BrokenLandPiece_Blue.png
        gameEngine/textures/jimmyJump_pack/PNG/BrokenLandPiece_Gray.png
        gameEngine/textures/jimmyJump_pack/PNG/BrokenLandPiece_Green.png
        gameEngine/textures/jimmyJump_pack/PNG/BrokenLandPiece_Multicolored.png
        gameEngine/textures/jimmyJump_pack/PNG/BrokenLandPiece_Pink.png
        gameEngine/textures/jimmyJump_pack/PNG/Bubble_Big.png
        gameEngine/textures/jimmyJump_pack/PNG/Bubble_Small.png
        gameEngine/textures/jimmyJump_pack/PNG/Bullet.png
        gameEngine/textures/jimmyJump_pack/PNG/CharacterLeft_Jump.png
        gameEngine/textures/jimmyJump_pack/PNG/CharacterLeft_Standing.png
        gameEngine/textures/jimmyJump_pack/PNG/CharacterLeft_Walk1.png
        gameEngine/textures/jimmyJump_pack/PNG/CharacterLeft_Walk2.png
        gameEngine/textures/jimmyJump_pack/PNG/CharacterRight_Jump.png
        gameEngine/textures/jimmyJump_pack/PNG/CharacterRight_Standing.png
        gameEngine/textures/jimmyJump_pack/PNG/CharacterRight_Walk1.png
        gameEngine/textures/jimmyJump_pack/PNG/CharacterRight_Walk2.png
        gameEngine/textures/jimmyJump_pack/PNG/CloudWind.png
        gameEngine/textures/jimmyJump_pack/PNG/Coin.png
        gameEngine/textures/jimmyJump_pack/PNG/HalfLandPiece_Left_Beige.png
        gameEngine/textures/jimmyJump_pack/PNG/HalfLandPiece_Left_Blue.png
        gameEngine/textures/jimmyJump_pack/PNG/HalfLandPiece_Left_Gray.png
        gameEngine/textures/jimmyJump_pack/PNG/HalfLandPiece_Left_Green.png
        gameEngine/textures/jimmyJump_pack/PNG/HalfLandPiece_Left_Multicolored.png
        gameEngine/textures/jimmyJump_pack/PNG/HalfLandPiece_Left_Pink.png
        gameEngine/textures/jimmyJump_pack/PNG/HalfLandPiece_Right_Beige.png
        gameEngine/textures/jimmyJump_pack/PNG/HalfLandPiece_Right_Blue.png
        gameEngine/textures/jimmyJump_pack/PNG/HalfLandPiece_Right_Gray.png
        gameEngine/textures/jimmyJump_pack/PNG/HalfLandPiece_Right_Green.png
        gameEngine/textures/jimmyJump_pack/PNG/HalfLandPiece_Right_Multicolored.png
        gameEngine/textures/jimmyJump_pack/PNG/HalfLandPiece_Right_Pink.png
        gameEngine/textures/jimmyJump_pack/PNG/HappyCloud.png
        gameEngine/textures/jimmyJump_pack/PNG/HearthEnemy1.png
        gameEngine/textures/jimmyJump_pack/PNG/HearthEnemy2.png
        gameEngine/textures/jimmyJump_pack/PNG/JetFire1.png
        gameEngine/textures/jimmyJump_pack/PNG/JetFire2.png
        gameEngine/textures/jimmyJump_pack/PNG/Jetpack_Big.png
        gameEngine/textures/jimmyJump_pack/PNG/Jetpack_Small.png
        gameEngine/textures/jimmyJump_pack/PNG/LandPiece_DarkBeige.png
        gameEngine/textures/jimmyJump_pack/PNG/LandPiece_DarkBlue.png
        gameEngine/textures/jimmyJump_pack/PNG/LandPiece_DarkGray.png
        gameEngine/textures/jimmyJump_pack/PNG/LandPiece_DarkGreen.png
        gameEngine/textures/jimmyJump_pack/PNG/LandPiece_DarkMulticolored.png
        gameEngine/textures/jimmyJump_pack/PNG/LandPiece_DarkPing.png
        gameEngine/textures/jimmyJump_pack/PNG/LandPiece_LightBeige.png
        gameEngine/textures/jimmyJump_pack/PNG/LandPiece_LightBlue.png
        gameEngine/textures/jimmyJump_pack/PNG/LandPiece_LightGray.png
        gameEngine/textures/jimmyJump_pack/PNG/LandPiece_LightGreen.png
        gameEngine/textures/jimmyJump_pack/PNG/LandPiece_LightMulticolored.png
        gameEngine/textures/jimmyJump_pack/PNG/LandPiece_LightPing.png
        gameEngine/textures/jimmyJump_pack/PNG/Lightning1.png
        gameEngine/textures/jimmyJump_pack/PNG/Lightning2.png
        gameEngine/textures/jimmyJump_pack/PNG/Mushroom.png
        gameEngine/textures/jimmyJump_pack/PNG/Number_0.png
        gameEngine/textures/jimmyJump_pack/PNG/Number_1.png
        gameEngine/textures/jimmyJump_pack/PNG/Number_2.png
        gameEngine/textures/jimmyJump_pack/PNG/Number_3.png
        gameEngine/textures/jimmyJump_pack/PNG/Number_4.png
        gameEngine/textures/jimmyJump_pack/PNG/Number_5.png
        gameEngine/textures/jimmyJump_pack/PNG/Number_6.png
        gameEngine/textures/jimmyJump_pack/PNG/Number_7.png
        gameEngine/textures/jimmyJump_pack/PNG/Number_8.png
        gameEngine/textures/jimmyJump_pack/PNG/Number_9.png
        gameEngine/textures/jimmyJump_pack/PNG/Number_Point.png
        gameEngine/textures/jimmyJump_pack/PNG/Pistol.png
        gameEngine/textures/jimmyJump_pack/PNG/Spring.png
        gameEngine/textures/jimmyJump_pack/license.txt
        gameEngine/Bomb.cpp
        gameEngine/Bomb.hpp
        gameEngine/Camera2D.cpp
        gameEngine/Camera2D.hpp
        gameEngine/gameEngine.cpp
        gameEngine/gameEngine.hpp
        gameEngine/GLSLProgram.cpp
        gameEngine/GLSLProgram.hpp
        gameEngine/GLTexture.hpp
        gameEngine/ImageLoader.cpp
        gameEngine/ImageLoader.hpp
        gameEngine/InputManager.cpp
        gameEngine/InputManager.hpp
        gameEngine/IOManager.cpp
        gameEngine/IOManager.hpp
        gameEngine/Log.cpp
        gameEngine/Log.hpp
        gameEngine/Logger.cpp
        gameEngine/Logger.hpp
        gameEngine/picoPNG.cpp
        gameEngine/picoPNG.hpp
        gameEngine/ResourceManager.cpp
        gameEngine/ResourceManager.hpp
        gameEngine/Sprite.cpp
        gameEngine/Sprite.hpp
        gameEngine/SpriteBatch.cpp
        gameEngine/SpriteBatch.hpp
        gameEngine/TextureCache.cpp
        gameEngine/TextureCache.hpp
        gameEngine/Timing.cpp
        gameEngine/Timing.hpp
        gameEngine/Vertex.cpp
        gameEngine/Vertex.hpp
        gameEngine/Window.cpp
        gameEngine/Window.hpp
        Levels/level1.txt
        colourshading.vert
        colourshading.frag
        Shaders/textureShading.frag
        Shaders/textureShading.vert
        Textures/circle.png
        Textures/credits.txt
        Textures/glass.png
        Textures/light_bricks.png
        Textures/red_bricks.png
        Agent.cpp
        Agent.hpp
        Bullet.cpp
        Bullet.hpp
        Gun.cpp
        Gun.hpp
        Human.cpp
        Human.hpp
        Level.cpp
        Level.hpp
        main.cpp
        mainGame.cpp
        mainGame.h
        Player.cpp
        Player.hpp
        Zombie.cpp
        Zombie.hpp)

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
#        ~/.brew/Cellar/sdl/1.2.15/include/SDL
#        ~/.brew/opt/sdl/include/SDL
        ~/.brew/Cellar/sdl2/2.0.5/include/SDL2
        ~/.brew/opt/sdl2/include/SDL2
        ~/.brew/Cellar/glfw/3.2.1/include/
)

# Directories to find the libraries
link_directories(
        ~/.brew/opt/alut/lib
#       ~/.brew/Cellar/sdl/1.2.15/lib
        ~/.brew/Cellar/sdl2/2.0.5/lib
        ~/.brew/opt/sdl2/include/SDL2/
#       ~/.brew/opt/sdl/lib
        ~/.brew/Cellar/glfw/3.2.1/lib
        ~/.brew/opt/sdl2/lib
        ${PROJECT_SOURCE_DIR}
        ${GLEW_LIBRARY_DIRS}
        ${GLM_LIBRARY_DIRS}
        ${GLFW_LIBRARY_DIRS}
)

add_executable(gameEngine ${SOURCE_FILES})

# Link executable with libraries
target_link_libraries(${PROJECT_NAME}
        ${OPENGL_LIBRARIES}
        ${OPENAL_LIBRARY}
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
        ${GLFW_LIBRARIES}
        alut
        glfw
        sdl2
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