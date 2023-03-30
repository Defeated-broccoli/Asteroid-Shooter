#pragma once
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include <iostream>

class Player
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	
	//Private Functions
	void initVariables();
	void initTexture();
	void initSprite();
	

	float movementSpeed;

	float attackCooldown;
	float attackCooldownMax;

	int hp;
	int hpMax;



public:
	Player();
	 ~Player();

	 //accessors
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const int& getHp() const;
	const int& getHpMax() const;




    const bool canAttack();

	//Modifieers
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);
	void setHp(const int hp);
	void loseHp(const int value);

	//Functions
	void update();
	void updateAttack();
	void render(sf::RenderTarget& target);
	void move(const float dirx, const float diry);




};

