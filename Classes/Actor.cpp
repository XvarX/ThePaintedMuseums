#include"Actor.h"
#include<iostream>
using namespace std;
//Base Actor
Actor::Actor(string ActorName, int ActorNumber) {
	Name = ActorName;
	Number = ActorNumber;
	state = -1;

	stand = initAnimationByName("stand", -1, false);
	walk = initAnimationByName("walk", -1, false);
	talk = initAnimationByName("talk", 1, false);
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
	def->loops = times;						// 循环次数
	def->filePath = path;				// 文件路径
	def->delayPerUnit = 1.0 / 30;			// 每帧间隔
	def->restoreOriginalFrame = back;	// 还原初始状态

										// 创建动画
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
	playerDownStair = initAnimationByName("playerDownStair", -1, false);
	playerUpStair = initAnimationByName("playerUpStair", -1, false);
	playerJump = initAnimationByName("playerJump", -1, false);
	playerRecovery = initAnimationByName("playerRecovery", 1, false);
	playerNoIdea = initAnimationByName("playerNoIdea", 1, false);
	playerWindowOpen = initAnimationByName("playerWindowOpen", 1, false);
	playerAtticOpen = initAnimationByName("playerAtticOpen", 1, false);
	playerOutFire = initAnimationByName("playerOutFire", 1, false);
	playerOilPour = initAnimationByName("playerOilPour", 1, false);
	playerIgnite = initAnimationByName("playerIgnite", 1, false);
	playerWheelTurn = initAnimationByName("playerWheelTurn", 1, false);
	playerClimb = initAnimationByName("playerClimb", 1, false);
	playerSearch = initAnimationByName("playerSearch", 1, false);
	playerGet = initAnimationByName("playerGet", 1, false);

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