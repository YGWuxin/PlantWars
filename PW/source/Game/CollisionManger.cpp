#include "CollisionManger.h"
#include "Camera.h"
#include "../Utils/helper.h"
#include <math.h>
#include <graphics.h>	


using namespace std;

CollisionBox* CollisionManger::create_collision_box()
{
	CollisionBox* box = new CollisionBox();
	collision_box_list.push_back(box);
	return box;
}


void CollisionManger::destroy_collision_box(CollisionBox* box)
{
	collision_box_list.erase(std::remove(collision_box_list.begin(), collision_box_list.end(), box), collision_box_list.end());
	delete box;
}



void CollisionManger::process_collide(float delta)
{
	for (CollisionBox* collision_box_src : collision_box_list)
	{
		if (!collision_box_src->get_enabled() || collision_box_src->layer_dst == (int)CollisionLayer::None)
			continue;

		for (CollisionBox* collision_box_dst : collision_box_list)
		{
			if (!collision_box_src->get_enabled())
				break;

			int res = (int)(collision_box_dst->get_layer_self()) & collision_box_src->get_layer_dst();
			if (res == 0 || !collision_box_dst->get_enabled() || collision_box_src == collision_box_dst)
				continue;
	
			bool is_collide_x = abs(collision_box_src->get_position().x - collision_box_dst->get_position().x) 
				<= collision_box_src->get_size().x / 2 + collision_box_dst->get_size().x / 2;

			
			bool is_collide_y = abs(collision_box_src->get_position().y - collision_box_dst->get_position().y) 
				<= (collision_box_src->get_size().y / 2 + collision_box_dst->get_size().y / 2);
			//bool is_collide_y = true;

			if (is_collide_x && is_collide_y && collision_box_src->on_collide)
			{
				HitInfo info;
				info.item = collision_box_dst->item_object;
				info.box = collision_box_dst;
				info.delta = delta;
				info.size = collision_box_dst->get_size();
				info.position = collision_box_dst->position;
				info.layer = collision_box_dst->layer_self;
				collision_box_src->on_collide(info);
			}

		}
	}
}


void CollisionManger::on_debug_render(const Camera& camera)
{
	if (!is_enabled_debug)
		return;
	settextcolor(RGB(255, 0, 0));
	outtextxy(15,15,_T("调试模式已开启，按'Q'键关闭"));
	for (CollisionBox* box : collision_box_list) {
		if (box)
		{
			//helper::putimage_ex(camera, item->image, &item->rect_dst, &item->rect_src);
			setlinecolor(box->get_enabled() ? RGB(255,195,195) : RGB(115,115,175));
			rectangle((int)(box->get_position().x - box->get_size().x / 2 + camera.get_position().x),
					  (int)(box->get_position().y - box->get_size().y / 2 + camera.get_position().y),
					  (int)(box->get_position().x + box->get_size().x / 2 + camera.get_position().x),
					  (int)(box->get_position().y + box->get_size().y / 2 + camera.get_position().y));
		}
	}
}

