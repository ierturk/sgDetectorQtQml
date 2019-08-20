cmake_minimum_required(VERSION 3.1)

project(sgDetector LANGUAGES CXX)

# Qt specific
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# LİbTorch
set(Torch_DIR
    /home/ierturk/Work/Tools/pyENVs/pytorch-py37/lib/python3.7/site-packages/torch/share/cmake/Torch)

# Required Libraries
find_package(Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Torch REQUIRED)

#Sources
aux_source_directory(./Source/Src DIR_SRC)
set(RSRC ./Resource/qml.qrc)
include_directories(
    ./Source/Inc
    )

add_executable(${PROJECT_NAME} ${DIR_SRC} ${RSRC})
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(${PROJECT_NAME}
    PRIVATE Qt5::Core Qt5::Quick
    ${TORCH_LIBRARIES}
    )
