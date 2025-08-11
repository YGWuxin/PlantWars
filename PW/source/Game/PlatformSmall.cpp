#include "PlatformSmall.h"
#include "RenderItem.h"
#include "RenderManager.h"
#include "CollisionManger.h"
#include "../Parameter/GlobeGameParameters.h"
#include "ResourcesManger.h"

PlatformSmall::PlatformSmall(Vector2 position)
{
	this->position = position;
	size = { 220,8 };
	set_enable_gravity(false);

	IMAGE* img_platform_small = ResourcesManger::GetInstance().find_image("img_platform_small");
	init_render_item(img_platform_small, LAYER_ITEM_PLATFORM, CollisionLayer::PlatformSmall);


}

