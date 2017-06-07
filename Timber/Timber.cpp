#include "stdafx.h"
#include <SFML\Graphics.hpp>

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

    while (window.isOpen())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        sf::Time delta = clock.restart();

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

        window.clear();

        window.draw(spriteBackground);
        window.draw(spriteTree);
        window.draw(spriteBee);
        window.draw(spriteCloud01);
        window.draw(spriteCloud02);
        window.draw(spriteCloud03);

        window.display();
    }

    return 0;
}