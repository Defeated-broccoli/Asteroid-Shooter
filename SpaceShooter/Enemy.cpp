#include "Enemy.h"

void Enemy::initvariables()
{
	pointCount = rand() % 8 + 3;  //min 3, max 10
	type     = 0;
	hp       = hpMax;
	hpMax    = static_cast<int>(pointCount);
	damage   = pointCount;
	points   = pointCount;
	speed = static_cast<float>(pointCount)* 0.6;
}

void Enemy::initShape()
{
	shape.setRadius(pointCount * 4);
	shape.setPointCount(pointCount);
	shape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255, 255));
}

Enemy::Enemy(float pos_x, float pos_y)
{
	initvariables();
	initShape();

	shape.setPosition(pos_x, pos_y);

}

Enemy::~Enemy()
{
}

//Functions
void Enemy::update()
{
	shape.move(0.f, speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(shape);
}

sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Enemy::getPoints()
{
	return points;
}

const int& Enemy::getDamage() const
{
	return damage;
}


