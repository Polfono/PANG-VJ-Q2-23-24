#include "Menu.h"
#include "ShaderProgramManager.h"
#include <iostream>

Menu::Menu()
{
	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(currentWidth / 1.5f, currentHeight / 1.5f) };
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

	sprite1->setPosition(glm::vec2(round(7.0f/92.0f*currentWidth), round(5.0f/18.0f*currentHeight)));
	sprite2->setPosition(glm::vec2(round(51.0f/92.0f*currentWidth), round(5.0f / 18.0f * currentHeight)));

	menu.loadFromFile("images/menu.png", TEXTURE_PIXEL_FORMAT_RGBA);
	credits.loadFromFile("images/credits.png", TEXTURE_PIXEL_FORMAT_RGBA);
	instructions1.loadFromFile("images/instructions1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	instructions2.loadFromFile("images/instructions2.png", TEXTURE_PIXEL_FORMAT_RGBA);
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
}

void Menu::update(int deltaTime)
{
	sprite1->update(deltaTime);
	sprite2->update(deltaTime);
}

void Menu::setPosIndex(int pos)
{
	if (pos == 0) {
		sprite1->setPosition(glm::vec2(round(70.0f/920.0*currentWidth), round(5.0f / 18.0f * currentHeight)));
		sprite2->setPosition(glm::vec2(round(510.f/920.0f*currentWidth), round(5.0f / 18.0f * currentHeight)));
	} else if (pos == 1) {
		sprite1->setPosition(glm::vec2(round(70.0f / 920.0 * currentWidth), round(265.f/720.f*currentHeight)));
		sprite2->setPosition(glm::vec2(round(510.f / 920.0f * currentWidth), round(265.f / 720.f * currentHeight)));
	} else if (pos == 2) {
		sprite1->setPosition(glm::vec2(round(70.0f / 920.0 * currentWidth), round(330.f/720.f*currentHeight)));
		sprite2->setPosition(glm::vec2(round(510.f / 920.0f * currentWidth), round(330.f / 720.f * currentHeight)));
	} else {
		sprite1->setPosition(glm::vec2(round(70.0f / 920.0 * currentWidth), round(395.f / 720 * currentHeight)));
		sprite2->setPosition(glm::vec2(round(510.f / 920.0f * currentWidth), round(395.f/720*currentHeight)));
	}
}

void Menu::render(int n)
{
	ShaderProgramManager::instance().useShaderProgram();

	if (n == 0) {
		bground->render(menu);
		sprite1->render();
		sprite2->render();
	}
	else if(n == 1)
		bground->render(instructions1);
	else if (n == 2)
		bground->render(instructions2);
	else if (n == 3)
		bground->render(credits);
}

void Menu::resizeMenu(int width, int height)
{
	currentWidth = width;
	currentHeight = height;
	cout << "width " << width << " height " << height << endl;

	glm::vec2 geom[2] = { glm::vec2(0.f, 0.f), glm::vec2(currentWidth / 1.5f, currentHeight / 1.5f) };
	glm::vec2 texCoords[2] = { glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f) };
	bground = TexturedQuad::createTexturedQuad(geom, texCoords, ShaderProgramManager::instance().getShaderProgram());
	sprite1->setPosition(glm::vec2(round(7.0f / 92.0f * currentWidth), round(5.0f / 18.0f * currentHeight)));
	sprite2->setPosition(glm::vec2(round(51.0f / 92.0f * currentWidth), round(5.0f / 18.0f * currentHeight)));
}