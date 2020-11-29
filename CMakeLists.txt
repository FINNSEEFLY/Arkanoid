cmake_minimum_required(VERSION 3.17)
project(Arkanoid)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_CXX_STANDARD_LIBRARIES} -lgdiplus")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(Arkanoid WIN32 main.cpp Platform.cpp Platform.h DrawableShape.cpp DrawableShape.h Brick.cpp Brick.h Complementary.h Ball.cpp Ball.h GameSession.cpp GameSession.h Bonus.cpp Bonus.h Complementary.cpp TextBox.cpp TextBox.h icon.o app.o)