#include"Actor.h"
#include<iostream>
using namespace std;
//Base Actor
Actor::Actor(string ActorName, int ActorNumber) {
	Name = ActorName;
	Number = ActorNumber;
	state = -1;
	canMove = true;
	stand = initAnimationByName("stand", -1, false);
	walk = initAnimationByName("walk", -1, false);
	talk = initAnimationByName("talk", 1, false);
}
bool Actor::actorCanMove() {
	return canMove;
}
string Actor::getActorName() {
	return Name;
}
int Actor::getActorNumber() {
	return Number;
}
Animation* Actor::getActionStand() {
	return stand;
}
Animation* Actor::getActionWalk() {
	return walk;
}
Animation* Actor::getActionTalk() {
	return talk;
}
Animation* Actor::initAnimationByName(string actionName, int times, bool back) {
	auto path = "actor//" + Name + "//" + actionName+ ".gif";
	GifAnimationDef* def = new GifAnimationDef;
	def->loops = times;						// ѭ������
	def->filePath = path;				// �ļ�·��
	def->delayPerUnit = 1.0 / 30;			// ÿ֡���
	def->restoreOriginalFrame = back;	// ��ԭ��ʼ״̬

										// ��������
	return GifAnimation::getInstance()->createAnimation(*def);
}
int Actor::getState() {
	return state;
}
void Actor::setState(int _state) {
	state = _state;
}

//Derived Princess Class
Princess::Princess(string ActorName, int ActorNumber) :Actor(ActorName, ActorNumber) {
	priRelyOn = initAnimationByName("priRelyOn", 1, false);
	priThrow = initAnimationByName("priThrow", 1, false);
}
Animation* Princess::getActionPriRelyOn() {
	return priRelyOn;
}
Animation* Princess::getActionPriThrow() {
	return priThrow;
}

//Derived Dad Class
Dad::Dad(string ActorName, int ActorNumber) :Actor(ActorName, ActorNumber) {
	dadStandBy = initAnimationByName("dadStandBy", 1, false);
	dadOutFire = initAnimationByName("dadOutFire", -1, false);
}
Animation* Dad::getActionDadStandBy() {
	return dadStandBy;
}
Animation* Dad::getActionDadoutFire() {
	return dadOutFire;
}

//Derived Mom Class

//Derived Player Class
Player::Player(string ActorName, int ActorNumber) :Actor(ActorName, ActorNumber) {
	HoldingTool = NULL;
	HoldingNum = -1;
	playerDownStair = initAnimationByName("playerDownStair", -1, false);
	playerUpStair = initAnimationByName("playerUpStair", -1, false);
	playerJump = initAnimationByName("playerJump", 1, false);
	playerFall = initAnimationByName("playerFall", 1, false);
	playerRecovery = initAnimationByName("playerRecovery", 1, false);
	playerNoIdea = initAnimationByName("playerNoIdea", 1, false);
	playerWindowOpen = initAnimationByName("playerWindowOpen", 1, false);
	playerAtticOpen = initAnimationByName("playerAtticOpen", 1, false);
	playerOutFire = initAnimationByName("playerOutFire", 1, false);
	playerOilPour = initAnimationByName("playerOilPour", 1, false);
	playerIgnite = initAnimationByName("playerIgnite", 1, false);
	playerWheelTurn = initAnimationByName("playerWheelTurn", 1, false);
	playerClimb = initAnimationByName("playerClimb", -1, false);
	playerSearch = initAnimationByName("playerSearch", 1, false);
	playerGet = initAnimationByName("playerGet", 1, false);
	playerDoorOpen = initAnimationByName("playerDoorOpen", 1, false);
}
Animation* Player::getActionPlayerDownStair() {
	return playerDownStair;
}
Animation* Player::getActionPlayerUpStair() {
	return playerUpStair;
}
Animation* Player::getActionPlayerJump() {
	return playerJump;
}
Animation* Player::getActionPlayerRecovery() {
	return playerRecovery;
}
Animation* Player::getActionPlayerNoIdea() {
	return playerNoIdea;
}
Animation* Player::getActionPlayerWindowOpen() {
	return playerWindowOpen;
}
Animation* Player::getActionPlayerAtticOpen() {
	return playerAtticOpen;
}
Animation* Player::getActionPlayerOutFire() {
	return playerOutFire;
}
Animation* Player::getActionPlayerDoorOpen() {
	return playerDoorOpen;
}
Animation* Player::getActionPlayerOilPour() {
	return playerOilPour;
}
Animation* Player::getActionPlayerIgnite() {
	return playerIgnite;
}
Animation* Player::getActionPlayerWheelTurn() {
	return playerWheelTurn;
}
Animation* Player::getActionPlayerClimb() {
	return playerClimb;
}
Animation* Player::getActionPlayerSearch() {
	return playerSearch;
}
Animation* Player::getActionPlayerGet() {
	return playerGet;
}
Animation* Player::getActionPlayerFall() {
	return playerFall;
}
void Player::addNewTool(Tool* newTool) {
	toolHoldingVector.push_back(newTool);
	if (toolHoldingVector.size() == 1) {
		HoldingTool = newTool;
		HoldingNum = 0;
	}
}
void Player::turnHoldingTool(int location) {
	if (HoldingNum >= 0) {
		if (location == 0) {
			if (HoldingNum == 0) {
				HoldingNum = toolHoldingVector.size()-1;
				HoldingTool = toolHoldingVector[HoldingNum];
			}
			else {
				HoldingNum--;
				HoldingTool = toolHoldingVector[HoldingNum];
			}
		}
		else if (location == 1) {
			if (HoldingNum == toolHoldingVector.size() - 1) {
				HoldingNum = 0;
				HoldingTool = toolHoldingVector[HoldingNum];
			}
			else {
				HoldingNum++;
				HoldingTool = toolHoldingVector[HoldingNum];
			}
		}
	}
}
int Player::getHoldingToolsNum() {
	return toolHoldingVector.size();
}
Tool* Player::getHoldingTool() {
	return HoldingTool;
}