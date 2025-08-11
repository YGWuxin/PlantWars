#include "PeaBullet.h"
#include "RenderItem.h"
#include "RenderManager.h"
#include "CollisionManger.h"
#include "../Parameter/GlobeGameParameters.h"
#include "ResourcesManger.h"
#include "Character.h"
#include "../Res/atlas.h"
#include "AudioManger.h"

PeaBullet::PeaBullet()
{
	this->position = { -200,-200 };			//设置生成的位置

	set_collision_size({ 25,25 });			//设置碰撞箱大小					

	damage = 5;								//设置伤害值

	set_enable_gravity(false);				//禁用模拟物理

	img_pea = ResourcesManger::GetInstance().find_image("img_pea");				//获取默认图像

	init_render_item(img_pea, LAYER_ITEM_BULLET, CollisionLayer::Bullet);		//生成用于渲染的item和碰撞箱

	//添加碰撞
	collision_box->add_layer_dst(CollisionLayer::Player);

	//初始化破碎动画
	Atlas* tlas_pea_breakatlas_pea_break = ResourcesManger::GetInstance().find_atlas("atlas_pea_breakatlas_pea_break");
	animation_break.add_animation(tlas_pea_breakatlas_pea_break);
	animation_break.set_interval(100);
	animation_break.set_loop(false);
	animation_break.set_on_finished_callback([&]() {
		disable();
		});

	update_animation = false;						//静止当前动画更新

	set_current_animation(&animation_break);		//设置当前动画

	disable();										//禁用当前子弹
}


void PeaBullet::begin(Character* character)
{
	Bullet::begin(character);
	animation_break.reset();
	current_animation->reset();
	update_animation = false;
	render_item->setImage(img_pea);
	bool is_face_right = character->get_is_face_rigth();
	if (is_face_right)
	{
		position.x = character->get_current_posistion().x + character->get_collision_size().x * 0.6;
		position.y = character->get_current_posistion().y - character->get_collision_size().y * 0.88;
		velocity.x = speed;
	}
	else
	{
		position.x = character->get_current_posistion().x - character->get_collision_size().x * 0.6;
		position.y = character->get_current_posistion().y - character->get_collision_size().y * 0.88;
		velocity.x = -speed;
	}
}


void PeaBullet::play_sound()
{
	switch (rand() % 3)
	{
	case 0:
		AudioManger::GetInstance().PlaySoundAudio("res/sound/pea_break_1.mp3", false);
		break;
	case 1:
		AudioManger::GetInstance().PlaySoundAudio("res/sound/pea_break_2.mp3", false);
		break;
	case 2:
		AudioManger::GetInstance().PlaySoundAudio("res/sound/pea_break_3.mp3", false);
		break;
	default:
		break;
	}

}


void PeaBullet::on_update(float delta)
{
	if (!is_anble)
		return;

	Bullet::on_update(delta);

	if (!valid)
		update_animation = true;

	check_exceeds_screen();
}


