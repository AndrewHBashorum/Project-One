#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>



class EnemyFollower
{
	sf::Texture enemyFollowerNorth; // texture for enemy follower 
	sf::Texture enemyFollowerSouth;
	sf::Texture enemyFollowerWest;
	sf::Texture enemyFollowerEast;
	sf::Sprite enemyFollowerSprite;
	float image_width = 64;
	float image_height = 64;

	int direction; // direction for follower

public:
	EnemyFollower(); // enemy follower object
	void loadImageEnemy(); 
	sf::Sprite getEnemyFollower(); // return sprite

	int speed; // speed of follower
	bool enemyFollwerDied = false; // enemy follower died
	bool droppedHealth = false;
	void die(); // follower died
	void setSpeed(int t_speed); // sets speed of follower
	void enemyFollowerSetSpeed(int t_speed); // i dunno
	sf::Sprite getEnemyFollowerBody(); // return sprite
	void setPosition(int t_Xpos, int t_YPos); // sets position  of player
	void enemyFollowerMoveLeft(); // moves follower left
	void enemyFollowerMoveRight(); // moves follower right
	void enemyFollowerMoveUp(); // moves follwer up
	void enemyFollowerMoveDown(); // moves follower down
	void loadImageEnemyFollower(); 

	void restart(); // restart follower 
};