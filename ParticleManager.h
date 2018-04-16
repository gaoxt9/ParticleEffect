#pragma once
#include "particleConfigur.h"
#include "ParticleSystem.h"
#include "SFMLHeader.h"

class ParticleManager
{
public:
	ParticleManager();
	~ParticleManager();

	ParticleSystem* addNewSystem(Vector2f);
	void increaseAllMaxNum();
	void decreaseAllMaxNum();
	void drawWholeSystem(RenderWindow*);
	void updateWholeSystem(float);

	void deleteAllSystems();

	void addNewSystemBySceneId(int);

	int getWholeParticleNum();
private:
	vector<ParticleSystem*> childSystems;
	vector<Texture> textureArray;
	int curTextIndex;

	int getInitAngleByPos(Vector2f);
};

