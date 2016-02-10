#include "SimpleAudioEngine.h"
#include "GameScene.h"

USING_NS_CC;

const int height = 500;
const int width = 500;
int head_x, head_y, food_x, food_y;
int body_x[2500], body_y[2500];
int nBody;
int score;
bool lose;

enum direction { LEFT, RIGHT, UP, DOWN, STOP = 0 };
direction dir;

Scene* GameScene::createScene()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("intro.wav");
	audio->playBackgroundMusic("intro.wav");

	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}


bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	
	auto bg = Sprite::create("background.png");
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setPosition(0, 0);
	this->addChild(bg);

	lose = false;
	dir = STOP;
	head_x = width / 2;
	head_y = height / 2;
	food_x = rand() % width;
	food_y = rand() % height;
	score = 0;

	auto head = Sprite::create("head.png");
	
	for (int i = 0; i < width + 2; i++)
	{
		auto wall_0 = Sprite::create("wall.png");
		wall_0->setAnchorPoint(Vec2(0.5, 0.5));
		wall_0->setPosition(i, 0);
		this->addChild(wall_0);
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
			{
				auto wall_1 = Sprite::create("wall.png");
				wall_1->setAnchorPoint(Vec2(0.5, 0.5));
				wall_1->setPosition(j, i);
				this->addChild(wall_1);
			}
			if (i == head_y && j == head_x)
			{
				head->setAnchorPoint(Vec2(0.5, 0.5));
				head->setPosition(j, i);
				this->addChild(head);
			}
			else if (i == food_y && j == food_x)
			{
				auto food = Sprite::create("food.png");
				food->setAnchorPoint(Vec2(0.5, 0.5));
				food->setPosition(j, i);
				this->addChild(food);
			}
			else
			{
				for (int k = 0; k < nBody; k++)
				{
					if (body_x[k] == j && body_y[k] == i)
					{
						auto body = Sprite::create("body.png");
						body->setAnchorPoint(Vec2(0.5, 0.5));
						body->setPosition(j, i);
						this->addChild(body);
					}
				}
			}
			if (j == width - 1)
			{
				auto wall_2 = Sprite::create("wall.png");
				wall_2->setAnchorPoint(Vec2(0.5, 0.5));
				wall_2->setPosition(j, i);
				this->addChild(wall_2);
			}
		}
	}
	for (int i = 0; i < width + 2; i++)
	{
		auto wall_3 = Sprite::create("wall.png");
		wall_3->setAnchorPoint(Vec2(0.5, 0.5));
		wall_3->setPosition(i, 0);
		this->addChild(wall_3);
	}

	auto eventListener = EventListenerKeyboard::create();

	eventListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {

		Vec2 loc = event->getCurrentTarget()->getPosition();
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_A:
			dir = LEFT;
			event->getCurrentTarget()->setPosition(loc.x - 15, loc.y);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D:
			dir = RIGHT;
			event->getCurrentTarget()->setPosition(loc.x + 15, loc.y);
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		case EventKeyboard::KeyCode::KEY_W:
			dir = UP;
			event->getCurrentTarget()->setPosition(loc.x, loc.y + 15);
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_S:
			dir = DOWN;
			event->getCurrentTarget()->setPosition(loc.x, loc.y - 15);
			break;
		}
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, head);

	this->scheduleUpdate();
	return true;
}

void GameScene::update(float delta) 
{
	
}
