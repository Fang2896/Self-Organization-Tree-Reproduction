cmake_minimum_required(VERSION 3.25)
project(Self-Organization-Tree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/Qt5.15.2/5.15.2/mingw81_32")

include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/Sources/Headers
        ${PROJECT_SOURCE_DIR}/Sources/Utils/Headers
        ${PROJECT_SOURCE_DIR}/Sources/Objects/Headers

        # third party

)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

# qrc
set(QRC_SOURCE_FILES Sources/res.qrc)
qt_add_resources(${QRC_SOURCE_FILES})

add_executable(${PROJECT_NAME}
        ${QRC_SOURCE_FILES}
        Sources/main.cpp Sources/mainwindow.cpp
        Sources/Headers/mainwindow.h
        Sources/Forms/mainwindow.ui
        Sources/OGLAdapter.cpp
        Sources/Headers/OGLAdapter.h
        Sources/Utils/Camera.cpp
        Sources/Utils/Headers/Camera.h
        Sources/Utils/ResourceManager.cpp
        Sources/Utils/Headers/ResourceManager.h
        Sources/Utils/ShaderManager.cpp
        Sources/Utils/Headers/ShaderManager.h
        Sources/Utils/TextureManager.cpp
        Sources/Utils/Headers/TextureManager.h
        Sources/Objects/Light.cpp
        Sources/Objects/Headers/Light.h
        Sources/Objects/Model.cpp
        Sources/Objects/Headers/Model.h
        Sources/Objects/BasicGeometry.cpp
        Sources/Objects/Headers/BasicGeometry.h)


target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets

)