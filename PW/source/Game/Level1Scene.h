#pragma once
#include "Scene.h"
#include "../Utils/Timer.h"
#include <vector>

class Camera;
class Character;
class Controller;
class PlatformSmall;
class PlatformLarge;
class StatusBar;
class RenderUI;
class BuffBox;

class Level1Scene :	public Scene
{
public:
	Level1Scene() = default;
	~Level1Scene() = default;

	void on_enter() override;

	void on_update(int delta) override;

	void on_input(const ExMessage& msg) override;

	void on_exit() override;

private:
	const char* backgroud_music_alias = nullptr;
	const char* game_over_music_alias = nullptr;

	Camera* main_camera = nullptr;
	Character* character1 = nullptr;
	Character* character2 = nullptr;
	Controller* play1 = nullptr;
	Controller* play2 = nullptr;
	PlatformSmall* platform_small_top = nullptr;
	PlatformSmall* platform_small_left = nullptr;
	PlatformSmall* platform_small_right = nullptr;
	PlatformLarge* platform_large = nullptr;

	StatusBar* player_bar_1 = nullptr;
	StatusBar* player_bar_2 = nullptr;

	RenderUI* UI_1P_cursor = nullptr;
	RenderUI* UI_2P_cursor = nullptr;

	Timer timer_cursor_disappear;
	bool is_cursor_disappear = false;

	bool is_game_over = false;

	RenderUI* UI_winner_bar = nullptr;
	RenderUI* UI_1P_winner = nullptr;
	RenderUI* UI_2P_winner = nullptr;
	RenderUI* UI_winner = nullptr;
	float speed_winner_bar = 2.0f;
	float speed_winner_text = 1.0f;

	bool is_winner_silde_out_start= false;

	Timer timer_winner_bar_slide_in;
	Timer timer_game_over;

	int generate_buff_box_time = 5000;
	Timer timer_generate_buff_box;

};

