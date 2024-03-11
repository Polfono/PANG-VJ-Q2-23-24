#include "Powerup.h"
#include "PowerupsManager.h"
#include "Game.h"
#include <iostream>
#include <chrono>


void Powerup::init(glm::vec2 pos, const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	auto currentTime = std::chrono::system_clock::now();
	auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime.time_since_epoch()).count();

	// Inicializa la semilla srand con el valor de la marca de tiempo
	srand(static_cast<unsigned int>(timestamp));
	type = PowerupType(rand() % 5);
	posPowerup = glm::ivec2(pos.x, std::min(pos.y, 184.f));

	spritesheet.loadFromFile("images/powerups.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(0.33332f, 0.33332f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);
	sprite->setAnimationSpeed(0, 8);

	if (type == DYNAMITE) sprite->addKeyframe(0, glm::vec2(0.66664f, 0.33332f));
	else if (type == FREEZETIME) sprite->addKeyframe(0, glm::vec2(0.f, 0.33332f));
	else if (type == INVINCIBILITY) sprite->addKeyframe(0, glm::vec2(0.33332f, 0.66664f));
	else if (type == SLOWTIME) sprite->addKeyframe(0, glm::vec2(0.33332f, 0.33332f));
	else if (type == EXTRALIFE) sprite->addKeyframe(0, glm::vec2(0.f, 0.66664f));


	sprite->addKeyframe(1, glm::vec2(0.66664f, 0.66664f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
}

void Powerup::update()
{
	timeCounter++;

	// Si el contador de tiempo es mayor que 7 segundos
	if (timeCounter > 420) {
		blinking = true;
	}

	if (blinking && timeCounter % 30 == 0) {
		sprite->changeAnimation(1);
	}
	else if (blinking && timeCounter % 30 == 15) {
		sprite->changeAnimation(0);
	}

	if (timeCounter > 600) {
		PowerupsManager::instance()->removePowerup(this);
		return;
	}

	// gravedad
	posPowerup.y += 1.75f;
	map->collisionMoveDownPlayer(posPowerup, glm::ivec2(16, 16), &posPowerup.y);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPowerup.x), float(tileMapDispl.y + posPowerup.y)));
}

void Powerup::render()
{
	sprite->render();
}

void Powerup::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Powerup::checkCollision(glm::vec2 posPlayer)
{
	if(this == nullptr) return;
	if ((posPlayer.x + 30 > posPowerup.x && posPlayer.x < posPowerup.x + 16) && (posPlayer.y + 32 > posPowerup.y && posPlayer.y < posPowerup.y + 16)) {
		SoundManager::instance().getSoundEngine()->play2D("sounds/item.mp3", GL_FALSE);

		// Aplicar efecto
		if (type == DYNAMITE) Game::instance().dynamite();

		else if (type == FREEZETIME) Game::instance().freezeTime();

		else if (type == INVINCIBILITY) {

		}
		else if (type == SLOWTIME) Game::instance().slowTime();
		else if (type == EXTRALIFE) Game::instance().extraLife();

		PowerupsManager::instance()->removePowerup(this);
	}
}	