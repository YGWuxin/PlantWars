#pragma once

#include "ItemObject.h"
#include "Vector2.h"


class CollisionBox;
class RenderItem;

class PlatformSmall : public ItemObject
{

public:
	PlatformSmall(Vector2 position);
	~PlatformSmall() = default;

	void set_position(Vector2 position) { this->position = position; }


private:



};

