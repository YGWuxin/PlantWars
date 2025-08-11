#pragma once

#include <vector>

using namespace std;

class ItemObject;

class ItemManger
{
public:
    static ItemManger& GetInstance()
    {
        static ItemManger instance; // 静态局部变量，确保唯一性
        return instance;
    }

    // 删除拷贝构造函数和赋值运算符
    ItemManger(const ItemManger&) = delete;
    ItemManger& operator=(const ItemManger&) = delete;

    //将item添加到列表
    void add_item_to_list(ItemObject* object);

    //销毁item
    void destory_item(ItemObject* object);

    //销毁item
    void remove_item(ItemObject* object);

    //销毁item
    void clear_items();

    //执行update
    void on_update(float delta);


private:
    ItemManger() = default;    // 私有构造函数，防止外部创建实例
    ~ItemManger() = default;

private:
    vector<ItemObject*> items_list;

};

