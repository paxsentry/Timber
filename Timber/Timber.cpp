#include "stdafx.h"
#include <sstream>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

void updateBranches(int seed);
const int NUM_BRANCHES = 6;
sf::Sprite branches[NUM_BRANCHES];

enum class Side { LEFT, RIGHT, NONE };
Side branchPosition[NUM_BRANCHES];

int main()
{
    sf::VideoMode vm(1920, 1080);
    sf::RenderWindow window(vm, "Timber");
    window.setFramerateLimit(60);

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

    sf::Texture tree2;
    tree2.loadFromFile("graphics/tree2.png");
    sf::Sprite spriteTree2;
    spriteTree2.setTexture(tree2);
    spriteTree2.setPosition(20, 0);

    sf::Sprite spriteTree3;
    spriteTree3.setTexture(tree2);
    spriteTree3.setPosition(300, -400);

    sf::Sprite spriteTree4;
    spriteTree4.setTexture(tree2);
    spriteTree4.setPosition(1300, -400);

    sf::Sprite spriteTree5;
    spriteTree5.setTexture(tree2);
    spriteTree5.setPosition(1500, -500);

    sf::Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    sf::Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 800);

    bool beeIsActive = false;
    float beeSpeed = 0.0f;

    sf::Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");
    const int NUM_CLOUDS = 6;
    sf::Sprite clouds[NUM_CLOUDS];
    int cloudSpeed[NUM_CLOUDS];
    bool cloudIsActive[NUM_CLOUDS];

    for (int i = 0; i < NUM_CLOUDS; i++)
    {
        clouds[i].setTexture(textureCloud);
        clouds[i].setPosition(-300, i * 150);
        cloudIsActive[i] = false;
        cloudSpeed[i] = 0;
    }

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
    sf::Text fpsText;

    sf::Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");

    messageText.setFont(font);
    scoreText.setFont(font);
    fpsText.setFont(font);

    messageText.setString("Press Enter to start!");
    scoreText.setString("Score = 0");

    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);

    messageText.setFillColor(sf::Color::White);
    scoreText.setFillColor(sf::Color::White);
    fpsText.setFillColor(sf::Color::White);

    sf::FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
    scoreText.setPosition(20, 20);

    fpsText.setPosition(1200, 20);

    sf::RectangleShape textBg;
    textBg.setFillColor(sf::Color(0, 0, 0, 150));
    textBg.setSize(sf::Vector2f(600, 105));
    textBg.setPosition(0, 30);

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

    sf::SoundBuffer chopBuffer;
    chopBuffer.loadFromFile("sound/chop.wav");
    sf::Sound chop;
    chop.setBuffer(chopBuffer);

    sf::SoundBuffer deathBuffer;
    deathBuffer.loadFromFile("sound/death.wav");
    sf::Sound death;
    death.setBuffer(deathBuffer);

    sf::SoundBuffer outOfTimeBuffer;
    outOfTimeBuffer.loadFromFile("sound/out_of_time.wav");
    sf::Sound outOfTime;
    outOfTime.setBuffer(outOfTimeBuffer);

    int lastDrawn = 0;

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

                chop.play();
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

                chop.play();
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

                outOfTime.play();
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

            for (int i = 0; i < NUM_CLOUDS; i++)
            {
                if (!cloudIsActive[i])
                {
                    srand((int)time(0) * 10);
                    cloudSpeed[i] = (rand() % 200);

                    srand((int)time(0) * 10);
                    float height = (rand() % 150);
                    clouds[i].setPosition(-200, height);
                    cloudIsActive[i] = true;
                }
                else
                {
                    clouds[i].setPosition(
                        clouds[i].getPosition().x + (cloudSpeed[i] * delta.asSeconds()),
                        clouds[i].getPosition().y);

                    if (clouds[i].getPosition().x > 1920)
                    {
                        cloudIsActive[i] = false;
                    }
                }
            }

            lastDrawn++;

            if (lastDrawn == 100)
            {
                std::stringstream ss;
                ss << "Score = " << score;
                scoreText.setString(ss.str());

                std::stringstream ssFps;
                ssFps << "FPS: " << 1 / delta.asSeconds();
                fpsText.setString(ssFps.str());
                lastDrawn = 0;
            }

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

            if (branchPosition[5] == playerSide)
            {
                pause = true;
                acceptInput = false;

                spriteRip.setPosition(525, 760);
                spriteAxe.setPosition(2000, 660);
                spritePlayer.setPosition(2000, 660);

                messageText.setString("SQUISHED!!!");

                sf::FloatRect textRect = messageText.getLocalBounds();

                messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

                messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

                death.play();
            }
        }

        window.clear();

        window.draw(spriteBackground);

        for (int i = 0; i < NUM_CLOUDS; i++)
        {
            window.draw(clouds[i]);
        }

        for (int i = 0; i < NUM_BRANCHES; i++)
        {
            window.draw(branches[i]);
        }

        window.draw(spriteTree);
        window.draw(spriteTree2);
        window.draw(spriteTree3);
        window.draw(spriteTree4);
        window.draw(spriteTree5);

        window.draw(spritePlayer);
        window.draw(spriteAxe);
        window.draw(spriteLog);
        window.draw(spriteRip);

        window.draw(spriteBee);

        window.draw(scoreText);
        window.draw(textBg);

        window.draw(fpsText);

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