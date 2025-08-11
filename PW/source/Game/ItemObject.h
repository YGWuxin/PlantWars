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

    //获取碰撞箱大小
    Vector2 get_collision_size() {return size;}

    Vector2 get_collision_position();

    //获取物体当前大小
    Vector2 get_item_size();

    //获取当前锚点模式
    AnchorMode get_anchor_mode() { return mode; }

    //设置锚点模式
    void set_anchor_mode(const AnchorMode& mode);

    //设置是否启用模拟物理重力
    void set_enable_gravity(bool val) { enable_gravity = val; }

    //设置当前位置
    void set_current_posistion(Vector2 position) { this->position = position; }

    //获取当前位置
    Vector2 get_current_posistion() { return this->position; }

    //设置当前动画
    void set_current_animation(Animation* animation);

    //设置当前动画
    void set_current_animation_reset(Animation* animation);

    //设置当前渲染的图形

    //设置渲染层级
    void set_render_layer(int l);

    //设置拥有的摄像机
    void set_own_camera(Camera* camera){ own_camera = camera;}

    //获取拥有的摄像机
    Camera* get_own_camera() const { return own_camera; }

    //设置是否朝右
    void set_is_face_rigth(bool is_right) { is_face_rigth = is_right; };

    //获取是否朝右
    bool get_is_face_rigth() { return is_face_rigth; };

    //item的移动
    virtual void on_move(float distance)
    {
        position.x += distance;
    };

    //是否启用碰撞
    void set_enable_collision(bool flag);

    //设置是否可视
    void set_visible(bool visible);

    //获取是否可视
    bool get_visiable() { return is_visible; }

    //设置重力系数
    bool set_gravity(float gravity) { this->gravity = gravity; }

    //设置空气阻力系数
    bool set_airDrag(float airDrag) { this->airDrag = airDrag; }

    //设置速度
    void set_velocity(float x, float y)
    {
        velocity.x = x;
        velocity.y = y;
    }

    //设置速度
    void set_velocity_x(float x)
    {
        velocity.x = x;
    }

    //设置速度
    void set_velocity_y(float y)
    {
        velocity.y = y;
    }

    //标记为可清除
    void set_is_clear() { is_clear = true; };

protected:

    //物品创建时执行
    void init_render_item(IMAGE* image, int layer, CollisionLayer layer_tpye);

    //物品创建在UI上时执行
    void init_render_on_ui(IMAGE* image, int layer, CollisionLayer layer_tpye);

    //item的数据更新
    virtual void on_update(float delta);

    //item的碰撞回调
    virtual void handleCollision(const HitInfo& hit_info) {};

   

    //设置碰撞体大小
    void set_collision_size(Vector2 size);


protected:
    RenderItem* render_item = nullptr;          //用于渲染的item
    RenderUI* render_item_ui = nullptr;         //用于渲染在UI层面的item
    AnchorMode mode = AnchorMode::Centered;     //item的位置锚点

    CollisionBox* collision_box = nullptr;      //碰撞箱
    Vector2 size = { 0,0 };                     //碰撞箱大小
    int collision_offset_x = 0;                 //碰撞箱在x轴上的偏移
    int collision_offset_y = 0;                 //碰撞箱在y轴上的偏移

    Vector2 position = { 0,0 };                 //item的位置
    Vector2 velocity = { 0,0 };                 //item的速度
    bool enable_gravity = true;                 //是否启用模拟物理
    float gravity = 1.6e-3f;                    //重力系数
    float airDrag = 0;                          //空气阻力系数


    bool is_face_rigth = true;                  //是否朝右
    bool is_on_ui = false;                      //是否显示在UI上
    bool on_ground = false;                     //是否在地面上

    bool update_animation = true;               //是否更新当前动画

    //外部赋值，不需要销毁
    Animation* current_animation = nullptr;     //itme的当前动画
    Camera* own_camera = nullptr;               //item的摄像机

    bool is_visible = true;                     //当前是否可视

    bool is_clear = false;                      //是否要被销毁

};

