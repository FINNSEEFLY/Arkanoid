#ifndef ARKANOID_COMPLEMENTARY_H
#define ARKANOID_COMPLEMENTARY_H

#define RESOURCE_ROOT "res\\"
#define LVL_DIR "lvl\\"
#define LVL_EXTENSION ".txt"
#define LEADER_BOARD_PATH "res\\data\\lb.txt"
#define BACKGROUND_PIC_PATH L"res\\interface\\SpaceBlurred720p.jpg"
#define PAUSE_PIC_PATH L"res\\interface\\Pause.png"
#define LEADER_BOARD_PIC_PATH L"res\\interface\\LeaderBoard.png"
#define GAME_BOX_PIC_PATH L"res\\interface\\GamingZone.png"
#define PLATFORM_PIC_PATH L"res\\platform\\platform.png"
#define BALL_PIC_PATH L"res\\ball\\Ball32x32.png"
#define BLUE_BRICK_PIC_PATH L"res\\bricks\\BlueBrick.png"
#define GREEN_BRICK_PIC_PATH L"res\\bricks\\GreenBrick.png"
#define PURPLE_BRICK_PIC_PATH L"res\\bricks\\PurpleBrick.png"
#define RED_BRICK_PIC_PATH L"res\\bricks\\RedBrick.png"
#define YELLOW_BRICK_PIC_PATH L"res\\bricks\\YellowBrick.png"
#define FIREBALL_PIC_PATH L"res\\ball\\FireBall32x32.png"

#define BONUS_BALL_PATH L"res\\bonus\\BonusBall.png"
#define BONUS_CUT_PATH L"res\\bonus\\BonusCut.png"
#define BONUS_EXPAND_PATH L"res\\bonus\\BonusExpand.png"
#define BONUS_FIREBALL_PATH L"res\\bonus\\BonusFireBall.png"
#define BONUS_EXP1_PATH L"res\\bonus\\BonusEXP1.png"
#define BONUS_EXP2_PATH L"res\\bonus\\BonusEXP2.png"
#define BONUS_EXP3_PATH L"res\\bonus\\BonusEXP3.png"
#define BONUS_EXP4_PATH L"res\\bonus\\BonusEXP4.png"
#define BONUS_EXP5_PATH L"res\\bonus\\BonusEXP5.png"

#define TEXT_TOP 64
#define TEXT_BOTTOM 128
#define LEVEL_LEFT 20
#define LEVEL_RIGHT 156
#define SCORE_LEFT 217
#define SCORE_RIGHT 863
#define LIVES_LEFT 923
#define LIVES_RIGHT 1059

#define BALL_SIZE 32

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
#define DEFAULT_ANGLE 315
#define DEFAULT_TIME 1

#define INTERSECTION_LEFT 1
#define INTERSECTION_LEFT_AND_UP 2
#define INTERSECTION_UP 3
#define INTERSECTION_RIGHT_AND_UP 4
#define INTERSECTION_RIGHT 5
#define INTERSECTION_RIGHT_AND_DOWN 6
#define INTERSECTION_DOWN 7
#define INTERSECTION_LEFT_AND_DOWN 8
#define INTERSECTION_INSIDE 9
#define INTERSECTION_NONE 0

#define FLOAT_MAX_VALUE 100000
#define FLOAT_MIN_VALUE -100000

#define LEFT_SIDE_LEFT FLOAT_MIN_VALUE
#define LEFT_SIDE_RIGHT -1
#define LEFT_SIDE_TOP 0
#define LEFT_SIDE_BOTTOM 931

#define RIGHT_SIDE_LEFT DEFAULT_GAME_ZONE_WIDTH
#define RIGHT_SIDE_RIGHT FLOAT_MAX_VALUE
#define RIGHT_SIDE_TOP 0
#define RIGHT_SIDE_BOTTOM 931

#define DOWN_SIDE_LEFT -1
#define DOWN_SIDE_RIGHT DEFAULT_GAME_ZONE_WIDTH
#define DOWN_SIDE_TOP 930 + BALL_SIZE
#define DOWN_SIDE_BOTTOM FLOAT_MAX_VALUE

#define UP_SIDE_LEFT -1
#define UP_SIDE_RIGHT DEFAULT_GAME_ZONE_WIDTH
#define UP_SIDE_TOP FLOAT_MIN_VALUE
#define UP_SIDE_BOTTOM 0

#define DEFAULT_PLATFORM_MOVE 70

#define NUM_OF_LEAD_OFFSET_X 20
#define NUM_OF_LEAD_WIDTH 63
#define LEAD_OFFSET_Y 265
#define LEAD_HEIGHT 54
#define NAME_OF_LEAD_OFFSET_X 118
#define NAME_OF_LEAD_WIDTH 477
#define SCORE_OF_LEAD_OFFSET_X 632
#define SCORE_OF_LEAD_WIDTH 428
#define LEAD_VERTICAL_INTERVAL 72

#define WM_NEED_A_DIALOG_BOX 1337

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

std::string ConvertIntToString(int value);

float ConvertDegToRad(float value);

long ConvertStringToLong(std::string str);


#endif //ARKANOID_COMPLEMENTARY_H
