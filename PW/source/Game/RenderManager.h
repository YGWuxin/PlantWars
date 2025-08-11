#pragma once

#include <vector>
#include "RenderItem.h"
#include "../Parameter/GlobeGameParameters.h"


//Item����
#define LAYER_ITEM_PLAYER									10								//�����ʾ�㼶
#define LAYER_ITEM_PARTICLE									9								//������ʾ�㼶
#define LAYER_ITEM_PLATFORM									4								//�ذ���ʾ�㼶
#define LAYER_ITEM_BUFFBOX								    15								//�ذ���ʾ�㼶
#define LAYER_ITEM_BULLET									14								//�ӵ���ʾ�㼶

//UI����


class Camera;

class RenderManager
{
public:
    // ����ģʽ��ȡʵ��
    static RenderManager& getInstance() {
        static RenderManager instance;
        return instance;
    }

    // ���ø��ƺ͸�ֵ����
    RenderManager(const RenderManager&) = delete;
    RenderManager& operator=(const RenderManager&) = delete;


    // �������������ڴ���RenderItem
    RenderItem* createRenderItem(IMAGE* img, int layer, bool canDestroyed = true);
    RenderItem* createRenderItem(IMAGE* img, const Vector2& position, int layer, bool canDestroyed = true);

    // ����RenderItem
    void destroyRenderItem(RenderItem* item);

    // ��Ⱦ����������layer�����������Ⱦ
    void render_object(const Camera& camera);

    //������Ա����ٵ���Ⱦ����
    void clearDestroyedItems();

    /* �й�UI�� */
    //Ĭ������λ���������Ͻ�
    RenderUI* createRenderItemUIIamge(IMAGE* img, const Vector2& position, int layer, bool canDestroyed = true);
    //Ĭ������λ���������Ͻ�
    RenderUI* createRenderItemUIText(LPCTSTR str, Vector2 position, int layer);
    //Ĭ������λ���������Ͻ�
    RenderUI* createRenderItemUIBar(Vector2 position, Vector2 size, S_RGB rgb, int ellipsewidth, int ellipsheight, int layer, bool canDestroyed = true);

    void destroyRenderItemUI(RenderUI* itemUI);

    // ��Ⱦ����������layer�����������Ⱦ
    void render_ui();

    //������Ա����ٵ���ȾUI
    void clearDestroyedUI();


private:
    bool isSort_Object = false;
    bool isSort_UI = false;

    std::vector<RenderItem*> renderList;
    std::vector<RenderUI*> renderUIList;

    // ȷ������ģʽ
    RenderManager() = default;
    ~RenderManager() = default;

};

