// Name: Andrew Bashorum 
// Login: C00238900
// Date: 21/2/ 19
// Approximate time taken: 50 hours
//---------------------------------------------------------------------------
// Project description: This is a game in which the player must kill all enemies
// which appear on-screen before losing all base health or player health.
// There are two types of enemy and one final boss.
// Sentry: Moves towards players base. These damage the base if they reach it (-15). They do not hurt the player.
// Follower: These enemies follow the player and deal massive damage while near the player. They do not hurt the base.
// Boss: This enemy shoots at the player during round 4.
// ---------------------------------------------------------------------------
// Known Bugs: Bullet bug on round 3 (not the directional bug)
// ?

//////////////////////////////////////////////////////////// 
// include correct library file for release and debug versions
//////////////////////////////////////////////////////////// 

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 



#include "Game.h"   // include Game header file
#include <ctime>

int main()
{
	Game aGame;
	aGame.loadContent();
	aGame.run();
	Player();
	return 0;
}

Game::Game() : window(sf::VideoMode(static_cast<int>(SCREEN_WIDTH), static_cast<int>(SCREEN_HEIGHT)), "Joint Project Game", sf::Style::Default)
// Default constructor
{
}

void Game::loadContent()
// load the font file & setup the message
{
	if (!m_font.loadFromFile("ASSETS/FONTS/BebasNeue.otf"))
	{
		std::cout << "error with font file file";
	}
	if (!floorTexture.loadFromFile("ASSETS/IMAGES/floor.png"))  // Loads tecture for player moving south
	{
		std::cout << "error with floor image file";
	}
	{
		floorSprite.setTexture(floorTexture);
	}
	// set up the message string 
	m_message.setFont(m_font);  // set the font for the text
	m_message.setCharacterSize(24); // set the text size
	m_message.setFillColor(sf::Color::Red); // set the text colour
	m_message.setPosition(10, 10);  // its position on the screen

	m_messageBoss.setFont(m_font);  // set the font for the text
	m_messageBoss.setCharacterSize(24); // set the text size
	m_messageBoss.setFillColor(sf::Color::Red); // set the text colour
	m_messageBoss.setPosition(500, 10);  // its position on the screen

	m_messageScore.setFont(m_font);  // set the font for the text
	m_messageScore.setCharacterSize(24); // set the text size
	m_messageScore.setFillColor(sf::Color::White); // set the text colour
	m_messageScore.setPosition(10, 70);  // its position on the screen

	m_messageBase.setFont(m_font);  // set the font for the text
	m_messageBase.setCharacterSize(24); // set the text size
	m_messageBase.setFillColor(sf::Color::Blue); // set the text colour
	m_messageBase.setPosition(10,40 );  // its position on the screen

	m_messageLevel.setFont(m_font);  // set the font for the text
	m_messageLevel.setCharacterSize(24); // set the text size
	m_messageLevel.setFillColor(sf::Color::White); // set the text colour
	m_messageLevel.setPosition(10, 100);  // its position on the screen

	m_messageRound.setFont(m_font);  // set the font for the text
	m_messageRound.setCharacterSize(45); // set the text size
	m_messageRound.setFillColor(sf::Color::White); // set the text colour
	m_messageRound.setPosition(200, SCREEN_HEIGHT / 2);  // its position on the screen

	m_messageGameOver.setFont(m_font);  // set the font for the text
	m_messageGameOver.setCharacterSize(40); // set the text size
	m_messageGameOver.setFillColor(sf::Color::Red); // set the text colour
	m_messageGameOver.setPosition(200, SCREEN_HEIGHT / 2);  // its position on the screen

	m_messageGameWon.setFont(m_font);  // set the font for the text
	m_messageGameWon.setCharacterSize(40); // set the text size
	m_messageGameWon.setFillColor(sf::Color::Yellow); // set the text colour
	m_messageGameWon.setPosition(200, SCREEN_HEIGHT / 2);  // its position on the screen

	westBase.setFillColor(sf::Color::Black); // west base set up for wave 1
	westBase.setPosition(0, 0);
	westBase.setSize(verticalBase);

	northBase.setFillColor(sf::Color::Black); // south base for round 2
	northBase.setPosition(0, 0);
	northBase.setSize(horozontialBase);

	eastBase.setFillColor(sf::Color::Black);  // east base for round 3
	eastBase.setPosition(770, 0);
	eastBase.setSize(verticalBase);

	Health.setFillColor(sf::Color::Red);  // east base for round 3
	Health.setPosition(1500, 1500);
	Health.setSize(dropBaseHealth);

	baseHealth.setPosition(1500, 1500);
	baseHealth.setFillColor(sf::Color::Blue);  // east base for round 3
	baseHealth.setSize(dropBaseHealth);

	bossHealth.setFillColor(sf::Color::Red);
	bossHealth.setPosition(200, 10);
	float bob = boss.getHealth();
	sf::Vector2f bosssHealth = { bob * 5, 25 };
	bossHealth.setSize(bosssHealth);
	
}

void Game::updateBossHealth()
{
	float bob = boss.getHealth();
	sf::Vector2f bosssHealth = { bob * 5, 25 };
	bossHealth.setSize(bosssHealth);
}

void Game::run()
// This function contains the main game loop which controls the game. 
{

	srand(time(nullptr)); // set the seed once

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);

	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	// the clock object keeps the time.
	sf::Clock clock;
	setUpGame();

	clock.restart();

	while (window.isOpen())
	{
		// check if the close window button is clicked on
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//get the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();

		//update every 60th of a second
		//only when the time since last update is greater than 1/60 update the world.
		if (timeSinceLastUpdate > timePerFrame)
		{
			

			if (roundFourStart == true) // has round four started
			{
				bossShoot(); // boss can shoot
			}
			
			myPlayer.setPositionToLocation(); // sets vector location to sprite location
			boss.setPositionToLocation();  // sets vector location to sprite location 
			myPlayer.die(); // player dies
			levels(); // levels check
			isGameWon(); // checks if game is won
			update(); 
			draw();


			if (myPlayer.gameOver == true || gameWon == true) // if player dies
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) // press r to restart
				{
					myPlayer.gameOver = false;
					gameWon = false;
					restart();
				}
			}

			// reset the timeSinceLastUpdate to 0 
			timeSinceLastUpdate = sf::Time::Zero;
		}
	}  // end while loop

}

void Game::playerShoot() // player shooting function call
{
	myPlayer.moveBullet(); // moves bullet
	myPlayer.whereIsTheBullet(); // checks bullet bools
}

void Game::bossShoot() // boss shooting function call
{
	boss.whereIsTheBullet(); // checks bosses bullets bool
	boss.moveBullet(); // moves bosses bullet
	
}

void Game::levels() // level checking
{
	if (myPlayer.score >= 15 && roundTwoStart == false) // player has killed all wave 1 enemies
	{
		roundOver = true;
		level = 2; // wave is 2
	}

	if (myPlayer.score >= 30 && roundThreeStart == false)  // player has killed all wave 2 enemies
	{
		roundOver = true;
		level = 3; // wave is
	}

	if (myPlayer.score >= 45 && roundFourStart == false)  // player has killed all wave 3 enemies
	{
		roundOver = true;
		level = 4; // boss level
	}
		
}


void Game::update()
// This function takes the keyboard input and updates the game world
{
	if (myPlayer.gameOver == false)
	{
		updateBossHealth();
		follower();  // calls on follower function every frame
		followBoss(); // calls boss follower every frame
		playerShoot(); // check if player shoots every frame

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			myPlayer.moveLeft(); // calls player to move left
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			myPlayer.moveRight(); // calls player to move
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (level > 0 && level < 4)
			{
				myPlayer.moveUp();  // calls player to move normally
			}
			
			if (level == 4) // on level 4 player is restricted to a smaller portian of the screen
			{
				myPlayer.moveUpBoss();
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			myPlayer.moveDown(); // calls player to move
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			myPlayer.shoot(); // calls player shoots function
		}

		if (level == 2 && roundTwoStart == false)   
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			{
				levelTwo(); // starts level 2
			}
		}

		if (level == 3 && roundThreeStart == false)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			{
				levelThree(); // starts level 3
			}
		}

		if (level == 4 && roundFourStart == false)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			{
				levelBoss(); // starts level 4 boss level
			}
		}

		if (roundFourStart == true)
		{
			boss.changeScale(); // makes boss biggir sprite
			boss.shoot(); // boss start shooting
			boss.setPositionToLocation(); 
		}
		
		myPlayer.setPositionToLocation();
		myPlayer.updateBullet();
		collision(); // checks collision every frame
		moveEnemy(); // moves sentry
	}
	// get keyboard input
	

}

void Game::draw()
// This function draws the game world
{
	// Clear the screen and draw your game sprites
	m_message.setString("Health:" + std::to_string(myPlayer.getHealth()));
	m_messageScore.setString("Score:" + std::to_string(myPlayer.getScore()));
	m_messageBase.setString("Base Health:" + std::to_string(myPlayer.getBaseHealth()));
	m_messageLevel.setString("Wave:" + std::to_string(level));
	m_messageGameOver.setString("YOU DIED Press R to Restart");
	m_messageRound.setString("Press Q for next wave");
	m_messageBoss.setString("BOSS HEALTH:" + std::to_string(boss.getHealth()));
	m_messageGameWon.setString("YOU WON Press R to Restart");
	window.clear();
	
	
	if (gameWon == false) // doesnt draw any of the game if the game is won
	{
		window.draw(floorSprite); 

		if (myPlayer.gameOver == true) // if game is over 
		{
			window.draw(m_messageGameOver);
		}

		if (level == 1)
		{
			window.draw(westBase);
		}

		if (level == 2)
		{
			window.draw(northBase);
		}

		if (level == 3)
		{
			window.draw(eastBase);
		}

		if (roundOver)
		{
			window.draw(m_messageRound);// write message to the screen
		}

		window.draw(myPlayer.getBody()); // draws player
		window.draw(Health);
		window.draw(baseHealth);
		if (myPlayer.bulletFired) // only draws if bullet has been fired
		{
			window.draw(myPlayer.getBullet()); // draws players bullet
		}


		if (boss.bulletFired) // only draws if bullet has been fired
		{
			window.draw(boss.getBullet()); // draw bosses bullets
		}
	

		for (int i = 0; i < numOfSentry; i++)
		{
			window.draw(enemySentry[i].getEnemyBody()); // draws enemy sentry
		}

		for (int i = 0; i < numOfFollower; i++)
		{
			window.draw(EnemyFollower[i].getEnemyFollowerBody()); // draws enemy follower
		}

		if (level == 4) // if boss level
		{
			window.draw(bossHealth); // draws boss health
			window.draw(boss.getEnemyFollower()); // draws boss
		}
	}
	else
	{
		window.draw(m_messageGameWon); // draws game victory screen

	}
		
		window.draw(m_message);  // write message to the screen
		window.draw(m_messageScore); // draws score
		window.draw(m_messageBase);// write message to the screen for base
		window.draw(m_messageLevel);// write message to the screen for level counter
	
	window.display();
}


void Game::setUpGame() // sets up wave 1
{
	float xPos = SCREEN_WIDTH;       
	float yPos = SCREEN_HEIGHT / 2;

	enemySentry[0].setPosition(xPos, yPos); // sets up positions for enemy sentries in wave 1 off-set from each other
	enemySentry[1].setPosition(xPos - 2, yPos - 100);
	enemySentry[2].setPosition(xPos + 250, yPos -200);
	enemySentry[3].setPosition(xPos + 70, yPos - 300);
	enemySentry[4].setPosition(xPos - 80, yPos + 100);
	enemySentry[5].setPosition(xPos + 150, yPos + 200);

	EnemyFollower[0].setPosition(xPos , yPos); // sets up positions for enemy followers in wave 1 off-set from each other
	EnemyFollower[1].setPosition(xPos + 250, yPos-150);
	EnemyFollower[2].setPosition(xPos + 350, yPos+150);

	EnemyFollower[0].setSpeed(EnemyFollower[1].speed - 0.8); // off-sets speed in follower so they are diverse and attack diffrently 
	EnemyFollower[2].setSpeed(EnemyFollower[1].speed + 1.5);
}

void Game::levelTwo() // sets up level 2 
{
	roundOver = false; // round is no longer over
	roundTwoStart = true; // round two has started
	int levelTwoX = SCREEN_WIDTH / 2; // midway on the x co-ord
	int levelTwoY = SCREEN_HEIGHT; // start position is bottom of screen

		if (level == 2)
		{
			enemySentry[0].setPosition(levelTwoX + 150, levelTwoY); // sets position of sentries for wave 2 off-set for diversity
			enemySentry[1].setPosition(levelTwoX - 100, levelTwoY - 50);
			enemySentry[2].setPosition(levelTwoX - 250, levelTwoY + 150);
			enemySentry[3].setPosition(levelTwoX + 250, levelTwoY - 125);
			enemySentry[4].setPosition(levelTwoX + 5, levelTwoY + 250);
			enemySentry[5].setPosition(levelTwoX, levelTwoY + 70);
			

			for (int i = 0; i < numOfSentry; i++)
			{
				enemySentry[i].setSpeed(enemySentry[0].speed + 0.95); // increases speed to add difficulty
				enemySentry[i].enemyDied = false; // sentries alive
			}	
		
			EnemyFollower[0].setPosition(levelTwoX - 100, levelTwoY - 100);  // sets position of followers for wave 2 off-set for diversity
			EnemyFollower[1].setPosition(levelTwoX + 200, levelTwoY + 200);
			EnemyFollower[2].setPosition(levelTwoX, levelTwoY);
			for (int i = 0; i < numOfFollower; i++)
			{
				EnemyFollower[i].setSpeed(EnemyFollower[i].speed + 0.52);  // increases speed to add difficulty
				EnemyFollower[i].enemyFollwerDied = false;
			}
			
		}
	
}

void Game::levelThree() // sets up wave 3
{
	roundOver = false; // round started
	roundThreeStart = true; // round three has started
	int levelThreeX = 0; 
	int levelThreeY = SCREEN_HEIGHT / 2;

	if (level == 3)
	{
		enemySentry[0].setPosition(levelThreeX -50, levelThreeY); // set position of sentries for wave 3 
		enemySentry[1].setPosition(levelThreeX - 100, levelThreeY -250); 
		enemySentry[2].setPosition(levelThreeX +50, levelThreeY + 140);
		enemySentry[3].setPosition(levelThreeX + 80, levelThreeY - 172);
		enemySentry[4].setPosition(levelThreeX + 5, levelThreeY + 250);
		enemySentry[5].setPosition(levelThreeX, levelThreeY + 70);


		for (int i = 0; i < numOfSentry; i++)
		{
			enemySentry[i].setSpeed(enemySentry[0].speed + 0.97); // increases speed to add difficulty
			enemySentry[i].enemyDied = false; // they are back in play
		}

		EnemyFollower[0].setPosition(levelThreeX - 100, levelThreeY - 100);  // set position of followers for wave 3 
		EnemyFollower[1].setPosition(levelThreeX - 250, levelThreeY + 200);
		EnemyFollower[2].setPosition(levelThreeX, levelThreeY);

		//EnemyFollower[2].changeScale(1.5,1.5);
		for (int i = 0; i < numOfFollower; i++)
		{
			EnemyFollower[i].setSpeed(EnemyFollower[i].speed + 0.58); // increases speed to add difficulty
			EnemyFollower[i].enemyFollwerDied = false; // they are back in play
		}

	}

}

void Game::levelBoss() // sets up boss level
{
	if (level == 4) // check wave counter
	{
		roundOver = false; // round started
		roundFourStart = true; // round four is started
		
		boss.setPosition(0,-10); // sets boss position
	}
}

void Game::isGameWon() // has player won the game by killing boss
{
	if (boss.getHealth() <= 0) // if boss is dead
	{
		boss.die(); // calls boss death function
		gameWon = true; // game over player has won
	}
}
void Game::restart() // restarts game
{
	gameWon = false; // resets bools
	roundOver = false; 
	roundTwoStart = false;
	roundThreeStart = false;
	roundFourStart = false;
	level = 1;
	myPlayer.restart();
	boss.restart();
	for (int i = 0; i < numOfFollower; i++)
	{
		EnemyFollower[i].restart(); // calls reset follower 
	}

	for (int i = 0; i < numOfSentry; i++)
	{
		enemySentry[i].restart();  // calls reset sentry
	}

	int xPos = SCREEN_WIDTH;        // place the player object in the centre of the screen
	int yPos = SCREEN_HEIGHT / 2;

	enemySentry[0].setPosition(xPos, yPos); // resets position 
	enemySentry[1].setPosition(xPos - 2, yPos - 100);
	enemySentry[2].setPosition(xPos + 250, yPos - 200);
	enemySentry[3].setPosition(xPos + 70, yPos - 300);
	enemySentry[4].setPosition(xPos - 80, yPos + 100);
	enemySentry[5].setPosition(xPos + 150, yPos + 200);

	EnemyFollower[0].setPosition(xPos, yPos);
	EnemyFollower[1].setPosition(xPos + 250, yPos - 150);
	EnemyFollower[2].setPosition(xPos + 350, yPos + 150);



	EnemyFollower[0].setSpeed(EnemyFollower[1].speed - 0.8); // increases difficulty
	EnemyFollower[2].setSpeed(EnemyFollower[1].speed + 1.5);
}



void Game::moveEnemy() // moves enemy
{
	for (int i = 0; i < numOfSentry; i++)
	{
		if (level == 1) // when level
		{
			enemySentry[i].enemyMoveLeft(); // moves sentrys left
		}
		
		if (level == 2)
		{
			enemySentry[i].enemyMoveUp(); // moves sentries up
		}

		if (level == 3)
		{
			enemySentry[i].enemyMoveRight(); // moves enemies right
		}
	}
}

void Game::followBoss() // so boss follows enemy along the Y axis
{
	if (boss.getEnemyFollower().getPosition().x > myPlayer.getBody().getPosition().x) // if enemy is right of the player
	{
		boss.direction = SOUTH; // bullet direction
		boss.enemyFollowerMoveLeft(); // move boss left
	}

	if (boss.getEnemyFollower().getPosition().x < myPlayer.getBody().getPosition().x) // if enemy is left of the player 
	{
		boss.direction = SOUTH;
		boss.enemyFollowerMoveRight(); // move boss right
	}
}

void Game::follower()
{

	for (int i = 0; i < numOfFollower; i++)
	{
		
		if (EnemyFollower[i].getEnemyFollowerBody().getPosition().x > myPlayer.getBody().getPosition().x)  // if enemy is right of the player 
		{
			EnemyFollower[i].enemyFollowerMoveLeft(); // moves follower left
		}

		if (EnemyFollower[i].getEnemyFollowerBody().getPosition().x < myPlayer.getBody().getPosition().x)  // if enemy is left of the player 
		{
			EnemyFollower[i].enemyFollowerMoveRight(); // moves follower right
		}

		if (EnemyFollower[i].getEnemyFollowerBody().getPosition().y > myPlayer.getBody().getPosition().y)  // if enemy is below of the player 
		{
			EnemyFollower[i].enemyFollowerMoveUp(); // moves follower up
		}

		if (EnemyFollower[i].getEnemyFollowerBody().getPosition().y < myPlayer.getBody().getPosition().y)  // if enemy is above of the player 
		{
			EnemyFollower[i].enemyFollowerMoveDown(); // moves follower down
		}
	}
	
	
}

//void Game::dropBase
//{
//	baseHealth.setPosition();
//}

void Game::collision()
{
	for (int i = 0; i < numOfSentry; i++)
	{
		if (enemySentry[i].getEnemyBody().getGlobalBounds().intersects(myPlayer.getBullet().getGlobalBounds())) // if bullet hits sentry
		{
			myPlayer.bulletLocation = sf::Vector2f{ 1000,1000 }; // starting bullet location set
			myPlayer.killedSentry(); // gives score to player
			if (enemySentry[i].droppedBase == true)// && baseHealth.getPosition() == {1500, 1500})
			{
				baseHealth.setPosition(enemySentry[i].getEnemyBody().getPosition()); // sets position of dropped item to killed sentries pos
			}
			enemySentry[i].die(); // calls enemy sentry die
		}
		if (enemySentry[i].leftScreen) // if sentry has hit the bass
		{
			myPlayer.decreaseBase(); // base health -15
			enemySentry[i].leftScreen = false; // reset bool
		}
	}

	for (int i = 0; i < numOfFollower; i++)
	{
		if (EnemyFollower[i].getEnemyFollowerBody().getGlobalBounds().intersects(myPlayer.getBullet().getGlobalBounds())) // if bullet hits follower
		{
			if (EnemyFollower[i].enemyFollwerDied == false) // if enemy is alive
			{
				myPlayer.killedFollower(); // gives player score
			}

			if (EnemyFollower[i].droppedHealth == true)
			{
				Health.setPosition(EnemyFollower[i].getEnemyFollowerBody().getPosition()); // sets position of dropped item to killed sentries pos
			}

			EnemyFollower[i].die(); // follower died
			myPlayer.bulletLocation = sf::Vector2f{ 1000,1000 }; // bullet location reset
		}

		if (EnemyFollower[i].getEnemyFollowerBody().getGlobalBounds().intersects(myPlayer.getBody().getGlobalBounds())) // if follower runs hit the player
		{
			myPlayer.decreaseLives(); // lives decrease
		}
	}
	if (myPlayer.getBody().getGlobalBounds().intersects(boss.getBullet().getGlobalBounds())) // if boss shoots player
	{
		boss.bulletLocation = sf::Vector2f{ 1000,1000 }; // starting bullet location set
		myPlayer.gotShot(); // player loses health
	}

	if (boss.getEnemyFollower().getGlobalBounds().intersects(myPlayer.getBullet().getGlobalBounds())) // if player hits boss
	{
		myPlayer.bulletLocation = sf::Vector2f{ 1000,1000 }; // starting bullet location set
		boss.lessHealth(); // boss loses health
	}

	if (myPlayer.getBody().getGlobalBounds().intersects(baseHealth.getGlobalBounds())) // if player hits base drop
	{
		myPlayer.increaseBase(); // calls to increase base health of player
		baseHealth.setPosition(1500, 1500); // resets position to storage position
	}

	if (myPlayer.getBody().getGlobalBounds().intersects(Health.getGlobalBounds())) // if player hits health drop
	{
		myPlayer.increaseLives(); // calls to increase health of player
		Health.setPosition(1500, 1500);  // resets position to storage position
	}

}
