#pragma once

#include "../Parameter/GlobeGameParameters.h"


enum class CollisionLayer
{
	None = 0,
	Player = BIT0,
	PlatformSmall = BIT1,
	PlatformLarge = BIT2,
	Bullet = BIT3,
	BuffBox = BIT4,

};



