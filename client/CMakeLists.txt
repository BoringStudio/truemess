set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(CLIENT_LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/x64)
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin/x64)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
	set(CLIENT_LIBS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/extlibs/x86)
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin/x86)
endif()

file(GLOB_RECURSE CLIENT_SRCS
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/Truemess/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/include/Truemess/*.inl"
)

#file(GLOB CLIENT_SRCS
#	${CMAKE_CURRENT_SOURCE_DIR}/src/Truemess/System/Core.cpp
#	${CMAKE_CURRENT_SOURCE_DIR}/src/Truemess/System/SmartString.cpp
#	${CMAKE_CURRENT_SOURCE_DIR}/src/XCurses/XCurses.cpp
#	${CMAKE_CURRENT_SOURCE_DIR}/src/XCurses/XWindow.cpp
#	${CMAKE_CURRENT_SOURCE_DIR}/include/Truemess/System/Core.h
#	${CMAKE_CURRENT_SOURCE_DIR}/include/Truemess/System/SmartString.h
#	${CMAKE_CURRENT_SOURCE_DIR}/include/Truemess/System/State.h
#	${CMAKE_CURRENT_SOURCE_DIR}/include/Truemess/System/StateManager.h
#	${CMAKE_CURRENT_SOURCE_DIR}/include/Truemess/System/StateManager.inl
#	${CMAKE_CURRENT_SOURCE_DIR}/include/Truemess/System/Truelogger.h
#	${CMAKE_CURRENT_SOURCE_DIR}/include/Truemess/System/Utf.h
#	${CMAKE_CURRENT_SOURCE_DIR}/include/Truemess/System/Vector.h
#	${CMAKE_CURRENT_SOURCE_DIR}/include/Truemess/System/Vector.inl
#	${CMAKE_CURRENT_SOURCE_DIR}/include/Truemess/Memory/ObjectPool.h
#	${CMAKE_CURRENT_SOURCE_DIR}/include/Truemess/Memory/Resource.h
#	${CMAKE_CURRENT_SOURCE_DIR}/include/XCurses/XCurses.h
#	${CMAKE_CURRENT_SOURCE_DIR}/include/XCurses/XCursesConfig.h
#	${CMAKE_CURRENT_SOURCE_DIR}/include/XCurses/XWindow.h
#	${CMAKE_CURRENT_SOURCE_DIR}/include/XCurses/XBorder.h
#)

add_definitions(-DPDC_WIDE)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_executable(truemess ${CLIENT_SRCS})

target_link_libraries(truemess "${CLIENT_LIBS_DIR}/pdcurses.lib")