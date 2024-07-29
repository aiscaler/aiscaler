run-debug: shared-debug
	cd build && ./AIScaler.exe

run-release: shared-release
	cd build && ./install/AIScaler.exe

run-static: static
	cd mvsc/Release && ./AIScaler.exe

shared-debug:
	cmake --build build --config Debug

shared-release:
	cmake --build build --config Release

static:
	cmake --build mvsc --config Release

static-install:
	cmake --install mvsc --config Release

init-debug:
	cmake -S . -B build -G "Ninja" -DCMAKE_BUILD_TYPE="Debug"

init-release:
	cmake -S . -B build -G "Ninja" -DCMAKE_BUILD_TYPE="Release"

init-static:
	cmake -S . -B mvsc -G "Visual Studio 17 2022" -DCMAKE_CONFIGURATION_TYPES="Release"
