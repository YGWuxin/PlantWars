#include "CharacterEffect.h"
#include "ResourcesManger.h"


RunEffect::RunEffect(Vector2 position, int lifespan): Particle(position, lifespan)
{
	Atlas* atlas_effect_run =  ResourcesManger::GetInstance().find_atlas("atlas_effect_run");
	set_atlas(atlas_effect_run);
}


JumpEffect::JumpEffect(Vector2 position, int lifespan) : Particle(position, lifespan)
{
	Atlas* atlas_effect_jump = ResourcesManger::GetInstance().find_atlas("atlas_effect_jump");
	set_atlas(atlas_effect_jump);
}


LandEffect::LandEffect(Vector2 position, int lifespan) : Particle(position, lifespan)
{
	Atlas* atlas_effect_land = ResourcesManger::GetInstance().find_atlas("atlas_effect_land");
	set_atlas(atlas_effect_land);
}


