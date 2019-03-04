#pragma once
#include <SFML/Graphics.hpp>

class EnemySentry
{
	int speed;
	int numberOf;
	sf::RectangleShape body;
	sf::Vector2f enemyPositonMiddle;
	void Follow(sf::Vector2f);
	void die();
};
