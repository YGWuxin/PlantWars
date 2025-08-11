#pragma once

#include "vector"
#include <memory>
#include "CharacterEffect.h"


using namespace std;

class Particle;

class ParticleManger
{
public:
    static ParticleManger& getInstance()
    {
        static ParticleManger instance;
        return instance;
    }

    // 允许传递子类的特有参数
    template<typename T, typename... Args>
    std::shared_ptr<T> createParticleInstance(Args&&... args)
    {
        static_assert(std::is_base_of<Particle, T>::value, "T must derive from Sound");

        auto ParticleInstance = std::make_shared<T>(std::forward<Args>(args)...);
        ParticleList.push_back(ParticleInstance);
        return ParticleInstance;
    }

    void on_update(float delta);

    void removeParticleInstance(shared_ptr<Particle> ParticleInstance);

    void clearParticleList()
    {
        ParticleList.clear();
    }

private:
    ParticleManger() = default;
    ~ParticleManger() = default;

    vector<shared_ptr<Particle>> ParticleList;

};

