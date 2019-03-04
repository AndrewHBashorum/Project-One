#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class boss // boss class for wave four
{
	sf::Texture enemyBossNorth; // textures for boss enemy type
	sf::Texture enemyBossSouth; 
	sf::Texture enemyBossWest;
	sf::Texture enemyBossEast;
	sf::Sprite enemyBossSprite;

	sf::Texture fireNorthBoss; // textures for enemy bullet
	sf::Texture fireSouthBoss;
	sf::Texture fireWestBoss;
	sf::Texture fireEastBoss;
	sf::Sprite bulletSpriteBoss;

	float image_width = 64; // for scaling
	float image_height = 64;

	

public:
	boss(); // boss default constructer
	int direction; // direction the boss is facing
	int health; // boss health
	void loadImageEnemy(); 
	sf::Sprite getEnemyFollower(); // returns sprite
	sf::Vector2f bulletLocation = { 1000,1000 }; // original bullet location
	int speed; // speed  of boss
	
	bool enemyFollwerDied = false; // boss died
	bool bulletFired = false; // bullet fired
	void lessHealth(); // loses health
	int getHealth(); // returns boss health
	void changeScale(); // increases scale of boss sprite
	void die(); // boss dies
	void setSpeed(int t_speed); // sets speed of boss
	void setPosition(int t_Xpos, int t_YPos); // sets position
	void enemyFollowerMoveLeft(); // move boss left
	void enemyFollowerMoveRight(); // moves boss right
	void enemyFollowerMoveUp(); // move follower up
	void enemyFollowerMoveDown(); // move follower down
	void moveBullet(); // move bullet of boss
	sf::Sprite getBullet(); // returns sprite of bullet 
	void whereIsTheBullet(); // checks bools of bullets
	void shoot(); // shoot functiuon for boss
	void restart(); // restart
	void setPositionToLocation(); // sets vector location to sprite position
};