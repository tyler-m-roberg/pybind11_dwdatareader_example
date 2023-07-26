cmake_minimum_required(VERSION 3.15...3.26)
#project(${SKBUILD_PROJECT_NAME} LANGUAGES CXX)
project(${SKBUILD_PROJECT_NAME} LANGUAGES CXX C)

set(Project_Base_DIR "C:\\Users\\theoz\\source\\repos\\PyBind11_Example")

set(pybind11_DIR "${Project_Base_DIR}/.venv/Lib/site-packages/pybind11/share/cmake/pybind11")
set(Arrow_DIR "C:/src/vcpkg/packages/arrow_x64-windows/share/arrow")


set(PYBIND11_NEWPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)

find_package(Arrow CONFIG REQUIRED)

message("Project Source Directory: ${PROJECT_SOURCE_DIR}")

message("---Linking DWDataReader")
add_library(DWDataReaderLib64 MODULE DWDataReaderLib64.dll)
set_target_properties(DWDataReaderLib64 PROPERTIES LINKER_LANGUAGE C)

pybind11_add_module(pybind11example src/pybind11example/example.cpp src/pybind11example/DWLoadLib.c)

target_include_directories(
    pybind11example
    PUBLIC
    C:/src/vcpkg/packages/arrow_x64-windows/include/arrow
    "${Project_Base_DIR}/.venv/Lib/site-packages/pyarrow/include"
    C:/Users/theoz/AppData/Local/Programs/Python/Python311/include
)

target_link_directories(pybind11example PUBLIC "${Project_Base_DIR}/.venv/Lib/site-packages/pyarrow")
target_link_libraries(pybind11example PUBLIC Arrow::arrow_shared arrow_python)

install(TARGETS pybind11example LIBRARY DESTINATION ./pybind11example)

