#pragma once

#include "ItemObject.h"
#include "Vector2.h"

class CollisionBox;
class RenderItem;

class PlatformLarge : public ItemObject
{
public:
	PlatformLarge(Vector2 position);
	~PlatformLarge() = default;

	void set_position(Vector2 position) { this->position = position; }


private:


};

