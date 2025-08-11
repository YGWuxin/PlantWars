#include "PlatformLarge.h"
#include "RenderItem.h"
#include "RenderManager.h"
#include "CollisionManger.h"
#include "../Parameter/GlobeGameParameters.h"
#include "ResourcesManger.h"

PlatformLarge::PlatformLarge(Vector2 position)
{
	this->position = position;
	size = { 1030,280 };
	set_enable_gravity(false);

	IMAGE* img_platform_large = ResourcesManger::GetInstance().find_image("img_platform_large");
	init_render_item(img_platform_large, LAYER_ITEM_PLATFORM, CollisionLayer::PlatformLarge);

}



