#pragma once
#include "Vector2.h"
#include <vector>


#define	   BUFF_NUMBER		4

class Character;
class IMAGE;
class RenderUI;
class Controller;
class BuffBox;


class StatusBar
{
public:
	StatusBar(Controller* player,Vector2 position);
	~StatusBar();

	void on_update(float delta);

	void add_buff_info(BuffBox* buff);

	void remove_buff_info(BuffBox* buff);

private:
	Controller* owned_player = nullptr;
	int hp = 0;
	int mp = 0;
	Vector2 position = { 0,0 };		//显示的位置
	IMAGE* img_avater = nullptr;    //显示的图片

	int hp_bar_offset_x = 100;
	int hp_bar_offset_y = 16;
	int mp_bar_offset_x = 100;
	int mp_bar_offset_y = 63;


	int buff_offset_x = 95;
	int buff_offset_y = -60;
	int buff_offset_interval = 15;
	int buff_size = 60;

	int bar_shade_offset_x = 4;
	int bar_shade_offset_y = 4;

	RenderUI* avater = nullptr;
	RenderUI* hp_bar_shade = nullptr;
	RenderUI* hp_bar_bottom = nullptr;
	RenderUI* hp_bar = nullptr;

	RenderUI* mp_bar_shade = nullptr;
	RenderUI* mp_bar_bottom = nullptr;
	RenderUI* mp_bar = nullptr;


	RenderUI* buff_grids[BUFF_NUMBER] = {nullptr};

	const float width = 275;
	const float height = 26;

	
	BuffBox* BuffList[BUFF_NUMBER] = { nullptr };
	int current_buff = 0;
};

