// Player class declaration
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Player
{
	sf::Texture textureNorth; // textures for four diffrent player directions
	sf::Texture textureSouth; 
	sf::Texture textureWest;
	sf::Texture textureEast;
	sf::Sprite sprite; // player sprite

	sf::Texture fireNorth; // textures for bullets
	sf::Texture fireSouth; 
	sf::Texture fireWest;
	sf::Texture fireEast;
	sf::Sprite bulletSprite; // sprite for bullet
	
	// private data members
	int health; // player health
	int speed;
	int direction = 1; // direction of player
	int bulletDirection = 0;
	int baseHealth; // base health if 0 player has lost game
	sf::Vector2f playersLocation = { 400,300 }; // stating location of player / not updates or used again throughout the game
	
	void setSpeed(int t_speed); // set new speed of player
	void setPosition(int xPos, int yPos); // sets position of player
	
public:

	Player();
	void die(); // player has died and game is over function
	void killedSentry(); // player gains points if a sentry was killed
	void killedFollower(); // player gains points if a follower was killed
	sf::Vector2f bulletLocation = { 1000,1000 }; // bullet in "chamber" position
	int score; // players score
	int getHealth();  // returns health of player
	int getBaseHealth(); // returns base health
	
	bool bulletFired = false; // is bullet fired
	bool gameOver = false; // is game over bool
	void updateBullet();
	void setDirection(int t_direction); //set direction of player

	void shoot(); // player shoots by pressing spacebar.
	void moveBullet(); // moves bullet
	void whereIsTheBullet(); // checks if bullet is fired

	int getScore(); // returns player score
	void loadImage(); // loads player sprite

	sf::Sprite getBody(); // returns player sprite
	sf::Sprite getBullet(); // returns bullet sprite

	void gotShot(); // player got shot by the boss
	void moveLeft(); // move player left
	void moveRight(); // moves player right
	void moveUp(); // moves player north
	void moveUpBoss(); // moves player north in boss level
	void moveDown(); // moves player south
	void decreaseLives(); // player loses health depending on time
	void decreaseBase(); // base loses 15 health if sentry passes through it
	void increaseLives(); // player loses health depending on time
	void increaseBase(); // base loses 15 health if sentry passes through it
	void setPositionToLocation(); // sets vector location to sprite position
	

	void restart();
};