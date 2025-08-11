#pragma once

#include "Scene.h"
#include "Camera.h"


class MenuScene :	public Scene
{
public:
	MenuScene() = default;
	~MenuScene() = default;

	void on_enter() override;

	void on_update(int delta) override;

	void on_input(const ExMessage& msg) override;

	void on_exit() override;

private:
	IMAGE* img_backgroud = nullptr;
	Camera* main_camera = nullptr;
	const char* backgroud_music_alias;

};

