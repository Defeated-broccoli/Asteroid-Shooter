#pragma once

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include <iostream>


class Bullet
{
private:

	sf::Sprite shape;
	
	sf::Vector2f direction;
	float movementSpeed;
	
	
public:
	Bullet();
	Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float movementSpeed);
	~Bullet();

	//Accessor
	sf::FloatRect getBounds() const;

	void update();
	void render(sf::RenderTarget* target);
};

