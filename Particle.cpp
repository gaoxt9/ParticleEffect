#include "Particle.h"

Particle::Particle(float pV, Vector2f angleVec)
{
	velocity = pV;
	angle = randomFloat(angleVec.x, angleVec.y);
	float radian = PI * angle / 180;
	direction = Vector2f(sin(radian), -cos(radian));
	lifetime = randomFloat(0.1, RANDOM_LTL);
	curTime = 0;
	isDeadBool = false;

	//sizeStrategy = NULL;
	//velocityStrategy = NULL;
	//rotationStrategy = NULL;
}

//Particle::~Particle()
//{
//	if (velocityStrategy != NULL)
//	{
//		delete velocityStrategy;
//		velocityStrategy = NULL;
//	}
//
//	if (rotationStrategy != NULL)
//	{
//		delete rotationStrategy;
//		rotationStrategy = NULL;
//	}
//
//	if (sizeStrategy != NULL)
//	{
//		delete sizeStrategy;
//		sizeStrategy = NULL;
//	}
//}

void Particle::updateParticle(float dt)
{
	//if (velocityStrategy != NULL)
	//{
	//	velocity = velocityStrategy->executeStrategy(curTime / lifetime);
	//}

	//if (sizeStrategy != NULL)
	//{
	//	float newScale = sizeStrategy->executeStrategy(curTime / lifetime);
	//	setScale(Vector2f(newScale, newScale));
	//}

	//if (rotationStrategy != NULL)
	//{
	//	setRotation(rotationStrategy->executeStrategy(curTime / lifetime));
	//}

	setPosition(getPosition() + velocity * direction * dt);

	curTime = curTime + dt;
	float remainTime = lifetime - curTime;

	if (remainTime <= 0)
	{
		isDeadBool = true;
	}
}

float Particle::randomFloat(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

//StrategyBase* Particle::chooseStrategy(int pType, float a, float b)
//{
//	if (pType == LINEAR_S)
//	{
//		return new LinearStrategy(a, b);
//	}
//	else if (pType == EASE_OUT_S)
//	{
//		return new EaseOutStrategy(a, b);
//	}
//	else if (pType == EASE_IN_S)
//	{
//		return new EaseInStrategy(a, b);
//	}
//	else if (pType == SIN_S)
//	{
//		return new SinStrategy(a, b);
//	}
//	else
//	{
//		return NULL;
//	}
//}

//void Particle::setSizeStrategy(int pType, float a, float b)
//{
//	sizeStrategy = chooseStrategy(pType, a, b);
//}
//
//void Particle::setVelocityStrategy(int pType, float a, float b)
//{
//	velocityStrategy = chooseStrategy(pType, a, b);
//}
//
//void Particle::setRotationStrategy(int pType, float a, float b)
//{
//	rotationStrategy = chooseStrategy(pType, a, b);
//}