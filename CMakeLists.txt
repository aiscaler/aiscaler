cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

cmake_policy(SET CMP0091 NEW)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INSTALL_PREFIX "install") 

project(AIScaler VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

set(SOURCES 
	src/main.cpp
	src/mainwindow.cpp
	src/image.cpp
	src/worker.cpp
)

set(HEADERS
	src/mainwindow.h
	src/image.h
	src/worker.h
)

set(UIS 
	src/ui/mainwindow.ui
	src/ui/image.ui
)

set(RESOURCES
	src/resources.qrc
	src/appicon.rc
)

add_executable(${PROJECT_NAME}
	${SOURCES}
	${HEADERS}
	${UIS}
	${RESOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
	Qt6::Core
	Qt6::Widgets
	Qt6::Gui
)

if(MSVC)
	add_compile_options(/Zc:__cplusplus)
	target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
endif()

if(WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_CONFIGURATION_TYPE STREQUAL "Release")
	set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)

  set(INSTALL_PATH "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_PREFIX}")

  file(MAKE_DIRECTORY ${INSTALL_PATH})

  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E make_directory "${INSTALL_PATH}"
      COMMAND windeployqt6 --no-translations --no-opengl-sw --no-translations --no-compiler-runtime --dir ${INSTALL_PATH} $<TARGET_FILE:${PROJECT_NAME}>
      COMMENT "Deploying Qt application..."
  )

  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ${INSTALL_PATH}
      COMMENT "Copying executable to deployment directory"
  )
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION . COMPONENT ${PROJECT_NAME})
