/*
*   植物明星大乱斗 -C++项目
*
*/


#pragma comment (lib,"winmm.lib") 

#include <graphics.h>								 //C++的Easyx图形库，需要安装
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


//引入命名空间
using namespace std;
using namespace std::chrono;
using namespace std::this_thread;


//操作信息
ExMessage msg;
HWND hwnd;

//帧率计时
const nanoseconds	frame_duration(1000000000 / GAME_FPS);
steady_clock::time_point	start_frame;
steady_clock::time_point	last_frame;


//函数声明
bool InitGame();


bool InitGame()
{


	//hwnd = initgraph(WIN_WIDTH, WIN_HIGH);		//创建窗口
	hwnd = initgraph(WIN_WIDTH, WIN_HIGH, EW_SHOWCONSOLE);		//创建窗口，显示控制台

	SceneManger& scene_manger = SceneManger::GetInstance();		//获取到场景管理器

	Scene* menu_scene = new MenuScene();						//创建菜单场景
	Scene* level1_scene = new Level1Scene();					//创建关卡1场景
	Scene* select_scene = new SelectScene();					//创建角色选择场景

	scene_manger.addSceneToMap(SceneManger::SceneType::Menu, menu_scene);				//将菜单场景添加到场景管理器中
	scene_manger.addSceneToMap(SceneManger::SceneType::Level1, level1_scene);			//将关卡1添加到场景管理器中
	scene_manger.addSceneToMap(SceneManger::SceneType::Select, select_scene);			//将角色选择场景添加到场景管理器中

	//AddFontResourceEx(_T("res/font/IPix.ttf"), FR_PRIVATE, NULL);			//加载字体

	try
	{
		ResourcesManger::GetInstance().loadAndValidate("res/data/resouces.csv");
	}
	catch (const std::runtime_error& e)
	{
		MessageBoxA(hwnd, e.what(), "资源加载失败", MB_OK | MB_ICONERROR);
		return false;
	}

	scene_manger.create_main_camera();								//创建主摄像机

	scene_manger.switch_to(SceneManger::SceneType::Menu);			//进入主菜单

	//设置字体
	settextstyle(28,0, _T("res/font/IPix.ttf"));
	setbkmode(TRANSPARENT);

	//创建玩家控制器
	PlayerControllerManger::GetInstance().create_player(PlayerControllerManger::PlayerType::Player_P1);
	PlayerControllerManger::GetInstance().create_player(PlayerControllerManger::PlayerType::Player_P2);

	last_frame = steady_clock::now();		//记录当前时间

	/*配置随机种子*/
	srand((unsigned int)time(NULL));

	return true;;
}

int main(int argc, char** argv) {

	if (!InitGame())					//初始化游戏
		return 0;


	BeginBatchDraw();				//开始双缓冲

	while (1) {

		/* 记录当前时间并进行间隔计算 */
		start_frame = steady_clock::now();
		duration<float>	delta = duration<float>(start_frame - last_frame);

		SceneManger& scene_manger = SceneManger::GetInstance();		//获取场景管理器

		//检查用户按键输入
		while (peekmessage(&msg))
		{
			scene_manger.on_input(msg);
		}

		static DWORD  last_tick_time = GetTickCount();
		DWORD current_tick_time = GetTickCount();
		DWORD delta_tick = current_tick_time - last_tick_time;

		scene_manger.on_update(delta_tick);							//更新游戏数据

		last_tick_time = current_tick_time;

		cleardevice();						//清空屏幕

		scene_manger.on_draw();				//渲染图形

		FlushBatchDraw();					//将缓冲写入屏幕

		//强制锁帧，保证性能
		last_frame = start_frame;
		nanoseconds	sleep_duration = frame_duration - (steady_clock::now() - start_frame);
		if (sleep_duration > nanoseconds(0))
			sleep_for(sleep_duration);

	}

	EndBatchDraw();					//结束双缓冲
	return 0;
}

