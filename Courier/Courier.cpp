/***************************************************************/
/*  THIS GAME WAS PROGRAMMED AND CREATED BY JOONAS HEINONEN AS */
/*  AN INDEPENDENT PROJECT WITH C++/SFML IN 2018.              */
/***************************************************************/

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Road.h"
#include "Player.h"
#include "EnemyCar.h"

using namespace sf;
using namespace std;

const int WIDTH = 640, HEIGHT = 480;

const float DEFAULT_SPEED = 2.0f;

int main()
{
	enum class State { 
		START,
		PAUSED, 
		GAME_OVER, 
		PLAYING
	};

	State state = State::START;

	// Get the screen resolution and create an SFML window
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	RenderWindow window(VideoMode(WIDTH, HEIGHT),
		"Courier", Style::Close);

	// Create a an SFML View for the main action
	View mainView(sf::FloatRect(0, 0, WIDTH, HEIGHT));

	// Here is our clock for timing everything
	Clock clock;
	// How long has the playing STATE been active
	Time gameTimeTotal;

	// Prepare the objects for road
	Road road1;
	road1.setPosition(0, -480);
	Road road2;
	road2.setPosition(0, 0);

	// Create an instance of the Player class
	Player player;

	// Create instances of the EnemyCar class
	EnemyCar enemy1;
	enemy1.spawn(resolution);

	// The boundaries of the arena
	IntRect arena;

	// Hide the mouse cursor
	window.setMouseCursorVisible(false);

	// Health bar
	RectangleShape healthBar;
	RectangleShape healthBarBasis;
	healthBar.setFillColor(Color::Red);
	healthBarBasis.setFillColor(Color::Black);
	healthBar.setPosition(275, 420);
	healthBarBasis.setPosition(273, 418);

	// Prepare the start sound
	SoundBuffer startBuffer;
	startBuffer.loadFromFile("sound/start.wav");
	Sound start;
	start.setBuffer(startBuffer);
	start.setVolume(50);

	// Prepare the hit sound
	SoundBuffer hitBuffer;
	hitBuffer.loadFromFile("sound/hit.wav");
	Sound hit;
	hit.setBuffer(hitBuffer);
	hit.setVolume(50);

	// Prepare the game over sound
	SoundBuffer failureBuffer;
	failureBuffer.loadFromFile("sound/failure.wav");
	Sound failure;
	failure.setBuffer(failureBuffer);

	// Prepare the game music
	Music playTrack;
	if (!playTrack.openFromFile("music/track00.wav"))
		std::cout << "Can not find track00.ogg" << std::endl;
	playTrack.setVolume(15);

	// Prepare the scores / hi score
	int score = 0;
	int hiScore = 0;

	// Prepare the start screen
	Sprite spriteStart;
	Texture textureStart;
	textureStart.loadFromFile("graphics/Start.png");
	spriteStart.setTexture(textureStart);
	spriteStart.setPosition(0, 0);

	// Prepare the game over screen
	Sprite spriteGameOver;
	Texture textureGameOver;
	textureGameOver.loadFromFile("graphics/GameOver.png");
	spriteGameOver.setTexture(textureGameOver);
	spriteGameOver.setPosition(0, 0);

	// Prepare the font for the game to use
	Font font;
	font.loadFromFile("fonts/VertigoFLF.ttf");

	// Credits text
	Text creditsText;
	creditsText.setFont(font);
	creditsText.setCharacterSize(25);
	creditsText.setFillColor(Color::White);
	creditsText.setPosition(10, 370);
	creditsText.setString("Courier is developed by Joonas Heinonen\nYear developed: 2018\nTechnologies used: SFML and C++");

	// Start text
	Text startText;
	startText.setFont(font);
	startText.setCharacterSize(80);
	startText.setFillColor(Color::White);
	startText.setPosition(110, 130);
	startText.setString("Press Enter to start!");

	// Game Over
	Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(100);
	gameOverText.setFillColor(Color::White);
	gameOverText.setPosition(105, 130);
	gameOverText.setString("    YOU NOOB!\nPress Esc to quit");

	// Pasued text
	Text pausedText;
	pausedText.setFont(font);
	pausedText.setCharacterSize(80);
	pausedText.setFillColor(Color::White);
	pausedText.setPosition(200, 180);
	pausedText.setString("Game paused");

	// Score
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(40);
	scoreText.setFillColor(Color::White);
	scoreText.setPosition(20, 20);

	// Load the high score from a text file/
	std::ifstream inputFile("gamedata/scores.txt");
	if (inputFile.is_open())
	{
		inputFile >> hiScore;
		inputFile.close();
	}

	// Notification of updating Hi Score
	Text updateHiScoreText;
	updateHiScoreText.setFont(font);
	updateHiScoreText.setCharacterSize(60);
	updateHiScoreText.setFillColor(Color::White);
	updateHiScoreText.setPosition(140, 10);

	// Hi Score
	Text hiScoreText;
	hiScoreText.setFont(font);
	hiScoreText.setCharacterSize(60);
	hiScoreText.setFillColor(Color::White);
	hiScoreText.setPosition(140, 380);
	std::stringstream s;
	s << "Highest score by now: " << hiScore;
	hiScoreText.setString(s.str());

	// Danger
	Text dangerText;
	dangerText.setFont(font);
	dangerText.setCharacterSize(30);
	dangerText.setFillColor(Color::Red);
	dangerText.setPosition(240, 220);
	dangerText.setString("DANGER! HEALTH TOO LOW!");

	while (window.isOpen())
	{
		Event event;
		Time dt = clock.restart();

		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
			{
				// Pause a game while playing
				if (event.key.code == Keyboard::Return &&
					state == State::START)
				{
					state = State::PLAYING;
					start.play();
				}
				// Pause a game while playing
				if (event.key.code == Keyboard::Space &&
					state == State::PLAYING)
				{
					state = State::PAUSED;
				}
				// Restart while paused
				else if (event.key.code == Keyboard::Space &&
					state == State::PAUSED)
				{
					state = State::PLAYING;
					// Reset the clock so there isn't a frame jump
					clock.restart();
				}
				// Start a new game while in GAME_OVER state
				else if (event.key.code == Keyboard::Return &&
					state == State::GAME_OVER)
				{
					cout << "You failed!" << endl;
				}
				if (state == State::PLAYING)
				{
				}
			} // End event polling
		}

		// Quit the game via Escape-key
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Quit the game via X-button
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}

		// Handle controls while playing
		if (state == State::PLAYING)
		{
			// Handle the pressing and releasing of the WASD keys

			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				player.moveUp();
			}
			else
			{
				player.stopUp();
			}

			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				player.moveDown();
			}
			else
			{
				player.stopDown();
			}

			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				player.moveLeft();
			}
			else
			{
				player.stopLeft();
			}

			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				player.moveRight();
			}
			else
			{
				player.stopRight();
			}
		}

		if (state == State::START)
		{
			window.draw(spriteStart);
			window.draw(startText);
			window.draw(creditsText);
			playTrack.setLoop(true);
			playTrack.play();
		}

		// Handle controls while playing
		if (state == State::PLAYING)
		{
			// Prepare thelevel
			// We will modify the next two lines later
			arena.width = 640;
			arena.height = 480;
			arena.left = 0;
			arena.top = 0;

			// Spawn the player in the middle of the arena
			player.spawn(arena, resolution);

			// Reset the clock so there isn't a frame jump
			clock.restart();
		}

		if (state == State::PLAYING)
		{

			// Update the delta time
			Time dt = clock.restart();

			// Update the total game time
			gameTimeTotal += dt;

			// Make a decimal fraction of 1 from the delta time
			float dtAsSeconds = dt.asSeconds();

			// Update the player
			player.update();

			// Make a note of the players current position
			Vector2f playerPosition(player.getCenter());

			// Update the enemy
			enemy1.update();

			// Update the roads
			road1.update();
			road2.update();

			if (player.getPosition().intersects(enemy1.getPosition()))
			{
				player.decreaseHealth(30);
				score += 10;
				hit.play();
				enemy1.spawn(resolution);
				if (score > hiScore)
				{
					hiScore = score;
				}
			}
			if (player.getHealth() <= 0)
			{
				state = State::GAME_OVER;
				std::ofstream outputFile("gamedata/scores.txt");
				outputFile << hiScore;
				outputFile.close();
				playTrack.stop();
				failure.play();
			}

			// Update game HUD text
			std::stringstream ssScore;

			// Update the score text
			ssScore << "Score: " << score;
			scoreText.setString(ssScore.str());
		} // End updating the scene

		 // Size up the health bar
		healthBar.setSize(Vector2f(player.getHealth() * 1, 20));
		healthBarBasis.setSize(Vector2f(94, 24));

		window.setFramerateLimit(50);

		if (state == State::PLAYING)
		{
			window.clear();

			// set the mainView to be displayed in the window
			// And draw everything related to it
			window.setView(mainView);

			window.draw(road1.getSprite());
			window.draw(road2.getSprite());

			// Draw the player
			window.draw(player.getSprite());

			// Draw the enemy
			window.draw(enemy1.getSprite());

			// Draw the HUD
			window.draw(healthBarBasis);
			window.draw(healthBar);

			if (player.getHealth() < 30)
			{
				window.draw(dangerText);
			}

			window.draw(scoreText);
		}

		if (state == State::PAUSED)
		{
			window.draw(pausedText);
		}

		if (state == State::GAME_OVER)
		{
			window.draw(spriteGameOver);
			window.draw(gameOverText);
			window.draw(hiScoreText);
			// Update the high score, if an update happened
			std::stringstream us;
			if (score < hiScore)
			{
				updateHiScoreText.setPosition(115, 10);
				us << "High Score remains the same.";
			}
			else
			{
				updateHiScoreText.setPosition(160, 10);
				us << "You made new record!";
			}
			updateHiScoreText.setString(us.str());
			window.draw(updateHiScoreText);
		}
		window.display();
	}
	return 0;
}