run-debug: shared-debug
	cd build/msys && ./AIScaler.exe

run-release: shared-release
	cd build/msys && ./install/AIScaler.exe

run-static: static
	cd build/msvc/Release && ./AIScaler.exe

shared-debug:
	cmake --build build/msys --config Debug

shared-release:
	cmake --build build/msys --config Release

static:
	cmake --build build/msvc --config Release

static-install:
	cmake --install build/msvc --config Release

init-debug:
	cmake -S . -B build/msys -G "Ninja" -DCMAKE_BUILD_TYPE="Debug"

init-release:
	cmake -S . -B build/msys -G "Ninja" -DCMAKE_BUILD_TYPE="Release"

init-static:
	cmake -S . -B build/msvc -G "Visual Studio 17 2022" -DCMAKE_CONFIGURATION_TYPES="Release"
