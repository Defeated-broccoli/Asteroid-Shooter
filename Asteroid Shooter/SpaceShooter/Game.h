#pragma once
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include <map>
#include <string>
#include <sstream>

class Game
{
private:
	//Window
	sf::RenderWindow* window;

	//Resources
	std::map <std::string, sf::Texture*> textures;
	std::vector <Bullet*> bullets;

	//GUI
	sf::Font font;
	sf::Text pointText;

	sf::Text gameOverText;

	//World
	sf::Sprite worldBackground;
	sf::Texture worldbackgroundTexture;

	//Systems
	unsigned points;

	//Player
	Player* player;

	//Player GUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;



	//Private Functions
	void initWindow();
	void initSystems();
	void initTextures();
	void initGUI();
	void initPlayer();
	void initEnemies();
	void initWorld();


public:
	//Constr and destr
	Game();
	~Game();


	//Functions

	void run();

	void updatePollEvents();
	void updateInput();
	void updateGUI();
	void updateWorld();
	void updateCollision();
	void updateBullets();
	void updateEnemies();
	void updateCombat();
	void update();
	void renderGUI();
	void renderWorld();
	void render();

};

