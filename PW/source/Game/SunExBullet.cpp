#include "SunExBullet.h"
#include "RenderItem.h"
#include "RenderManager.h"
#include "CollisionManger.h"
#include "../Parameter/GlobeGameParameters.h"
#include "ResourcesManger.h"
#include "Character.h"
#include "../Res/atlas.h"
#include "AudioManger.h"
#include "SceneManger.h"



SunExBullet::SunExBullet()
{
	this->position = { -400,-400 };			//设置生成的位置

	set_collision_size({ 200,200 });			//设置碰撞箱大小

	damage = 20;							//设置伤害值

	is_enable_shake = true;
	strenth = 10;
	duration = 500;

	set_enable_gravity(false);				//禁用模拟物理

	init_render_item(nullptr, LAYER_ITEM_BULLET, CollisionLayer::Bullet);		//生成用于渲染的item和碰撞箱

	//添加碰撞
	collision_box->add_layer_dst(CollisionLayer::Player);

	//初始化待机动画
	Atlas* atlas_sun_ex = ResourcesManger::GetInstance().find_atlas("atlas_sun_ex");
	animation_idle.add_animation(atlas_sun_ex);
	animation_idle.set_interval(100);
	animation_idle.set_loop(true);

	//初始化爆炸动画
	Atlas* atlas_sun_ex_explode = ResourcesManger::GetInstance().find_atlas("atlas_sun_ex_explode");
	animation_explode.add_animation(atlas_sun_ex_explode);
	animation_explode.set_interval(100);
	animation_explode.set_loop(false);
	animation_explode.set_on_finished_callback([&]() {
		position = { -300,-300 };
		disable();
		
		});

	set_current_animation(&animation_idle);							//设置当前动画

	disable();														//禁用当前子弹

}


void SunExBullet::begin(Character* character)
{
	Bullet::begin(character);
	//this->position = { 200,-144 };			//设置生成的位置
	set_current_animation(&animation_idle);		//设置当前动画
	set_velocity_y(0.2f);
	animation_idle.reset();
	animation_explode.reset();
}


void SunExBullet::check_exceeds_screen()
{
	//检查子弹是已经到屏幕外面
	if (position.x + size.x / 2 <= 0 || position.x - size.x / 2 >= getwidth()
		|| position.y - size.y / 2 >= getheight())
	{
		disable();
	}
}


void SunExBullet::play_sound()
{
	AudioManger::GetInstance().PlaySoundAudio("res/sound/sun_explode_ex.mp3", 800);
}


void SunExBullet::on_update(float delta)
{
	if (!is_anble)
		return;

	Bullet::on_update(delta);

	if (!valid)
	{
		velocity = { 0,0 };
		set_current_animation(&animation_explode);		//设置当前动画
	}

	check_exceeds_screen();
}