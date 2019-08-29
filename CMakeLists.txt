cmake_minimum_required(VERSION 3.1)

project(sgDetector LANGUAGES CXX)

# Qt specific
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# LibTorch
set(Torch_DIR
    /home/ierturk/Work/Tools/Libs/libtorch/share/cmake/Torch)

# Required Libraries
find_package(Qt5 COMPONENTS Core Quick Multimedia REQUIRED)
find_package(Torch REQUIRED)
find_package(OpenCV REQUIRED)

find_package(Qt5GStreamer REQUIRED)

# Sources
# aux_source_directory(./Source/Src DIR_SRC)
# aux_source_directory(./Source/Src DIR_INC)

include_directories(
    ${OpenCV_INCLUDE_DIRS}
    ${QTGSTREAMER_INCLUDES}
    )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${QTGSTREAMER_FLAGS}")
add_definitions(${QTGSTREAMER_DEFINITIONS})

set(SRC
    ./Source/Src/main.cpp
    ./Source/Src/SGDetFilter.cpp
    ./Source/Src/SGDetFilterRunnable.cpp
    ./Source/Src/SSDNet.cpp
    )
set(INC
    ./Source/Inc/SGDetFilter.h
    ./Source/Inc/SGDetFilterRunnable.h
    ./Source/Inc/SSDNet.h
    )
set(RSRC ./Resource/qml.qrc)

include_directories(./Source/Inc)

add_executable(${PROJECT_NAME} ${SRC} ${INC} ${RSRC})
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(${PROJECT_NAME}
    PRIVATE Qt5::Core Qt5::Quick Qt5::Multimedia
    ${QTGSTREAMER_QUICK_LIBRARIES}
    ${TORCH_LIBRARIES}
    ${OpenCV_LIBS}
    )

# set_property(TARGET sgDetector PROPERTY CXX_STANDARD 11)
