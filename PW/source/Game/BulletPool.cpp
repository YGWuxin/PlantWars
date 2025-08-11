#include "BulletPool.h"
#include "Bullet.h"
#include "PeaBullet.h"
#include "SunBullet.h"
#include "SunExBullet.h"
#include "BubbleBullet.h"
#include "BubbleExBullet.h"
#include "NutExplode.h"
#include "AudioManger.h"
#include "Controller.h"
#include "PlayerControllerManger.h"
#include "Character.h"


void BulletPool::InitPool(int num, BulletTyep type)
{
	for (int i = 0; i < num; i++)
	{
		switch (type)
		{
			case BulletTyep::PeaBullet:
			{
				PeaBullet* bullet = new PeaBullet();
				PeaBulletList.push_back(bullet);
				break;
			}
			case BulletTyep::SunBullet:
			{
				SunBullet* bullet = new SunBullet();
				SunBulletList.push_back(bullet);
				break;
			}
			case BulletTyep::SunExBullet:
			{
				SunExBullet* bullet = new SunExBullet();
				SunExBulletList.push_back(bullet);
				break;
			}
			case BulletTyep::BubbleBullet:
			{
				BubbleBullet* bullet = new BubbleBullet();
				BubbleBulletList.push_back(bullet);
				break;
			}
			case BulletTyep::BubbleExBullet:
			{
				BubbleExBullet* bullet = new BubbleExBullet();
				BubbleExBulletList.push_back(bullet);
				break;
			}
			case BulletTyep::Explode:
			{
				NutExplode* bullet = new NutExplode();
				NutExplodeList.push_back(bullet);
				break;
			}
			default:
				break;
		}
	}
}



Bullet* BulletPool::spawn_pea_bullet(Character* character,float speed)
{
	if (!character)
		return nullptr;

	bool find_bullet = false;
	for (PeaBullet * bullet : PeaBulletList)
	{
		if (!bullet->is_anble)
		{
			bullet->speed = speed;
			bullet->begin(character);
			find_bullet = true;
			return bullet;
		}
	}
	if (!find_bullet)
	{
		PeaBullet* bullet_temp = new PeaBullet();
		PeaBulletList.push_back(bullet_temp);
		bullet_temp->speed = speed;
		bullet_temp->begin(character);
		return bullet_temp;
	}
}


Bullet* BulletPool::spawn_sun_bullet(Character* character)
{
	if (!character)
		return nullptr;

	bool find_bullet = false;
	for (SunBullet* bullet : SunBulletList)
	{
		if (!bullet->is_anble)
		{
			bullet->begin(character);
			find_bullet = true;
			return bullet;
		}
	}
	if (!find_bullet)
	{
		SunBullet* bullet_temp = new SunBullet();
		SunBulletList.push_back(bullet_temp);
		bullet_temp->begin(character);
		return bullet_temp;
	}
}


Bullet* BulletPool::spawn_sun_ex_bullet(Character* character)
{
	if (!character)
		return nullptr;

	bool find_bullet = false;

	PlayerControllerManger::PlayerType type = PlayerControllerManger::PlayerType::None;

	if (character->get_owned_controller()->get_type() == PlayerControllerManger::PlayerType::Player_P1)
		type = PlayerControllerManger::PlayerType::Player_P2;
	else
		type = PlayerControllerManger::PlayerType::Player_P1;

	if (type == PlayerControllerManger::PlayerType::None)
		return nullptr;

	Vector2 posistion = PlayerControllerManger::GetInstance().get_player(type)->get_owned_character()->get_current_posistion();

	for (SunExBullet* bullet : SunExBulletList)
	{
		if (!bullet->is_anble)
		{
			bullet->begin(character);
			bullet->set_current_posistion({ posistion.x, -144 });
			find_bullet = true;
			return bullet;
		}
	}
	if (!find_bullet)
	{
		SunExBullet* bullet_temp = new SunExBullet();
		SunExBulletList.push_back(bullet_temp);
		bullet_temp->begin(character);
		bullet_temp->set_current_posistion({ posistion.x, -144});
		return bullet_temp;
	}
}



Bullet* BulletPool::spawn_bubble_bullet(Character* character)
{
	if (!character)
		return nullptr;

	bool find_bullet = false;
	for (BubbleBullet* bullet : BubbleBulletList)
	{
		if (!bullet->is_anble)
		{
			bullet->begin(character);
			find_bullet = true;
			return bullet;
		}
	}
	if (!find_bullet)
	{
		BubbleBullet* bullet_temp = new BubbleBullet();
		BubbleBulletList.push_back(bullet_temp);
		bullet_temp->begin(character);
		return bullet_temp;
	}

	// Return nullptr if object creation failed
	return nullptr;
}


Bullet* BulletPool::spawn_bubble_ex_bullet(Character* character)
{
	if (!character)
		return nullptr;
	bool find_bullet = false;
	for (BubbleExBullet* bullet : BubbleExBulletList)
	{
		if (!bullet->is_anble)
		{
			bullet->begin(character);
			find_bullet = true;
			return bullet;
		}
	}
	if (!find_bullet)
	{
		BubbleExBullet* bullet_temp = new BubbleExBullet();
		BubbleExBulletList.push_back(bullet_temp);
		bullet_temp->begin(character);
		return bullet_temp;
	}


}


Bullet* BulletPool::spawn_explode(Character* character)
{
	if (!character)
		return nullptr;
	bool find_bullet = false;
	for (NutExplode* bullet : NutExplodeList)
	{
		if (!bullet->is_anble)
		{
			bullet->begin(character);
			find_bullet = true;
			return bullet;
		}
	}
	if (!find_bullet)
	{
		NutExplode* bullet_temp = new NutExplode();
		NutExplodeList.push_back(bullet_temp);
		bullet_temp->begin(character);
		return bullet_temp;
	}
}


void BulletPool::clear_pool()
{
	//清空豌豆子弹
	/*for (PeaBullet* bullet : PeaBulletList)
	{
		if (bullet)
			delete bullet;
	}*/
	PeaBulletList.clear();

	//清空太阳子弹
	SunBulletList.clear();

	//清空特殊太阳子弹
	SunExBulletList.clear();

	//清空泡泡子弹
	BubbleBulletList.clear();

	//清空特殊泡泡子弹
	BubbleExBulletList.clear();

	//清空特殊泡泡子弹
	NutExplodeList.clear();


}

