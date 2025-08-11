#pragma once

#include "../Utils/helper.h"
#include <vector>
#include <algorithm>
#include "Vector2.h"
#include "../Parameter/GlobeGameParameters.h"

class RenderItem {
public:
    // ����ͼ��
    void setImage(IMAGE* img) { image = img; }

    // ��ȡͼ��
    IMAGE* getImage() const { return image; }

    // ��ȡĿ�����
    Rect getRectDst() const { return rect_dst; }

    // ����Դ����
    void setRectSrc(const Rect& src) { rect_src = src; }

    // ��ȡԴ����
    Rect getRectSrc() const { return rect_src; }


    //������Ⱦ��λ��
    void setPositionX(int x)
    {
        rect_dst.x = x;
    }

    void setPositionY(int y)
    {
        rect_dst.y = y;
    }

    void setDstWidth(int w)
    {
        rect_dst.w = w;
    }

    void setDstHeight(int h)
    {
        rect_dst.h = h;
    }

    void setImageSize(int w, int h)
    {
        rect_src.w = w;
        rect_src.h = h;
        rect_dst.w = w;
        rect_dst.h = h;
    }

    void setRenderX(int x)
    {
        rect_src.x = x;
    }

    void setRenderY(int y)
    {
        rect_src.y = y;
    }

    // ���ò㼶
    void setLayer(int l) { layer = l; }

    // ��ȡ�㼶
    int getLayer() const { return layer; }

    void setCanRender(bool isRender) { this->isRender = isRender; };

    bool getCanRender() { return isRender; }

    //��ȡ�Ƿ��ܱ�����
    bool canBeDestroyed() const { return beDestroyed; }

    // �����Ƿ��������
    void setCanBeDestroyed(bool canDestroy) {
        beDestroyed = canDestroy;
    }

    void setAnchorMode(AnchorMode mode) { this->mode = mode; }
    AnchorMode getAnchorMode() { return mode; }

    void setPosition(Vector2 position)
    {
        rect_dst.x = (int)position.x - rect_src.w / 2;
        switch (mode)
        {
        case AnchorMode::Centered:
            rect_dst.y = (int)position.y - rect_src.h / 2;
            break;
        case AnchorMode::BottomCrented:
            rect_dst.y = (int)position.y - rect_src.h;
            break;
        default:
            break;
        }
        rect_dst.w = rect_src.w;
        rect_dst.h = rect_src.h;
    }

    Vector2 getPostion()
    {
        float x = (int)rect_dst.x + rect_src.w / 2;
        float y = 0;
        switch (mode)
        {
        case AnchorMode::Centered:
            y = (int)rect_dst.y + rect_src.h / 2;
            break;
        case AnchorMode::BottomCrented:
            y = (int)rect_dst.y + rect_src.h;
            break;
        default:
            break;
        }
        return Vector2(x,y);
    }

private:
    IMAGE* image;
    Rect rect_dst;
    Rect rect_src;
    int layer;
    bool beDestroyed;  // ��ʾ�Ƿ���Ա�����
    AnchorMode mode = AnchorMode::Centered;
    bool isRender = true;


private:
    // ���캯��˽�л��������ⲿֱ��ʵ����
    RenderItem(IMAGE* img,Vector2 position ,int lyr,bool beDestroyed)
        : image(img), layer(lyr), beDestroyed(beDestroyed) {

        if (img)
        {
            this->rect_src.x = 0;
            this->rect_src.y = 0;
            this->rect_src.w = img->getwidth();
            this->rect_src.h = img->getheight();

            this->rect_dst.x = position.x;
            this->rect_dst.y = position.y;
            this->rect_dst.w = img->getwidth();
            this->rect_dst.h = img->getheight();
        }
        else
        {
            this->rect_src = { 0,0,0,0 };
            this->rect_dst = this->rect_src;
        }
    }


    // ��Ԫ��
    friend class RenderManager;
};



class RenderUI {

    enum class UIType
    {
        Node,
        Image,
        Text,
        Bar
    };

public:

    // ����ͼ��
    void setImage(IMAGE* img) 
    {
        image = img;
        if (img)
        {
            this->rect_src.w = img->getwidth();
            this->rect_src.h = img->getheight();
            this->rect_dst.w = img->getwidth();
            this->rect_dst.h = img->getheight();
        }
    }

    // ��ȡͼ��
    IMAGE* getImage() const { return image; }

    // ��ȡĿ�����
    Rect getRectDst() const { return rect_dst; }

      // ����Դ����
    void setRectSrc(const Rect& src) { rect_src = src; }

    void setImageSize(int w, int h)
    {
        rect_dst.w = w;
        rect_dst.h = h;
    }

    // ��ȡԴ����
    Rect getRectSrc() const { return rect_src; }

    //������Ⱦ��λ��
    void setPosition(Vector2 position)
    {
        rect_dst.x = position.x;
        rect_dst.y = position.y;
    }

    void setPositionX(int x)
    {
        rect_dst.x = x;
    }

    void setPositionY(int y)
    {
        rect_dst.y = y;
    }

    void setRenderWidth(int w)
    {
        rect_dst.w = w;
        rect_src.w = w;
    }

    void setRenderHeight(int h)
    {
        rect_dst.h = h;
        rect_src.h = h;
    }

    void setRenderX(int x)
    {
        rect_src.x = x;
    }

    void setRenderY(int y)
    {
        rect_src.y = y;
    }

    void setCanRender(bool isRender) { this->isRender = isRender; };

    bool getCanRender() { return isRender; }

    // ���ò㼶
    void setLayer(int l) { layer = l; }

    // ��ȡ�㼶
    int getLayer() const { return layer; }

    //��ȡ�Ƿ��ܱ�����
    bool canBeDestroyed() const { return beDestroyed; }

    // �����Ƿ��������
    void setCanBeDestroyed(bool canDestroy) {
        beDestroyed = canDestroy;
    }

    Vector2 getPostion()
    {
        float x = (int)rect_dst.x;
        float y = (int)rect_dst.y;
        return Vector2(x, y);
    }

    UIType get_type() { return type; }

    void set_text(LPCTSTR str) { this->str = str; }

    void setBarWidth(float w) { bar_width = (int)w; }
    void setBarHeight(float h) { bar_height = (int)h; }
    void setBarMode(AnchorMode mode) { bar_mode = mode; }

private:
    IMAGE* image = nullptr;
    int layer = 0;
    bool beDestroyed = true;  // ��ʾ�Ƿ���Ա�����
    Rect rect_dst = { 0,0,0,0 };
    Rect rect_src = { 0,0,0,0 };
    LPCTSTR str = _T("");
    UIType type = UIType::Node;
    bool isRender = true;

    //�������
    AnchorMode bar_mode = AnchorMode::LeftCentered;

    int bar_width = 0;
    int bar_height = 0;
    int bar_ellipsewidth = 0;
    int bar_ellipsheight = 0;
    S_RGB bar_rgb;


private:
    // ���캯��˽�л��������ⲿֱ��ʵ����
    RenderUI(IMAGE* img, Vector2 position, int lyr, bool beDestroyed)
        : image(img), layer(lyr), beDestroyed(beDestroyed){

        if (img)
        {
            this->rect_src.w = img->getwidth();
            this->rect_src.h = img->getheight();
            this->rect_dst.w = img->getwidth();
            this->rect_dst.h = img->getheight();
        }
        this->rect_src.x = 0;
        this->rect_src.y = 0;
        this->rect_dst.x = position.x;
        this->rect_dst.y = position.y;
        type = UIType::Image;
    }


    RenderUI(LPCTSTR str, Vector2 position, int lyr, bool beDestroyed)
        : str(str), layer(lyr), beDestroyed(beDestroyed)
    {
        this->rect_dst.x = position.x;
        this->rect_dst.y = position.y;
        type = UIType::Text;
    }


    RenderUI(Vector2 position,Vector2 size,S_RGB rgb,int lyr,int ellipsewidth,int ellipsheight, bool beDestroyed)
    {
        this->rect_dst.x = position.x;
        this->rect_dst.y = position.y;
        this->beDestroyed = beDestroyed;
        bar_width = size.x;
        bar_height = size.y;
        bar_ellipsewidth = ellipsewidth;
        bar_ellipsheight = ellipsheight;
        bar_rgb = rgb;
        layer = lyr;
        type = UIType::Bar;
    }


    // ��Ԫ��
    friend class RenderManager;
};


