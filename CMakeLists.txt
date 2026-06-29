cmake_minimum_required(VERSION 3.16)

project(3D_SIMULATOR LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(3D_SIMULATOR main.cpp
    cpoint.h cpoint.cpp
    cline.h cline.cpp
    cvector.h cvector.cpp)

include(GNUInstallDirs)
install(TARGETS 3D_SIMULATOR
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
