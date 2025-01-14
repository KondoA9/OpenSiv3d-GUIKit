cmake_minimum_required (VERSION 3.1)

enable_language(CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-unknown-pragmas -fPIC -msse4.1")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -pg -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG -march=x86-64")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g3 -Og -pg")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG -march=x86-64")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	add_compile_options ("-fcolor-diagnostics")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	add_compile_options ("-fdiagnostics-color=always")
endif()

find_package(PkgConfig)

pkg_check_modules(OPENCV4 REQUIRED opencv4)

project(Aoba-Example)

include_directories(
	SYSTEM "/usr/include"
	SYSTEM "../../Dependencies/include"
	SYSTEM "../../Dependencies/include/ThirdParty"
	"../../Aoba/include"
)

set(SOURCE_FILES
	"../../Test/Example/Example.cpp"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../../App)

add_executable(Aoba-Example ${SOURCE_FILES})

target_link_libraries(Aoba-Example
	${PROJECT_SOURCE_DIR}/../build/libaoba.a
	${PROJECT_SOURCE_DIR}/../../Dependencies/lib/Linux/libSiv3D.a
	${OPENCV4_LIBRARIES}
	-lasound
	-lavcodec
	-lavformat
	-lavutil
	-lcurl
	-ldl
	-lfreetype
	-lGL
	-lglib-2.0
	-lgobject-2.0
	-lgif
	-lgio-2.0
	-lgdk-3
	-lgtk-3
	-lharfbuzz
	  -logg
	-lopencv_core
	-lopencv_imgcodecs
	-lopencv_imgproc
	-lopencv_objdetect
	-lopencv_photo
	-lopencv_videoio
	-lopus
	-lopusfile
	-lpthread
	-lpng
	-lSoundTouch
	-lswresample
	-ltiff
	-lturbojpeg
	-luuid
	  -lvorbis
	  -lvorbisenc
	  -lvorbisfile
	-lwebp
	-lX11
	-lXft
)