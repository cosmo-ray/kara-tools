cmake_minimum_required(VERSION 2.8)
PROJECT(helloworld)
FIND_PACKAGE(Qt4 REQUIRED)

SET(helloworld_SOURCES test.cpp MainWindow.cpp)
SET(helloworld_HEADERS MainWindow.hh)

#QT4_WRAP_CPP(helloworld_HEADERS_MOC ${helloworld_HEADERS})

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

ADD_EXECUTABLE(helloworld ${helloworld_SOURCES}
    ${helloworld_HEADERS_MOC})
TARGET_LINK_LIBRARIES(helloworld ${QT_LIBRARIES})
