#include "Game.h"

//Private Functions
void Game::initWindow()
{
	window = new sf::RenderWindow(sf::VideoMode(600, 800), "Shooter");
	window->setFramerateLimit(144);
	window->setVerticalSyncEnabled(false);
}

void Game::initSystems()
{
	points = 0;
}

void Game::initTextures()
{
	textures["BULLET"] = new sf::Texture();
	if (!textures["BULLET"]->loadFromFile("images/bullet.png"))
	{
		std::cout << "Failed to load bullet texture" << std::endl;
	}
}

void Game::initGUI()
{
	//Load font
	if (!font.loadFromFile("Fonts/Endor.ttf"))
	{
		std::cout << "Error, game failed to load font" << std::endl;
	}

	//init point text
	pointText.setFont(font);
	pointText.setCharacterSize(20);
	pointText.setPosition(20.f, 20.f);
	pointText.setFillColor(sf::Color::White);
	pointText.setString("TEXT");

	//init player GUI
	playerHpBar.setSize(sf::Vector2f(200.f, 25.f));
	playerHpBarBack.setSize(sf::Vector2f(200.f, 25.f));

	playerHpBar.setFillColor(sf::Color::Red);
	playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));

	playerHpBar.setPosition(sf::Vector2f(window->getSize().x - playerHpBar.getSize().x - 20.f, 20.f));
	playerHpBarBack.setPosition(sf::Vector2f(window->getSize().x - playerHpBarBack.getSize().x - 20.f, 20.f));


	gameOverText.setFont(font);
	gameOverText.setCharacterSize(50);
	gameOverText.setString("Game Over!");
	gameOverText.setPosition(window->getSize().x / 2.f - gameOverText.getGlobalBounds().width / 2.f, window->getSize().y / 2.f - gameOverText.getGlobalBounds().height / 2.f);
	gameOverText.setFillColor(sf::Color::Red);
}

void Game::initPlayer()
{
	player = new Player();
	player->setPosition(window->getSize().x / 2 - player->getBounds().width / 2, window->getSize().y * 4 / 5);
}

void Game::initEnemies()
{
	spawnTimerMax = 100.f;
	spawnTimer = spawnTimerMax;
}

void Game::initWorld()
{
	if (!worldbackgroundTexture.loadFromFile("images/background.jpg"))
	{
		std::cout << "ERROR. Game could not load background texture!" << std::endl;
	}
	
	worldBackground.setTexture(worldbackgroundTexture);
}

Game::Game()
{
	initWindow();
	initTextures();
	initGUI();
	initPlayer();
	initEnemies();
	initWorld();
	initSystems();
}

Game::~Game()
{
	delete window;
	delete player;

	//delete textures
	for (auto &i : textures)
	{
		delete i.second;
	}
	//delete bullets
	for (auto *i : bullets)
	{
		delete i;
	}

	//delete enemies
	for (auto* i : enemies)
	{
		delete i;
	}

}

void Game::run()
{
	while (window->isOpen())
	{
		updatePollEvents();

		if (player->getHp() > 0)
		{
			update();
		}
		
		render();
	}
	

}

void Game::updatePollEvents()
{
	sf::Event ev;
	while (window->pollEvent(ev))
	{
		if (ev.Event::type == sf::Event::Closed)
		{
			window->close();

		}
		if (ev.Event::KeyPressed && ev.Event::key.code == sf::Keyboard::Escape)
		{
			window->close();

		}
	}
}

void Game::updateInput()
{
	//move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		player->move(-1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		player->move(1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		player->move(0.f, -1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		player->move(0.f, 1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player -> canAttack())
	{
		bullets.push_back(new Bullet(textures["BULLET"], player -> getPos().x + player -> getBounds().width/2.f - 4.f, player->getPos().y, 0.f, -1.f, 5.f));
	}
}

void Game::updateGUI()
{
	std::stringstream ss;
	ss << "Points: " <<  points;
	pointText.setString(ss.str());

	//update Player GUI
	float hpPercent = static_cast<float>(player->getHp()) / player->getHpMax();
	playerHpBar.setSize(sf::Vector2f(playerHpBarBack.getSize().x * hpPercent, playerHpBar.getSize().y));
}

void Game::updateWorld()
{
}

void Game::updateCollision()
{
	//left world collision
	if (player->getBounds().left < 0.f)
	{
		player->setPosition(0.f, player->getBounds().top);
	}
	//right 
	if (player->getBounds().left + player -> getBounds().width > window -> getSize().x)
	{
		player->setPosition(window->getSize().x - player -> getBounds().width, player->getBounds().top);
	}
	//top
	if (player->getBounds().top < 0.f)
	{
		player->setPosition(player -> getBounds().left, 0.f);
	}
	//bottom
	if (player->getBounds().top + player->getBounds().height > window->getSize().y)
	{
		player->setPosition(player->getBounds().left, window->getSize().y - player->getBounds().height);
	}
}

void Game::updateBullets()
{

	unsigned counter = 0;

	for (auto* bullet : this->bullets)
	{
		bullet->update();

		//Bullet calling (top of the screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//delete bullets
			delete bullets.at(counter);
			bullets.erase(bullets.begin() + counter);
		}

		++counter;
	}
}

void Game::updateEnemies()
{
	//Spawning
	spawnTimer += 1.5f; 
	if (spawnTimer >= spawnTimerMax)
	{
		enemies.push_back(new Enemy(rand() % window->getSize().x - 50.f, -100.f));
		spawnTimer = 0.f;
	}

	//Update
	unsigned counter = 0;

	for (auto *enemy : this->enemies)
	{
		enemy->update();

		//enemy calling (botton of the screen)
		if (enemy->getBounds().top  > window->getSize().y)
		{
			//delete enemy
			delete enemies.at(counter);
			enemies.erase(enemies.begin() + counter);
		}
		//enemy - player collision
		else if(enemy -> getBounds().intersects(player -> getBounds()))
		{
			//at collision with the player
			player->loseHp(enemies.at(counter)->getDamage());

			delete enemies.at(counter);
			enemies.erase(enemies.begin() + counter);
		}
		++counter;
	} 
}



void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k < bullets.size() && enemy_deleted == false; k++)
		{

			if (enemies[i]->getBounds().intersects(bullets[k]->getBounds()))
			{
				points += enemies[i]->getPoints();
				
				delete enemies[i];
				enemies.erase(enemies.begin() + i);
				delete bullets[k];
				bullets.erase(bullets.begin() + k);

				enemy_deleted = true;

			}
		}

	}
}



void Game::update()
{
	updateInput();

	player->update();

	updateCollision();

	updateBullets();

	updateEnemies();

	updateGUI();

	updateCombat();

	updateWorld();
}

void Game::renderGUI()
{
	window->draw(pointText);
	window->draw(playerHpBarBack);
	window->draw(playerHpBar);
}

void Game::renderWorld()
{
	window->draw(worldBackground);
}

void Game::render()
{
	window->clear();

	//render world
	renderWorld();

	//draw everything
	player->render(*this->window);

	for (auto* bullet : this -> bullets)
	{
		bullet->render(window);
	}

	for (auto* enemy : this->enemies)
	{
		enemy->render(window);
	}

	renderGUI();

	//Game Over screen
	if (player->getHp() <= 0)
	{
		window->draw(gameOverText);
	}

	window->display();
}
