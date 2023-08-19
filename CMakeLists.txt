cmake_minimum_required(VERSION 3.25)
project(Self-Organization-Tree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/Qt5.15.2/5.15.2/mingw81_32")

include_directories(
        ${PROJECT_SOURCE_DIR}/Sources/Headers
        ${PROJECT_SOURCE_DIR}/Sources/DataStructures/Headers
        ${PROJECT_SOURCE_DIR}/Sources/Objects/Headers
        ${PROJECT_SOURCE_DIR}/Sources/Managers/Headers
        ${PROJECT_SOURCE_DIR}/Sources/TreeStructures/Headers
        ${PROJECT_SOURCE_DIR}/Sources/Utils/Headers

        # third party

)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

# qrc
set(QRC_SOURCE_FILES Resources/res.qrc)
qt_add_resources(${QRC_SOURCE_FILES})

add_executable(${PROJECT_NAME}
        ${QRC_SOURCE_FILES}
        Sources/main.cpp Sources/mainwindow.cpp
        Sources/Headers/mainwindow.h
        Sources/Forms/mainwindow.ui
        Sources/OGLAdapter.cpp
        Sources/Headers/OGLAdapter.h
        Sources/Managers/Camera.cpp
        Sources/Managers/Headers/Camera.h
        Sources/Managers/ResourceManager.cpp
        Sources/Managers/Headers/ResourceManager.h
        Sources/Managers/ShaderManager.cpp
        Sources/Managers/Headers/ShaderManager.h
        Sources/Managers/TextureManager.cpp
        Sources/Managers/Headers/TextureManager.h
        Sources/Objects/Light.cpp
        Sources/Objects/Headers/Light.h
        Sources/Objects/Model.cpp
        Sources/Objects/Headers/Model.h
        Sources/Objects/BasicGeometry.cpp
        Sources/Objects/Headers/BasicGeometry.h
        Sources/DataStructures/BoundingBox.cpp
        Sources/DataStructures/Headers/BoundingBox.h
        Sources/DataStructures/Headers/Range.h
        Sources/DataStructures/Range.cpp
        Sources/DataStructures/Vector.cpp
        Sources/DataStructures/Headers/Vector.h
        Sources/DataStructures/Headers/Types.h
        Sources/TreeStructures/MarkerSet.cpp
        Sources/TreeStructures/Headers/MarkerSet.h
        Sources/Utils/BaseAlgorithms.cpp
        Sources/Utils/Headers/BaseAlgorithms.h
        Sources/TreeStructures/Headers/Environment.h
        Sources/TreeStructures/Metamer.cpp
        Sources/TreeStructures/Headers/Metamer.h
        Sources/Objects/TreeSkeleton.cpp
        Sources/Objects/TreeSkeleton.h
        Sources/TreeStructures/Tree.cpp
        Sources/TreeStructures/Headers/Tree.h)


target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets

)