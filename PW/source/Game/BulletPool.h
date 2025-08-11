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
        static BulletPool instance; // ��̬�ֲ�������ȷ��Ψһ��
        return instance;
    }

    // ɾ���������캯���͸�ֵ�����
    BulletPool(const BulletPool&) = delete;
    BulletPool& operator=(const BulletPool&) = delete;

    //��ʼ����ͬ�ӵ������
    void InitPool(int num, BulletTyep type);

    //�����ӵ�
    Bullet* spawn_pea_bullet(Character* character, float speed);

    Bullet* spawn_sun_bullet(Character* character);

    Bullet* spawn_sun_ex_bullet(Character* character);

    Bullet* spawn_bubble_bullet(Character* character);

    Bullet* spawn_bubble_ex_bullet(Character* character);

    Bullet* spawn_explode(Character* character);

    //����ӵ������
    void clear_pool();

private:
    BulletPool() = default;    // ˽�й��캯������ֹ�ⲿ����ʵ��
    ~BulletPool() = default;

private:
    vector<PeaBullet*> PeaBulletList;
    vector<SunBullet*> SunBulletList;
    vector<SunExBullet*> SunExBulletList;
    vector<BubbleBullet*> BubbleBulletList;
    vector<BubbleExBullet*> BubbleExBulletList;
    vector<NutExplode*> NutExplodeList;

};

