#pragma once
#include "raylib.h"
#include <string>
#include "Nemo.h"


namespace Game
{
	class Sprite
	{
	public:
		int pos_x;
		int pos_y;
		Texture2D texture_;
		Nemo nemo_;
		

		Sprite() = delete;

		Sprite(int pos_x, int pos_y, Texture2D texture);

		Sprite(int pos_x, int pos_y, const std::string& filename);

		Sprite(int pos_x, int pos_y, const char* filename);

		~Sprite();
	};
}
