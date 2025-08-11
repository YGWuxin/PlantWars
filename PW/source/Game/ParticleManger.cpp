#include "ParticleManger.h"
#include "Particle.h"


void ParticleManger::on_update(float delta)
{
    //printf("Updating particles...\n");
    for (const auto& Particle : ParticleList)
    {
        if (!Particle)
        {
            //printf("Particle无效\r\n");
            continue;
        }

      //  printf("Particle valid at position (%f, %f)\n", Particle->get_position().x, Particle->get_position().y);

        if (Particle->check_valid())
            Particle->on_update(delta);
        else
        {
            removeParticleInstance(Particle);
            // printf("移除特效\r\n");
        }
    }

}


void ParticleManger::removeParticleInstance(std::shared_ptr<Particle> ParticleInstance)
{
    auto it = std::remove(ParticleList.begin(), ParticleList.end(), ParticleInstance);
    if (it != ParticleList.end())
    {
        ParticleList.erase(it, ParticleList.end());
    }
}




