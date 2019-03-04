
#include "enemySentry.h"  
#include "Globals.h"
#include "Player.h" 

EnemySentry::EnemySentry() // default constructor
{
	loadImageEnemy(); // load the image file for the sprite
	speed = 2.8; // the average speed  
	direction = WEST;
}

void  EnemySentry::restart() // resets enemy sentry
{
	speed = 2.8; // the average speed  
	direction = WEST; // reset directiom
	bulletHitSentry = false; // reset bools
	enemyDied = false;
	leftScreen = false;
}

void EnemySentry::setPosition(int t_Xpos, int t_Ypos) // set Pos of sentry to new inputed c0-ords
{
	enemySprite.setPosition(t_Xpos, t_Ypos);
}

sf::Sprite EnemySentry::getEnemyBody() // returns sprite
{
	return enemySprite; // enemy sprite
}

void EnemySentry::die() // if enemy is shot function
{
	enemyDied = true; // enemy is dead  / bool for drawing
	bulletHitSentry = true; // bullet hit sentry
	enemySprite.setPosition(2000,2000); // set Pos and off screen

	int num = (rand() % 7) + 1; // random number between 1 and 7

	if (num == 2) // random chance of dropping item
	{
		droppedBase = true; 
	}
	else
		droppedBase = false;
}

void EnemySentry::enemySetSpeed(int t_speed)
{
	speed = t_speed; // set new speed of enemy sentry
}

void EnemySentry::enemyMoveLeft() // moves enemy left
{
	enemySprite.setTexture(enemyWest); // sets texture to west
	if (enemySprite.getPosition().x >= 1) // border checking
	{
		enemySprite.setPosition(enemySprite.getPosition().x - speed, enemySprite.getPosition().y); // minuses speed from x c0-ord of sentry
	}
	else // off-screen
	{
		enemySprite.setPosition(enemySprite.getPosition().x + SCREEN_WIDTH, enemySprite.getPosition().y);  // minuses speed from y c0-ord of sentry
		leftScreen = true; //
	}
}

void EnemySentry::enemyMoveRight() // moves enemy right
{
	enemySprite.setTexture(enemyEast); // moves enemy east
	if (enemySprite.getPosition().x <= SCREEN_WIDTH) // border checking
	{
		enemySprite.setPosition(enemySprite.getPosition().x + speed, enemySprite.getPosition().y); // updates x pos of sentry
	}
	else if (enemyDied == false) // enemy still alive / // off-screen
	{
		enemySprite.setPosition(enemySprite.getPosition().x - SCREEN_WIDTH, enemySprite.getPosition().y);  // updates y pos of sentry
		leftScreen = true;
	}
}

void EnemySentry::enemyMoveUp() // moves enemy north
{
	enemySprite.setTexture(enemyNorth); // sets texture to north facing texture
	if (enemySprite.getPosition().y > 0) // border checking
	{
		enemySprite.setPosition(enemySprite.getPosition().x, enemySprite.getPosition().y - speed); // updates y co-ord of the sentry
	}
	else // off-screen
	{
		enemySprite.setPosition(enemySprite.getPosition().x , enemySprite.getPosition().y + SCREEN_HEIGHT); // moves back to south of screen 
		leftScreen = true; // enemy has reached base off-screen so base should lose health
	}
}

void EnemySentry::enemyMoveDown() // moves enemy south
{
	enemySprite.setTexture(enemySouth); // sets texture to south facing sentry
	if (enemySprite.getPosition().y < SCREEN_HEIGHT) // border checking
	{
		enemySprite.setPosition(enemySprite.getPosition().x, enemySprite.getPosition().y + speed); // updates y co-ord of the sentry
	}

	else // off-screen
	{
		enemySprite.setPosition(enemySprite.getPosition().x, enemySprite.getPosition().y - SCREEN_HEIGHT); // moves enemy back to south of screen
		leftScreen = true;
	}
}

void EnemySentry::setSpeed(int t_speed) // set new speed of enemy sentry
{
	speed = t_speed;
}


void EnemySentry::loadImageEnemy()
{
	if (!enemyWest.loadFromFile("ASSETS/IMAGES/enemy1_left.png"))  // Loads tecture for player moving left
	{
		std::cout << "error with enemy1_left file";
	}

	if (!enemyEast.loadFromFile("ASSETS/IMAGES/enemy1_right.png"))  // Loads tecture for player moving left
	{
		std::cout << "error with enemy1_right file";
	}

	if (!enemyNorth.loadFromFile("ASSETS/IMAGES/enemy1_up.png"))  // Loads tecture for player moving left
	{
		std::cout << "error with enemy1_up file";
	}

	if (!enemySouth.loadFromFile("ASSETS/IMAGES/enemy1_down.png"))  // Loads tecture for player moving left
	{
		std::cout << "error with enemy1_down file";
	}
	
	enemySprite.setTexture(enemyWest); // default texture setting

}