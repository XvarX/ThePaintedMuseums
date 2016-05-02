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
	Animation* stand;
private:
	string Name;
	int Number;
	int state;
	bool canMove;

	Animation* walk;
	Animation* talk;
};

//Derived Princess Class
class Princess :public Actor {
public:
	Princess(string ActorNmae, int ActorNumber);
	Animation* getActionPriRelyOn();
	Animation* getActionPriThrow();
	Animation* getActionPriDownStair();
private:
	Animation* priRelyOn;
	Animation* priThrow;
	Animation* priDownStair;
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
	void turnHoldingTool(int location);//0向前，1向后
	void addNewTool(Tool* newTool);
	void changeStand(int i);
	int getHP();
	void reduceHp();
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

	Animation* getActionPlayerScareLv1();
	Animation* getActionPlayerScareLv2();
	Animation* getActionPlayerShake();
	Animation* getActionPlayerComa();
private:
	int HP;
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
	Animation* playerScareLv1;
	Animation* playerScareLv2;
	Animation* playerComa;
	Animation* playerShake;
	vector<Tool*> toolHoldingVector;
	Tool* HoldingTool;
	int HoldingNum;
};
#endif