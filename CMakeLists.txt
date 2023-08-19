cmake_minimum_required(VERSION 3.25)
project(Self-Organization-Tree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/Qt5.15.2/5.15.2/mingw81_32")

file(GLOB_RECURSE HEADER_DIRS LIST_DIRECTORIES true "${PROJECT_SOURCE_DIR}/Sources/*Headers")
include_directories(${HEADER_DIRS})

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

# qrc
set(QRC_SOURCE_FILES Resources/res.qrc)
qt_add_resources(${QRC_SOURCE_FILES})

file(GLOB_RECURSE SOURCE_FILES
        Sources/*.cpp
        Sources/*.h
        Sources/*.ui
        )

add_executable(${PROJECT_NAME} ${QRC_SOURCE_FILES} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)