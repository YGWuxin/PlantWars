#include "ItemObject.h"
#include <cstdio>
#include "Controller.h"
#include "RenderItem.h"
#include "RenderManager.h"
#include "CollisionManger.h"
#include "ItemManger.h"

ItemObject::~ItemObject()
{
	//ItemManger::GetInstance().remove_item(this);
	if (render_item)
	{
		render_item->setCanBeDestroyed(true);
		RenderManager::getInstance().destroyRenderItem(render_item);
	}
	else if (render_item_ui)
	{
		RenderManager::getInstance().destroyRenderItemUI(render_item_ui);
	}
	if (collision_box)
	{
		CollisionManger::GetInstance().destroy_collision_box(collision_box);
	}
}

void ItemObject::on_update(float delta)
{
	//j简单物理模拟部分
	if (enable_gravity)
	{
		if (velocity.y == 0)
			on_ground = true;
		else
			on_ground = false;

		velocity.y += gravity * delta;
		printf("enable_gravity velocity.y:%0.2f\r\n", velocity.y);
		if (airDrag != 0 && velocity.x != 0)
		{
			if (velocity.x > 0)
			{
				velocity.x -= airDrag * delta;
				if (velocity.x <= 0)
					velocity.x = 0;
			}
			else if (velocity.x < 0)
			{
				velocity.x += airDrag * delta;
				if (velocity.x >= 0)
					velocity.x = 0;
			}
		}
	}
	position += velocity * delta;


	if (current_animation && update_animation)
	{
		current_animation->on_update(delta);		//更新动画
	}


	if (render_item )
	{
		render_item->setPosition(position);
		//render_item->setCanRender(is_visible);
		if(current_animation && update_animation)
			render_item->setImage(current_animation->get_current_frame_image());
	}
	else if (render_item_ui)
	{
		render_item_ui->setPosition(position);
		//render_item_ui->setCanRender(is_visible);
		if(current_animation && update_animation)
			render_item_ui->setImage(current_animation->get_current_frame_image());
	}


	//碰撞体
	if (collision_box)
		collision_box->set_position(position, mode, collision_offset_x, collision_offset_y);
}


void ItemObject::init_render_item(IMAGE* image, int layer, CollisionLayer layer_tpye)
{
	render_item = RenderManager::getInstance().createRenderItem(image, layer, false);
	render_item->setAnchorMode(mode);
	render_item->setPosition(position);

	collision_box = CollisionManger::GetInstance().create_collision_box();
	collision_box->set_item_object(this);
	collision_box->set_layer_self(layer_tpye);
	collision_box->set_enabled(true);
	collision_box->set_size(size);
	collision_box->set_position(position, mode, collision_offset_x, collision_offset_y);
	collision_box->set_on_collide([&](HitInfo hit_info) {
		handleCollision(hit_info);
		});

	is_on_ui = false;
	ItemManger::GetInstance().add_item_to_list(this);

}


void ItemObject::init_render_on_ui(IMAGE* image, int layer, CollisionLayer layer_tpye)
{
	render_item_ui = RenderManager::getInstance().createRenderItemUIIamge(image, position, layer, false);
	enable_gravity = false;
	is_on_ui = true;
	ItemManger::GetInstance().add_item_to_list(this);
}


void ItemObject::set_enable_collision(bool flag)
{
	if (collision_box)
		collision_box->set_enabled(flag);
}

void ItemObject::set_collision_size(Vector2 size)
{
	this->size = size;
	if (collision_box)
		collision_box->set_size(size);
}

Vector2 ItemObject::get_item_size()
{
	if (render_item)
		return { (float)render_item->getImage()->getwidth(), (float)render_item->getImage()->getheight() };
	if (render_item_ui)
		return { (float)render_item_ui->getImage()->getwidth(), (float)render_item_ui->getImage()->getheight() };
	return { 0,0 };
}


void ItemObject::set_anchor_mode(const AnchorMode& mode)
{
	this->mode = mode;
	if (render_item)
		render_item->setAnchorMode(mode);
	if (collision_box)
		collision_box->set_position(position, mode, collision_offset_x, collision_offset_y);
}


void ItemObject::set_render_layer(int l)
{
	if (render_item)
		render_item->setLayer(l);
	else if (render_item_ui)
		render_item_ui->setLayer(l);
}

void ItemObject::set_current_animation(Animation* animation)
{
	current_animation = animation;
	if (!current_animation)
		return;
	//current_animation->reset();
	if (render_item)
	{
		render_item->setImage(current_animation->get_current_frame_image());
		render_item->setImageSize(current_animation->get_current_frame_image()->getwidth(), current_animation->get_current_frame_image()->getheight());
		render_item->setRectSrc(current_animation->get_current_frame_rect_src());
	}
	else if (render_item_ui)
	{
		render_item_ui->setImage(current_animation->get_current_frame_image());
		render_item_ui->setImageSize(current_animation->get_current_frame_image()->getwidth(), current_animation->get_current_frame_image()->getheight());
		render_item_ui->setRectSrc(current_animation->get_current_frame_rect_src());
	}
}


void ItemObject::set_current_animation_reset(Animation* animation)
{
	current_animation = animation;
	if (!current_animation)
		return;
	current_animation->reset();
	if (render_item)
	{
		render_item->setImage(current_animation->get_current_frame_image());
		render_item->setImageSize(current_animation->get_current_frame_image()->getwidth(), current_animation->get_current_frame_image()->getheight());
		render_item->setRectSrc(current_animation->get_current_frame_rect_src());
	}
	else if (render_item_ui)
	{
		render_item_ui->setImage(current_animation->get_current_frame_image());
		render_item_ui->setImageSize(current_animation->get_current_frame_image()->getwidth(), current_animation->get_current_frame_image()->getheight());
		render_item_ui->setRectSrc(current_animation->get_current_frame_rect_src());
	}
}


Vector2 ItemObject::get_collision_position()
{
	if (collision_box)
		return collision_box->get_position();
	return { 0,0 };
}

void ItemObject::set_visible(bool visible)
{
	is_visible = visible;
	if (render_item)
	{
		render_item->setCanRender(is_visible);
	}
	else if (render_item_ui)
	{
		render_item_ui->setCanRender(is_visible);
	}
}