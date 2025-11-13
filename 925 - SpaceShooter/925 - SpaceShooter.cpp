#include <random>

#include "enemy_manager.hpp"
#include "SFML/Graphics.hpp"
#include "Motor.h"
#include "starship_player.hpp"
#include "state_manager.hpp"
#include "ui.hpp"

int main()
{
	constexpr sf::Vector2f playerSpawmPosition = { 600, 1500 };

		sf::RenderWindow window(sf::VideoMode({ 1200, 1600 }), "The Game");
		sf::Clock clock;

	StarshipPlayer starship_player;
	starship_player.Load(playerSpawmPosition);

	EnemyManager enemies;

	UI ui;
	ui.Load(window);


	// Basic Setup of the window
	// Vertical sync, framerate
	window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(30);

	while (window.isOpen())
	{

		sf::Time deltaTime = clock.restart();


		// on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
					window.close();
			}
		}

		// Inputs ----------------------------------------------------------------------------------------
		starship_player.HandleEvent();
		if (starship_player.CheckCollisions(enemies.GetEntities()))
		{
			// Game Play ......................
			StateManager::LostLife();
			starship_player.SetPosition(playerSpawmPosition);
			starship_player.SetShield(3.0f);
		}
		starship_player.CheckProjectileCollisions(enemies.GetEntities());

		// Physics FRAME
		// Updates ----------------------------------------------------------------------------------------
		starship_player.Update(window, deltaTime.asSeconds());
		enemies.Update(window, deltaTime.asSeconds());
		ui.Update();

		// Graphical FRAME ---------------------------------------
		window.clear(sf::Color::Black);
				
		window.draw(enemies);
		window.draw(starship_player);
		window.draw(ui);

		// Window Display
		window.display();


	}



}
