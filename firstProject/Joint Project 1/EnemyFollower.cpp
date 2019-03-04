  
#include "Globals.h"
#include "Player.h"
#include "EnemyFollower.h"

EnemyFollower::EnemyFollower() // default constructor
{
	loadImageEnemy(); // load the image file for the sprite
	speed = 2.8; // the average speed  
	direction = WEST;
}

void EnemyFollower::restart()
{
	enemyFollwerDied = false;
	speed = 2.8; // the average speed  
	direction = WEST;

}

void EnemyFollower::setPosition(int t_Xpos, int t_Ypos)
{
	enemyFollowerSprite.setPosition(t_Xpos, t_Ypos);
}

void EnemyFollower::die()
{

	enemyFollowerSprite.setPosition(2000, 2000); // sets pos off screen when they die
	enemyFollwerDied = true;

	int num = (rand() % 4) + 1; // random number between 1 and 4

	if (num == 2) // random chance of dropping item
	{
		droppedHealth = true;
	}
	else
		droppedHealth = false;
}

sf::Sprite EnemyFollower::getEnemyFollowerBody() // returns sprite
{
	return enemyFollowerSprite;
}

void EnemyFollower::setSpeed(int t_speed) // to change enemy speed
{
	speed = t_speed;
}


void EnemyFollower::loadImageEnemy()
{
	if (!enemyFollowerWest.loadFromFile("ASSETS/IMAGES/enemy2_left.png"))  // Loads tecture for player moving left
	{
		std::cout << "error with enemy2_left file";
	}

	if (!enemyFollowerEast.loadFromFile("ASSETS/IMAGES/enemy2_right.png"))  // Loads tecture for player moving left
	{
		std::cout << "error with enemy2_right file";
	}

	if (!enemyFollowerNorth.loadFromFile("ASSETS/IMAGES/enemy2_up.png"))  // Loads tecture for player moving left
	{
		std::cout << "error with enemy2_up file";
	}

	if (!enemyFollowerSouth.loadFromFile("ASSETS/IMAGES/enemy2_down.png"))  // Loads tecture for player moving left
	{
		std::cout << "error with enemy2_down file";
	}

	enemyFollowerSprite.setTexture(enemyFollowerWest);


}

void EnemyFollower::enemyFollowerMoveLeft() // moves enemy follower left
{
	if (enemyFollowerSprite.getPosition().x >= 1) // moves follower only left only if its on screen
	{
		enemyFollowerSprite.setTexture(enemyFollowerWest); // sets the texture to west 
		enemyFollowerSprite.setPosition(enemyFollowerSprite.getPosition().x - speed, enemyFollowerSprite.getPosition().y); // moves left by speed
	}
}
void EnemyFollower::enemyFollowerMoveRight() // moves enemy follower right
{
	if (enemyFollowerSprite.getPosition().x < SCREEN_WIDTH) // only if inside boundries 
	{
		enemyFollowerSprite.setTexture(enemyFollowerEast); // sets texture to east when follower moves left
		enemyFollowerSprite.setPosition(enemyFollowerSprite.getPosition().x + speed, enemyFollowerSprite.getPosition().y); // adds speed to x co-ord
	}
}
void EnemyFollower::enemyFollowerMoveUp() // moves follower north
{
	if (enemyFollowerSprite.getPosition().y >= 1) // only if inside boundries  
	{
		enemyFollowerSprite.setTexture(enemyFollowerNorth); // sets texture to north
		enemyFollowerSprite.setPosition(enemyFollowerSprite.getPosition().x, enemyFollowerSprite.getPosition().y - speed); // moves sprite by speed on the Y co-or
	}
}

void EnemyFollower::enemyFollowerMoveDown() // moves follower south
{
	if (enemyFollowerSprite.getPosition().y <= SCREEN_HEIGHT) // border checking
	{
		enemyFollowerSprite.setTexture(enemyFollowerSouth); // sets texture to follower facing south texture
		enemyFollowerSprite.setPosition(enemyFollowerSprite.getPosition().x, enemyFollowerSprite.getPosition().y + speed); // moves follower by speed on the Y
	}
}