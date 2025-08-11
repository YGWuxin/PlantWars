#include "SunBullet.h"
#include "RenderItem.h"
#include "RenderManager.h"
#include "CollisionManger.h"
#include "../Parameter/GlobeGameParameters.h"
#include "ResourcesManger.h"
#include "Character.h"
#include "../Res/atlas.h"
#include "AudioManger.h"
#include "SceneManger.h"

SunBullet::SunBullet()
{
	this->position = { -200,-200 };			//设置生成的位置

	set_collision_size({64,64});			//设置碰撞箱大小

	damage = 10;							//设置伤害值

	mp_value = 25;

	is_enable_shake = true;
	strenth = 5;
	duration = 50;

	airDrag = 1.6e-4f;						//设置空气阻力系数

	set_enable_gravity(false);				//禁用模拟物理

	init_render_item(nullptr, LAYER_ITEM_BULLET, CollisionLayer::Bullet);		//生成用于渲染的item和碰撞箱

	//添加碰撞
	collision_box->add_layer_dst(CollisionLayer::Player);

	//初始化待机动画
	Atlas* atlas_sun = ResourcesManger::GetInstance().find_atlas("atlas_sun");
	animation_idle.add_animation(atlas_sun);
	animation_idle.set_interval(100);
	animation_idle.set_loop(true);


	//初始化爆炸动画
	Atlas* atlas_sun_explode = ResourcesManger::GetInstance().find_atlas("atlas_sun_explode");
	animation_explode.add_animation(atlas_sun_explode);
	animation_explode.set_interval(100);
	animation_explode.set_loop(false);
	animation_explode.set_on_finished_callback([&]() {
		disable();
		});


	set_current_animation(&animation_idle);							//设置当前动画

	disable();														//禁用当前子弹
}



void SunBullet::begin(Character* character)
{
	Bullet::begin(character);
	set_current_animation(&animation_idle);		//设置当前动画
	set_enable_gravity(true);

	animation_idle.reset();
	animation_explode.reset();

	bool is_face_right = character->get_is_face_rigth();
	if (is_face_right)
	{
		position.x = character->get_current_posistion().x;
		position.y = character->get_current_posistion().y - character->get_collision_size().y * 0.9;
		velocity = { 0.4f , -0.4f };
	}
	else
	{
		position.x = character->get_current_posistion().x;
		position.y = character->get_current_posistion().y - character->get_collision_size().y * 0.9;
		velocity = { -0.4f ,- 0.4f };
	}
}


void SunBullet::check_exceeds_screen()
{
	//检查子弹是已经到屏幕外面
	if (position.x + size.x / 2 <= 0 || position.x - size.x / 2 >= getwidth()
		|| position.y - size.y / 2 >= getheight())
	{
		disable();
	}
}

void SunBullet::play_sound()
{
	AudioManger::GetInstance().PlaySoundAudio("res/sound/sun_explode.mp3", 200);
}

void SunBullet::on_update(float delta)
{
	if (!is_anble)
	{
		set_enable_gravity(false);
		return;
	}

	Bullet::on_update(delta);

	if (!valid)
	{
		set_enable_gravity(false);
		velocity = { 0,0 };
		set_current_animation(&animation_explode);		//设置当前动画
	}

	check_exceeds_screen();
}

