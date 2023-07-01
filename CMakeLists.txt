cmake_minimum_required(VERSION 3.15...3.26)
#project(${SKBUILD_PROJECT_NAME} LANGUAGES CXX)
project(${SKBUILD_PROJECT_NAME} LANGUAGES CXX C)

list(APPEND CMAKE_PREFIX_PATH "C:/src/vcpkg/packages/arrow_x64-windows")
list(APPEND CMAKE_PREFIX_PATH "C:/Users/theoz/source/repos/PyBind11_Example/.venv/Lib/site-packages/pyarrow")


set(PYBIND11_NEWPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)

include_directories(.)
include_directories(C:/Users/theoz/source/repos/PyBind11_Example/.venv/Lib/site-packages/pyarrow/include/)
include_directories(C:/src/vcpkg/packages/arrow_x64-windows/include/arrow)
include_directories("${PROJECT_SOURCE_DIR}")



find_package(Arrow CONFIG REQUIRED)
#find_package(ArrowPython HINTS "C:/Users/theoz/source/repos/PyBind11_Example/.venv/Lib/site-packages/pyarrow")
    
#include_directories("${PROJECT_SOURCE_DIR}/DWDataReader")
#add_subdirectory(DWDataReader)

#message("---Linking DWDataReader")
add_library(DWDataReaderLib64 MODULE DWDataReaderLib64.dll)
link_directories(C:/Users/theoz/source/repos/PyBind11_Example/.venv/Lib/site-packages/pyarrow)
set_target_properties(DWDataReaderLib64 PROPERTIES LINKER_LANGUAGE C)

pybind11_add_module(PyBind11Example example.cpp DWLoadLib.c)
#target_link_libraries(${SKBUILD_PROJECT_NAME} PRIVATE DWDataReaderLib64)

target_link_libraries(PyBind11Example PRIVATE Arrow::arrow_shared arrow_python)

install(TARGETS PyBind11Example LIBRARY DESTINATION .)

