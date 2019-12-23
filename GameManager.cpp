#include "GameManager.h"

GameManager::GameManager(int width, int height, int originWidth, int originHeight)
{
	mapCreator = new MapCreator();
	uiManager = new UIManager(width, height);
	player = new Player(new Vector2(10, 5));
	this->width = width;
	this->height = height;
	this->originWidth = originWidth;
	this->originHeight = originHeight;
}

void GameManager::init()
{
	player->load();
	player->init();
	mapCreator->loadMap(player->getFloor(), player->getMaxFloor());
	uiManager->init();
}

void GameManager::load()
{
	player->load();
}

void GameManager::save()
{
	player->save();
	mapCreator->saveMap(player->getFloor());
}

void GameManager::drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	if (player->getFloor() == 3 && player->getStatus() == PlayerStatus::animating)
	{
		counter++;
		if (counter == 30)
			downStairs();
	}

	if (player->getFloor() == 10)
	{
		Object* boss = mapCreator->getObject(1, 5);
		if (boss != NULL)
		{
			if (((Boss*)boss)->getIndexOfMessage() == 1)
			{
				if (isAnimated)
				{
					if (mapCreator->getObject(3, 5) != NULL
						&& mapCreator->getObject(5, 5) != NULL
						&& mapCreator->getObject(5, 6) != NULL
						&& mapCreator->getObject(5, 4) != NULL
						&& mapCreator->getObject(3, 4) != NULL
						&& mapCreator->getObject(3, 6) != NULL
						&& mapCreator->getObject(4, 4) != NULL
						&& mapCreator->getObject(4, 6) != NULL
						&& mapCreator->getObject(1, 5) != NULL) // 如果都移动到位
					{
						((IronDoor*)mapCreator->getObject(3, 3))->openDoor(false);
						((IronDoor*)mapCreator->getObject(3, 7))->openDoor(false);
						isAnimated = false;
					}

				}
				else
				{
					if (mapCreator->getObject(3, 5) == NULL
						&& mapCreator->getObject(5, 5) == NULL
						&& mapCreator->getObject(5, 6) == NULL
						&& mapCreator->getObject(5, 4) == NULL
						&& mapCreator->getObject(3, 4) == NULL
						&& mapCreator->getObject(3, 6) == NULL
						&& mapCreator->getObject(4, 4) == NULL
						&& mapCreator->getObject(4, 6) == NULL
						&& mapCreator->getObject(2, 5) != NULL)
					{
						((IronDoor*)mapCreator->getObject(2, 5))->openDoor(true);
						if (player->getStatus() == PlayerStatus::idle)
						{
							player->talk((Boss*)boss);
							((Boss*)boss)->talk();
						}
					}
				}
			}
			else if (((Boss*)boss)->getIndexOfMessage() == 2)
			{
				if (((Boss*)boss)->getHealth() == 0)
				{
					if (player->getStatus() == PlayerStatus::idle)
					{
						player->talk((Boss*)boss);
						((Boss*)boss)->talk();
					}
				}
			}
		}
	}

	if (!restart && player->getStatus() != PlayerStatus::usingItem)
	{
		if (this->usingStairs != uiManager->getIsUsingStairs())
		{
			this->usingStairs = false;
			if (isUpStairs)
			{
				mapCreator->saveMap(player->getFloor());
				player->upStairs(mapCreator->getUpPosition(), mapCreator->getUpDirection(), player->getFloor() + 1);
				mapCreator->loadMap(player->getFloor(), player->getMaxFloor());
			}
			else
			{
				if (player->getFloor() == 3 && player->getStatus() == PlayerStatus::animating)
				{
					mapCreator->getObject(6, 4)->destroyThis();
					mapCreator->getObject(8, 3)->destroyThis();
					mapCreator->getObject(8, 5)->destroyThis();
					mapCreator->getObject(7, 4)->destroyThis();
					mapCreator->getObject(9, 4)->destroyThis();
					mapCreator->display(player->getPositon());
					mapCreator->saveMap(player->getFloor());
					player->downStairs(new Vector2(7, 2), new Vector2(1, 0), 2);
				}
				else
				{
					mapCreator->saveMap(player->getFloor());
					player->downStairs(mapCreator->getDownPosition(), mapCreator->getDownDirection(), player->getFloor() - 1);
				}
				mapCreator->loadMap(player->getFloor(), player->getMaxFloor());
			}
			uiManager->finishUsingStaris();
			this->finishUsingStairs = true;
		}

		if (this->finishUsingStairs != uiManager->getIsFinishUsingStairs())
		{
			this->finishUsingStairs = false;
			player->finishUsingStairs();
			if (isAnimated)
			{
				isAnimated = false;
				Object* object = mapCreator->getObject(6, 2);
				object->collide();
				player->talk((NPC*)object);
				if (((NPC*)player->getNPC())->isToNote())
					((TheOrbOfWisdom*)player->getUseItems()[1])->addMessage(((NPC*)player->getNPC())->getSentence());
			}
		}
	}
	else if(restart && player->getStatus() != PlayerStatus::usingItem)
	{
		if (this->usingStairs != uiManager->getIsUsingStairs())
		{
			this->usingStairs = false;
			mapCreator = new MapCreator();
			player = new Player(new Vector2(10, 5));
			player->init();
			mapCreator->loadMap(player->getFloor(), player->getMaxFloor());
			uiManager->messageDraw("Restart the game.");
			uiManager->finishUsingStaris();
			this->finishUsingStairs = true;
		}
		if (this->finishUsingStairs != uiManager->getIsFinishUsingStairs())
		{
			this->finishUsingStairs = false;
			this->restart = false;
		}
	}
	else if (player->getStatus() == PlayerStatus::usingItem)
	{
		if (this->usingStairs != uiManager->getIsUsingStairs())
		{
			this->usingStairs = false;
			if (isUpStairs)
			{
				mapCreator->loadMap(player->getFloor() - 1, player->getMaxFloor());
				player->upStairs(mapCreator->getUpPosition(), mapCreator->getUpDirection(), player->getFloor());
				mapCreator->loadMap(player->getFloor(), player->getMaxFloor());
			}
			else
			{
				mapCreator->loadMap(player->getFloor() + 1, player->getMaxFloor());
				player->downStairs(mapCreator->getDownPosition(), mapCreator->getDownDirection(), player->getFloor());
				mapCreator->loadMap(player->getFloor(), player->getMaxFloor());
			}
			uiManager->finishUsingStaris();
			this->finishUsingStairs = true;
		}
		if (this->finishUsingStairs != uiManager->getIsFinishUsingStairs())
		{
			this->finishUsingStairs = false;
			this->restart = false;
		}
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
	((TheOrbOfTheHero*)(player->getUseItems()[0]))->setPlayer(player->getAttack(), player->getDefence());
	((TheOrbOfTheHero*)(player->getUseItems()[0]))->clearMonster();
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			Object* object = mapCreator->getObject(i, j);
			if (object != NULL)
			{
				if (object->getTag() == Tag::monster || object->getTag() == Tag::boss)
				{
					if(!((Monster*)object)->isAppearMonster())
						((TheOrbOfTheHero*)(player->getUseItems()[0]))->addMonster((Monster*)object);
				}
			}
		}
	}

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
		Object* object = player->getNPC();
		if (object->getTag() == Tag::NPC)
		{
			if (((NPC*)object)->isEndTalking())
				uiManager->dialogDraw(((NPC*)object)->getEndSentence(), false);
			else
			{
				uiManager->dialogDraw(((NPC*)object)->getSentence(), ((NPC*)object)->isChoose());
				uiManager->messageDraw(((NPC*)object)->getMessage());
			}
		}
		else if (object->getTag() == Tag::boss)
		{
				uiManager->dialogDraw(((Boss*)object)->getSentence(), ((Boss*)object)->isChoose());
				uiManager->messageDraw(((Boss*)object)->getMessage());
		}
	}

	if (player->getHealth() <= 0 && !restart)
	{
		gameOver = true;
		uiManager->dialogDraw("Game Over!#Press R to restart", false);
	}

	glMatrixMode(GL_PROJECTION);						// 选择透视矩阵
	glLoadIdentity();									// 重设透视矩阵

	gluPerspective(60.0f, width * 1.3f / height, 0.025f, 1000.0f); //	设置回透视投影

	glMatrixMode(GL_MODELVIEW);							// 选择模型矩阵
	glLoadIdentity();									// 重新载入模型矩阵

}

void GameManager::setWindow(int width, int height, int originWidth, int originHeight)
{
	this->width = width;
	this->height = height;
	this->originWidth = originWidth;
	this->originHeight = originHeight;
	uiManager->setWindow(width, height);
}

void GameManager::upStairs()
{
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
	if (isAnimated)
		return;

	// 移动player的时候，关闭底部message显示
	if(player->getStatus() == PlayerStatus::idle)
		uiManager->deleteMessage();
	if (gameOver)
		return;

	Object* object;
	if (isUp)
		object = mapCreator->getObject((int)floor(player->getPositionInMap()->x - player->getDirection()->x + 0.5f), (int)floor(player->getPositionInMap()->y - player->getDirection()->y + 0.5f));
	else
		object = mapCreator->getObject((int)floor(player->getPositionInMap()->x + player->getDirection()->x + 0.5f), (int)floor(player->getPositionInMap()->y + player->getDirection()->y + 0.5f));
	if (object == NULL)
	{
		if (player->getStatus() == PlayerStatus::idle)
		{
			bool canMove = true;
			Object* object1 = mapCreator->getObject((int)floor(player->getPositionInMap()->x - player->getDirection()->x + 0.5f), (int)floor(player->getPositionInMap()->y - player->getDirection()->y + 1 + 0.5f));
			Object* object2 = mapCreator->getObject((int)floor(player->getPositionInMap()->x - player->getDirection()->x + 0.5f), (int)floor(player->getPositionInMap()->y - player->getDirection()->y - 1 + 0.5f));
			if (object1 != NULL)
			{
				if (strcmp("Altar", object1->getName()) == 0)
				{
					canMove = false;
					object1->collide();
					player->talk((NPC*)object1);
				}
			}
			else if (object2 != NULL)
			{
				if (strcmp("Altar", object2->getName()) == 0)
				{
					canMove = false;
					object1->collide();
					player->talk((NPC*)object2);
				}
			}
			if(canMove)
				player->move(isUp);
		}
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
		else if(!((Door*)object)->isOpen())
			uiManager->messageDraw("You don't have the key");
	}
	else if (object->getTag() == Tag::NPC && player->getStatus() == PlayerStatus::idle)
	{
		object->collide();
		player->talk((NPC*)object);
		if(((NPC*)player->getNPC())->isToNote())
			((TheOrbOfWisdom*)player->getUseItems()[1])->addMessage(((NPC*)player->getNPC())->getSentence());
		if (((NPC*)player->getNPC())->isAction() && !((NPC*)player->getNPC())->isChoose() && strcmp(player->getNPC()->getName(), "Old Man") == 0)
		{
			player->action();
		}
	}
	else if (object->getTag() == Tag::upStairs && player->getStatus() == PlayerStatus::idle)
	{
		char message[100];
		sprintf_s(message, "You're using stairs");
		uiManager->messageDraw(message);
		player->useStairs();
		upStairs();
	}
	else if (object->getTag() == Tag::downStairs && player->getStatus() == PlayerStatus::idle)
	{
		char message[100];
		sprintf_s(message, "You're using stairs");
		uiManager->messageDraw(message);
		player->useStairs();
		downStairs();
	}
	else if (object->getTag() == Tag::wall && player->getStatus() == PlayerStatus::idle)
	{
		object->collide();
	}
	else if (object->getTag() == Tag::ironDoor && ((IronDoor*)object)->isClose())
	{
		if (player->getStatus() == PlayerStatus::idle)
			player->move(isUp);
	}
	else if (object->getTag() != Tag::prison)
	{
		if (player->getStatus() == PlayerStatus::idle)
			player->move(isUp);
	}
}

void GameManager::spinPlayer(bool isLeft)
{
	if (gameOver)
		return;
	if (player->getStatus() == PlayerStatus::idle)
		player->spin(isLeft);
	else if (player->getStatus() == PlayerStatus::usingItem)
	{
		if (player->getUseItems()[1]->ifIsUsing())
		{
			if (isLeft)
				((TheOrbOfWisdom*)player->getUseItems()[1])->previousMessage();
			else
				((TheOrbOfWisdom*)player->getUseItems()[1])->nextMessage();
		}
	}
}

void GameManager::mouseButtonClick(int x, int y)
{
	if (player->getStatus() == PlayerStatus::talking)
	{
		Object* object = player->getNPC();
		if (object->getTag() == Tag::NPC)
		{
			if (((NPC*)player->getNPC())->isToNote())
				((TheOrbOfWisdom*)player->getUseItems()[1])->addMessage(((NPC*)player->getNPC())->getSentence());
			if (((NPC*)object)->isChoose())
			{
				// 选中Yes
				if ((x - (originWidth - width) / 2) > width * 1150 / 1600 && (x - (originWidth - width) / 2) < width * 1250 / 1600 && y > height * 590 / 1200 && y < height * 630 / 1200)
				{
					if (strcmp(((NPC*)object)->getName(), "Merchant") == 0)
					{
						if ((int)player->getMoney() >= ((Merchant*)player->getNPC())->getCost())
						{
							((Merchant*)player->getNPC())->setCanBuy(true);
							AudioManager::playSound("Data/Audio/get.wav");
							player->action();
						}
						((NPC*)object)->nextSentence();
						if (!((NPC*)object)->isTalking())
						{
							player->endTalk();
							uiManager->closeDialog();
						}
					}
				}
				// 选中No
				else if ((x - (originWidth - width) / 2) > width * 1174 / 1600 && (x - (originWidth - width) / 2) < width * 1250 / 1600 && y > height * 630 / 1200 && y < height * 670 / 1200)
				{
					player->endTalk();
					uiManager->closeDialog();
				}
			}
			else if (strcmp(player->getNPC()->getName(), "Altar") == 0)
			{
				if (((NPC*)object)->isAction())
				{
					if ((x - (originWidth - width) / 2) > width * 320 / 1600 && (x - (originWidth - width) / 2) < 1280 * width / 1600)
					{
						if (y > height * 220 / 1200 && y < height * 260 / 1200)
						{
							player->endTalk();
							uiManager->closeDialog();
						}
						else if (y > height * 100 / 1200 && y < height * 220 / 1200)
						{
							if (y > height * 100 / 1200 && y < height * 140 / 1200)
								((Altar*)player->getNPC())->setIndexOfChoose(0);
							else if (y > height * 140 / 1200 && y < height * 180 / 1200)
								((Altar*)player->getNPC())->setIndexOfChoose(1);
							else if (y > height * 180 / 1200 && y < height * 220 / 1200)
								((Altar*)player->getNPC())->setIndexOfChoose(2);
							if ((int)player->getMoney() >= ((Altar*)player->getNPC())->getCost())
							{
								((Altar*)player->getNPC())->setCanBuy(true);
								AudioManager::playSound("Data/Audio/get.wav");
								player->action();
							}
							((NPC*)object)->nextSentence();
							if (!((NPC*)object)->isTalking())
							{
								player->endTalk();
								uiManager->closeDialog();
							}
						}
					}
				}
				else
				{
					((NPC*)object)->nextSentence();
					if (!((NPC*)object)->isTalking())
					{
						player->endTalk();
						uiManager->closeDialog();
					}
				}
			}
			else if (strcmp(((NPC*)object)->getName(), "Thief") == 0)
			{
				if (((Thief*)player->getNPC())->getFloor() == 2)
				{
					if (((Thief*)player->getNPC())->getIndexOfMessage() == 3)
					{
						Vector2* brokenWallPosition = ((Thief*)player->getNPC())->getBrokenWallPosition();
						((Wall*)mapCreator->getObject((int)floor(brokenWallPosition->x + 0.5f), (int)floor(brokenWallPosition->y + 0.5f)))->setBrokenWall();
						((Wall*)mapCreator->getObject((int)floor(brokenWallPosition->x + 0.5f), (int)floor(brokenWallPosition->y + 0.5f)))->collide();
					}
				}
				((NPC*)object)->nextSentence();
				if (!((NPC*)object)->isTalking())
				{
					player->endTalk();
					uiManager->closeDialog();
				}
			}
			else
			{
				((NPC*)object)->nextSentence();
				if (!((NPC*)object)->isTalking())
				{
					player->endTalk();
					uiManager->closeDialog();
				}
			}
		}
		else if (object->getTag() == Tag::boss)
		{
			if (strcmp(object->getName(), "The Magic Sergeant") == 0 && player->getFloor() == 3)
			{
				if (((Boss*)object)->getIndexOfMessage() == 0)
				{
					AudioManager::playSound("Data/Audio/3f.wav");
					((Monster*)mapCreator->getObject(8, 3))->toAppear();
					((Monster*)mapCreator->getObject(8, 5))->toAppear();
					((Monster*)mapCreator->getObject(7, 4))->toAppear();
					((Monster*)mapCreator->getObject(9, 4))->toAppear();
				}
				else if (((Boss*)object)->getIndexOfMessage() == 1)
				{
					player->action3F();
				}
			}
			else if (strcmp(object->getName(), "SkeletonA") == 0)
			{
				if (((Boss*)object)->getIndexOfMessage() == 0)
				{
					this->isAnimated = true;
					Vector2** nodes;
					nodes = new Vector2 * [1]();
					nodes[0] = new Vector2(1, 5);
					((Monster*)object)->move(nodes, 1);
					((IronDoor*)mapCreator->getObject(2, 5))->openDoor(false);
					((IronDoor*)mapCreator->getObject(6, 5))->openDoor(false);
					((IronDoor*)mapCreator->getObject(3, 3))->openDoor(false);
					((IronDoor*)mapCreator->getObject(3, 7))->openDoor(false);
					((Wall*)mapCreator->getObject(5, 4))->collide();
					((Wall*)mapCreator->getObject(5, 6))->collide();
					nodes = new Vector2 * [3]();
					nodes[0] = new Vector2(3, 4);
					nodes[1] = new Vector2(5, 4);
					nodes[2] = new Vector2(5, 5);
					((Monster*)mapCreator->getObject(3, 1))->move(nodes, 3); // 第一个骷髅兵
					nodes = new Vector2 * [1]();
					nodes[0] = new Vector2(3, 5);
					((Monster*)mapCreator->getObject(3, 9))->move(nodes, 1); // 第二个骷髅兵
					nodes = new Vector2*[3]();
					nodes[0] = new Vector2(3, 2);
					nodes[1] = new Vector2(3, 4);
					nodes[2] = new Vector2(5, 4);
					((Monster*)mapCreator->getObject(2, 2))->move(nodes, 3);
					nodes = new Vector2 * [3]();
					nodes[0] = new Vector2(3, 1);
					nodes[1] = new Vector2(3, 4);
					nodes[2] = new Vector2(4, 4);
					((Monster*)mapCreator->getObject(2, 1))->move(nodes, 3);
					nodes = new Vector2 * [3]();
					nodes[0] = new Vector2(3, 0);
					nodes[1] = new Vector2(3, 4);
					((Monster*)mapCreator->getObject(2, 0))->move(nodes, 2); // 左边三个骷髅
					nodes = new Vector2 * [3]();
					nodes[0] = new Vector2(3, 8);
					nodes[1] = new Vector2(3, 6);
					nodes[2] = new Vector2(5, 6);
					((Monster*)mapCreator->getObject(2, 8))->move(nodes, 3);
					nodes = new Vector2 * [3]();
					nodes[0] = new Vector2(3, 9);
					nodes[1] = new Vector2(3, 6);
					nodes[2] = new Vector2(4, 6);
					((Monster*)mapCreator->getObject(2, 9))->move(nodes, 3);
					nodes = new Vector2 * [3]();
					nodes[0] = new Vector2(3, 10);
					nodes[1] = new Vector2(3, 6);
					((Monster*)mapCreator->getObject(2, 10))->move(nodes, 2); // 右边三个骷髅
				}
				else if (((Boss*)object)->getIndexOfMessage() == 2)
				{
					((IronDoor*)mapCreator->getObject(6, 5))->openDoor(true);
					((IronDoor*)mapCreator->getObject(3, 3))->openDoor(true);
					((IronDoor*)mapCreator->getObject(3, 7))->openDoor(true);
					object->destroyThis();
					this->gameOver = true;
				}
			}
			((Boss*)object)->nextSentence();
			if (!((Boss*)object)->isTalking())
			{
				if(player->getStatus() == PlayerStatus::talking)
					player->endTalk();
				uiManager->closeDialog();
				if(gameOver)
					uiManager->dialogDraw("Game Clear!#Thanks for your playing!!!#Please press R to restart or exit the game#The game will be updated someday.", false);
			}
		}
	}
	else if (player->getStatus() == PlayerStatus::idle || player->getStatus() == PlayerStatus::usingItem)
	{
		if (player->getUseItems()[2]->ifIsUsing() && !usingStairs && !finishUsingStairs) // 选择楼层
		{
			int floor;
			floor = (((x - (originWidth - width) / 2) * 1600 / width) - 270) / 40 + 10 * (((y * 1200 / height) - 560) / 40) + 1;
			if (floor > 0 && floor <= player->getMaxFloor() && floor != player->getFloor())
			{
				if (player->getUseItems()[2]->isCanUse())
				{
					if (floor > player->getFloor())
					{
						player->moveFloor(floor);
						usingStairs = true;
						finishUsingStairs = false;
						isUpStairs = true;
						uiManager->useStairs();
					}
					else
					{
						player->moveFloor(floor);
						usingStairs = true;
						finishUsingStairs = false;
						isUpStairs = false;
						uiManager->useStairs();
					}
				}
				else
					this->uiManager->messageDraw("You must near the stairs to fly");
			}
		}
		int index;
		index = ((((x - (originWidth - width) / 2) * 1600 / width) - 40) / 75) + 3 * (((y * 1200 / height) - 560) / 88);
		if (index > -1 && index < 15)
		{
			if (player->getUseItems()[index] != NULL)
			{
				bool isUsing = false;
				for (int i = 0; i < 15; i++)
				{
					if (i == index)
						continue;
					if(player->getUseItems()[i] != NULL && !usingStairs && !finishUsingStairs)
						isUsing = player->getUseItems()[i]->ifIsUsing();
				}
				if (!isUsing)
				{
					player->useItem(index);
					uiManager->closeDialog();
				}
			}
		} //  // 关闭当前打开的道具
    }
}

void GameManager::newGame()
{
	uiManager->closeDialog();
	usingStairs = true;
	finishUsingStairs = false;
	isUpStairs = false;
	talking = false;
	isAnimated = false;
	gameOver = false;
	restart = true;
	counter = 0;
	uiManager = new UIManager(width, height);
	uiManager->init();
	uiManager->useStairs();
}

void GameManager::detectCollision()
{
	if (player->getStatus() == PlayerStatus::idle)
	{
		if (player->getFloor() == 3 && player->getStatus() == PlayerStatus::idle)
		{
			if ((int)floor(player->getPositionInMap()->x + 0.5) == 8 && (int)floor(player->getPositionInMap()->y + 0.5) == 4)
			{
				Object* object = mapCreator->getObject((int)floor(player->getPositionInMap()->x - 2 + 0.5f), (int)floor(player->getPositionInMap()->y + 0.5f));
				if (object != NULL && !this->isAnimated)
				{
					this->isAnimated = true;
					AudioManager::playSound("Data/Audio/3f.wav");
					((Boss*)object)->toAppear();
					((Boss*)object)->talk();
					player->talk((Boss*)object);
				}
			}
		}
		else if (player->getFloor() == 10 && player->getStatus() == PlayerStatus::idle && !isAnimated)
		{
			if ((int)floor(player->getPositionInMap()->x + 0.5) == 4 && (int)floor(player->getPositionInMap()->y + 0.5) == 5)
			{
				Object *object = mapCreator->getObject((int)floor(player->getPositionInMap()->x - 1 + 0.5f), (int)floor(player->getPositionInMap()->y + 0.5f));
				if (object != NULL)
				{
					if (strcmp(object->getName(), "SkeletonA") == 0)
					{
						this->isAnimated = true;
						((Boss*)object)->talk();
						player->talk((Boss*)object);
					}
				}
			}
		}
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
			else if (object->getTag() == Tag::monster || object->getTag() == Tag::boss)
			{
				if (!((Monster*)object)->isAppearMonster() && ((Monster*)object)->getHealth() != 0)
				{
					player->battle((Monster*)object);
					uiManager->loadMonster((Monster*)object);
				}
			}
			else if (object->getTag() == Tag::useItem)
			{
				char message[100];
				sprintf_s(message, "You've found a %s", object->getName());
				uiManager->messageDraw(message);
				AudioManager::playSound("Data/Audio/get.wav");
				player->reciveUseItems((UseItem*)object);
				object->destroyThis();
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
		bool canUse = false;
		for (int i = 0; i < 4; i++)
		{
			switch (i)
			{
			case 0:
				object = mapCreator->getObject((int)floor(player->getPositionInMap()->x + 1 + 0.5f), (int)floor(player->getPositionInMap()->y + 0.5f));
				break;
			case 1:
				object = mapCreator->getObject((int)floor(player->getPositionInMap()->x - 1 + 0.5f), (int)floor(player->getPositionInMap()->y + 0.5f));
				break;
			case 2:
				object = mapCreator->getObject((int)floor(player->getPositionInMap()->x + 0.5f), (int)floor(player->getPositionInMap()->y + 1 + 0.5f));
				break;
			case 3:
				object = mapCreator->getObject((int)floor(player->getPositionInMap()->x + 0.5f), (int)floor(player->getPositionInMap()->y - 1 + 0.5f));
				break;
			default:
				break;
			}
			if (object != NULL)
			{
				if (object->getTag() == Tag::upStairs || object->getTag() == Tag::downStairs)
					canUse = true;
			}
		}
		player->getUseItems()[2]->setCanUse(canUse);
	}
}
