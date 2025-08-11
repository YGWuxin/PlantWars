#include "ItemManger.h"
#include "ItemObject.h"


void ItemManger::add_item_to_list(ItemObject* object)
{
	items_list.push_back(object);
}



void ItemManger::destory_item(ItemObject* object)
{
	// 使用 std::remove 来将目标元素移到末尾，并使用 erase 删除它
	items_list.erase(std::remove(items_list.begin(), items_list.end(), object), items_list.end());
	if (!object)
		return;
	delete object;
}


void ItemManger::remove_item(ItemObject* object)
{
	items_list.erase(std::remove(items_list.begin(), items_list.end(), object), items_list.end());
}


void ItemManger::clear_items()
{
	for (auto it = items_list.begin(); it != items_list.end(); ++it) {
		// 对 items_list 中的每个元素进行操作		
		ItemObject* item_ptr = *it;
		//destory_item(item_ptr);
		if (item_ptr)
			delete item_ptr;
	}
	items_list.clear();
}


void ItemManger::on_update(float delta)
{
	vector<ItemObject*> remove_list;
	for (auto it = items_list.begin(); it != items_list.end(); ++it) {
		// 对 items_list 中的每个元素进行操作		
		ItemObject* item_ptr = *it;
		if (item_ptr)
		{
			if (!item_ptr->is_clear)
				item_ptr->on_update(delta);
			else
				remove_list.push_back(item_ptr);
		}
		else
			remove_list.push_back(item_ptr);
	}

	for (auto it = remove_list.begin(); it != remove_list.end(); ++it) {
		// 对 items_list 中的每个元素进行操作		
		ItemObject* item_ptr = *it;
		destory_item(item_ptr);
	}


}
