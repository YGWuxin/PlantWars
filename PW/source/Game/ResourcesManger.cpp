#include "ResourcesManger.h"
#include <iostream>
#include <string>
#include <sstream>
#include "../Utils/helper.h"
#include <tchar.h>    // For TCHAR
#include "../Utils/helper.h"

using namespace std;


void ResourcesManger::loadAndValidate(const string& filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        file.close();
        throw runtime_error("无法打开文件: " + filename);
    }

    string line;
    // 读取并处理标题行（如果有的话）
    if (!getline(file, line))
    {
        file.close();
        throw runtime_error("无法读取标题行: " + filename);
    }

    // 验证标题行是否正确
    if (!validateHeader(line))
    {
        file.close();
        throw runtime_error("标题行不正确: " + filename);
    }

    while (getline(file, line))
    {
        stringstream ss(line);
        string token;

        // 读取每列的内容
        vector<string> columns;
        while (getline(ss, token, ','))
        {
            columns.push_back(token);
        }

        if (columns.size() < 5)
        {
            throw runtime_error("数据行格式错误: " + filename);
        }

        string id = columns[0];
        string path = columns[1];
        string type = columns[2];
        bool needFlip = stoi(columns[3]);
        int FrameNum = stoi(columns[4]);

        if (type == "atlas")
        {
            Atlas* src_atlas = new Atlas();
            // 转换为 std::wstring
            std::wstring wpath = helper::stringToWstring(path);
            src_atlas->load_from_file(wpath.c_str(), FrameNum);
            for (int i = 0; i < src_atlas->get_size(); i++)
            {
                IMAGE* image = src_atlas->get_image(i);
                if (!helper::check_image_valid(image))
                {
                    delete src_atlas; // 清理已分配的资源
                    file.close();
                    throw runtime_error("图像验证失败: " + path);
                }
            }
            if (!needFlip)
            {
                atlas_pool[id] = src_atlas;
            }
            else
            {
                Atlas* dst_atlas = new Atlas();
                helper::flip_atlas(*src_atlas, *dst_atlas);
                delete src_atlas;
                atlas_pool[id] = dst_atlas;
            }


           
        }
        else if (type == "image")
        {
            IMAGE* src_image = new IMAGE();
            std::wstring wpath = helper::stringToWstring(path);
            loadimage(src_image, wpath.c_str());
            if (!helper::check_image_valid(src_image))
            {
                delete src_image; // 清理已分配的资源
                file.close();
                throw runtime_error("图像验证失败: " + path);
            }
            if (!needFlip)
            {
                image_pool[id] = src_image;
            }
            else
            {
                IMAGE* dst_image = new IMAGE();
                helper::flip_image(src_image, dst_image);
                delete src_image;
                image_pool[id] = dst_image;
            }
        }
        else
        {
            throw runtime_error("不支持的类型: " + type);
        }
    }
    file.close();
}



bool ResourcesManger::validateHeader(const std::string& header) const
{
    vector<string> expectedHeader = { "id", "path", "type","needFlip","FrameNum","Notes"};
    stringstream ss(header);
    string token;
    vector<string> headerColumns;

    while (getline(ss, token, ','))
    {
        headerColumns.push_back(token);
    }

    if (headerColumns.size() != expectedHeader.size())
    {
        return false;
    }

    for (size_t i = 0; i < expectedHeader.size(); ++i)
    {
        if (headerColumns[i] != expectedHeader[i])
        {
            return false;
        }
    }

    return true;
}



Atlas* ResourcesManger::find_atlas(const string& id) const
{
    const auto& itor = atlas_pool.find(id);
    if (itor == atlas_pool.end())
        return nullptr;

	return itor->second;
}


IMAGE* ResourcesManger::find_image(const string& id) const
{
    const auto& itor = image_pool.find(id);
    if (itor == image_pool.end())
        return nullptr;

    return itor->second;
}