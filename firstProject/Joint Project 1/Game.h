// Game class declaration
#pragma once
#include "enemySentry.h" 
#include "Player.h"   // include Player header file
#include "SFML/Graphics.hpp" 
#include <iostream>
#include <cstdlib>  // include support for randomizing
#include <ctime>   // supports ctime function
#include "enemyFollower.h" 
#include "Globals.h"   // include Global header file
#include "boss.h"


class Game
{
	// private data members

	// put your game objects here eg player object and 
	// array of enemy objects etc.
	boss boss; // creates boss object 
	Player myPlayer;  // creates an object of type Player using the default constructor
	EnemySentry enemySentry[numOfSentry]; //  creates enemy entry object
	EnemyFollower EnemyFollower[numOfFollower]; // creates enemy follower object

	bool roundOver = false; // wave one is over
	bool roundTwoStart = false; // wave two started
	bool roundThreeStart = false; // wave three started
	bool roundFourStart = false; // wave four started
	bool gameWon = false; // game is over as the player has won
	sf::Texture floorTexture; // backround texture
	sf::RenderWindow window;
	sf::Sprite floorSprite; // backround window
	sf::RectangleShape northBase;
	sf::RectangleShape westBase; // wave 1
	sf::RectangleShape southBase; // wave 2
 	sf::RectangleShape eastBase; // wave 3
	sf::RectangleShape bossHealth; // the amount of health the boss has
	sf::RectangleShape Health; // health drop player can pick up
	sf::RectangleShape baseHealth; // base health player can pic up

	sf::Vector2f verticalBase = { 50,600 }; // for west and east base
	sf::Vector2f horozontialBase = { 800,55 }; // for south base
	sf::Vector2f dropBaseHealth = { 20,20 };
	sf::Font m_font;  // font for writing text
	sf::Text m_message;  // text for health
	sf::Text m_messageScore; // text for score
	sf::Text m_messageBase; // text for base health
	sf::Text m_messageLevel; // text for which round it is
	sf::Text m_messageRound; // text for end of round
	sf::Text m_messageGameOver; // text for when of game of
	sf::Text m_messageBoss; // text for when boss appears
	sf::Text m_messageGameWon; // text for when game is won by player

public:	  // declaration of member functions	
	Game(); // default constructor
	void	loadContent(); // loads content
	void	run(); // runs game
	void	update(); // updates 1/60 a second
	void	draw(); // draws game
	void    setUpGame(); // sets up first level
	void    moveEnemy(); // moves sentry
	void    collision(); // for all collision in the game
	void    follower(); // to get the follower to follow the player
	void    followBoss(); // follower code for the boss
	void    playerShoot(); // shooting for the player
	void    bossShoot(); // shooting for the boss
	int     level = 1; // wave counter
	void    levels(); // wave counter function
	void    levelTwo(); // level two starter 
	void    levelThree(); // level three starter
	void    levelBoss(); // level four starter
	void    restart(); // restarts game
	void    isGameWon(); // checks if player has killed boss
	void    updateBossHealth();
	//void    coll
};
