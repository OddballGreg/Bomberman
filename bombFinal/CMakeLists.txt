cmake_minimum_required(VERSION 3.8)
project(bomberman)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)

# Check the dependencies are install on MACOS
execute_process(COMMAND bash INSTALL.sh)

# Adding dependencies
pkg_search_module(GLEW REQUIRED glew)
pkg_search_module(GLFW3 REQUIRED glfw3)
pkg_search_module(GLM REQUIRED glm)
pkg_search_module(FREETYPE REQUIRED freetype2)
pkg_search_module(SDL REQUIRED sdl)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(LIBPNG REQUIRED libpng)

# These directories get symlinked into the build directory after compilation
set(RESOURCE_DIRS
        resources
        gameEngine/src/perspectiveMatrixLightedShader.vert
        gameEngine/perspectiveMatrixLightedShader.vert
        gameEngine/resources/shaders/OpenGL33/
        gameEngine/resources/shaders/OpenGL21/
        gameEngine/resources/fonts/
        )

set(SOURCE_FILES
        src/main.cpp
        src/GameLogic.cpp
        gameEngine/src/BoundingBoxSet.cpp
        gameEngine/src/GetTokens.cpp
        gameEngine/src/Image.cpp
        gameEngine/src/Logger.cpp
        gameEngine/src/Model.cpp
        gameEngine/src/Renderer.cpp
        gameEngine/src/SceneObject.cpp
        gameEngine/include/BoundingBoxSet.hpp
        gameEngine/include/GetTokens.hpp
        gameEngine/include/Image.hpp
        gameEngine/include/Logger.hpp
        gameEngine/include/Model.hpp
        gameEngine/include/Renderer.hpp
        gameEngine/include/SceneObject.hpp
		)

# Directories to find the header files
include_directories(
        include
		~/.brew/include
		~/.brew/include/freetype2
		#${NANOGUI_DIR}/ext/glfw/include
		#${NANOGUI_DIR}/include
		#${NANOGUI_DIR}/ext/eigen
		#${NANOGUI_DIR}/ext/nanovg/src
)

# Directories to find the libraries
link_directories(
		~/.brew/lib
        ${PROJECT_SOURCE_DIR}
        ${GLEW_LIBRARY_DIRS}
        ${GLM_LIBRARY_DIRS}
        ${GLFW_LIBRARY_DIRS}
		#${NANOGUI_DIR}
		#${NANOGUI_DIR}/ext/eigen
		#${NANOGUI_DIR}/ext/nanovg/src
)

add_executable(bomberman ${SOURCE_FILES})

# Link executable with libraries
target_link_libraries(${PROJECT_NAME}
        ${OPENGL_LIBRARIES}
        ${OPENAL_LIBRARY}
        ${GLEW_LIBRARIES}
        ${GLM_LIBRARIES}
        ${GLFW_LIBRARIES}
        ${FT_LIBRARIES}
        freetype
		png
		glfw
		GLEW
	)

set(LINKER_FLAGS "-framework Cocoa -framework OpenGL -framework IOKit -framework CoreFoundation -framework CoreVideo -framework Carbon -lfreetype -lpng -lglfw -lGLEW")

if (APPLE)
    target_link_libraries(${PROJECT_NAME}
		${LINKER_FLAGS})
endif()

