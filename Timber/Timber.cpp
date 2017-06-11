#include "stdafx.h"
#include <sstream>
#include <SFML\Graphics.hpp>

void updateBranches(int seed);
const int NUM_BRANCHES = 6;
sf::Sprite branches[NUM_BRANCHES];

enum class Side { LEFT, RIGHT, NONE };
Side branchPosition[NUM_BRANCHES];

int main()
{
    sf::VideoMode vm(1920, 1080);
    sf::RenderWindow window(vm, "Timber");

    sf::Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");
    sf::Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0, 0);

    sf::Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
    sf::Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810, 0);

    sf::Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    sf::Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 800);

    bool beeIsActive = false;
    float beeSpeed = 0.0f;

    sf::Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");
    sf::Sprite spriteCloud01;
    sf::Sprite spriteCloud02;
    sf::Sprite spriteCloud03;
    spriteCloud01.setTexture(textureCloud);
    spriteCloud02.setTexture(textureCloud);
    spriteCloud03.setTexture(textureCloud);
    spriteCloud01.setPosition(0, 0);
    spriteCloud02.setPosition(0, 250);
    spriteCloud03.setPosition(0, 500);
    bool cloud01IsActive = false;
    bool cloud02IsActive = false;
    bool cloud03IsActive = false;
    float cloud01Speed = 0.0f;
    float cloud02Speed = 0.0f;
    float cloud03Speed = 0.0f;

    sf::Clock clock;
    bool pause = true;

    sf::RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;

    timeBar.setSize(sf::Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(sf::Color::Red);
    timeBar.setPosition(1920 / 2 - timeBarStartWidth / 2, 980);

    sf::Time gameTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    int score = 0;
    sf::Text messageText;
    sf::Text scoreText;

    sf::Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");

    messageText.setFont(font);
    scoreText.setFont(font);

    messageText.setString("Press Enter to start!");
    scoreText.setString("Score = 0");

    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);

    messageText.setFillColor(sf::Color::White);
    scoreText.setFillColor(sf::Color::White);

    sf::FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
    scoreText.setPosition(20, 20);

    sf::Texture textureBranch;
    textureBranch.loadFromFile("graphics/branch.png");
    for (int i = 0; i < NUM_BRANCHES; i++)
    {
        branches[i].setTexture(textureBranch);
        branches[i].setPosition(-2000, -2000);

        branches[i].setOrigin(220, 20);
    }

    sf::Texture texturePlayer;
    texturePlayer.loadFromFile("graphics/player.png");
    sf::Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setPosition(580, 720);

    Side playerSide = Side::LEFT;

    sf::Texture textureRip;
    textureRip.loadFromFile("graphics/rip.png");
    sf::Sprite spriteRip;
    spriteRip.setTexture(textureRip);
    spriteRip.setPosition(600, 860);

    sf::Texture textureAxe;
    textureAxe.loadFromFile("graphics/axe.png");
    sf::Sprite spriteAxe;
    spriteAxe.setTexture(textureAxe);
    spriteAxe.setPosition(700, 830);

    const float AXE_POSITION_LEFT = 700;
    const float AXE_POSITION_RIGHT = 1075;

    sf::Texture textureLog;
    textureLog.loadFromFile("graphics/log.png");
    sf::Sprite spriteLog;
    spriteLog.setTexture(textureLog);
    spriteLog.setPosition(810, 720);

    bool isLogActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;

    bool acceptInput = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyReleased && !pause)
            {
                acceptInput = true;

                spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            pause = false;

            score = 0;
            timeRemaining = 5;

            for (int i = 0; i < NUM_BRANCHES; i++)
            {
                branchPosition[i] = Side::NONE;
            }

            spriteRip.setPosition(675, 2000);

            spritePlayer.setPosition(580, 720);
            acceptInput = true;
        }

        if (acceptInput)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                playerSide = Side::RIGHT;
                score++;

                timeRemaining += (2 / score) + .15;

                spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);

                spritePlayer.setPosition(1200, 720);

                updateBranches(score);

                spriteLog.setPosition(810, 720);
                logSpeedX = -5000;
                isLogActive = true;
                acceptInput = false;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                playerSide = Side::LEFT;
                score++;

                timeRemaining += (2 / score) + .15;

                spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);

                spritePlayer.setPosition(580, 720);

                updateBranches(score);

                spriteLog.setPosition(810, 720);
                logSpeedX = 5000;
                isLogActive = true;
                acceptInput = false;
            }
        }

        if (!pause)
        {
            sf::Time delta = clock.restart();

            timeRemaining -= delta.asSeconds();
            timeBar.setSize(sf::Vector2f(timeBarWidthPerSecond* timeRemaining, timeBarHeight));

            if (timeRemaining <= 0.0f)
            {
                pause = true;

                messageText.setString("Time has run out!");
                sf::FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                messageText.setPosition(1920 / 2.0f, 108 / 2.0f);
            }

            if (!beeIsActive)
            {
                srand((int)time(0) * 10);
                beeSpeed = (rand() % 200) + 200;

                srand((int)time(0) * 10);
                float height = (rand() % 500) + 500;
                spriteBee.setPosition(2000, height);
                beeIsActive = true;
            }
            else
            {
                spriteBee.setPosition(
                    spriteBee.getPosition().x - (beeSpeed * delta.asSeconds()),
                    spriteBee.getPosition().y);

                if (spriteBee.getPosition().x < -100)
                {
                    beeIsActive = false;
                }
            }

            if (!cloud01IsActive)
            {
                srand((int)time(0) * 10);
                cloud01Speed = (rand() % 200);

                srand((int)time(0) * 10);
                float height = (rand() % 150);
                spriteCloud01.setPosition(-200, height);
                cloud01IsActive = true;
            }
            else
            {
                spriteCloud01.setPosition(
                    spriteCloud01.getPosition().x + (cloud01Speed * delta.asSeconds()),
                    spriteCloud01.getPosition().y);

                if (spriteCloud01.getPosition().x > 1920)
                {
                    cloud01IsActive = false;
                }
            }

            if (!cloud02IsActive)
            {
                srand((int)time(0) * 20);
                cloud02Speed = (rand() % 200);

                srand((int)time(0) * 20);
                float height = (rand() % 300) - 150;
                spriteCloud02.setPosition(-200, height);
                cloud02IsActive = true;
            }
            else
            {
                spriteCloud02.setPosition(
                    spriteCloud02.getPosition().x + (cloud02Speed * delta.asSeconds()),
                    spriteCloud02.getPosition().y);

                if (spriteCloud02.getPosition().x > 1920)
                {
                    cloud02IsActive = false;
                }
            }

            if (!cloud03IsActive)
            {
                srand((int)time(0) * 30);
                cloud03Speed = (rand() % 200);

                srand((int)time(0) * 30);
                float height = (rand() % 450) - 450;
                spriteCloud03.setPosition(-200, height);
                cloud03IsActive = true;
            }
            else
            {
                spriteCloud03.setPosition(
                    spriteCloud03.getPosition().x + (cloud03Speed * delta.asSeconds()),
                    spriteCloud03.getPosition().y);

                if (spriteCloud03.getPosition().x > 1920)
                {
                    cloud03IsActive = false;
                }
            }

            std::stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());

            for (int i = 0; i < NUM_BRANCHES; i++)
            {
                float height = i * 150;
                if (branchPosition[i] == Side::LEFT)
                {
                    branches[i].setPosition(610, height);
                    branches[i].setRotation(180);
                }
                else if (branchPosition[i] == Side::RIGHT)
                {
                    branches[i].setPosition(1330, height);
                    branches[i].setRotation(0);
                }
                else
                {
                    branches[i].setPosition(3000, height);
                }
            }

            if (isLogActive)
            {
                spriteLog.setPosition(spriteLog.getPosition().x + (logSpeedX * delta.asSeconds()),
                    spriteLog.getPosition().y + (logSpeedY * delta.asSeconds()));

                if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().y >2000)
                {
                    isLogActive = false;
                    spriteLog.setPosition(810, 720);
                }
            }
        }

        window.clear();

        window.draw(spriteBackground);

        window.draw(spriteCloud01);
        window.draw(spriteCloud02);
        window.draw(spriteCloud03);

        for (int i = 0; i < NUM_BRANCHES; i++)
        {
            window.draw(branches[i]);
        }

        window.draw(spriteTree);

        window.draw(spritePlayer);
        window.draw(spriteAxe);
        window.draw(spriteLog);
        window.draw(spriteRip);

        window.draw(spriteBee);

        window.draw(scoreText);

        window.draw(timeBar);
        if (pause)
        {
            window.draw(messageText);
        }

        window.display();
    }

    return 0;
}

void updateBranches(int seed)
{
    for (int i = NUM_BRANCHES - 1; i > 0; i--)
    {
        branchPosition[i] = branchPosition[i - 1];
    }

    srand((int)time(0) + seed);
    int r = (rand() % 5);

    switch (r)
    {
    case 0:
        branchPosition[0] = Side::LEFT;
        break;
    case 1:
        branchPosition[0] = Side::RIGHT;
        break;
    default:
        branchPosition[0] = Side::NONE;
        break;
    }
}