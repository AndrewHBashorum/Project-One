 

#include "Player.h"   // include Player header file
#include "Globals.h"
// Player function definitions here



Player::Player() // default constructor
{
	
	setSpeed(speed);
	loadImage();  // load the image file for the sprite
	int xPos = SCREEN_WIDTH / 2;    // place the player object in the centre of the screen
	int yPos = SCREEN_HEIGHT / 2;
	setPosition(xPos, yPos);  // set the position of the players sprite
	direction = EAST;
	speed = 7; // the average speed 
	health = 100; // player health
	baseHealth = 100; // base health
	score = 0; // score of player
}


void Player::setSpeed(int t_speed) // sets speed of player
{
 	speed = t_speed; // sets speed to inputed speed
}

void Player::setPosition(int xPos, int yPos)
{
	sprite.setPosition(xPos, yPos);
}

sf::Sprite Player::getBody()
{
	return sprite;
}

sf::Sprite Player::getBullet()
{
	return bulletSprite;
}

void Player::setDirection(int t_direction)
{
	direction = t_direction;
}

void Player::moveLeft() // move player left
{
	direction = WEST;
	sprite.setTexture(textureWest);
	if (playersLocation.x >= 0 + WALL_THICK) // border checking for western border
	{
		playersLocation.x = playersLocation.x - speed; // updates player speed
	}
}

void Player::moveRight() // moves player right
{
	direction = EAST;
	sprite.setTexture(textureEast);
	if (playersLocation.x <= SCREEN_WIDTH - 54 - WALL_THICK) // border checking for eastern border
	{
		playersLocation.x = playersLocation.x + speed; // updates player speed
	}
}

void Player::moveUpBoss() // moves player north during boss round
{
	direction = NORTH;
	
	sprite.setTexture(textureNorth);
	if (playersLocation.y >= 100) //WALL_THICK) // border checking for northen border
	{
		playersLocation.y = playersLocation.y - speed; // updates player speed
	}

}

void Player::moveUp() // moves player north
{
	direction = NORTH; // direction set to north

	sprite.setTexture(textureNorth);
	if (playersLocation.y >= 1 ) //WALL_THICK) // border checking for northen border
	{
		playersLocation.y = playersLocation.y - speed; // updates player speed
	}
	
}

void Player::updateBullet()
{
	if (bulletFired == false)  // only change direction if bullet has not been fired
	{
		bulletDirection = direction; // direction set to north
	}
}
void Player::moveDown() // moves player south
{
	direction = SOUTH;
	// only change direction if bullet has not been fired
	
	sprite.setTexture(textureSouth); // sets tecture to south facing player texture
	if (playersLocation.y < SCREEN_HEIGHT - 65 - WALL_THICK) // border checking for southern border
	{
		playersLocation.y = playersLocation.y + speed; // updates player speed
	}
}

void Player::die() // checks if player died
{
	if (baseHealth <= 0 || health <= 0) // if either health is 0
	{
		gameOver = true;
	}
}

int Player::getBaseHealth() // returns base health
{
	return baseHealth;
}

int Player::getHealth() // returns lives
{
	return health;
}

void Player::shoot() // sets up shooting
{
	if (bulletLocation == sf::Vector2f { 1000, 1000 }) // if in chamber position
	{
		bulletLocation = playersLocation; // bullet is set to player location
		bulletSprite.setPosition(bulletLocation);
		
		moveBullet(); // moves bullet
	}
}
void Player::moveBullet() // moves bullet
{
	if (bulletFired == true) // if bullet is fired
	{
		if (bulletDirection == NORTH) // checks direction so bullet goes same direction as player is facing
		{
			bulletSprite.setTexture(fireNorth);
			bulletLocation = bulletLocation + sf::Vector2f{ 0,-12 }; // moves bullet
			if (bulletLocation.y <= 1)  // border checking
			{
				bulletLocation = sf::Vector2f{ 1000,1000 }; // puts bullet in original position
			}
		}
		if (bulletDirection == WEST) // checks direction so bullet goes same direction as player is facing
		{
			bulletSprite.setTexture(fireWest);
			bulletLocation = bulletLocation + sf::Vector2f{ -12,0 }; // moves bullet
			if (bulletLocation.x <= 0) // border checking
			{
				bulletLocation = sf::Vector2f{ 1000,1000 };  // puts bullet in original position
			}
		}
		if (bulletDirection == EAST) // checks direction so bullet goes same direction as player is facing
		{
			bulletSprite.setTexture(fireEast);
			bulletLocation = bulletLocation + sf::Vector2f{ 12,0 }; // moves bullet
			if (bulletLocation.x >= SCREEN_WIDTH - 54)  // border checking
			{
				bulletLocation = sf::Vector2f{ 1000,1000 };  // puts bullet in original position
			}
		}
		if (bulletDirection == SOUTH) // checks direction so bullet goes same direction as player is facing
		{
			bulletSprite.setTexture(fireSouth);
			bulletLocation = bulletLocation + sf::Vector2f{ 0,12 }; // moves bullet
			if (bulletLocation.y > SCREEN_HEIGHT - 65)  // border checking
			{
				bulletLocation = sf::Vector2f{ 1000,1000 };  // puts bullet in original position
			}
		}
	}
	
}

void Player::killedSentry() // gives score if player kills sentry
{
	score = score + 1;
}

void Player::killedFollower()  // gives score if player kills follower
{
	score = score + 3;
}

void Player::whereIsTheBullet() // checks location of bullet
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

int Player::getScore() // returns score
{
	return score;
}

void Player::decreaseLives() // player loses health per second
{
	health = health - 0.0000000000001;
}

void Player::decreaseBase() // base loses health is sentry passes throuhh a wall
{
	baseHealth = baseHealth - 15;
}

void Player::increaseLives() // player picked up health drop and gains 20 health
{
	health = health + 20;

	if (health > 100) // health cant go above 100
	{
		int dif = health - 100;
		health = health - dif;
	}
}

void Player::gotShot() // player got shot by the boss man
{
	health = health - 20; // reduce health by 20
	if (health < 0) // cant go below 0
	{
		health = 0;
	}
}

void Player::increaseBase() // base loses health is sentry passes throuhh a wall
{
	baseHealth = baseHealth + 15;
	if (baseHealth > 100) // limits base health at 0
	{
		int dif = baseHealth - 100; // finds uneeded extra base health
		baseHealth = baseHealth - dif; // brings it down to 100
	}
}


void Player::setPositionToLocation() // sets vector location to sprite position
{
	sprite.setPosition(playersLocation);
	bulletSprite.setPosition(bulletLocation);
}

void Player::restart() // resets player
{
	int xPos = SCREEN_WIDTH / 2;    // place the player object in the centre of the screen
	int yPos = SCREEN_HEIGHT / 2;
	//sprite.setPosition(xPos, yPos);  // set the position of the players sprite
	direction = WEST; // resets direction
	bulletFired = false; // resets follower
	gameOver = false;  
	score = 0; // resets score
	health = 100; // reset health
	baseHealth = 100; // reset base health
}

void Player::loadImage()
{

		if (!textureNorth.loadFromFile("ASSETS/IMAGES/player_up.png")) // Loads tecture for player moving north
		{
			std::cout << "error with player north player file";
		}

		if (!textureWest.loadFromFile("ASSETS/IMAGES/player_left.png"))  // Loads tecture for player moving left
		{
			std::cout << "error with player image move left file";
		}

		if (!textureEast.loadFromFile("ASSETS/IMAGES/player_right.png"))  // Loads tecture for player moving left
		{
			std::cout << "error with fireball image right file";
		}
	
		if (!textureSouth.loadFromFile("ASSETS/IMAGES/player_down.png"))  // Loads tecture for player moving south
		{
			std::cout << "error with player image file";
		}

		if (!fireSouth.loadFromFile("ASSETS/IMAGES/fireball_down.png"))  // Loads tecture for player moving left
		{
			std::cout << "error with fireball image down file";
		}

		if (!fireEast.loadFromFile("ASSETS/IMAGES/fireball_right.png"))  // Loads tecture for player moving right
		{
			std::cout << "error with player image move right file";
		}

		if (!fireNorth.loadFromFile("ASSETS/IMAGES/fireball_up.png"))
		{
			std::cout << "error with player north fireball file";
		}

		if (!fireWest.loadFromFile("ASSETS/IMAGES/fireball_left.png"))  // Loads tecture for player moving left
		{
			std::cout << "error with player fireball left file";
		}
	
	sprite.setTexture(textureEast);
}