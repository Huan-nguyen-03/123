#pragma once

#include <iostream>

const std::string WINDOW_TITLE = "Gunny";
const int SCREEN_WIDTH = 1200;// 800;
const int SCREEN_HEIGHT = 600; //600;
// Các hàm chung về khởi tạo và huỷ SDL

const int FIGURE_WIDTH = 140;
const int FIGURE_HEIGHT = 118;

const int GRAVITY = 10;
enum WalkTypes
    {
        WALK_RIGHT, 
        WALK_LEFT
    };

enum status
{
    GO_RIGHT, 
    GO_LEFT
};