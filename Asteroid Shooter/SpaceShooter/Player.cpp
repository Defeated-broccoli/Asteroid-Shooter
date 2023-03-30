#include "Player.h"

void Player::initVariables()
{
	movementSpeed = 5.f;
	attackCooldownMax = 15.f;
	attackCooldown = attackCooldownMax;

	hpMax = 100;
	hp = hpMax;
}

void Player::initTexture()
{
	//load the texture from file
	if (!texture.loadFromFile("images/player.png"))
	{
		std::cout << "Loading texture failed for player" << std::endl;
	}
}

void Player::initSprite()
{
	//set sprite for texture
	sprite.setTexture(texture);

	//resize sprite
	sprite.scale(1.f, 1.f);
}



Player::Player()
{
	movementSpeed = 5.f;

	
	initVariables();
	initTexture();
	initSprite();
}

Player::~Player()
{
}

const sf::Vector2f& Player::getPos() const
{
	return sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return sprite.getGlobalBounds();
}

const int& Player::getHp() const
{
	return hp;
}

const int& Player::getHpMax() const
{
	return hpMax;
}


const bool Player::canAttack()
{
	if (attackCooldown >= attackCooldownMax)
	{
		attackCooldown = 0.f;
		return true;
	}
	else
	{
		return false;
	}
}

void Player::setPosition(const sf::Vector2f pos)
{
	sprite.setPosition(pos);

}

void Player::setPosition(const float x, const float y)
{
	sprite.setPosition(x, y);
}

void Player::setHp(const int hp)
{
	this->hp = hp;
}

void Player::loseHp(const int value)
{
	this->hp -= value;
	if (hp < 0)
	{
		hp = 0;
	}
}

void Player::update()
{
	updateAttack();
}

void Player::updateAttack()
{
	if (attackCooldown < attackCooldownMax)
	{
		attackCooldown += 1.f;
	}
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(sprite);
}

void Player::move(const float dirx, const float diry)
{
	sprite.move(movementSpeed * dirx, movementSpeed * diry);
}


