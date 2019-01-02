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

set(SRC_BASE ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SERVER_SRCS
	"${SRC_BASE}/main.cpp"
	"${SRC_BASE}/Core/Core.cpp"
	"${SRC_BASE}/Core/Core.h"
	"${SRC_BASE}/Managers/DatabaseManager.cpp"
	"${SRC_BASE}/Managers/DatabaseManager.h"
	"${SRC_BASE}/Managers/NetworkManager.cpp"
	"${SRC_BASE}/Managers/NetworkManager.h"
	"${SRC_BASE}/Managers/RoomManager.cpp"
	"${SRC_BASE}/Managers/RoomManager.h"
	"${SRC_BASE}/Managers/UserManager.cpp"
	"${SRC_BASE}/Managers/UserManager.h"
	"${SRC_BASE}/Stuff/Manager.h"
	"${SRC_BASE}/Stuff/Stuff.h"
)

add_definitions(
	-D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
	-DASIO_STANDALONE 
	-DASIO_HAS_STD_ADDRESSOF 
	-DASIO_HAS_STD_ARRAY
	-DASIO_HAS_CSTDINT
	-DASIO_HAS_STD_SHARED_PTR
	-DASIO_HAS_STD_TYPE_TRAITS)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include/)

add_executable(server ${SERVER_SRCS})

target_link_libraries(server 
	"${CLIENT_LIBS_DIR}/sqlite3pp.lib"
	"${CLIENT_LIBS_DIR}/sqlite3.lib")