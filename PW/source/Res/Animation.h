#pragma once

#include "../Utils/Timer.h"
#include "../Utils/helper.h"
#include "../Game/Vector2.h"
#include <vector>
#include <functional>
#include "atlas.h"
#include <cstdio>
#include "../Game/Camera.h"
#include "../Parameter/GlobeGameParameters.h"


using namespace std;

class Animation
{
public:
	Animation() 
	{
		timer.set_one_shot(false);
		timer.set_callback([&]() 
			{
				idx_frame++;
				if (idx_frame >= frame_list.size())
				{
					idx_frame = is_loop ? 0 : frame_list.size() - 1;
					if (!is_loop && on_finished)
						on_finished();
				}
			});
	};

	~Animation() = default;


	inline void reset()
	{
		timer.restart();
		idx_frame = 0;
		resume_animation();
	}

	inline void set_anchor_mode(AnchorMode mode)
	{
		anchor_mode = mode;
	}

	inline void set_loop(bool val)
	{
		this->is_loop = val;
	}

	inline void set_interval(float interval)
	{
		timer.set_wait_time(interval);
	}

	inline void set_on_finished_callback(function<void()> on_finished)
	{
		this->on_finished = on_finished;
	}

	inline IMAGE* get_current_frame_image()
	{
		if (frame_list.empty())
			return nullptr;
		const Frame& frame = frame_list[idx_frame];
		return frame.image;
	}


	inline Rect get_current_frame_rect_src()
	{
		if (frame_list.empty())
			return { 0,0,0,0 };
		const Frame& frame = frame_list[idx_frame];
		return frame.rect_src;
	}


	inline void add_animation(IMAGE* image, int num_h)
	{
		if (!frame_list.empty())
			return;
		if (image == nullptr)
			return;
		int w = image->getwidth();
		int h = image->getheight();
		int w_frame = w / num_h;
		for (int i = 0; i < num_h; i++)
		{
			Rect rect_scr;
			rect_scr.x = i * w_frame;
			rect_scr.y = 0;
			rect_scr.w = w_frame;
			rect_scr.h = h;

			frame_list.emplace_back(image,rect_scr);
		}
	}

	inline void add_animation(Atlas* atlas)
	{
		if (!frame_list.empty())
			return;
		if (atlas == nullptr)
		{
			printf("atlasŒ™ø’÷∏’Î\r\n");
			return;
		}
		int w = 0;
		int h = 0;
		for (int i = 0; i < atlas->get_size(); i++)
		{
			IMAGE* image = atlas->get_image(i);
			if(image == nullptr)
				continue;
			w = image->getwidth();
			h = image->getheight();
			Rect rect_src;
			rect_src.w = w, rect_src.h = h;
			rect_src.x = 0; rect_src.y = 0;
			frame_list.emplace_back(image, rect_src);
		}
	}

	inline void remove_animation()
	{
		if (frame_list.empty())
			return;
		frame_list.clear();
	}

	inline void on_update(float delta)
	{
		if (paused)
			return;
		timer.on_update(delta);
	}


	inline void pause_animation()
	{
		paused = true;
	}

	inline void resume_animation()
	{
		paused = false;
	}

private:
	struct Frame
	{
		Rect rect_src;
		IMAGE* image = nullptr;
		Frame() = default;
		Frame(IMAGE* image, const Rect& rect_src)
			: image(image), rect_src(rect_src){}

		~Frame() = default;
	};


private:
	Timer timer;
	bool is_loop = true;
	size_t idx_frame = 0;
	vector<Frame> frame_list;
	function<void()> on_finished;
	AnchorMode anchor_mode = AnchorMode::Centered;
	bool paused = false;			// «∑Ò‘›Õ£

};



