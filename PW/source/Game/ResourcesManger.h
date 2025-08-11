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
        static ResourcesManger instance; // 静态局部变量，确保唯一性
        return instance;
    }

    // 删除拷贝构造函数和赋值运算符
    ResourcesManger(const ResourcesManger&) = delete;
    ResourcesManger& operator=(const ResourcesManger&) = delete;


    //加载和验证csv文件的内容
    void loadAndValidate(const string& filename);


    Atlas* find_atlas(const string& id) const;
    IMAGE* find_image(const string& id) const;


private:
    unordered_map<string, Atlas*>  atlas_pool;
    unordered_map<string, IMAGE*>  image_pool;

    

    ResourcesManger() = default;    // 私有构造函数，防止外部创建实例
    ~ResourcesManger() = default;
    bool validateHeader(const string& header) const;       // 验证标题行是否符合预期

};

