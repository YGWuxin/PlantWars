#pragma once

#include <vector>

using namespace std;

class ItemObject;

class ItemManger
{
public:
    static ItemManger& GetInstance()
    {
        static ItemManger instance; // ��̬�ֲ�������ȷ��Ψһ��
        return instance;
    }

    // ɾ���������캯���͸�ֵ�����
    ItemManger(const ItemManger&) = delete;
    ItemManger& operator=(const ItemManger&) = delete;

    //��item��ӵ��б�
    void add_item_to_list(ItemObject* object);

    //����item
    void destory_item(ItemObject* object);

    //����item
    void remove_item(ItemObject* object);

    //����item
    void clear_items();

    //ִ��update
    void on_update(float delta);


private:
    ItemManger() = default;    // ˽�й��캯������ֹ�ⲿ����ʵ��
    ~ItemManger() = default;

private:
    vector<ItemObject*> items_list;

};

