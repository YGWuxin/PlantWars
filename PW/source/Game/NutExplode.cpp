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
	this->position = { -300,-300 };			//�������ɵ�λ��

	set_collision_size({ 200,200 });			//������ײ���С

	damage = 30;							//�����˺�ֵ

	mp_value = 0;

	//is_enable_shake = true;
	//strenth = 5;
	//duration = 50;

	set_enable_gravity(false);				//����ģ������

	init_render_item(nullptr, LAYER_ITEM_BULLET, CollisionLayer::Bullet);		//����������Ⱦ��item����ײ��

	//�����ײ
	collision_box->add_layer_dst(CollisionLayer::Player);


	//��ʼ����ը����
	Atlas* atlas_bubble_explode = ResourcesManger::GetInstance().find_atlas("atlas_nut_explode");
	animation_explode.add_animation(atlas_bubble_explode);
	animation_explode.set_interval(100);
	animation_explode.set_loop(false);
	animation_explode.set_on_finished_callback([&]() {
		disable();
		});


	set_current_animation(&animation_explode);							//���õ�ǰ����

	disable();														//���õ�ǰ�ӵ�
}


void NutExplode::begin(Character* character)
{
	Bullet::begin(character);
	set_current_animation(&animation_explode);							//���õ�ǰ����
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