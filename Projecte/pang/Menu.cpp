#include "Menu.h"
#include "ShaderProgramManager.h"
#include "Constants.h"

Menu::Menu()
{
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	bground = TexturedQuad::createTexturedQuad(geom, texCoords, ShaderProgramManager::instance().getShaderProgram());

	spritesheet.loadFromFile("images/cangrejos.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite1 = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.25f, 1.f), &spritesheet, &ShaderProgramManager::instance().getShaderProgram());
	sprite1->setNumberAnimations(4);
	sprite1->setAnimationSpeed(0, 3);
	sprite1->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite1->addKeyframe(0, glm::vec2(0.25f, 0.f));
	sprite1->addKeyframe(0, glm::vec2(0.5f, 0.f));
	sprite1->addKeyframe(0, glm::vec2(0.75f, 0.f));
	sprite1->changeAnimation(0);


	sprite2 = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.25f, 1.f), &spritesheet, &ShaderProgramManager::instance().getShaderProgram());
	sprite2->setNumberAnimations(4);
	sprite2->setAnimationSpeed(0, 3);
	sprite2->addKeyframe(0, glm::vec2(0.f, 0.f));
	sprite2->addKeyframe(0, glm::vec2(0.25f, 0.f));
	sprite2->addKeyframe(0, glm::vec2(0.5f, 0.f));
	sprite2->addKeyframe(0, glm::vec2(0.75f, 0.f));
	sprite2->changeAnimation(0);

	sprite1->setPosition(glm::vec2(70.f, 200.f));
	sprite2->setPosition(glm::vec2(510.f, 200.f));

	scene.loadFromFile("images/menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
}

Menu::~Menu()
{
	if (sprite1 != NULL)
		delete sprite1;
	if (sprite2 != NULL)
		delete sprite2;
	if (bground != NULL)
		delete bground;
}

void Menu::init(const int& idScene)
{
	scene.setWrapS(GL_CLAMP_TO_EDGE);
	scene.setWrapT(GL_CLAMP_TO_EDGE);
	scene.setMinFilter(GL_NEAREST);
	scene.setMagFilter(GL_NEAREST);
}

void Menu::update(int deltaTime)
{
	sprite1->update(deltaTime);
	sprite2->update(deltaTime);
}

void Menu::setPosIndex(int pos)
{
	if (pos == 0) {
		sprite1->setPosition(glm::vec2(70.f, 200.f));
		sprite2->setPosition(glm::vec2(510.f, 200.f));
	} else if (pos == 1) {
		sprite1->setPosition(glm::vec2(70.f, 265.f));
		sprite2->setPosition(glm::vec2(510.f, 265.f));
	} else if (pos == 2) {
		sprite1->setPosition(glm::vec2(70.f, 330.f));
		sprite2->setPosition(glm::vec2(510.f, 330.f));
	} else {
		sprite1->setPosition(glm::vec2(70.f, 395.f));
		sprite2->setPosition(glm::vec2(510.f, 395.f));
	}
}

void Menu::render()
{
	ShaderProgramManager::instance().useShaderProgram();
	bground->render(scene);
	sprite1->render();
	sprite2->render();
}