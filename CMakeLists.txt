cmake_minimum_required(VERSION 3.17)
project(Arkanoid)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_CXX_STANDARD_LIBRARIES} -lgdiplus")

add_executable(Arkanoid main.cpp Platform.cpp Platform.h DrawableShape.cpp DrawableShape.h Brick.cpp Brick.h Resources.h Ball.cpp Ball.h GameSession.cpp GameSession.h)