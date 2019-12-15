#include "GameManager.h"

GameManager::GameManager(int width, int height)
{
	audioManager = new AudioManager();
	mapCreator = new MapCreator();
	uiManager = new UIManager(width, height);
	battleController = new BattleController();
	player = new Player(new Vector2(10, 5));
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

	glRotatef(360.0f - player->getSpinY(), 0, 1, 0);
	glTranslatef(-player->getPositon()->x, -player->getPositon()->y, -player->getPositon()->z);

	player->display();

	mapCreator->display(player->getPositon());
	// ����3D����
	mapCreator->createMap3D();

	bool status = false;
	glMatrixMode(GL_PROJECTION);						// ѡ��͸�Ӿ���
	glLoadIdentity();									// ����͸�Ӿ���

	glOrtho(0.0f, width, height, 0.0f, -1.0f, 1.0f);   // ����ƽ��ͶӰ

	glMatrixMode(GL_MODELVIEW);							// ѡ��ģ�;���
	glLoadIdentity();									// ��������ģ�;���
	mapCreator->createMap2D(width, height);
	glEnable(GL_BLEND);
	player->draw2D(width, height);
	glDisable(GL_BLEND);

	uiManager->draw(player);

	glMatrixMode(GL_PROJECTION);						// ѡ��͸�Ӿ���
	glLoadIdentity();									// ����͸�Ӿ���

	gluPerspective(60.0f, width * 1.3f / height, 0.1f, 1000.0f); //	���û�͸��ͶӰ

	glMatrixMode(GL_MODELVIEW);							// ѡ��ģ�;���
	glLoadIdentity();									// ��������ģ�;���

}

void GameManager::setWindow(int width, int height)
{
	this->width = width;
	this->height = height;
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
	if(player->getStatus() == PlayerStatus::idle)
		player->move(isUp);
	/*Object* object;
	if (isUp)
		object = mapCreator->getObject((int)floor(player->getPostionInMap()->x - player->getDirection()->x + 0.5f) + 1, (int)floor(player->getPostionInMap()->y - player->getDirection()->y + 0.5f) + 1);
	else
		object = mapCreator->getObject((int)floor(player->getPostionInMap()->x + player->getDirection()->x + 0.5f) + 1, (int)floor(player->getPostionInMap()->y + player->getDirection()->y + 0.5f) + 1);
	if (object == NULL)
		player->move(isUp);
	else if (object->getTag() != Tag::wall
		&& object->getTag() != Tag::door
		&& object->getTag() != Tag::NPC
		&& object->getTag() != Tag::prison
		&& object->getTag() != Tag::ironDoor
		&& object->getTag() != Tag::upStairs
		&& object->getTag() != Tag::downStairs)
	{
		;
	}*/
}

void GameManager::spinPlayer(bool isLeft)
{
	if (player->getStatus() == PlayerStatus::idle)
		player->spin(isLeft);
}
