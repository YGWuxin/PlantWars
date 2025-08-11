#include "BuffBox.h"
#include "RenderItem.h"
#include "RenderManager.h"
#include "CollisionManger.h"
#include "../Parameter/GlobeGameParameters.h"
#include "ResourcesManger.h"
#include "../Res/atlas.h"
#include "Character.h"
#include "Controller.h"

BuffBox::BuffBox()
{
	int x = rand() % 920 + 180;
	this->position = { (float)x,-80 };
	size = { 65,65 };
	set_enable_gravity(false);

	type = BuffType(rand() % 4);
	int rand_color = rand() % 3;

	Atlas* atlas_buff_box_color = nullptr;

	switch (rand_color)
	{
	case 0:
		//初始化动画
		atlas_buff_box_color = ResourcesManger::GetInstance().find_atlas("atlas_buff_box_blue");
		break;
	case 1:
		//初始化动画
		atlas_buff_box_color = ResourcesManger::GetInstance().find_atlas("atlas_buff_box_pink");
		break;
	case 2:
		//初始化动画
		atlas_buff_box_color = ResourcesManger::GetInstance().find_atlas("atlas_buff_box_yellow");
		break;
	default:
		break;
	}

	switch (type)
	{
	case BuffBox::BuffType::Hurry:
		printf("New Hurry\r\n");
		buff_icon = ResourcesManger::GetInstance().find_image("img_buff_icon_hurry");
		buff_time = 6000;
		break;
	case BuffBox::BuffType::Invisible:
		printf("New Invisible\r\n");
		buff_icon = ResourcesManger::GetInstance().find_image("img_buff_icon_invisible");
		buff_time = 5000;
		break;
	case BuffBox::BuffType::Recover:
		printf("New Recover\r\n");
		buff_icon = ResourcesManger::GetInstance().find_image("img_buff_icon_recover");
		buff_time = 2000;
		break;
	case BuffBox::BuffType::Silence:
		printf("New Recover\r\n");
		buff_icon = ResourcesManger::GetInstance().find_image("img_buff_icon_silence");
		buff_time = 4000;
		break;
	default:
		break;
	}

	animation_idle.add_animation(atlas_buff_box_color);
	animation_idle.reset();
	animation_idle.set_interval(100);
	animation_idle.set_loop(true);

	set_current_animation(&animation_idle);							//设置当前动画

	init_render_item(animation_idle.get_current_frame_image(), LAYER_ITEM_BUFFBOX, CollisionLayer::BuffBox);

	//添加碰撞
	collision_box->add_layer_dst(CollisionLayer::Player);

	set_velocity_y(0.08f);

	timer_buff.set_wait_time(buff_time);
	timer_buff.restart();
	timer_buff.set_one_shot(true);
	timer_buff.pause();
	timer_buff.set_callback([&]() {
		this->event_buff_end();
		this->set_is_clear();
		this->hited_character->get_owned_controller()->get_status_bar()->remove_buff_info(this);
		});

	timer_recover_hp.set_wait_time(65);
	timer_recover_hp.restart();
	timer_recover_hp.pause();
	timer_recover_hp.set_callback([&]() {
		this->hited_character->add_hp(1);
		});

}



void BuffBox::check_exceeds_screen()
{
	//检查是否已经到屏幕下 面
	if (position.y - size.y / 2 >= getheight())
	{
		this->set_is_clear();
	}
}

void BuffBox::on_update(float delta)
{
	ItemObject::on_update(delta);

	timer_buff.on_update(delta);

	timer_recover_hp.on_update(delta);

	check_exceeds_screen();
}

void BuffBox::handleCollision(const HitInfo& hit_info)
{
	set_visible(false);
	collision_box->set_enabled(false);

	hited_character = dynamic_cast<Character*>(hit_info.item);

	hited_character->get_owned_controller()->get_status_bar()->add_buff_info(this);

	timer_buff.resume();

	set_velocity_y(0);

	event_buff_begin();
}


void BuffBox::event_buff_begin()
{
	switch (type)
	{
	case BuffBox::BuffType::Hurry:
		hited_character->set_run_velocity(hited_character->get_run_velocity() + 0.21f);
		break;
	case BuffBox::BuffType::Invisible:
		hited_character->set_visible(false);
		//hited_character->set_to_invulnerable_no_timer(true);
		break;
	case BuffBox::BuffType::Recover:
		timer_recover_hp.resume();
		break;
	case BuffBox::BuffType::Silence:
		hited_character->set_attack(false);
		break;
	default:
		break;
	}
}


void BuffBox::event_buff_end()
{
	switch (type)
	{
	case BuffBox::BuffType::Hurry:
		hited_character->set_run_velocity(hited_character->get_run_velocity() - 0.21f);
		break;
	case BuffBox::BuffType::Invisible:
		hited_character->set_visible(true);
		//hited_character->set_to_invulnerable_no_timer(false);
		break;
	case BuffBox::BuffType::Recover:
		timer_recover_hp.pause();
		break;
	case BuffBox::BuffType::Silence:
		hited_character->set_attack(true);
		break;
	default:
		break;
	}
}
