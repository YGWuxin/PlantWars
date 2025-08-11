#include "Character.h"
#include <cstdio>
#include "Controller.h"
#include "RenderItem.h"
#include "RenderManager.h"
#include "CollisionManger.h"
#include "../Utils/helper.h"
#include "ParticleManger.h"
#include "Vector2.h"


Character::Character(Vector2 position, bool is_render_on_ui)
{
	this->position = position;
	mode = AnchorMode::BottomCrented;
	set_collision_size({ 60 , 80 });
	//collision_offset_x = 0;
	//collision_offset_y = -8;

	

	if (is_render_on_ui == false)
	{
		init_render_item(nullptr, LAYER_ITEM_PLAYER, CollisionLayer::Player);

		collision_box->add_layer_dst(CollisionLayer::PlatformSmall);
		collision_box->add_layer_dst(CollisionLayer::PlatformLarge);
		//collision_box->add_layer_dst(CollisionLayer::Player);

		state_machine = new StateMachine();
		state_machine->set_own_character(this);
	}
	else
	{
		init_render_on_ui(nullptr, LAYER_ITEM_PLAYER, CollisionLayer::Player);
	}

	//添加输入事件
	addInputEvent("move_right", bind(&Character::Move_right_down, this), KeyState::KEY_DOWN);
	addInputEvent("move_right", bind(&Character::Move_right_up, this), KeyState::KEY_UP);

	addInputEvent("move_left", bind(&Character::Move_left_down, this), KeyState::KEY_DOWN);
	addInputEvent("move_left", bind(&Character::Move_left_up, this), KeyState::KEY_UP);

	addInputEvent("jump", bind(&Character::On_Jump, this), KeyState::KEY_DOWN);
	addInputEvent("attack", bind(&Character::On_Attack, this), KeyState::KEY_DOWN);
	addInputEvent("attack_ex", bind(&Character::On_Attack_Ex, this), KeyState::KEY_DOWN);

	//初始化普通攻击定时器
	timer_attack_cd.set_wait_time(attck_cd);
	timer_attack_cd.set_one_shot(true);
	timer_attack_cd.set_callback([&]() {
		can_attack = true;
		});

	//无敌状态定时器
	timer_invulnerable.set_wait_time(500);
	timer_invulnerable.set_one_shot(true);
	timer_invulnerable.set_callback([&]() {
		is_invulnerable = false;
		is_enable_sketch = false;
		});

	//剪影闪烁定时器
	timer_invulnerable_blink.set_wait_time(50);
	timer_invulnerable_blink.set_callback([&]() {
		is_showing_sketch_frame = !is_showing_sketch_frame;
		});


	timer_run_effect_generation.set_wait_time(65);
	timer_run_effect_generation.pause();
	timer_run_effect_generation.set_callback([&]() {
		Vector2 run_effect_position = {this->position.x - current_animation->get_current_frame_image()->getwidth() / 2 - 15 ,
									   this->position.y - current_animation->get_current_frame_image()->getheight() - 38 };
		ParticleManger::getInstance().createParticleInstance<RunEffect>(run_effect_position, 45);
		});

	timer_die_effect_generation.set_wait_time(35);
	timer_die_effect_generation.set_callback([&]() {
			Vector2 run_effect_position = { this->position.x - current_animation->get_current_frame_image()->getwidth() / 2 - 15 ,
									   this->position.y - current_animation->get_current_frame_image()->getheight() - 38 };
			ParticleManger::getInstance().createParticleInstance<RunEffect>(run_effect_position, 200);
		});


	on_init();
}

Character::~Character()
{
	if (state_machine)
	{
		delete state_machine;
	}
	if (controller)
	{
		controller->UnPossess(false);
	}
}


void Character::on_update(float delta)
{
	ItemObject::on_update(delta);

	if (state_machine)
		state_machine->on_update(delta);

	timer_invulnerable.on_update(delta);

	timer_attack_cd.on_update(delta);

	if (hp > 0)
		timer_run_effect_generation.on_update(delta);
	else
		timer_die_effect_generation.on_update(delta);

	if (is_invulnerable && is_enable_sketch)
		timer_invulnerable_blink.on_update(delta);
	else
		is_showing_sketch_frame = false;


	//若当前是白色剪影帧则执行
	if (is_showing_sketch_frame)
	{
		helper::sketch_image(current_animation->get_current_frame_image(), &sketch_image, {255,0,0});
		if (render_item)
			render_item->setImage(&sketch_image);
	}

	int direction = is_right_key_down - is_left_key_down;
	if (direction != 0)
		is_face_rigth = direction > 0;

	if (current_movement_state != MovementState::Attack_ex && !is_die)
	{
		if (direction != 0)
		{
			velocity.x = direction * run_velocity;				//水平方向上的速度
			current_movement_state = MovementState::Run;
			timer_run_effect_generation.resume();
		}
		else
		{
			velocity.x = 0;
			current_movement_state = MovementState::Idle;
			timer_run_effect_generation.restart();
			timer_run_effect_generation.pause();
		}
	}
}


void Character::set_to_invulnerable(bool enable_sketch,int invulnerable_time)
{
	timer_invulnerable.restart();
	timer_invulnerable.set_wait_time(invulnerable_time);
	is_invulnerable = true;

	if (enable_sketch)
	{
		timer_invulnerable_blink.restart();
		is_enable_sketch = true;
	}
}


void Character::set_timer_attack_cd(int cd_time)
{
	attck_cd = cd_time;
	timer_attack_cd.set_wait_time(cd_time);
	timer_attack_cd.restart();
}

void Character::set_owned_controller(Controller* controller)
{
	if (!controller)
		return;
	this->controller = controller;
}

void Character::handleCollision(const HitInfo& hit_info)
{
	if (hit_info.layer == CollisionLayer::PlatformSmall || hit_info.layer == CollisionLayer::PlatformLarge)
	{
		if (velocity.y > 0)
		{
			printf("velocity.y:%0.2f\r\n", velocity.y);

			float delta_pos_y = velocity.y * hit_info.delta;
			float last_tick_pos_y = position.y - delta_pos_y;
			if (last_tick_pos_y <= (hit_info.position.y - hit_info.size.y / 2 - collision_offset_y))
			{
				position.y = (hit_info.position.y - hit_info.size.y / 2 - collision_offset_y);
				velocity.y = 0;
				if (!on_ground)
				{
					on_land();
					Vector2 land_effect_position = { position.x - current_animation->get_current_frame_image()->getwidth() / 2 - 15 ,
													position.y - current_animation->get_current_frame_image()->getheight() - 38 };
					ParticleManger::getInstance().createParticleInstance<LandEffect>(land_effect_position, 40);
				}
				on_ground = true;
				return;
			}
		}
		
	}
}


void Character::on_die()
{

	if (!get_owned_controller() || !collision_box || is_die)
		return;
	is_die = true;
	get_owned_controller()->disable_input();
	current_movement_state = MovementState::Die;
	collision_box->remove_layer_all();
	set_velocity(hit_direction_right ? -0.4f : 0.4f,-1.0f);
}


//添加输入事件
void Character::addInputEvent(string vk_code, function<void()> event, KeyState key_state)
{
	switch (key_state)
	{
	case Character::KeyState::KEY_UP:
		input_event_map_key_up[vk_code] = event;
		break;
	case Character::KeyState::KEY_DOWN:
		input_event_map_key_down[vk_code] = event;
		break;
	default:
		break;
	}
}

//执行输入事件
void Character::executeInputEvent(string vk_code, KeyState key_state)
{
	if (key_state == KeyState::KEY_UP)
	{
		auto it_up = input_event_map_key_up.find(vk_code);
		if (it_up != input_event_map_key_up.end()) {
			it_up->second();
		}
	}
	else if (key_state == KeyState::KEY_DOWN)
	{
		auto it_down = input_event_map_key_down.find(vk_code);
		if (it_down != input_event_map_key_down.end()) {
			it_down->second();
		}
	}
}



/* 向右移动 */
void Character::Move_right_down()
{
	is_right_key_down = true;
}

void Character::Move_right_up()
{
	is_right_key_down = false;
}


/* 向左移动 */
void Character::Move_left_down()
{
	is_left_key_down = true;
}

void Character::Move_left_up()
{
	is_left_key_down = false;
}

void Character::On_Jump()
{
	if (velocity.y != 0 || !can_jump)
		return;
	velocity.y += jump_velocity;
	on_jump = true;

	Vector2 jump_effect_position = { position.x - current_animation->get_current_frame_image()->getwidth() / 2 - 15 ,
		position.y - current_animation->get_current_frame_image()->getheight() - 38};

	ParticleManger::getInstance().createParticleInstance<JumpEffect>(jump_effect_position,40);


}












