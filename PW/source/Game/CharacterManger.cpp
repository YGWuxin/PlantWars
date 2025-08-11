#include "CharacterManger.h"
#include "Character.h"
#include "PeashooterCharacter.h"
#include "SunflowerCharacter.h"
#include <vector>
#include <algorithm>
#include "Camera.h"
#include "ItemManger.h"
#include "GloomshroomCharacter.h"
#include "NutCharacter.h"


using namespace std;

Character* CharacterManger::create_character(Vector2 position,bool is_render_on_ui)
{
	Character* character = new Character(position, is_render_on_ui);
	return character;
}

Character* CharacterManger::create_character(Camera* camera,Vector2 position, bool is_render_on_ui)
{
	Character* character = new Character(position, is_render_on_ui);
	character->set_own_camera(camera);
	return character;
}


Character* CharacterManger::create_character(CharacterType type, Camera* camera, bool is_render_on_ui)
{
	if (!camera)
		return nullptr;
	Character* character = create_character(type, camera, {0,0}, is_render_on_ui);
	return character;
}


Character* CharacterManger::create_character(CharacterType type, Camera* camera, Vector2 position,bool is_render_on_ui)
{
	if (!camera)
		return nullptr;
	Character* character = nullptr;
	switch (type)
	{
	case CharacterManger::CharacterType::PeashooterCharacter:
		character = new PeashooterCharacter(position, is_render_on_ui);
		break;
	case CharacterManger::CharacterType::SunflowerCharacter:
		character = new SunflowerCharacter(position, is_render_on_ui);
		break;
	case CharacterManger::CharacterType::GloomshroomCharacter:
		character = new GloomshroomCharacter(position, is_render_on_ui);
		break;
	case CharacterManger::CharacterType::NutCharacter:
		character = new NutCharacter(position, is_render_on_ui);
		break;
	default:
		break;
	}
	
	character->set_own_camera(camera);
	return character;
}


void CharacterManger::destory_character(Character* character)
{
	ItemManger::GetInstance().destory_item(character);
}

