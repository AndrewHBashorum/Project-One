#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class EnemySentry
{
	sf::Texture enemyWest; // texture for enemy sentries 
	sf::Texture enemyEast; 
	sf::Texture enemyNorth;
	sf::Texture enemySouth;
	sf::Sprite enemySprite;
	
	int direction; // direction of sentry
public:
	
	EnemySentry();
	int speed; // speed of sentry
	bool bulletHitSentry = false; // bullet hit sentry
	bool enemyDied = false; // enemy sentry is dead
	bool leftScreen = false; // sentry has hit the base and left the screen
	bool droppedBase = false;
	void die(); // stentry died
	void enemySetSpeed(int t_speed); // sets speed of sentry
	sf::Sprite getEnemyBody(); // returns sprite
	void setPosition(int t_Xpos, int t_YPos); // sets position
	void enemyMoveLeft(); // moves enemy left
	void enemyMoveRight(); // moves enemy right
	void enemyMoveUp(); // moves enemy up
	void enemyMoveDown(); // enemy moves down
	void loadImageEnemy();
	void setSpeed(int t_speed);

	void restart();
};