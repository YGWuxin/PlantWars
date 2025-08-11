#pragma once

#include <vector>

using namespace std;

class Bullet;
class PeaBullet;
class Character;
class SunBullet;
class SunExBullet;
class BubbleBullet;
class BubbleExBullet;
class NutExplode;

class BulletPool
{

public:
    enum class BulletTyep 
    {
        PeaBullet,
        SunBullet,
        SunExBullet,
        BubbleBullet,
        BubbleExBullet,
        Explode,
    };

public:
    static BulletPool& GetInstance()
    {
        static BulletPool instance; // 静态局部变量，确保唯一性
        return instance;
    }

    // 删除拷贝构造函数和赋值运算符
    BulletPool(const BulletPool&) = delete;
    BulletPool& operator=(const BulletPool&) = delete;

    //初始化不同子弹对象池
    void InitPool(int num, BulletTyep type);

    //发射子弹
    Bullet* spawn_pea_bullet(Character* character, float speed);

    Bullet* spawn_sun_bullet(Character* character);

    Bullet* spawn_sun_ex_bullet(Character* character);

    Bullet* spawn_bubble_bullet(Character* character);

    Bullet* spawn_bubble_ex_bullet(Character* character);

    Bullet* spawn_explode(Character* character);

    //清空子弹对象池
    void clear_pool();

private:
    BulletPool() = default;    // 私有构造函数，防止外部创建实例
    ~BulletPool() = default;

private:
    vector<PeaBullet*> PeaBulletList;
    vector<SunBullet*> SunBulletList;
    vector<SunExBullet*> SunExBulletList;
    vector<BubbleBullet*> BubbleBulletList;
    vector<BubbleExBullet*> BubbleExBulletList;
    vector<NutExplode*> NutExplodeList;

};

