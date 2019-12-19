#include "GameManager.h"

GameManager::GameManager(int width, int height)
{
	mapCreator = new MapCreator();
	uiManager = new UIManager(width, height);
	battleController = new BattleController();
	player = new Player(new Vector2(10, 5));
	this->width = width;
	this->height = height;
}

void GameManager::init()
{
	player->load();
	player->init();
	mapCreator->loadMap(player->getFloor());
	Vector2** nodes = new Vector2*[3]();
	nodes[0] = new Vector2(0, 0);
	nodes[1] = new Vector2(0, 9);
	nodes[2] = new Vector2(0, 5);
	((Monster*)mapCreator->getObject(0, 2))->move(nodes, 3);
	uiManager->init();
}

void GameManager::load()
{
	// player->load();
}

void GameManager::save()
{
	// player->save();
	// mapCreator->saveMap(player->getFloor());
}

void GameManager::drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	if (this->usingStairs != uiManager->getIsUsingStairs())
	{
		this->usingStairs = false;
		if (isUpStairs)
		{
			player->upStairs(mapCreator->getUpPosition(), mapCreator->getUpDirection());
			mapCreator->loadMap(player->getFloor());
		}
		else
		{
			player->downStairs(mapCreator->getDownPosition(), mapCreator->getDownDirection());
			mapCreator->loadMap(player->getFloor());
		}
		uiManager->finishUsingStaris();
		this->finishUsingStairs = true;
	}

	if (this->finishUsingStairs != uiManager->getIsFinishUsingStairs())
	{
		this->finishUsingStairs = false;
		player->finishUsingStairs();
	}

	player->display();
	if (uiManager->getMonster() != NULL)
	{
		if (uiManager->getMonster()->isDestroy())
		{
			char message[100];
			sprintf_s(message, "You've beat %s. Receive %d Gold", uiManager->getMonster()->getName(), uiManager->getMonster()->getMoney());
			uiManager->messageDraw(message);
			uiManager->loadMonster(NULL);
		}
	}

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

	if (player->getStatus() == PlayerStatus::talking)
	{
		if(player->getNPC()->isEndTalking())
			uiManager->dialogDraw(player->getNPC()->getEndSentence(), false);
		else
		{
			uiManager->dialogDraw(player->getNPC()->getSentence(), player->getNPC()->isChoose());
			uiManager->messageDraw(player->getNPC()->getMessage());
		}
	}

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
	mapCreator->saveMap(player->getFloor());
	this->usingStairs = true;
	this->isUpStairs = true;
	uiManager->useStairs();
}

void GameManager::downStairs()
{
	this->usingStairs = true;
	this->isUpStairs = false;
	uiManager->useStairs();
}

void GameManager::movePlayer(bool isUp)
{
	// 移动player的时候，关闭底部message显示
	if(player->getStatus() == PlayerStatus::idle)
		uiManager->deleteMessage();

	Object* object;
	if (isUp)
		object = mapCreator->getObject((int)floor(player->getPositionInMap()->x - player->getDirection()->x + 0.5f), (int)floor(player->getPositionInMap()->y - player->getDirection()->y + 0.5f));
	else
		object = mapCreator->getObject((int)floor(player->getPositionInMap()->x + player->getDirection()->x + 0.5f), (int)floor(player->getPositionInMap()->y + player->getDirection()->y + 0.5f));
	if (object == NULL)
	{
		if (player->getStatus() == PlayerStatus::idle)
			player->move(isUp);
	}
	else if (object->getTag() == Tag::door && player->getStatus() == PlayerStatus::idle)
	{
		bool canOpen = false;
		if (strcmp(object->getName(), "Yellow Door") == 0)
		{
			if (player->getYellowKeyNumber() > 0 && !((Door*)object)->isOpen())
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
			char message[100];
			sprintf_s(message, "The door has opened");
			uiManager->messageDraw(message);
			object->collide();
		}
	}
	else if (object->getTag() == Tag::NPC && player->getStatus() == PlayerStatus::idle)
	{
		object->collide();
		player->talk((NPC*)object);
		if (player->getNPC()->isAction() && !player->getNPC()->isChoose())
		{
			AudioManager::playSound("Data/Audio/get.wav");
			player->action();
		}
	}
	else if (object->getTag() == Tag::upStairs && player->getStatus() == PlayerStatus::idle)
	{
		char message[100];
		sprintf_s(message, "You're using stairs");
		uiManager->messageDraw(message);
		upStairs();
	}
	else if (object->getTag() == Tag::downStairs && player->getStatus() == PlayerStatus::idle)
	{
		char message[100];
		sprintf_s(message, "You're using stairs");
		uiManager->messageDraw(message);
		downStairs();
	}
	else if (object->getTag() == Tag::wall && player->getStatus() == PlayerStatus::idle)
	{
		object->collide();
	}
	else if (object->getTag() != Tag::prison
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

void GameManager::mouseButtonClick(int x, int y)
{
	if (player->getStatus() == PlayerStatus::talking)
	{
		if (player->getNPC()->isChoose())
		{
			// 选中Yes
			if (x > width * 1150 / 1600 && x < width * 1250 / 1600 && y > height * 590 / 1200 && y < height * 630 / 1200)
			{
				if (strcmp(player->getNPC()->getName(), "Merchant") == 0)
				{
					if ((int)player->getMoney() > ((Merchant*)player->getNPC())->getCost())
					{
						((Merchant*)player->getNPC())->setCanBuy(true);
						AudioManager::playSound("Data/Audio/get.wav");
						player->action();
					}
					player->getNPC()->nextSentence();
					if (!player->getNPC()->isTalking())
					{
						player->endTalk();
						uiManager->closeDialog();
					}
				}
			}
			// 选中No
			else if (x > width * 1174 / 1600 && x < width * 1250 / 1600 && y > height * 630 / 1200 && y < height * 670 / 1200)
			{
				player->endTalk();
				uiManager->closeDialog();
			}
		}
		else if (strcmp(player->getNPC()->getName(), "Altar") == 0)
		{
			if (player->getNPC()->isAction())
			{
				if (x > width * 320 / 1600 && x < 1280 * width / 1600)
				{
					if (y > height * 220 / 1200 && y < height * 260 / 1200)
					{
						player->endTalk();
						uiManager->closeDialog();
					}
					else if(y > height * 100 / 1200 && y < height * 220 / 1200)
					{
						if (y > height * 100 / 1200 && y < height * 140 / 1200)
							((Altar*)player->getNPC())->setIndexOfChoose(0);
						else if (y > height * 140 / 1200 && y < height * 180 / 1200)
							((Altar*)player->getNPC())->setIndexOfChoose(1);
						else if (y > height * 180 / 1200 && y < height * 220 / 1200)
							((Altar*)player->getNPC())->setIndexOfChoose(2);
						if ((int)player->getMoney() > ((Altar*)player->getNPC())->getCost())
						{
							((Altar*)player->getNPC())->setCanBuy(true);
							AudioManager::playSound("Data/Audio/get.wav");
							player->action();
						}
						player->getNPC()->nextSentence();
						if (!player->getNPC()->isTalking())
						{
							player->endTalk();
							uiManager->closeDialog();
						}
					}
				}
			}
			else
			{
				player->getNPC()->nextSentence();
				if (!player->getNPC()->isTalking())
				{
					player->endTalk();
					uiManager->closeDialog();
				}
			}
		}
		else
		{
			player->getNPC()->nextSentence();
			if (!player->getNPC()->isTalking())
			{
				player->endTalk();
				uiManager->closeDialog();
			}
		}
	}
}

void GameManager::detectCollision()
{
	if (player->getStatus() == PlayerStatus::idle)
	{
		Object* object = mapCreator->getObject((int)floor(player->getPositionInMap()->x + 0.5f), (int)floor(player->getPositionInMap()->y + 0.5f));
		if (object != NULL)
		{
			if (object->getTag() == Tag::consumbleItem || object->getTag() == Tag::shield || object->getTag() == Tag::sword)
			{
				char message[100];
				sprintf_s(message, "You've found a %s", object->getName());
				AudioManager::playSound("Data/Audio/get.wav");
				player->reciveItems((ConsumbleItem*)object);
				uiManager->messageDraw(message);
				object->destroyThis();
			}
			else if (object->getTag() == Tag::monster)
			{
				player->battle((Monster*)object);
				uiManager->loadMonster((Monster*)object);
			}
			else if (object->getTag() == Tag::useItem)
			{
				char message[100];
				sprintf_s(message, "You've found a %s", object->getName());
				uiManager->messageDraw(message);
				AudioManager::playSound("Data/Audio/get.wav");
				player->reciveUseItems((UseItem*)object);
			}
		}
		object = mapCreator->getObject((int)floor(player->getPositionInMap()->x - player->getDirection()->x + 0.5f), (int)floor(player->getPositionInMap()->y - player->getDirection()->y + 0.5f));
		if (object != NULL)
		{
			if (object->getTag() == Tag::NPC)
			{
				char message[100];
				sprintf_s(message, "You'see a %s", object->getName());
				uiManager->messageDraw(message);
			}
			else if (object->getTag() == Tag::upStairs || object->getTag() == Tag::downStairs)
			{
				if (!usingStairs && !finishUsingStairs)
				{
					char message[100];
					sprintf_s(message, "You'see stairs");
					uiManager->messageDraw(message);
				}
			}
		}
	}
}
