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
	this->position = { -200,-200 };			//�������ɵ�λ��

	set_collision_size({64,64});			//������ײ���С

	damage = 10;							//�����˺�ֵ

	mp_value = 25;

	is_enable_shake = true;
	strenth = 5;
	duration = 50;

	airDrag = 1.6e-4f;						//���ÿ�������ϵ��

	set_enable_gravity(false);				//����ģ������

	init_render_item(nullptr, LAYER_ITEM_BULLET, CollisionLayer::Bullet);		//����������Ⱦ��item����ײ��

	//�����ײ
	collision_box->add_layer_dst(CollisionLayer::Player);

	//��ʼ����������
	Atlas* atlas_sun = ResourcesManger::GetInstance().find_atlas("atlas_sun");
	animation_idle.add_animation(atlas_sun);
	animation_idle.set_interval(100);
	animation_idle.set_loop(true);


	//��ʼ����ը����
	Atlas* atlas_sun_explode = ResourcesManger::GetInstance().find_atlas("atlas_sun_explode");
	animation_explode.add_animation(atlas_sun_explode);
	animation_explode.set_interval(100);
	animation_explode.set_loop(false);
	animation_explode.set_on_finished_callback([&]() {
		disable();
		});


	set_current_animation(&animation_idle);							//���õ�ǰ����

	disable();														//���õ�ǰ�ӵ�
}



void SunBullet::begin(Character* character)
{
	Bullet::begin(character);
	set_current_animation(&animation_idle);		//���õ�ǰ����
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
	//����ӵ����Ѿ�����Ļ����
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
		set_current_animation(&animation_explode);		//���õ�ǰ����
	}

	check_exceeds_screen();
}

