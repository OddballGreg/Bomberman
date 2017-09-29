cmake_minimum_required(VERSION 3.8)
project(bomberman)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)
find_package(OpenAL REQUIRED)
find_package(PkgConfig REQUIRED)

# Run install script
set(BASH_CMD "bash")
set(BASH_ARG "../INSTALL.sh")
set(GIT_CMD "git submodule")
set(GIT_ARG "update")
set(GIT_FLAG "--init --recursive")
execute_process(COMMAND ${BASH_CMD} ${BASH_ARG})
execute_process(COMMAND	${GIT_CMD} ${GIT_ARG} ${GIT_FLAG})

set(NANOGUI_DIR "external/nanogui")

# Adding dependencies
pkg_search_module(GLEW REQUIRED glew)
pkg_search_module(GLFW3 REQUIRED glfw3)
pkg_search_module(GLM REQUIRED glm)
pkg_search_module(FREETYPE REQUIRED freetype2)
pkg_search_module(SDL REQUIRED sdl)
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(LIBPNG REQUIRED libpng)

add_subdirectory(${NANOGUI_DIR})
include_directories(${NANOGUI_DIR}/include)
include_directories(${NANOGUI_EXTRA_INCS})
add_definitions(${NANOGUI_EXTRA_DEFS})

# These directories get symlinked into the build directory after compilation
set(RESOURCE_DIRS
        resources
        gameEngine/src/perspectiveMatrixLightedShader.vert
        gameEngine/perspectiveMatrixLightedShader.vert
        gameEngine/resources/shaders/OpenGL33/
        gameEngine/resources/shaders/OpenGL21/
        gameEngine/resources/fonts/
		SoundEngine/music/
		maps/
        )

set(SOURCE_FILES
        src/main.cpp
        src/GameLogic.cpp
        src/MapLoader.cpp
        include/MapLoader.hpp
		include/menu.hpp
		src/menu.cpp
		SoundEngine/SoundEngine.cpp
		SoundEngine/SoundEngine.hpp
        gameEngine/src/BoundingBoxSet.cpp
        gameEngine/src/GetTokens.cpp
        gameEngine/src/Image.cpp
        gameEngine/src/Logger.cpp
        gameEngine/src/Model.cpp
        gameEngine/src/Renderer.cpp
        gameEngine/src/SceneObject.cpp
		gameEngine/src/Menu.cpp
        gameEngine/include/BoundingBoxSet.hpp
        gameEngine/include/GetTokens.hpp
        gameEngine/include/Image.hpp
        gameEngine/include/Logger.hpp
        gameEngine/include/Model.hpp
        gameEngine/include/Renderer.hpp
        gameEngine/include/SceneObject.hpp
		gameEngine/include/Menu.hpp
		gameEngine/src/Enemy.cpp
		gameEngine/include/Enemy.hpp
		src/Settings.cpp
		include/Settings.hpp)

# Directories to find the header files
include_directories(
        include
		~/.brew/include
		~/.brew/include/freetype2
		~/.brew/include/eigen3
		${OPENAL_INCLUDE_DIR}
		~/.brew/opt/alut/include
		${PROJECT_SOURCE_DIR}/external/nanogui/include
		${PROJECT_SOURCE_DIR}/external/nanogui/ext
		${PROJECT_SOURCE_DIR}/external/nanogui/ext/nanovg/src
		${PROJECT_SOURCE_DIR}/external/nanogui/ext/eigen
		${PROJECT_SOURCE_DIR}/external/nanogui/ext/glfw/include
        #${NANOGUI_DIR}/include
		#${NANOGUI_DIR}/ext/nanovg/src
		#${NANOGUI_DIR}/ext/pybind11/include
        #${NANOGUI_DIR}/ext/glfw/include
        #${NANOGUI_DIR}/ext/eigen
        #${NANOGUI_DIR}/ext/glad/include
)

# Directories to find the libraries
link_directories(
		~/.brew/lib
		~/.brew/opt/alut/lib
        ${PROJECT_SOURCE_DIR}
        ${GLEW_LIBRARY_DIRS}
        ${GLM_LIBRARY_DIRS}
        ${GLFW_LIBRARY_DIRS}
		#${NANOGUI_DIR}/src
        #${NANOGUI_DIR}/python
		#${NANOGUI_DIR}/ext/nanovg/src
        #${NANOGUI_DIR}/ext/glfw/src
        #${NANOGUI_DIR}/ext/glad/src
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
		alut
		freetype
		png
		glfw
		GLEW
        nanogui
        ${NANOGUI_EXTRA_LIBS}
)

set(LINKER_FLAGS "-framework Cocoa -framework OpenGL -framework IOKit -framework CoreFoundation -framework CoreVideo -framework Carbon -lfreetype -lpng -lglfw -lGLEW")

if (APPLE)
    target_link_libraries(${PROJECT_NAME}
		${LINKER_FLAGS})
endif()

