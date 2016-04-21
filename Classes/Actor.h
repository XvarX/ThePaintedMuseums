#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "cocos2d.h"
#include "Gif\GifBase.h"
#include "Gif\InstantGif.h"
#include "GifAnimation.h"
#include <string>
#include<vector>
#include "Tool.h"
USING_NS_CC;
using namespace std;
class Actor {
public:
	Actor(string ActorNmae, int ActorNumber);
	string getActorName();
	int getActorNumber();
	int getState();
	void setState(int state);
	bool actorCanMove();
	Animation* initAnimationByName(string name, int times, bool back);
	Animation* getActionStand();
	Animation* getActionWalk();
	Animation* getActionTalk();

private:
	string Name;
	int Number;
	int state;
	bool canMove;
	Animation* stand;
	Animation* walk;
	Animation* talk;
};

//Derived Princess Class
class Princess :public Actor {
public:
	Princess(string ActorNmae, int ActorNumber);
	Animation* getActionPriRelyOn();
	Animation* getActionPriThrow();
private:
	Animation* priRelyOn;
	Animation* priThrow;
};

//Derived Dad Class
class Dad :public Actor {
public:
	Dad(string ActorName, int ActorNumber);
	Animation* getActionDadStandBy();
	Animation* getActionDadoutFire();
private:
	Animation* dadStandBy;
	Animation* dadOutFire;
};

//Derived Player Class
class Player :public Actor {
public:
	Player(string ActorName, int ActorNumber);
	int getHoldingToolsNum();
	void turnHoldingTool(int location);//0��ǰ��1���
	void addNewTool(Tool* newTool);
	Tool* getHoldingTool();
	Animation* getActionPlayerDownStair();
	Animation* getActionPlayerUpStair();
	Animation* getActionPlayerJump();
	Animation* getActionPlayerRecovery();
	Animation* getActionPlayerNoIdea();
	Animation* getActionPlayerWindowOpen();
	Animation* getActionPlayerAtticOpen();
	Animation* getActionPlayerOutFire();
	Animation* getActionPlayerDoorOpen();
	Animation* getActionPlayerOilPour();
	Animation* getActionPlayerIgnite();
	Animation* getActionPlayerWheelTurn();
	Animation* getActionPlayerClimb();
	Animation* getActionPlayerSearch();
	Animation* getActionPlayerGet();
	Animation* getActionPlayerFall();
private:
	Animation* playerDownStair;
	Animation* playerUpStair;
	Animation* playerJump;
	Animation* playerFall;
	Animation* playerRecovery;
	Animation* playerNoIdea;
	Animation* playerWindowOpen;
	Animation* playerAtticOpen;
	Animation* playerOutFire;
	Animation* playerDoorOpen;
	Animation* playerOilPour;
	Animation* playerIgnite;
	Animation* playerWheelTurn;
	Animation* playerClimb;
	Animation* playerSearch;
	Animation* playerGet;
	vector<Tool*> toolHoldingVector;
	Tool* HoldingTool;
	int HoldingNum;
};
#endif