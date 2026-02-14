#include "Game.h"

#include "GraphicsLib/Resource/ResourceManager.h"
#include "Player.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/trigonometric.hpp"

Game::Game() : _window{ gfx2d::Window::create(1200, 900, "gfx2d") }
{
    loadDefaultResources();
    _player = std::make_shared<Player>();

    auto shader = gfx2d::ResourceManager::getInstance()->getShader("defaultShader");
    _sprite = gfx2d::Sprite::create(shader);

    shader->use();
    shader->setFloat("borderSize", 0.1f);   // для теста БОЛЬШОЙ
    shader->setVector4("debugColor", {1,0,0,1});
    _sprite->setColor(gfx2d::DefColor::White);
    _sprite->setSize(300,300);
    _sprite->setPosition({500,500});

    _window->setOnFrameCallback([&](const float deltaTime) { onTickCallback(deltaTime); });
}

void Game::run() const { _window->runMainLoop(); }

void Game::onTickCallback(const float deltaTime) const 
{
    update(deltaTime);
    render();
}

void Game::render() const
{
    // std::vector<gfx2d::SpritePtr> sprites(9 * 9);
    //
    // const int mapWidth = 9;
    //
    // const float tileWidth = 150.f;
    // const float tileHeight = 75.f;
    //
    // for (int i = 0; i < mapWidth; ++i)
    // {
    //     for (int j = 0; j < mapWidth; ++j)
    //     {
    //         const int a = i * mapWidth + j;
    //
    //         auto shader = gfx2d::ResourceManager::getInstance()->getShader("defaultShader");
    //         shader->use();
    //         shader->setBool("showDebugRect", true);
    //         shader->setVector4("debugColor", {1.0f, 0.0f, 0.0f, 1.0f});
    //         shader->setFloat("borderSize", 0.02f); // ВАЖНО: не 2.0, а 0.02
    //         sprites[a] = gfx2d::Sprite::create(shader);
    //
    //         sprites[a]->setColor(gfx2d::DefColor::Green);
    //         sprites[a]->setSize(tileWidth, tileHeight);
    //
    //         const float isoX = (j - i) * (tileWidth / 2.f);
    //         const float isoY = (j + i) * (tileHeight / 2.f);
    //
    //         sprites[a]->setPosition((isoX + 500) + 10, isoY + 100);
    //     }
    // }
    //
    // for (const auto& sprite : sprites)
    // {
    //     _window->getRenderer()->render(sprite.get());
    // }
    _window->getRenderer()->render(_sprite.get());
    _window->getRenderer()->render(_player->graphicsItem().get());
}

void Game::update(const float deltaTime) const
{
    handleMouseScroll(deltaTime);
    handleKeyboard(deltaTime);

    _player->update(deltaTime);
}

void Game::handleKeyboard(const float deltaTime) const
{
    int speed = 300;
    if (gfx2d::Input::isKeyPressed(gfx2d::Keyboard::LShift))
        speed *= 2;
    else
        speed = 300;

    if (gfx2d::Input::isKeyPressed(gfx2d::Keyboard::W))
        _window->getCamera()->move({ 0, -speed * deltaTime });
    if (gfx2d::Input::isKeyPressed(gfx2d::Keyboard::A))
        _window->getCamera()->move({ -speed * deltaTime, 0 });
    if (gfx2d::Input::isKeyPressed(gfx2d::Keyboard::S))
        _window->getCamera()->move({ 0, speed * deltaTime });
    if (gfx2d::Input::isKeyPressed(gfx2d::Keyboard::D))
        _window->getCamera()->move({ speed * deltaTime, 0 });
}

void Game::handleMouseScroll(float deltaTime) const
{
    if (const auto scroll = gfx2d::Input::consumeMouseScroll(); scroll.y != 0.0f)
    {
        float zoom = _window->getCamera()->getZoom();
        zoom *= (1.0f + scroll.y * 0.1f);
        zoom = std::clamp(zoom, 0.1f, 5.0f);
        _window->getCamera()->setZoom(zoom);
    }
}

void Game::loadDefaultResources()
{
    gfx2d::ResourceManager::getInstance()->loadShader("defaultShader", "Assets/Shaders/Vertex.vert",
                                                      "Assets/Shaders/Fragment.frag");
    gfx2d::ResourceManager::getInstance()->loadTexture("Skin", "Assets/Textures/1.png");
    gfx2d::ResourceManager::getInstance()->loadTexture("Player_idle",
                                                       "Assets/Textures/Player/MPlayer_idle.png");
    gfx2d::ResourceManager::getInstance()->loadTexture("Player_walk",
                                                       "Assets/Textures/Player/MPlayer_walk.png");
}