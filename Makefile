run:
	./build/mingw/AIScaler

run-debug: shared-debug
	./build/mingw/AIScaler

run-release: shared-release
	./build/mingw/AIScaler

run-static: static
	./build/msvc/Release/AIScaler

shared-debug:
	cmake --build build/mingw --config Debug

shared-release:
	cmake --build build/mingw --config Release

static:
	cmake --build build/msvc --config Release

static-install:
	cmake --install build/msvc --config Release

init-debug:
	cmake -S . -B build/mingw -G "Ninja" -DCMAKE_INSTALL_PREFIX="AppDir" -DCMAKE_BUILD_TYPE="Debug"

init-release:
	cmake -S . -B build/mingw -G "Ninja" -DCMAKE_INSTALL_PREFIX="AppDir" -DCMAKE_BUILD_TYPE="Release"

init-static:
	cmake -S . -B build/msvc -G "Visual Studio 17 2022" -DCMAKE_PREFIX_PATH "D:/Qt/6.7.2/msvc2019_64_static" \
		-DCMAKE_INSTALL_PREFIX="install" -DCMAKE_CONFIGURATION_TYPES="Release"
