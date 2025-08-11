#include "NutExplode.h"
#include "RenderItem.h"
#include "RenderManager.h"
#include "CollisionManger.h"
#include "../Parameter/GlobeGameParameters.h"
#include "ResourcesManger.h"
#include "Character.h"
#include "../Res/atlas.h"
#include "AudioManger.h"
#include "SceneManger.h"


NutExplode::NutExplode()
{
	this->position = { -300,-300 };			//设置生成的位置

	set_collision_size({ 200,200 });			//设置碰撞箱大小

	damage = 30;							//设置伤害值

	mp_value = 0;

	//is_enable_shake = true;
	//strenth = 5;
	//duration = 50;

	set_enable_gravity(false);				//禁用模拟物理

	init_render_item(nullptr, LAYER_ITEM_BULLET, CollisionLayer::Bullet);		//生成用于渲染的item和碰撞箱

	//添加碰撞
	collision_box->add_layer_dst(CollisionLayer::Player);


	//初始化爆炸动画
	Atlas* atlas_bubble_explode = ResourcesManger::GetInstance().find_atlas("atlas_nut_explode");
	animation_explode.add_animation(atlas_bubble_explode);
	animation_explode.set_interval(100);
	animation_explode.set_loop(false);
	animation_explode.set_on_finished_callback([&]() {
		disable();
		});


	set_current_animation(&animation_explode);							//设置当前动画

	disable();														//禁用当前子弹
}


void NutExplode::begin(Character* character)
{
	Bullet::begin(character);
	set_current_animation(&animation_explode);							//设置当前动画
	animation_explode.reset();
	mp_value = 0;
	position.x = character->get_current_posistion().x;
	position.y = character->get_current_posistion().y - character->get_collision_size().y / 2;


}


void NutExplode::play_sound()
{

}


void NutExplode::on_update(float delta)
{
	if (!is_anble)
		return;

	Bullet::on_update(delta);

	if (!valid)
		velocity = { 0,0 };
	
}