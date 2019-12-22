#pragma once
#include "Door.h"
class IronDoor :
	public Door
{
private:
	Vector2* guardPosition;
	Vector2* otherGuardPosition;

	bool close = false; // �Ƿ�Ϊ�ر����͵�����
	bool toDestroy = false; // �Ƿ���ŵ�ʱ������

public:
	IronDoor(Vector2* positionInMap);
	void openDoor(bool destroy);

	void load(std::string jsonString);
	std::string save();

	void setClose(bool close) { this->close = close; this->index = 3; }

	void draw2D(int width, int height);
	void draw3D();

	bool isClose() { return this->close; }

	Vector2* getGuardPosition() { return guardPosition; }
	Vector2* getOtherGuardPosition() { return otherGuardPosition; }
};

