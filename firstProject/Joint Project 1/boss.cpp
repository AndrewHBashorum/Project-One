#include "Globals.h"
#include "Player.h"
#include "EnemyFollower.h"
#include "boss.h"

boss::boss() // default constructor
{
	loadImageEnemy(); // load the image file for the sprite
	health = 100;
	speed = 3.0; // the average speed  
	direction = WEST;
	enemyBossSprite.setPosition(4000, 4000); // sets boss location to 
}

void boss::restart()
{
	health = 100;
	enemyFollwerDied = false;
	speed = 2.8; // the average speed  
	direction = WEST;
	enemyBossSprite.setPosition(4000, 4000);
}

void boss::setPosition(int t_Xpos, int t_Ypos)
{
	enemyBossSprite.setPosition(t_Xpos, t_Ypos);
}

void boss::die() // sets boss Pos of screen
{
	enemyBossSprite.setPosition(4000, 4000); // sets boss Pos of screen
}
int boss::getHealth() // returns boss health
{
	return health;
}

void boss::lessHealth() // boss loses health depending on time a bullet stikes him / better shot
{
	health = health - 20;
}

void boss::changeScale() // increases sclae of boss by 1.5
{
	enemyBossSprite.setScale(1.5, 1.5); //  increases scale of boss sprite
	image_width = image_width * 1.5; // image fits sprite size
	image_height = image_height * 1.5;
}

sf::Sprite boss::getEnemyFollower() // retuns sprite
{
	return enemyBossSprite;
}

void boss::setSpeed(int t_speed) // sets bosses speed
{
	speed = t_speed;
}

sf::Sprite boss::getBullet() // return bosses bullet sprite
{
	return bulletSpriteBoss;
}

void boss::loadImageEnemy()
{
	if (!enemyBossWest.loadFromFile("ASSETS/IMAGES/enemy2_left.png"))  // Loads tecture for boss  moving left
	{
		std::cout << "error with enemy2_left file";
	}

	if (!enemyBossEast.loadFromFile("ASSETS/IMAGES/enemy2_right.png"))  // Loads tecture for boss  moving rifht
	{
		std::cout << "error with enemy2_right file";
	}

	if (!enemyBossNorth.loadFromFile("ASSETS/IMAGES/enemy2_up.png"))  // Loads tecture for boss  moving north
	{
		std::cout << "error with enemy2_up file";
	}

	if (!enemyBossSouth.loadFromFile("ASSETS/IMAGES/enemy2_down.png"))  // Loads tecture for boss  moving south
	{
		std::cout << "error with enemy2_down file";
	}


	if (!fireSouthBoss.loadFromFile("ASSETS/IMAGES/fireball_down.png"))  // Loads tecture for boss bullet moving left
	{
		std::cout << "error with fireball image down file";
	}

	if (!fireEastBoss.loadFromFile("ASSETS/IMAGES/fireball_right.png"))  // Loads tecture for boss bullet moving right
	{
		std::cout << "error with player image move right file";
	}

	if (!fireNorthBoss.loadFromFile("ASSETS/IMAGES/fireball_up.png")) // Loads tecture for boss bullet moving north
	{
		std::cout << "error with player north fireball file";
	}

	if (!fireWestBoss.loadFromFile("ASSETS/IMAGES/fireball_left.png"))  // Loads tecture for boss bullet moving west
	{
		std::cout << "error with player fireball left file";
	}

	enemyBossSprite.setTexture(enemyBossSouth); // initializes sprites texture
	bulletSpriteBoss.setTexture(fireSouthBoss);

}

void boss::enemyFollowerMoveLeft() // moves enemy boss left
{
	if (bulletFired == false) // if bullet in chamber bullet can change direction only
	{
		direction = WEST;
	}

	if (enemyBossSprite.getPosition().x >= 1) // border checking
	{
		enemyBossSprite.setTexture(enemyBossWest); // sets enemy boss texture to west 
		enemyBossSprite.setPosition(enemyBossSprite.getPosition().x - speed, enemyBossSprite.getPosition().y);  // changes Y co-ord of boss
	}
}
void boss::enemyFollowerMoveRight()  // moves enemy boss righy
{

	if (enemyBossSprite.getPosition().x < SCREEN_WIDTH) // border checking
	{
		enemyBossSprite.setTexture(enemyBossEast); // sets enemy boss texture to east
		enemyBossSprite.setPosition(enemyBossSprite.getPosition().x + speed, enemyBossSprite.getPosition().y); // changes x co-ord of boss
	}
}
void boss::enemyFollowerMoveUp() // moves enemy boss up
{
	if (enemyBossSprite.getPosition().y >= 1)  // border checking
	{
		enemyBossSprite.setTexture(enemyBossNorth);  // sets enemy boss texture to north
		enemyBossSprite.setPosition(enemyBossSprite.getPosition().x, enemyBossSprite.getPosition().y - speed);  // border checking
	}
}

void boss::enemyFollowerMoveDown()  // moves enemy boss down
{

	if (enemyBossSprite.getPosition().y <= SCREEN_HEIGHT) // border checking
	{
		enemyBossSprite.setTexture(enemyBossSouth);  // sets enemy boss texture to nsouth
		enemyBossSprite.setPosition(enemyBossSprite.getPosition().x, enemyBossSprite.getPosition().y + speed);  // changes y co-ord of boss
	}
}

void boss::moveBullet() // moves bullet of the boss
{
	if (bulletFired == true)
	{
		if (direction == NORTH) // checks direction so bullet goes same direction as player is facing
		{
			bulletSpriteBoss.setTexture(fireNorthBoss);
			bulletLocation = bulletLocation + sf::Vector2f{ 0,-12 }; // moves bullet
			if (bulletLocation.y <= 1)  // border checking
			{
				bulletLocation = sf::Vector2f{ 1000,1000 }; // puts bullet in original position
			}
		}
		if (direction == WEST) // checks direction so bullet goes same direction as player is facing
		{
			bulletSpriteBoss.setTexture(fireWestBoss);
			bulletLocation = bulletLocation + sf::Vector2f{ -12,0 }; // moves bullet
			if (bulletLocation.x <= 0) // border checking
			{
				bulletLocation = sf::Vector2f{ 1000,1000 };  // puts bullet in original position
			}
		}
		if (direction == EAST) // checks direction so bullet goes same direction as player is facing
		{
			bulletSpriteBoss.setTexture(fireEastBoss);
			bulletLocation = bulletLocation + sf::Vector2f{ 12,0 }; // moves bullet
			if (bulletLocation.x >= SCREEN_WIDTH - 54)  // border checking
			{
				bulletLocation = sf::Vector2f{ 1000,1000 };  // puts bullet in original position
			}
		}
		if (direction == SOUTH) // checks direction so bullet goes same direction as player is facing
		{
			bulletSpriteBoss.setTexture(fireSouthBoss);
			bulletLocation = bulletLocation + sf::Vector2f{ 0,12 }; // moves bullet
			if (bulletLocation.y > SCREEN_HEIGHT - 65)  // border checking
			{
				bulletLocation = sf::Vector2f{ 1000,1000 };  // puts bullet in original position
			}
			
		}
	}

}

void boss::setPositionToLocation()
{
	
	bulletSpriteBoss.setPosition(bulletLocation);;
}

void boss::shoot() // shoots bullet
{
	if (bulletLocation == sf::Vector2f{ 1000, 1000 }) // if bullet is in chamber
	{
		bulletLocation = enemyBossSprite.getPosition(); // set the bullets position to the bosses current position
		bulletSpriteBoss.setPosition(bulletLocation); // set the bullets position to the bosses current position//
		bulletFired = true; // bullet has breen fired
		moveBullet(); // move from bosses location
	}
}

void boss::whereIsTheBullet() // checks location of bullet
{
	if (bulletLocation == sf::Vector2f{ 1000,1000 }) // is it in original position
	{
		bulletFired = false; // if so its not fired and can be
	}
	else
	{
		bulletFired = true; // if not it should not change direction with player or be fired again
	}
}