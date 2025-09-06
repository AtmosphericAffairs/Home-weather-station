cmake_minimum_required(VERSION 4.0.2)
project(CMakeProject3)  # Имя проекта

# Настройка стандарта C++ (например, C++17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавление исполняемого файла


# Если нужны библиотеки (например, Qt)
#set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};C:/Program Files/Microsoft Visual Studio/2022/Community/VC/vcpkg/installed/x64-windows/share/cmake/Qt5")
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};C:/Program Files/Microsoft Visual Studio/2022/Community/VC/vcpkg/installed/x64-windows/share/boost_system")
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};C:/Program Files/Microsoft Visual Studio/2022/Community/VC/vcpkg/installed/x64-windows/share/nlohmann_json")
#set(CMAKE_TOOLCHAIN_FILE "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/vcpkg/scripts/buildsystems/vcpkg.cmake")
add_compile_definitions(QT_USE_UTF8_STRING_LITERALS)

#f(WIN32)
#   set(CMAKE_WIN32_EXECUTABLE TRUE)  # Указываем, что это GUI-приложение
#ndif()

find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Boost REQUIRED COMPONENTS system) 
find_package(nlohmann_json REQUIRED)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)


add_executable(CMakeProject3 "CMakeProject3/meteo_client.cpp" "CMakeProject3/toppanel/topPanel.cpp" "CMakeProject3/toppanel/topPanel.h" CMakeProject3/resources.qrc "CMakeProject3/mainWindow/mainWindow.h" "CMakeProject3/mainWindow/mainWindow.cpp"
 "CMakeProject3/com_port/com_port.h" "CMakeProject3/com_port/com_potr.cpp"  "CMakeProject3/middlepanel/middle_panel.h" "CMakeProject3/middlepanel/middle_panel.cpp"  )
target_link_libraries(CMakeProject3 PRIVATE Qt5::Core Qt5::Widgets Qt5::Gui Boost::system nlohmann_json::nlohmann_json)


