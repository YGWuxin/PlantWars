#include "PlayerControllerManger.h"
#include "Controller.h"

using namespace std;


void PlayerControllerManger::create_player(const PlayerType& type)
{
	//如果已经创建则返回不用创建
	if (player_list[type])
		return;

	Controller* player = nullptr;
	player = new Controller(type);

	player_list[type] = player;
}


void PlayerControllerManger::on_input(const ExMessage& msg)
{
	for (auto it = player_list.begin(); it != player_list.end(); ++it) {
		Controller* player = it->second;  // 获取 Controller* 指针
		if (player)
			player->check_input(msg);
	}
}

