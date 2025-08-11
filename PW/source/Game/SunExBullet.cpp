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
	this->position = { -400,-400 };			//�������ɵ�λ��

	set_collision_size({ 200,200 });			//������ײ���С

	damage = 20;							//�����˺�ֵ

	is_enable_shake = true;
	strenth = 10;
	duration = 500;

	set_enable_gravity(false);				//����ģ������

	init_render_item(nullptr, LAYER_ITEM_BULLET, CollisionLayer::Bullet);		//����������Ⱦ��item����ײ��

	//�����ײ
	collision_box->add_layer_dst(CollisionLayer::Player);

	//��ʼ����������
	Atlas* atlas_sun_ex = ResourcesManger::GetInstance().find_atlas("atlas_sun_ex");
	animation_idle.add_animation(atlas_sun_ex);
	animation_idle.set_interval(100);
	animation_idle.set_loop(true);

	//��ʼ����ը����
	Atlas* atlas_sun_ex_explode = ResourcesManger::GetInstance().find_atlas("atlas_sun_ex_explode");
	animation_explode.add_animation(atlas_sun_ex_explode);
	animation_explode.set_interval(100);
	animation_explode.set_loop(false);
	animation_explode.set_on_finished_callback([&]() {
		position = { -300,-300 };
		disable();
		
		});

	set_current_animation(&animation_idle);							//���õ�ǰ����

	disable();														//���õ�ǰ�ӵ�

}


void SunExBullet::begin(Character* character)
{
	Bullet::begin(character);
	//this->position = { 200,-144 };			//�������ɵ�λ��
	set_current_animation(&animation_idle);		//���õ�ǰ����
	set_velocity_y(0.2f);
	animation_idle.reset();
	animation_explode.reset();
}


void SunExBullet::check_exceeds_screen()
{
	//����ӵ����Ѿ�����Ļ����
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
		set_current_animation(&animation_explode);		//���õ�ǰ����
	}

	check_exceeds_screen();
}