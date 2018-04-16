#include "ParticleManager.h"

ParticleManager::ParticleManager()
{
	for (int i = 1; i <= TEXTURE_NUM; i++)
	{
		Texture tempTexture;
		tempTexture.loadFromFile("P" + to_string(i) + ".png");
		textureArray.push_back(tempTexture);
	}

	curTextIndex = 0;
}

ParticleManager::~ParticleManager()
{
	deleteAllSystems();
}

void ParticleManager::deleteAllSystems()
{
	int sysNum = childSystems.size();
	for (int i = sysNum - 1; i >= 0; i--)
	{
		delete childSystems[i];
		childSystems.erase(childSystems.begin() + i);
	}
}

void ParticleManager::addNewSystemBySceneId(int sceneId)
{
	if (sceneId == 0)
	{
		return;
	}

	int startIndex = _SceneStartIndex[sceneId - 1];
	for (int i = 0; i < _SceneLength[sceneId - 1]; i++)
	{
		ConfigueStruct temp = _ConfigueArray[startIndex + i];
		ParticleSystem *newSystem = addNewSystem(temp.cPos);
		if (temp.cChangeType != NO_CHANGE)
		{
			newSystem->setAStrategy(temp.cChangeType, temp.cStrategyType, temp.cA, temp.cB);
		}
	}
}

int ParticleManager::getWholeParticleNum()
{
	int curNum = 0;
	for (int i = 0; i < childSystems.size(); i++)
	{
		curNum = curNum + childSystems[i]->getParticleNum();
	}
	return curNum;
}

int ParticleManager::getInitAngleByPos(Vector2f pos)
{
	int startAngle = 0;
	if (pos.y <= WIN_HEIGHT / 2)
	{
		if (pos.x < WIN_WIDTH / 2)
		{
			startAngle = 150;
		}
		else
		{
			startAngle = 240;
		}
	}
	else
	{
		if (pos.x <= WIN_WIDTH / 2)
		{
			startAngle = 60;
		}
		else
		{
			startAngle = 30;
		}
	}

	return startAngle;
}

ParticleSystem* ParticleManager::addNewSystem(Vector2f pos)
{
	int randomTex = (curTextIndex++) % TEXTURE_NUM;
	int randomSpeed = 70 + rand() % 20;
	int randomBeginAngle = getInitAngleByPos(pos) + rand() % 30;
	int randomAngleRange = 60 + rand() % 60;
	int randomMaxNum = 10 + rand() % 15;
	int randomWidth = 50;

	ParticleSystem *newSystem = new ParticleSystem(pos, randomSpeed, Vector2f(randomBeginAngle - randomAngleRange, randomBeginAngle),
		&textureArray[randomTex], randomMaxNum, Vector2f(randomWidth, randomWidth));
	childSystems.push_back(newSystem);

	return newSystem;
}

void ParticleManager::increaseAllMaxNum()
{
	for (int i = 0; i < childSystems.size(); i++)
	{
		childSystems[i]->increaseMaxNum();
	}
}

void ParticleManager::decreaseAllMaxNum()
{
	for (int i = 0; i < childSystems.size(); i++)
	{
		childSystems[i]->decreaseMaxNum();
	}
}

void ParticleManager::drawWholeSystem(RenderWindow* window)
{
	for (int i = 0; i < childSystems.size(); i++)
	{
		childSystems[i]->drawAllParticles(window);
	}
}

void ParticleManager::updateWholeSystem(float dt)
{
	for (int i = 0; i < childSystems.size(); i++)
	{
		childSystems[i]->updateParticles(dt);
	}
}