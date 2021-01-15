cmake_minimum_required(VERSION 2.6)
project(MYENGINE)

string(TOLOWER "${CMAKE_CXX_COMPILER_ID}" COMP)
string(TOLOWER "${CMAKE_SYSTEM_NAME}" PLATFORM)
string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" ARCH)
message("${COMP}-${PLATFORM}-${ARCH}")

add_definitions(-DSDL_MAIN_HANDLED)

include_directories(
  	src
  	${PROJECT_SOURCE_DIR}/contrib/${COMP}-${PLATFORM}-${ARCH}/include
	)

link_directories(
  ${PROJECT_SOURCE_DIR}/contrib/${COMP}-${PLATFORM}-${ARCH}/lib
  )

if(MINGW)
  	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s -static")
  	add_definitions(-DGLEW_STATIC)
  	set(STATIC_LIBS imm32 iconv winmm ole32 gdi32 oleaut32 version)
  	set(LIBGLEW glew32)
  	set(LIBSDL2 SDL2)
elseif(MSVC)
  	#add_definitions(-DGLEW_STATIC)
  	set(STATIC_LIBS imm32 winmm setupapi version)
  	set(LIBGLEW glew32)
  	set(LIBSDL2 SDL2-static)
endif()

add_library(myengine
  	src/myengine/Additional.h
	src/myengine/Assets.h
	
	src/myengine/Camera.h
	src/myengine/Camera.cpp
	
	src/myengine/SaveScene.h
	src/myengine/SaveScene.cpp
	
	src/myengine/LoadScene.h
	src/myengine/LoadScene.cpp
	
	src/myengine/ToolPanel.h
	src/myengine/ToolPanel.cpp
	
	src/myengine/Clock.h
	src/myengine/Clock.cpp

	src/myengine/KeyboardAndMouse.h
	src/myengine/KeyboardAndMouse.cpp
	
	src/myengine/Model.h
	src/myengine/Model.cpp
	
	src/myengine/ShaderProgram.h
	src/myengine/ShaderProgram.cpp
	
	src/myengine/FragmentShader.h
	src/myengine/FragmentShader.cpp
	
	src/myengine/VertexShader.h
	src/myengine/VertexShader.cpp
	)
	
if(MSVC OR MINGW)
  	target_link_libraries(myengine ${LIBGLEW} opengl32 ${LIBSDL2} ${STATIC_LIBS})
else()
  	target_link_libraries(myengine GLEW GL ${LIBSDL2} ${STATIC_LIBS})
endif()

add_executable(demo
  	src/demo/main.cpp
	)
	
target_link_libraries(demo myengine)