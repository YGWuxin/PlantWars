#pragma once

#include <graphics.h>	
#include "../Parameter/GlobeGameParameters.h"
#include <locale>
#include <codecvt>


class Atlas;
class Camera;

struct  Rect
{
	int x, y;
	int w, h;
};

class helper
{
public:
	helper() = default;
	~helper() = default;


	static void flip_image(IMAGE* src, IMAGE* dst);
	static void flip_image(IMAGE* src, IMAGE* dst,int num_h);

	static void flip_atlas(Atlas& src, Atlas& dst);
	static bool check_image_valid(IMAGE* image);

	static void putimage_alpha(int dst_x,int dst_y,IMAGE* img);
	static void putimage_alpha(const Camera& camera,int dst_x, int dst_y, IMAGE* img);
	static void putimage_ex(IMAGE* img, const Rect* rect_dst, const Rect* rect_src = nullptr);
	static void putimage_ex(const Camera& camera,IMAGE* img, const Rect* rect_dst, const Rect* rect_src = nullptr);

	static void sketch_image(IMAGE* src,IMAGE* dst,S_RGB rgb);

	static std::wstring stringToWstring(const std::string& str);

private:

};

