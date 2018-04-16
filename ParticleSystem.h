#pragma once

#include "SFMLHeader.h"
#include "Particle.h"

class ParticleSystem
{
public:
	ParticleSystem(Vector2f, float, Vector2f, Texture*, int, Vector2f);
	~ParticleSystem();
	void updateParticles(float);
	void increaseMaxNum()
	{
		maxNum = maxNum + 5;
	}
	void decreaseMaxNum()
	{
		maxNum = maxNum - 5;

		maxNum = (maxNum < 5) ? 5 : maxNum;
	}
	void drawAllParticles(RenderWindow*);

	void setAStrategy(int, int, float, float);

	int getParticleNum()
	{
		return childParcitle.size();
	}
private:
	Vector2f bornPoint;
	float velocity;
	Vector2f emitAngleRange;
	Texture* texture;
	int maxNum;
	Vector2f size;

	int changeType;
	int strategyType;
	float strategyPA;
	float strategyPB;

	vector<Particle*> childParcitle;
	//void setParticleStrategy(Particle*);

	void createNewParticle();
};