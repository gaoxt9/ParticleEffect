#include <SFML/Graphics.hpp>
#include <time.h>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <cstring>
#include <iostream>

using namespace sf;

int windowWidth = 2200;
int windowHeight = 1500;

class ParticleBehavior
{
public:
	virtual float behavior(sf::Time currT, sf::Time totalT, float k, float b) = 0;
};

class LinearGrow : public ParticleBehavior
{
public:
	virtual float behavior(sf::Time currT, sf::Time totalT, float k, float b) 
	{
		return k * (totalT.asSeconds() + currT.asSeconds()) / totalT.asSeconds() + b;
	}
};

class LinearShrink : public ParticleBehavior
{
public:
	virtual float behavior(sf::Time currT, sf::Time time, float k, float b) 
	{
		float res = -k * (currT.asSeconds() - time.asSeconds()) / time.asSeconds() + b;
		if (res < 0) return 0;
		return res;
	}
};


////////////////////////////////////////////////////////////////////////
class EaseInOutCubic : public ParticleBehavior
{
public:
	virtual float behavior(sf::Time currT, sf::Time totalT, float k, float b) 
	{
		float tt = currT.asSeconds();
		tt /= b / 2;
		if (tt < 1) return k / 2 *tt*tt*tt + tt;
		tt -= 2;
		return k / 2 * (tt*tt*tt + 2) + b;
	}
};


class BounceEaseOut : public ParticleBehavior
{
public:
	virtual float behavior(sf::Time currT, sf::Time totalT, float k, float b)
	{
		float p = totalT.asSeconds() - currT.asSeconds();
		p /= totalT.asSeconds();
		if (p < 4 / 11.0)
		{
			return (121 * p * p) / 16.0 *k + b;
		}
		else if (p < 8 / 11.0)
		{
			return ((363 / 40.0 * p * p) - (99 / 10.0 * p) + 17 / 5.0)*k + b;
		}
		else if (p < 9 / 10.0)
		{
			return ((4356 / 361.0 * p * p) - (35442 / 1805.0 * p) + 16061 / 1805.0)*k + b;
		}
		else
		{
			return ((54 / 5.0 * p * p) - (513 / 25.0 * p) + 268 / 25.0)*k + b;
		}
	}
};

class ElasticEaseIn : public ParticleBehavior
{
public:
	virtual float behavior(sf::Time currT, sf::Time totalT, float k, float b)
	{
		float p = totalT.asSeconds() - currT.asSeconds();
		p /= totalT.asSeconds();
		return sin(13 * 3.14 * p) * pow(2, 10 * (p - 1)) * k;
	}
};

class ParticleManager
{
public:
	ParticleManager(unsigned int amount):
		amount(amount)
	{

	}

	void addParticleSystem()
	{
		for (size_t i = 0; i < amount; i++)
		{

		}
	}
	void rmParticleSystem()
	{
	}
	void update()
	{
}
private:
	unsigned int amount;
	//ParticleSystem theSystem;

};

class ParticleSystem
{
private:
	void resetParticle(std::size_t index)
	{
		float angle = -3.14f / 2 - angleRange*3.14f + (std::rand() % 360)*3.14f*angleRange / 180.f;
		float speed = (std::rand() % 50) + 50.f;

		particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
		particles[index].currTime = sf::milliseconds((std::rand() % 2000) + 1000);
		particles[index].sprite.setPosition(emitter);
	}

	sf::Time lifetime;
	sf::Vector2f emitter;
	sf::Texture texture;
	float angleRange, textureScale;
	ParticleBehavior *scaleBehavior, *speedBehavior, *rotationBehavior;

public:
	ParticleSystem(unsigned int count, sf::Time lifetime, sf::Vector2f emitter, float textureScale, float angle):
		count(count),
		particles(0),
		lifetime(lifetime),
		emitter(emitter),
		textureScale(textureScale),
		angleRange(angle),
		scaleBehavior(nullptr),
		speedBehavior(nullptr),
		rotationBehavior(nullptr)
	{
	}

	int count;

	struct Particle
	{
		sf::Sprite sprite;
		sf::Vector2f velocity;
		sf::Time currTime;
	};

	std::vector<Particle> particles;

	void setEmitter(sf::Vector2f position)
	{
		emitter = position;
	}

	bool setTexture(const std::string& texturefile)
	{
		if (!texture.loadFromFile(texturefile))
			return false;
	}

	void addParticle(int count) 
	{
		for (int i = 0; i < count; i++) 
		{
			Particle particleToAdd;
			float angle = -3.14f / 2 - angleRange*3.14f + (std::rand() % 360)*3.14f*angleRange / 180.f;
			float speed = (std::rand() % 50) + 150.f;//+50

			particleToAdd.sprite.setTexture(texture);
			particleToAdd.sprite.setPosition(emitter);
			particleToAdd.sprite.setScale(textureScale, textureScale);
			particleToAdd.sprite.setOrigin(particleToAdd.sprite.getLocalBounds().width / 2, particleToAdd.sprite.getLocalBounds().height / 2);
			
			particleToAdd.velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
			particleToAdd.currTime = sf::milliseconds((std::rand() % 2000) + 1000);//(std::rand() % 2000) + 1000
			particles.push_back(particleToAdd);
		}
	}

	void deleteParticle(int count) 
	{
		for (unsigned int i = count; count >= 0; count--)
		{
			if (particles.empty()) 
			{
				return;
			}
			std::vector<Particle>::iterator itr = particles.begin();
			particles.erase(itr);
		}
	}

	void update(sf::Time elapsed)
	{
		for (std::size_t i = 0; i < particles.size(); ++i)
		{
			Particle& p = particles[i];
			p.currTime -= elapsed;
			if (p.currTime <= sf::Time::Zero)
				resetParticle(i);

			float velocityFactor = 1;
			if (speedBehavior != nullptr) 
			{
				velocityFactor = speedBehavior->behavior(p.currTime, lifetime, 20, 0.01);
			}
			p.sprite.setPosition(p.sprite.getPosition() + p.velocity * elapsed.asSeconds() * velocityFactor);

			if (scaleBehavior != nullptr) 
			{
				float newScale = scaleBehavior->behavior(p.currTime, lifetime, 0.8, textureScale);
				p.sprite.setScale(newScale, newScale);
			}

			if (rotationBehavior != nullptr) 
			{
				float newAngle = rotationBehavior->behavior(p.currTime, lifetime, 360, 0);
				p.sprite.setRotation(newAngle);
			}
		}
	}

	void setScaleBehavior(std::string type) 
	{
		if (type == "linearGrow") 
		{
			scaleBehavior = new LinearGrow();
		}
		else if (type == "linearShrink") 
		{
			scaleBehavior = new LinearShrink();
		}
		else if (type == "EaseInOutCubic") 
		{
			scaleBehavior = new EaseInOutCubic();
		}
		else if (type == "BounceEaseOut") 
		{
			scaleBehavior = new BounceEaseOut();
		}
		else if (type == "ElasticEaseIn") 
		{
			scaleBehavior = new ElasticEaseIn();
		}
	}

	void setSpeedBehavior(std::string type) 
	{
		if (type == "linearGrow") 
		{
			speedBehavior = new LinearGrow();
		}
		else if (type == "linearShrink") 
		{
			speedBehavior = new LinearShrink();
		}
		else if (type == "EaseInOutCubic") 
		{
			speedBehavior = new EaseInOutCubic();
		}
		else if (type == "BounceEaseOut") 
		{
			speedBehavior = new BounceEaseOut();
		}
		else if (type == "ElasticEaseIn") 
		{
			speedBehavior = new ElasticEaseIn();
		}
	}

	void setRotateBehaviour(std::string type) 
	{
		if (type == "linearGrow") 
		{
			rotationBehavior = new LinearGrow();
		}
		else if (type == "linearShrink") 
		{
			rotationBehavior = new LinearShrink();
		}
		else if (type == "EaseInOutCubic") 
		{
			rotationBehavior = new EaseInOutCubic();
		}
		else if (type == "BounceEaseOut") 
		{
			rotationBehavior = new BounceEaseOut();
		}
		else if (type == "ElasticEaseIn") 
		{
			rotationBehavior = new ElasticEaseIn();
		}
	}
};



int main()
{
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Particle System");

	ParticleManager theManager(2);

	ParticleSystem tennisP(20, sf::seconds(5), sf::Vector2f(windowWidth / 8, windowHeight / 2), 0.2, 0.1);
	tennisP.setTexture("tennis.png");
	tennisP.addParticle(tennisP.count);
	tennisP.setSpeedBehavior("linearGrow");

	ParticleSystem snowP(10, sf::seconds(5), sf::Vector2f(windowWidth / 3, windowHeight / 2), 0.2, 0.1);
	snowP.setTexture("snow.png");
	snowP.addParticle(snowP.count);
	snowP.setSpeedBehavior("linearShrink");

	ParticleSystem lightning(20, sf::seconds(5), sf::Vector2f(windowWidth / 2.2, windowHeight / 2), 0.8, 0.1);
	lightning.setTexture("lightning.png");
	lightning.addParticle(lightning.count);
	lightning.setRotateBehaviour("ElasticEaseIn");


	ParticleSystem ink(5, sf::seconds(2), sf::Vector2f(windowWidth / 1.6, windowHeight / 1.05), 0.1, 0.2);
	ink.setTexture("ink.png");
	ink.addParticle(ink.count);
	ink.setScaleBehavior("ElasticEaseIn");
	ink.setSpeedBehavior("linearShrink");

	ParticleSystem fog(5, sf::seconds(2), sf::Vector2f(windowWidth / 1.2, windowHeight / 1.05), 0.1, 0.2);
	fog.setTexture("fog.png");
	fog.addParticle(ink.count);
	fog.setScaleBehavior("EaseInOutCubic");

	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
		{
			tennisP.addParticle(1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
		{
			tennisP.deleteParticle(1);
		}

		sf::Time elapsed = clock.restart();
		tennisP.update(elapsed);
		snowP.update(elapsed);
		lightning.update(elapsed);
		ink.update(elapsed);
		fog.update(elapsed);

		window.clear();

		// draw different particles
		for (unsigned int i = 0; i < tennisP.particles.size(); i++)
		{
			window.draw(tennisP.particles[i].sprite);
		}
		for (unsigned int i = 0; i < snowP.particles.size(); i++) 
		{
			window.draw(snowP.particles[i].sprite);
		}
		for (unsigned int i = 0; i < lightning.particles.size(); i++)
		{
			window.draw(lightning.particles[i].sprite);
		}
		for (unsigned int i = 0; i < ink.particles.size(); i++) 
		{
			window.draw(ink.particles[i].sprite);
		}
		for (unsigned int i = 0; i < ink.particles.size(); i++)
		{
			window.draw(fog.particles[i].sprite);
		}

		window.display();
	}

	return 0;
}