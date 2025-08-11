#include "RenderManager.h"
#include <iostream>


RenderItem* RenderManager::createRenderItem(IMAGE* img, const Vector2& position, int layer, bool canDestroyed)
{
    RenderItem* item = new RenderItem(img, position, layer, canDestroyed);
    renderList.push_back(item);
    isSort_Object = true;
    return item;
}

RenderItem* RenderManager::createRenderItem(IMAGE* img, int layer, bool canDestroyed)
{
    RenderItem* item = new RenderItem(img, {0,0}, layer, canDestroyed);
    renderList.push_back(item);
    isSort_Object = true;
    return item;
}


void RenderManager::destroyRenderItem(RenderItem* item)
{
    renderList.erase(std::remove(renderList.begin(), renderList.end(), item), renderList.end());
    if (item) {
        if(item->canBeDestroyed())
            delete item;
        isSort_Object = true;
    }
}


void RenderManager::render_object(const Camera& camera)
{


    if (isSort_Object)
    {
        // 按照 layer 从大到小排序
        std::sort(renderList.begin(), renderList.end(), [](RenderItem* a, RenderItem* b) {
            return a->layer < b->layer;
            });

        isSort_Object = false;
    }

    // 渲染所有的RenderItem
    for (auto& item : renderList) {
        if (!item)
        {
            destroyRenderItem(item);
            return;
        }
        if(item->image && item->isRender)
        {
            helper::putimage_ex(camera, item->image, &item->rect_dst, &item->rect_src);
        }
       
    }

}


void RenderManager::clearDestroyedItems()
{
    auto it = std::remove_if(renderList.begin(), renderList.end(), [](RenderItem* item) {
        if (item) {
            if (item->canBeDestroyed())
            {
                delete item;
                return true;
            }
            return false;
        }
        return false;
        });
    renderList.erase(it, renderList.end());
}




RenderUI* RenderManager::createRenderItemUIIamge(IMAGE* img, const Vector2& position, int layer, bool canDestroyed)
{
    RenderUI* item = new RenderUI(img, position, layer, canDestroyed);
    renderUIList.push_back(item);
    isSort_UI = true;
    return item;
}


RenderUI* RenderManager::createRenderItemUIText(LPCTSTR str, Vector2 position, int layer)
{
    RenderUI* item = new RenderUI(str, position, layer, true);
    renderUIList.push_back(item);
    isSort_UI = true;
    return item;
}

RenderUI* RenderManager::createRenderItemUIBar(Vector2 position,Vector2 size, S_RGB rgb, int ellipsewidth, int ellipsheight, int layer, bool canDestroyed)
{
    RenderUI* item = new RenderUI(position, size, rgb, layer, ellipsewidth, ellipsheight, canDestroyed);
    renderUIList.push_back(item);
    isSort_UI = true;
    return item;
}


void RenderManager::destroyRenderItemUI(RenderUI* itemUI)
{
    renderUIList.erase(std::remove(renderUIList.begin(), renderUIList.end(), itemUI), renderUIList.end());
    if (itemUI) 
    {
        delete itemUI;
        isSort_UI = true;
    }
}

void RenderManager::render_ui()
{
    if (isSort_UI)
    {

        // 按照 layer 从大到小排序
        std::sort(renderUIList.begin(), renderUIList.end(), [](RenderUI* a, RenderUI* b) {
            return a->layer < b->layer;
            });

        isSort_UI = false;
    }

    // 渲染所有的RenderItem
    for (auto& item : renderUIList) {
        if (!item)
        {
            destroyRenderItemUI(item);
            return;
        }

        RenderUI::UIType type = item->get_type();

        switch (type)
        {
        case RenderUI::UIType::Image:
        {
            if (item->image && item->isRender)
            {
               
                helper::putimage_ex(item->getImage(), &item->rect_dst, &item->rect_src);
            }
            break;
        }
        case RenderUI::UIType::Text:
        {
            //settextstyle(20, 0, _T("/res/font/IPix.ttf"));
            settextcolor(RGB(40, 40, 40));
            outtextxy(item->rect_dst.x + 3, item->rect_dst.y + 3, item->str);
            settextcolor(RGB(255,255,255));
            outtextxy(item->rect_dst.x, item->rect_dst.y, item->str);
            break;
        }
        case RenderUI::UIType::Bar:
        {
            setfillcolor(RGB(item->bar_rgb.Red, item->bar_rgb.Green, item->bar_rgb.Blue));
            Vector2 posistion = item->getPostion();
            if (item->bar_mode == AnchorMode::Centered)
            {
                solidroundrect(posistion.x - item->bar_width / 2, posistion.y - item->bar_height / 2,
                    posistion.x + item->bar_width / 2, posistion.y + item->bar_height / 2, item->bar_ellipsewidth, item->bar_ellipsheight);
            }
            else if(item->bar_mode == AnchorMode::LeftCentered)
            {
                solidroundrect(posistion.x, posistion.y - item->bar_height / 2,
                    posistion.x + item->bar_width, posistion.y + item->bar_height / 2, item->bar_ellipsewidth, item->bar_ellipsheight);
            }
            else if (item->bar_mode == AnchorMode::RightCentered)
            {
                solidroundrect(posistion.x - item->bar_width, posistion.y - item->bar_height / 2,
                    posistion.x, posistion.y + item->bar_height / 2, item->bar_ellipsewidth, item->bar_ellipsheight);
            }
            break;
        }
        default:
            break;
        }

       

    }
}

void RenderManager::clearDestroyedUI()
{
    auto it = std::remove_if(renderUIList.begin(), renderUIList.end(), [](RenderUI* item) {
        if (item->canBeDestroyed()) {
            delete item;
            return true;
        }
        return false;
        });
    renderUIList.erase(it, renderUIList.end());
}

