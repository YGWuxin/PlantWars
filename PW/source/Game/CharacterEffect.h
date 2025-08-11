#pragma once
#include "Particle.h"


class RunEffect : public Particle
{

public:
	RunEffect(Vector2 position, int lifespan);
	~RunEffect() = default;

};


class JumpEffect : public Particle
{

public:
	JumpEffect(Vector2 position, int lifespan);
	~JumpEffect() = default;

};


class LandEffect : public Particle
{

public:
	LandEffect(Vector2 position, int lifespan);
	~LandEffect() = default;
};

