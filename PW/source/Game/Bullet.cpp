#include "Bullet.h"
#include "RenderItem.h"
#include "Character.h"
#include "SceneManger.h"

void Bullet::on_update(float delta)
{
	ItemObject::on_update(delta);
}


void Bullet::check_exceeds_screen()
{
	//检查子弹是已经到屏幕外面
	if (position.x + size.x / 2 <= 0 || position.x - size.x / 2 >= getwidth()
		|| position.y + size.y / 2 <= 0 || position.y - size.y / 2 >= getheight())
	{
		disable();
	}
}


void Bullet::handleCollision(const HitInfo& hit_info)
{
	if (hit_info.item != owned_character)
	{
		Character* hit_player = dynamic_cast<Character*>(hit_info.item);
		if (hit_player->get_is_invulnerable())
			return;

		if (hit_info.layer == CollisionLayer::Player && valid)
		{
			play_sound();
			hit_player->subtract_hp(damage);
			hit_player->set_to_invulnerable(true);
			owned_character->add_mp(mp_value);
			if(is_enable_shake)
				SceneManger::GetInstance().get_main_camera()->Shake(strenth, duration,1);

			
			if (hit_info.position.x - this->get_collision_position().x >= 0)
			{
				hit_player->set_hit_direction_right(false);
				printf("左边\r\n");
			}
			else
			{
				hit_player->set_hit_direction_right(true);
				printf("右边\r\n");
			}
			this->collision_box->set_enabled(false);
		}
		valid = false;
	}
}


void Bullet::enable()
{
	set_visible(true);
	if (collision_box)
		collision_box->set_enabled(true);
	valid = true;
	is_anble = true;
}


void Bullet::disable()
{
	set_visible(false);
	if (collision_box)
		collision_box->set_enabled(false);
	is_anble = false;
}

