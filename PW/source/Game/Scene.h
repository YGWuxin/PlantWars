#pragma once

#include <graphics.h>



//��������
class Scene
{
public:
	Scene() = default;
	~Scene() = default;

	virtual void on_enter() {};							//�������غ���
	virtual void on_update(int delta) {};				//��������Ϸ���ݸ��º���
	virtual void on_input(const ExMessage &msg) {};		//�û����뺯��
	virtual void on_exit() {};							//����ж�غ���

private:
	
};





