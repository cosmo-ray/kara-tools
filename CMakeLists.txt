cmake_minimum_required(VERSION 2.8)
PROJECT(asraf)
FIND_PACKAGE(Qt4 REQUIRED)

set(CMAKE_SYSTEM_NAME Windows)

#set(CMAKE_CXX_COMPILER i486-mingw32-g++)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if (MINGW)
     set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static-libgcc")
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
     set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_C_FLAGS} -static-libgcc -s")
     set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS} -static-libgcc -static-libstdc++ -s")
endif()


set(asraf_SOURCES main.cpp MainWindow.cpp core.cpp)
set(asraf_HEADERS MainWindow.hh core.hh)
set(EXECUTABLE_OUTPUT_PATH ../)

QT4_WRAP_CPP(asraf_HEADERS_MOC ${asraf_HEADERS})

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

ADD_EXECUTABLE(asraf ${asraf_SOURCES}
    ${asraf_HEADERS_MOC})
TARGET_LINK_LIBRARIES(asraf ${QT_LIBRARIES})
