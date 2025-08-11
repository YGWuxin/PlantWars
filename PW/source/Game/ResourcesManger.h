#pragma once

#include "../Res/atlas.h"
#include <fstream>
#include <unordered_map>
#include <graphics.h>	

using namespace std;

class ResourcesManger
{
public:
    static ResourcesManger& GetInstance()
    {
        static ResourcesManger instance; // ��̬�ֲ�������ȷ��Ψһ��
        return instance;
    }

    // ɾ���������캯���͸�ֵ�����
    ResourcesManger(const ResourcesManger&) = delete;
    ResourcesManger& operator=(const ResourcesManger&) = delete;


    //���غ���֤csv�ļ�������
    void loadAndValidate(const string& filename);


    Atlas* find_atlas(const string& id) const;
    IMAGE* find_image(const string& id) const;


private:
    unordered_map<string, Atlas*>  atlas_pool;
    unordered_map<string, IMAGE*>  image_pool;

    

    ResourcesManger() = default;    // ˽�й��캯������ֹ�ⲿ����ʵ��
    ~ResourcesManger() = default;
    bool validateHeader(const string& header) const;       // ��֤�������Ƿ����Ԥ��

};

