#pragma once

#include "CollisionBox.h"
#include <vector>

using namespace std;

class Camera;

class CollisionManger
{
private:
    vector<CollisionBox*> collision_box_list;

public:
    static CollisionManger& GetInstance()
    {
        static CollisionManger instance; // ��̬�ֲ�������ȷ��Ψһ��
        return instance;
    }

    // ɾ���������캯���͸�ֵ�����
    CollisionManger(const CollisionManger&) = delete;
    CollisionManger& operator=(const CollisionManger&) = delete;

    //������ײ��
    CollisionBox* create_collision_box();

    //������ײ��
    void destroy_collision_box(CollisionBox* box);

    //��ײִ���߼�
    void process_collide(float delta);

    //��ײ���Ժ���
    void on_debug_render(const Camera& camera);

    //�����Ƿ�������
    void set_enabled_debug(bool flag) { is_enabled_debug = flag; }

    // ��ǰ����״̬
    bool get_enabled_debug() { return is_enabled_debug; }

private:
    bool is_enabled_debug = false;

private:
    CollisionManger() = default;    // ˽�й��캯������ֹ�ⲿ����ʵ��
    ~CollisionManger() = default;


};

