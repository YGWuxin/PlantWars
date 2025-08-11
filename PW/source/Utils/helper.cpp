#include "helper.h"
#include "../Res/atlas.h"
#include <graphics.h>	
#include "../Game/Camera.h"
#include "../Game/Vector2.h"


#pragma comment (lib,"winmm.lib") 
#pragma comment (lib,"Msimg32.lib") 

void helper::flip_image(IMAGE* src, IMAGE* dst) {
	//获取原图片的宽度和长度
	int w = src->getwidth();
	int h = src->getheight();

	Resize(dst, w, h);	//将原图片宽度和长度设置给目标图片

	//获取图片缓冲
	DWORD* src_buf = GetImageBuffer(src);
	DWORD* dst_buf = GetImageBuffer(dst);

	//进行翻转赋值
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			int idx_src = y * w + x;
			int idx_dst = y * w + (w - x - 1);
			dst_buf[idx_dst] = src_buf[idx_src];
		}
	}

};



void helper::flip_image(IMAGE* src, IMAGE* dst, int num_h) {
	//获取原图片的宽度和长度
	int w = src->getwidth();
	int h = src->getheight();
	int w_frame = w / num_h;

	Resize(dst, w, h);	//将原图片宽度和长度设置给目标图片

	//获取图片缓冲
	DWORD* src_buf = GetImageBuffer(src);
	DWORD* dst_buf = GetImageBuffer(dst);
	
	//进行翻转赋值
	for(int i = 0; i < num_h; i++)
	{
		int x_left = i * w_frame;
		int x_right = (i + 1) * w_frame;
		for (int y = 0; y < h; y++)
		{
			for (int x = x_left; x < x_right; x++)
			{
				int idx_src = y * w + x;
				int idx_dst = y * w + x_right - (x - x_left);
				dst_buf[idx_dst] = src_buf[idx_src];
			}
		}
	}
};


//翻转操作
void helper::flip_atlas(Atlas& src, Atlas& dst) {
	dst.clear();
	for (int i = 0; i < src.get_size(); i++)
	{
		IMAGE* img_flpipped = new IMAGE();
		flip_image(src.get_image(i), img_flpipped);
		dst.add_image(*img_flpipped);
	}
};

bool helper::check_image_valid(IMAGE* image)
{
	return GetImageBuffer(image);
}


void helper::putimage_alpha(int dst_x, int dst_y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();

	static BLENDFUNCTION belen_func = { AC_SRC_OVER,0,255,AC_SRC_ALPHA };

	AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, w, h,
		GetImageHDC(img), 0, 0, w, h, belen_func);
}

void helper::putimage_alpha(const Camera& camera, int dst_x, int dst_y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();


	Vector2 camera_position = camera.get_position();

	AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x + camera_position.x, dst_y + camera_position.y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}


void helper::putimage_ex(IMAGE* img, const Rect* rect_dst, const Rect* rect_src)
{
	static BLENDFUNCTION belen_func = { AC_SRC_OVER,0,255,AC_SRC_ALPHA };

	AlphaBlend(GetImageHDC(GetWorkingImage()), rect_dst->x, rect_dst->y, rect_dst->w, rect_dst->h,
		GetImageHDC(img), rect_src ? rect_src->x : 0, rect_src ? rect_src->y : 0, rect_src ? rect_src->w : img->getwidth(),
		rect_src ? rect_src->h : img->getheight(), belen_func);
}

void helper::putimage_ex(const Camera& camera,IMAGE* img, const Rect* rect_dst, const Rect* rect_src)
{
	static BLENDFUNCTION belen_func = { AC_SRC_OVER,0,255,AC_SRC_ALPHA };
	
	Vector2 camera_position = camera.get_position();


	AlphaBlend(GetImageHDC(GetWorkingImage()), rect_dst->x + camera_position.x, rect_dst->y + camera_position.y, rect_dst->w, rect_dst->h,
		GetImageHDC(img), rect_src ? rect_src->x : 0 , rect_src ? rect_src->y  : 0 ,
		rect_src ? rect_src->w : img->getwidth(),rect_src ? rect_src->h : img->getheight(), belen_func);
}


void helper::sketch_image(IMAGE* src, IMAGE* dst , S_RGB rgb)
{
	int w = src->getwidth();
	int h = src->getheight();
	Resize(dst,w,h);
	DWORD* src_buffer = GetImageBuffer(src);
	DWORD* dst_buffer = GetImageBuffer(dst);
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			int idx = y * w + x;
			dst_buffer[idx] = BGR(RGB(rgb.Red, rgb.Green, rgb.Blue) | (src_buffer[idx] & 0xFF000000));
		}
	}
}


std::wstring helper::stringToWstring(const std::string& str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.from_bytes(str);
}
