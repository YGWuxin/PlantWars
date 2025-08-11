/*
*   ֲ�����Ǵ��Ҷ� -C++��Ŀ
*
*/


#pragma comment (lib,"winmm.lib") 

#include <graphics.h>								 //C++��Easyxͼ�ο⣬��Ҫ��װ
#include <chrono>
#include <thread>
#include "Parameter/GlobeGameParameters.h"
#include "Utils/helper.h"
#include "Game/SelectScene.h"
#include "Game/MenuScene.h"
#include "Game/Level1Scene.h"
#include "Game/Scene.h"
#include "Game/SceneManger.h"
#include "Game/ResourcesManger.h"
#include "Game/AudioManger.h"
#include "Game/Camera.h"
#include "Game/PlayerControllerManger.h"
#include "Game/AudioManger.h"


//���������ռ�
using namespace std;
using namespace std::chrono;
using namespace std::this_thread;


//������Ϣ
ExMessage msg;
HWND hwnd;

//֡�ʼ�ʱ
const nanoseconds	frame_duration(1000000000 / GAME_FPS);
steady_clock::time_point	start_frame;
steady_clock::time_point	last_frame;


//��������
bool InitGame();


bool InitGame()
{


	//hwnd = initgraph(WIN_WIDTH, WIN_HIGH);		//��������
	hwnd = initgraph(WIN_WIDTH, WIN_HIGH, EW_SHOWCONSOLE);		//�������ڣ���ʾ����̨

	SceneManger& scene_manger = SceneManger::GetInstance();		//��ȡ������������

	Scene* menu_scene = new MenuScene();						//�����˵�����
	Scene* level1_scene = new Level1Scene();					//�����ؿ�1����
	Scene* select_scene = new SelectScene();					//������ɫѡ�񳡾�

	scene_manger.addSceneToMap(SceneManger::SceneType::Menu, menu_scene);				//���˵�������ӵ�������������
	scene_manger.addSceneToMap(SceneManger::SceneType::Level1, level1_scene);			//���ؿ�1��ӵ�������������
	scene_manger.addSceneToMap(SceneManger::SceneType::Select, select_scene);			//����ɫѡ�񳡾���ӵ�������������

	//AddFontResourceEx(_T("res/font/IPix.ttf"), FR_PRIVATE, NULL);			//��������

	try
	{
		ResourcesManger::GetInstance().loadAndValidate("res/data/resouces.csv");
	}
	catch (const std::runtime_error& e)
	{
		MessageBoxA(hwnd, e.what(), "��Դ����ʧ��", MB_OK | MB_ICONERROR);
		return false;
	}

	scene_manger.create_main_camera();								//�����������

	scene_manger.switch_to(SceneManger::SceneType::Menu);			//�������˵�

	//��������
	settextstyle(28,0, _T("res/font/IPix.ttf"));
	setbkmode(TRANSPARENT);

	//������ҿ�����
	PlayerControllerManger::GetInstance().create_player(PlayerControllerManger::PlayerType::Player_P1);
	PlayerControllerManger::GetInstance().create_player(PlayerControllerManger::PlayerType::Player_P2);

	last_frame = steady_clock::now();		//��¼��ǰʱ��

	/*�����������*/
	srand((unsigned int)time(NULL));

	return true;;
}

int main(int argc, char** argv) {

	if (!InitGame())					//��ʼ����Ϸ
		return 0;


	BeginBatchDraw();				//��ʼ˫����

	while (1) {

		/* ��¼��ǰʱ�䲢���м������ */
		start_frame = steady_clock::now();
		duration<float>	delta = duration<float>(start_frame - last_frame);

		SceneManger& scene_manger = SceneManger::GetInstance();		//��ȡ����������

		//����û���������
		while (peekmessage(&msg))
		{
			scene_manger.on_input(msg);
		}

		static DWORD  last_tick_time = GetTickCount();
		DWORD current_tick_time = GetTickCount();
		DWORD delta_tick = current_tick_time - last_tick_time;

		scene_manger.on_update(delta_tick);							//������Ϸ����

		last_tick_time = current_tick_time;

		cleardevice();						//�����Ļ

		scene_manger.on_draw();				//��Ⱦͼ��

		FlushBatchDraw();					//������д����Ļ

		//ǿ����֡����֤����
		last_frame = start_frame;
		nanoseconds	sleep_duration = frame_duration - (steady_clock::now() - start_frame);
		if (sleep_duration > nanoseconds(0))
			sleep_for(sleep_duration);

	}

	EndBatchDraw();					//����˫����
	return 0;
}

