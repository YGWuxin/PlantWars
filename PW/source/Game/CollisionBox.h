#pragma once

#include "Vector2.h"
#include "../Parameter/CollisionLayer.h"
#include "../Parameter/GlobeGameParameters.h"

#include <functional>

class CollisionManger;
class ItemObject;
class CollisionBox;

struct HitInfo
{
	ItemObject* item = nullptr;
	CollisionBox* box = nullptr;
	float delta = 0;
	Vector2 size = { 0,0 };
	Vector2 position = { 0,0 };
	CollisionLayer layer = CollisionLayer::None;
};


class CollisionBox 
{
	friend class CollisionManger;

private:
	Vector2 size = {0,0};
	Vector2 position = { 0,0 };
	bool enabled = false;
	std::function<void(HitInfo)> on_collide;
	CollisionLayer layer_self = CollisionLayer::None;		//������ײ�㼶	
	int layer_dst = 0;										//��ײ���Ĳ㼶
	ItemObject* item_object = nullptr;

public:
	//����ӵ�е���Ʒ
	void set_item_object(ItemObject* item) { item_object = item; }

	//������ײ���Ƿ�����
	void set_enabled(bool flag) { enabled = flag; };

	//��ȡ�Ƿ�����
	bool get_enabled() { return enabled; };

	//������ײ���С
	void set_size(Vector2 size) { this->size = size; };

	//��ȡ��ײ���С
	Vector2 get_size() { return size; };

	//������ײ��λ��
	void set_position(Vector2 position) { this->position = position; };

	//������ײ��λ��
	void set_position(Vector2 position, AnchorMode mode)
	{ 
		switch (mode)
		{
		case AnchorMode::Centered:
			this->position = position;
			break;
		case AnchorMode::BottomCrented:
			this->position.x = position.x;
			this->position.y = position.y - this->size.y / 2;
			break;
		default:
			break;
		}
	};

	//������ײ��λ��
	void set_position(Vector2 position, AnchorMode mode,int offset_x,int offset_y)
	{
		switch (mode)
		{
		case AnchorMode::Centered:
			this->position.x= position.x + offset_x;
			this->position.y = position.y + offset_y;
			break;
		case AnchorMode::BottomCrented:
			this->position.x = position.x + offset_x;
			this->position.y = (position.y - this->size.y / 2) + offset_y;
			break;
		default:
			break;
		}
	};

	//��ȡ��ײ��λ��
	Vector2 get_position() { return position; };

	//������ײ�ص�����
	void set_on_collide(std::function<void(HitInfo)> on_collide) { this->on_collide = on_collide; };

	//��������㼶
	void set_layer_self(CollisionLayer layer_self) { this->layer_self = layer_self; };

	//��ȡ����㼶
	CollisionLayer get_layer_self() { return layer_self; };

	//�����Ҫ��ײ���Ĳ㼶
	void add_layer_dst(CollisionLayer dst) { layer_dst = layer_dst | static_cast<int>(dst); };

	//ȡ��������Ҫ��ײ�Ĳ㼶
	void remove_layer_all() { layer_dst = 0; }

	//�Ƴ���ײ���Ĳ㼶
	void remove_layer_dst(CollisionLayer dst) { layer_dst = layer_dst & ~static_cast<int>(dst); };

	//��ȡ��ײ���Ĳ㼶
	int get_layer_dst() { return layer_dst; };

private:
	CollisionBox() = default;
	~CollisionBox() = default;

};


