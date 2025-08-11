#pragma once

#include "Vector2.h"
#include "StateMachine.h"
#include "CollisionBox.h"
#include "../Res/Animation.h"
#include <functional>
#include <unordered_map>
#include <string>
#include "../Parameter/GlobeGameParameters.h"


using namespace std;

class RenderItem;
class RenderUI;
class ItemManger;


class ItemObject {
    friend class ItemManger;

public:
    virtual ~ItemObject();

    //��ȡ��ײ���С
    Vector2 get_collision_size() {return size;}

    Vector2 get_collision_position();

    //��ȡ���嵱ǰ��С
    Vector2 get_item_size();

    //��ȡ��ǰê��ģʽ
    AnchorMode get_anchor_mode() { return mode; }

    //����ê��ģʽ
    void set_anchor_mode(const AnchorMode& mode);

    //�����Ƿ�����ģ����������
    void set_enable_gravity(bool val) { enable_gravity = val; }

    //���õ�ǰλ��
    void set_current_posistion(Vector2 position) { this->position = position; }

    //��ȡ��ǰλ��
    Vector2 get_current_posistion() { return this->position; }

    //���õ�ǰ����
    void set_current_animation(Animation* animation);

    //���õ�ǰ����
    void set_current_animation_reset(Animation* animation);

    //���õ�ǰ��Ⱦ��ͼ��

    //������Ⱦ�㼶
    void set_render_layer(int l);

    //����ӵ�е������
    void set_own_camera(Camera* camera){ own_camera = camera;}

    //��ȡӵ�е������
    Camera* get_own_camera() const { return own_camera; }

    //�����Ƿ���
    void set_is_face_rigth(bool is_right) { is_face_rigth = is_right; };

    //��ȡ�Ƿ���
    bool get_is_face_rigth() { return is_face_rigth; };

    //item���ƶ�
    virtual void on_move(float distance)
    {
        position.x += distance;
    };

    //�Ƿ�������ײ
    void set_enable_collision(bool flag);

    //�����Ƿ����
    void set_visible(bool visible);

    //��ȡ�Ƿ����
    bool get_visiable() { return is_visible; }

    //��������ϵ��
    bool set_gravity(float gravity) { this->gravity = gravity; }

    //���ÿ�������ϵ��
    bool set_airDrag(float airDrag) { this->airDrag = airDrag; }

    //�����ٶ�
    void set_velocity(float x, float y)
    {
        velocity.x = x;
        velocity.y = y;
    }

    //�����ٶ�
    void set_velocity_x(float x)
    {
        velocity.x = x;
    }

    //�����ٶ�
    void set_velocity_y(float y)
    {
        velocity.y = y;
    }

    //���Ϊ�����
    void set_is_clear() { is_clear = true; };

protected:

    //��Ʒ����ʱִ��
    void init_render_item(IMAGE* image, int layer, CollisionLayer layer_tpye);

    //��Ʒ������UI��ʱִ��
    void init_render_on_ui(IMAGE* image, int layer, CollisionLayer layer_tpye);

    //item�����ݸ���
    virtual void on_update(float delta);

    //item����ײ�ص�
    virtual void handleCollision(const HitInfo& hit_info) {};

   

    //������ײ���С
    void set_collision_size(Vector2 size);


protected:
    RenderItem* render_item = nullptr;          //������Ⱦ��item
    RenderUI* render_item_ui = nullptr;         //������Ⱦ��UI�����item
    AnchorMode mode = AnchorMode::Centered;     //item��λ��ê��

    CollisionBox* collision_box = nullptr;      //��ײ��
    Vector2 size = { 0,0 };                     //��ײ���С
    int collision_offset_x = 0;                 //��ײ����x���ϵ�ƫ��
    int collision_offset_y = 0;                 //��ײ����y���ϵ�ƫ��

    Vector2 position = { 0,0 };                 //item��λ��
    Vector2 velocity = { 0,0 };                 //item���ٶ�
    bool enable_gravity = true;                 //�Ƿ�����ģ������
    float gravity = 1.6e-3f;                    //����ϵ��
    float airDrag = 0;                          //��������ϵ��


    bool is_face_rigth = true;                  //�Ƿ���
    bool is_on_ui = false;                      //�Ƿ���ʾ��UI��
    bool on_ground = false;                     //�Ƿ��ڵ�����

    bool update_animation = true;               //�Ƿ���µ�ǰ����

    //�ⲿ��ֵ������Ҫ����
    Animation* current_animation = nullptr;     //itme�ĵ�ǰ����
    Camera* own_camera = nullptr;               //item�������

    bool is_visible = true;                     //��ǰ�Ƿ����

    bool is_clear = false;                      //�Ƿ�Ҫ������

};

