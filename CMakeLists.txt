cmake_minimum_required(VERSION 3.17)
project(Arkanoid)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_CXX_STANDARD_LIBRARIES} -lgdiplus")
set( ICON_NAME "icon.ico" )
set( ICON_PATH "res/ico/${ICON_NAME}" )
set(WIN32_EXECUTABLE)

add_executable(Arkanoid main.cpp Platform.cpp Platform.h DrawableShape.cpp DrawableShape.h Brick.cpp Brick.h Resources.h Ball.cpp Ball.h GameSession.cpp GameSession.h)