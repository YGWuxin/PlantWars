#pragma once

#include <vector>
#include "RenderItem.h"
#include "../Parameter/GlobeGameParameters.h"


//Item层面
#define LAYER_ITEM_PLAYER									10								//玩家显示层级
#define LAYER_ITEM_PARTICLE									9								//粒子显示层级
#define LAYER_ITEM_PLATFORM									4								//地板显示层级
#define LAYER_ITEM_BUFFBOX								    15								//地板显示层级
#define LAYER_ITEM_BULLET									14								//子弹显示层级

//UI层面


class Camera;

class RenderManager
{
public:
    // 单例模式获取实例
    static RenderManager& getInstance() {
        static RenderManager instance;
        return instance;
    }

    // 禁用复制和赋值操作
    RenderManager(const RenderManager&) = delete;
    RenderManager& operator=(const RenderManager&) = delete;


    // 工厂方法，用于创建RenderItem
    RenderItem* createRenderItem(IMAGE* img, int layer, bool canDestroyed = true);
    RenderItem* createRenderItem(IMAGE* img, const Vector2& position, int layer, bool canDestroyed = true);

    // 销毁RenderItem
    void destroyRenderItem(RenderItem* item);

    // 渲染函数，根据layer进行排序后渲染
    void render_object(const Camera& camera);

    //清除可以被销毁的渲染对象
    void clearDestroyedItems();

    /* 有关UI的 */
    //默认生成位置是在左上角
    RenderUI* createRenderItemUIIamge(IMAGE* img, const Vector2& position, int layer, bool canDestroyed = true);
    //默认生成位置是在左上角
    RenderUI* createRenderItemUIText(LPCTSTR str, Vector2 position, int layer);
    //默认生成位置是在左上角
    RenderUI* createRenderItemUIBar(Vector2 position, Vector2 size, S_RGB rgb, int ellipsewidth, int ellipsheight, int layer, bool canDestroyed = true);

    void destroyRenderItemUI(RenderUI* itemUI);

    // 渲染函数，根据layer进行排序后渲染
    void render_ui();

    //清除可以被销毁的渲染UI
    void clearDestroyedUI();


private:
    bool isSort_Object = false;
    bool isSort_UI = false;

    std::vector<RenderItem*> renderList;
    std::vector<RenderUI*> renderUIList;

    // 确保单例模式
    RenderManager() = default;
    ~RenderManager() = default;

};

