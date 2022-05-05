#include "Sprite.h"

Game::Sprite::Sprite(int pos_X, int pos_Y, Texture2D Texture)
{
    pos_x = pos_X;
    pos_y = pos_Y;
    texture_ = Texture;
}

Game::Sprite::Sprite(int pos_X, int pos_Y, const std::string& filename)
{
    pos_x = pos_X;
    pos_y = pos_Y;
    texture_ = LoadTexture(filename.c_str());
}

Game::Sprite::Sprite(int pos_X, int pos_Y, const char* filename)
{
    pos_x = pos_X;
    pos_y = pos_Y;
    texture_ = LoadTexture(filename);
}

Game::Sprite::~Sprite()
{
    TraceLog(LOG_INFO, "Willst du meine Sarah Connor sein?");
    UnloadTexture(texture_);
}

