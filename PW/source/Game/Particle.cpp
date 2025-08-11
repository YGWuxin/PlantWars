#include "Particle.h"
#include "RenderItem.h"
#include "RenderManager.h"



Particle::Particle(Vector2 position, int lifespan)
{
	render_item = RenderManager::getInstance().createRenderItem(nullptr, LAYER_ITEM_PARTICLE, false);
	render_item->setAnchorMode(AnchorMode::Centered);
	set_position(position);
	this->lifespan = lifespan;
}


Particle::~Particle()
{
	if (render_item)
	{
		render_item->setCanBeDestroyed(true);
		RenderManager::getInstance().destroyRenderItem(render_item);
	}
}


void Particle::set_position(Vector2 position)
{
	this->position = position;
	if (render_item)
	{
		render_item->setPosition(position);
	}
}


void Particle::on_update(float delta)
{
	if (!atlas || !render_item)
	{
		valid = false;
		return;
	}
	timer += delta;
	if (timer >= lifespan || idx_frame == 0)
	{
		timer = 0;
		idx_frame++;
		if (idx_frame >= atlas->get_size())
		{
			idx_frame = atlas->get_size() - 1;
			valid = false;
		}
		render_item->setImage(atlas->get_image(idx_frame));
		render_item->setImageSize(atlas->get_image(idx_frame)->getwidth(), atlas->get_image(idx_frame)->getheight());
	}
}