//
// Created by FINNSEEFLY on 21.11.2020.
//

#ifndef ARKANOID_COMPLEMENTARY_H
#define ARKANOID_COMPLEMENTARY_H

#define RESOURCE_ROOT "res\\"
#define LVL_DIR "lvl\\"
#define LVL_EXTENSION ".txt"
#define BACKGROUND_PIC_PATH L"res\\interface\\SpaceBlurred1080p.jpg"
#define PAUSE_PIC_PATH L"res\\interface\\Pause.png"
#define GAME_BOX_PIC_PATH L"res\\interface\\GamingZone.png"
#define PLATFORM_PIC_PATH L"res\\platform\\platform.png"
#define BALL_PIC_PATH L"res\\ball\\Ball32x32.png"
#define BLUE_BRICK_PIC_PATH L"res\\bricks\\BlueBrick.png"
#define GREEN_BRICK_PIC_PATH L"res\\bricks\\GreenBrick.png"
#define PURPLE_BRICK_PIC_PATH L"res\\bricks\\PurpleBrick.png"
#define RED_BRICK_PIC_PATH L"res\\bricks\\RedBrick.png"
#define YELLOW_BRICK_PIC_PATH L"res\\bricks\\YellowBrick.png"

#define TEXT_ZONE_HEIGHT 65
#define TEXT_TOP 64
#define TEXT_BOTTOM 128
#define LEVEL_LEFT 20
#define LEVEL_RIGHT 156
#define SCORE_LEFT 217
#define SCORE_RIGHT 863
#define LIVES_LEFT 923
#define LIVES_RIGHT 1059

#define DEFAULT_FONT_HEIGHT 55
#define DEFAULT_FONT_WIDTH 23
#define DEFAULT_FONT_WEIGHT 32
#define DEFAULT_FONT_ESCAPEMENT 0
#define DEFAULT_FONT_UNDERLINE false
#define DEFAULT_FONT_STRIKE_OUT false
#define DEFAULT_FONT_ITALIC false

#define DEFAULT_GAME_ZONE_TOP 150
#define DEFAULT_GAME_ZONE_WIDTH 1080
#define MIN_GAME_ZONE_SIDE 540

#define DEFAULT_PLATFORM_OFFSET_X 432
#define DEFAULT_PLATFORM_OFFSET_Y 890

#define DEFAULT_SPEED 1
#define DEFAULT_ANGLE 45

#include "iostream"
#include "Windows.h"
#include "sstream"

struct FloatRECT {
    float left;
    float top;
    float right;
    float bottom;
};

struct BoolRECT {
    bool leftUp = false;
    bool leftDown = false;
    bool rightUp = false;
    bool rightDown = false;
};

bool IsDotInRect(float x, float y, FloatRECT rect);

BoolRECT FindOccurrences(FloatRECT target, FloatRECT incoming);

LPCSTR ConvertIntToLPWSTR(int value);

std::string ConvertIntToString(int value);


#endif //ARKANOID_COMPLEMENTARY_H
