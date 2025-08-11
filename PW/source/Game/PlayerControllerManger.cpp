#include "PlayerControllerManger.h"
#include "Controller.h"

using namespace std;


void PlayerControllerManger::create_player(const PlayerType& type)
{
	//����Ѿ������򷵻ز��ô���
	if (player_list[type])
		return;

	Controller* player = nullptr;
	player = new Controller(type);

	player_list[type] = player;
}


void PlayerControllerManger::on_input(const ExMessage& msg)
{
	for (auto it = player_list.begin(); it != player_list.end(); ++it) {
		Controller* player = it->second;  // ��ȡ Controller* ָ��
		if (player)
			player->check_input(msg);
	}
}

