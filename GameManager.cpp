#include "GameManager.h"

GameManager::GameManager(int width, int height)
{
	audioManager = new AudioManager();
	mapCreator = new MapCreator();
	uiManager = new UIManager(width, height);
	battleController = new BattleController();
	player = new Player(new Vector2(0, 5));
	this->width = width;
	this->height = height;
}

void GameManager::init()
{
	player->init();
	mapCreator->loadMap(player->getFloor());
	uiManager->init();
}

void GameManager::load()
{
}

void GameManager::save()
{
}

void GameManager::drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	player->display();

	mapCreator->display(player->getPositon());
	detectCollision();

	glRotatef(360.0f - player->getSpinY(), 0, 1, 0);
	glTranslatef(-player->getPositon()->x, -player->getPositon()->y, -player->getPositon()->z);

	// 绘制3D场景
	mapCreator->createMap3D();

	bool status = false;
	glMatrixMode(GL_PROJECTION);						// 选择透视矩阵
	glLoadIdentity();									// 重设透视矩阵

	glOrtho(0.0f, width, height, 0.0f, -1.0f, 1.0f);   // 设置平行投影

	glMatrixMode(GL_MODELVIEW);							// 选择模型矩阵
	glLoadIdentity();								// 重新载入模型矩阵
	mapCreator->createMap2D(width, height);

	glEnable(GL_BLEND);
	player->draw2D(width, height);
	glDisable(GL_BLEND);

	uiManager->draw(player);

	glMatrixMode(GL_PROJECTION);						// 选择透视矩阵
	glLoadIdentity();									// 重设透视矩阵

	gluPerspective(60.0f, width * 1.3f / height, 0.1f, 1000.0f); //	设置回透视投影

	glMatrixMode(GL_MODELVIEW);							// 选择模型矩阵
	glLoadIdentity();									// 重新载入模型矩阵

}

void GameManager::setWindow(int width, int height)
{
	this->width = width;
	this->height = height;
	uiManager->setWindow(width, height);
}

void GameManager::upStairs()
{
	player->upStairs(mapCreator->getUpPosition(), mapCreator->getUpDirection());
	mapCreator->loadMap(player->getFloor());
}

void GameManager::downStairs()
{
	player->downStairs(mapCreator->getDownPosition(), mapCreator->getDownDirection());
	mapCreator->loadMap(player->getFloor());
}

void GameManager::movePlayer(bool isUp)
{
	Object* object;
	if (isUp)
		object = mapCreator->getObject((int)floor(player->getPostionInMap()->x - player->getDirection()->x + 0.5f) + 1, (int)floor(player->getPostionInMap()->y - player->getDirection()->y + 0.5f) + 1);
	else
		object = mapCreator->getObject((int)floor(player->getPostionInMap()->x + player->getDirection()->x + 0.5f) + 1, (int)floor(player->getPostionInMap()->y + player->getDirection()->y + 0.5f) + 1);
	if (object == NULL)
	{
		if (player->getStatus() == PlayerStatus::idle)
			player->move(isUp);
	}
	else if (object->getTag() == Tag::door)
	{
		bool canOpen = false;
		if (strcmp(object->getName(), "Yellow Door") == 0)
		{
			if (player->getYellowKeyNumber() > 0)
			{
				player->openDoor(0);
				canOpen = true;
			}
		}
		else if (strcmp(object->getName(), "Blue Door") == 0)
		{
			if (player->getBlueKeyNumber() > 0)
			{
				player->openDoor(1);
				canOpen = true;
			}
		}
		else if (strcmp(object->getName(), "Red Door") == 0)
		{
			if (player->getRedKeyNumber() > 0)
			{
				player->openDoor(2);
				canOpen = true;
			}
		}

		if (canOpen)
		{
			audioManager->playSound("Data/Audio/open.wav");
			object->collide();
		}
	}
	else if (object->getTag() == Tag::NPC)
	{

	}
	else if (object->getTag() == Tag::upStairs)
		upStairs();
	else if (object->getTag() == Tag::downStairs)
		downStairs();
	else if (object->getTag() != Tag::wall
		&& object->getTag() != Tag::prison
		&& object->getTag() != Tag::ironDoor)
	{
		if (player->getStatus() == PlayerStatus::idle)
			player->move(isUp);
	}
}

void GameManager::spinPlayer(bool isLeft)
{
	if (player->getStatus() == PlayerStatus::idle)
		player->spin(isLeft);
}

void GameManager::detectCollision()
{
	if (player->getStatus() == PlayerStatus::idle)
	{
		Object* object = mapCreator->getObject((int)floor(player->getPostionInMap()->x + 0.5f) + 1, (int)floor(player->getPostionInMap()->y + 0.5f) + 1);
		if (object == NULL)
			return;
		if (object->getTag() == Tag::consumbleItem || object->getTag() == Tag::shield || object->getTag() == Tag::sword)
		{
			audioManager->playSound("Data/Audio/get.wav");
			player->reciveItems((ConsumbleItem*)object);
			object->destroyThis();
		}
	}
}
