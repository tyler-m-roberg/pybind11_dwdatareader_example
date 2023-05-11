cmake_minimum_required(VERSION 3.15...3.26)
#project(${SKBUILD_PROJECT_NAME} LANGUAGES CXX)
project(${SKBUILD_PROJECT_NAME} LANGUAGES CXX C)

set(PYBIND11_NEWPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)

include_directories(.)
include_directories("${PROJECT_SOURCE_DIR}")
#include_directories("${PROJECT_SOURCE_DIR}/DWDataReader")
#add_subdirectory(DWDataReader)

#message("---Linking DWDataReader")
add_library(DWDataReaderLib64 MODULE DWDataReaderLib64.dll)
set_target_properties(DWDataReaderLib64 PROPERTIES LINKER_LANGUAGE C)

pybind11_add_module(PyBind11Example example.cpp DWLoadLib.c)
#target_link_libraries(${SKBUILD_PROJECT_NAME} PRIVATE DWDataReaderLib64)

install(TARGETS PyBind11Example LIBRARY DESTINATION .)

