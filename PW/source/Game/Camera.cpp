#include "Camera.h"

Camera::Camera()
{
	timer_shake.set_one_shot(true);
	timer_shake.set_callback([&]() {
		is_shakeing = false;
		reset();
		});
}

void Camera::reset()
{
	this->position.x = 0;
	this->position.y = 0;
}

void Camera::Shake(float strenth, int duration, float frq)
{
	is_shakeing = true;
	this->frq = frq;
	frq_temp = 0;
	shakeing_strength = strenth;
	timer_shake.set_wait_time(duration);
	timer_shake.restart();
}


void Camera::on_update(int delta)
{
	timer_shake.on_update(delta);
	if (is_shakeing && (frq_temp >= frq))
	{
		position.x = (-50 + rand() % 100) / 50.0f * shakeing_strength;
		position.y = (-50 + rand() % 100) / 50.0f * shakeing_strength;
		frq_temp = 0;
	}
	frq_temp += delta;
}
