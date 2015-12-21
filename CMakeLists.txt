cmake_minimum_required(VERSION 3.1)

project(offlinelauncher)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set (CMAKE_CXX_STANDARD 11)

# Find the QtWidgets library
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)
if(WIN32)
	find_package(Qt5WinExtras)
endif()

file(GLOB Sources "*.cpp")
file(GLOB Headers "*.h")
file(GLOB Resources "*.qrc" )
file(GLOB UIS "*.ui")

qt5_add_resources(ResourceSources ${Resources})
qt5_wrap_ui(UI_SRCS ${UIS})

# Tell CMake to create the helloworld executable
add_executable(Offline_Launcher WIN32 main.cpp ${Sources} ${Headers} ${ResourceSources} ${UI_SRCS})

# Use the Widgets module from Qt 5.
if(WIN32)
	target_link_libraries(Offline_Launcher Qt5::Core Qt5::Gui Qt5::Widgets Qt5::WinExtras)
else()
	target_link_libraries(Offline_Launcher Qt5::Core Qt5::Gui Qt5::Widgets)
endif()
