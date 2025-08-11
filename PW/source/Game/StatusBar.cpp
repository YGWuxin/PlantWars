#include "StatusBar.h"
#include "Character.h"
#include "Controller.h"
#include "CharacterManger.h"
#include "ResourcesManger.h"
#include "RenderManager.h"
#include "../Parameter/GlobeGameParameters.h"
#include "BuffBox.h"

StatusBar::StatusBar(Controller* player, Vector2 position)
{
	if (!player)
		return;
	owned_player = player;
	owned_player->set_status_bar(this);
	this->position = position;
	switch (owned_player->get_character_type())
	{
		case CharacterManger::CharacterType::PeashooterCharacter:
		{
			img_avater = ResourcesManger::GetInstance().find_image("img_avatar_peashooter");
			break;
		}
		case CharacterManger::CharacterType::SunflowerCharacter:
		{
			img_avater = ResourcesManger::GetInstance().find_image("img_avatar_sunflower");
			break;
		}
		case CharacterManger::CharacterType::GloomshroomCharacter:
		{
			img_avater = ResourcesManger::GetInstance().find_image("img_avatar_gloomshroom");
			break;
		}
		case CharacterManger::CharacterType::NutCharacter:
		{
			img_avater = ResourcesManger::GetInstance().find_image("img_avatar_nut");
			break;
		}
		default:
			break;
	}

	RenderManager& render_manger = RenderManager::getInstance();

	avater = render_manger.createRenderItemUIIamge(img_avater, position,14,false);

	//ÉúÃüÌõ
	hp_bar_bottom = render_manger.createRenderItemUIBar({ position.x + hp_bar_offset_x ,position.y + hp_bar_offset_y },
		{ width,height }, {67,47,47},8,8,13,false);
	hp_bar_shade = render_manger.createRenderItemUIBar({ position.x + hp_bar_offset_x + bar_shade_offset_x,position.y + hp_bar_offset_y + bar_shade_offset_y },
		{ width,height }, { 5,5,5 }, 8, 8, 12, false);
	hp_bar = render_manger.createRenderItemUIBar({ position.x + hp_bar_offset_x ,position.y + hp_bar_offset_y },
		{ width,height }, { 197,61,67 }, 8, 8, 14, false);

	mp_bar_bottom = render_manger.createRenderItemUIBar({ position.x + mp_bar_offset_x ,position.y + mp_bar_offset_y },
		{ width,height }, { 67,47,47 }, 8, 8, 13, false);
	mp_bar_shade = render_manger.createRenderItemUIBar({ position.x + mp_bar_offset_x + bar_shade_offset_x,position.y + mp_bar_offset_y + bar_shade_offset_y },
		{ width,height }, { 5,5,5 }, 8, 8, 12, false);
	mp_bar = render_manger.createRenderItemUIBar({ position.x + mp_bar_offset_x ,position.y + mp_bar_offset_y },
		{ width,height }, { 83,131,195 }, 8, 8, 14, false);


	for (int i = 0; i < BUFF_NUMBER; i++)
	{
		buff_grids[i] = render_manger.createRenderItemUIIamge(nullptr, { position.x + buff_offset_x + buff_size * i + buff_offset_interval * i, position.y + buff_offset_y }, 14, false);
	}

}


StatusBar::~StatusBar()
{
	RenderManager& render_manger = RenderManager::getInstance();
	if (avater)
	{
		avater->setCanBeDestroyed(true);
		render_manger.destroyRenderItemUI(avater);
	}

	if (hp_bar_bottom)
	{
		hp_bar_bottom->setCanBeDestroyed(true);
		render_manger.destroyRenderItemUI(hp_bar_bottom);
	}
	if (hp_bar_shade)
	{
		hp_bar_shade->setCanBeDestroyed(true);
		render_manger.destroyRenderItemUI(hp_bar_shade);
	}
	if (hp_bar)
	{
		hp_bar->setCanBeDestroyed(true);
		render_manger.destroyRenderItemUI(hp_bar);
	}


	if (mp_bar_bottom)
	{
		mp_bar_bottom->setCanBeDestroyed(true);
		render_manger.destroyRenderItemUI(mp_bar_bottom);
	}
	if (mp_bar_shade)
	{
		mp_bar_shade->setCanBeDestroyed(true);
		render_manger.destroyRenderItemUI(mp_bar_shade);
	}
	if (mp_bar)
	{
		mp_bar->setCanBeDestroyed(true);
		render_manger.destroyRenderItemUI(mp_bar);
	}

	for (int i = 0; i < BUFF_NUMBER; i++)
	{
		if (buff_grids[i])
		{
			buff_grids[i]->setCanBeDestroyed(true);
			render_manger.destroyRenderItemUI(buff_grids[i]);
		 }
	}

	if (owned_player)
	{
		owned_player->set_status_bar(nullptr);
	}

}


void StatusBar::on_update(float delta)
{
	if (!owned_player)
		return;
	Character* character = owned_player->get_owned_character();
	if (!character)
		return;

	hp = character->get_hp();
	mp = character->get_mp();

	float hp_bar_width = width * max(0, hp) / 100.0f;
	float mp_bar_width = width * min(100, mp) / 100.0f;

	if (hp_bar)
	{
		hp_bar->setBarWidth(hp_bar_width);
	}

	if (mp_bar)
	{
		mp_bar->setBarWidth(mp_bar_width);
	}


	for (int i = 0; i < BUFF_NUMBER; i++)
	{
		if (BuffList[i])
		{
			buff_grids[i]->setImage(BuffList[i]->get_buff_icon());
		}
		else
		{
			buff_grids[i]->setImage(nullptr);
		}
	}

}


void StatusBar::add_buff_info(BuffBox* buff)
{
	if (!buff || current_buff == BUFF_NUMBER)
		return;
	for (int i = 0; i < BUFF_NUMBER; i++)
	{
		if (BuffList[i])
		{
			if (BuffList[i]->getBuffType() == buff->getBuffType())
			{
				if (BuffList[i]->getBuffType() == BuffBox::BuffType::Hurry)
					BuffList[i]->event_buff_end();
				BuffList[i]->set_is_clear();
				BuffList[i] = buff;
				break;
			}
		}
		else
		{
			BuffList[i] = buff;
			current_buff++;
			break;
		}
	}

}

void StatusBar::remove_buff_info(BuffBox* buff)
{
	if (!buff)
		return;
	int index = -1;
	
	for (int i = 0; i < BUFF_NUMBER; i++)
	{
		if (BuffList[i] == buff)
		{
			BuffList[i] = nullptr;
			index = i;
			break;
		}
	}
	if (index == -1)
		return;
	for (int i = index + 1; i < BUFF_NUMBER; i++)
	{
		BuffList[i - 1] = BuffList[i];
		BuffList[i] = nullptr;
	}
	current_buff--;
}