#pragma once

#include <functional>

using namespace std;

class Timer
{
public:
	Timer() = default;
	~Timer() = default;

	inline void restart();

	inline void set_wait_time(int value);

	inline void set_one_shot(bool flag);

	inline void set_callback(function<void()> callback);

	inline void pause();

	inline void resume();

	inline void on_update(int delta);

private:
	int pass_time = 0;				//�Ѿ���ȥ��ʱ��
	int wait_time = 0;				//�ȴ�ʱ��
	bool paused = false;			//�Ƿ���ͣ
	bool shotted = false;			//�Ƿ񴥷�
	bool ont_shot = false;			//�Ƿ�Ϊ���δ���
	function<void()> callback;		//�����ص�

};


//���ö�ʱ��
void Timer::restart()
{
	pass_time = 0;
	shotted = false;
}

//���õȴ�ʱ��
void Timer::set_wait_time(int value)
{
	wait_time = value;
}

//�����Ƿ�Ϊ���δ���
void Timer::set_one_shot(bool flag)
{
	ont_shot = flag;
}

//���ûص�����
void Timer::set_callback(function<void()> callback)
{
	this->callback = callback;
}

//��ͣ��ʱ��
void Timer::pause()
{
	paused = true;
}

//�ָ���ʱ��
void Timer::resume()
{
	paused = false;
}


void Timer::on_update(int delta)
{
	if (paused)
		return;
	pass_time += delta;
	if (pass_time > wait_time)
	{
		if ((!ont_shot || (ont_shot && !shotted)) && callback)
			callback();
		shotted = true;
		pass_time = 0;
	}
}



