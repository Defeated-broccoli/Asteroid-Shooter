#pragma once

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include <iostream>

class Enemy
{
private:
	sf::CircleShape shape;
	
	unsigned int pointCount;
	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;


	void initvariables();
	void initShape();


public:

	//Constr and Destr
	Enemy(float pos_x, float pos_y);
	~Enemy();

	//Functions
	void update();
	void render(sf::RenderTarget* target);

	//Accessors
	sf::FloatRect getBounds() const;
	const int& getPoints();
	const int& getDamage() const;
};

