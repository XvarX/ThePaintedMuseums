#include "ObjectMy.h"
#include <string>
#include "SimpleAudioEngine.h"
#include<iostream>
using namespace std;
using namespace CocosDenshion;
ObjectMy::ObjectMy() {

}
ObjectMy::ObjectMy(string ObjectNmae, int ObjectNumber, bool back,bool damage_, int times_) {
	Name = ObjectNmae;
	Number = ObjectNumber;
	auto times = times_;
	auto path = "object//" + Name + "//01-play.gif";
	GifAnimationDef* def = new GifAnimationDef;
	def->loops = times;						// 循环次数
	def->filePath = path;				// 文件路径
	def->delayPerUnit = 1.0 / 30;			// 每帧间隔
	def->restoreOriginalFrame = back;	// 还原初始状态

										// 创建动画
	actionplay = GifAnimation::getInstance()->createAnimation(*def);
	damage = damage_;
	state = 0;
	preloadVoice();
}
string ObjectMy::getObjectName() {
	return Name;
}
int ObjectMy::getObjectNumber() {
	return Number;
}
Animation* ObjectMy::objectplay() {
	return actionplay;
}
bool ObjectMy::isDamage() {
	return damage;
}
void ObjectMy::pushActionVector(int i, bool back, int time) {
		std::stringstream ss;
		std::string str;
		ss << i;
		ss >> str;
		auto path = "object//" + Name + "//0";
		path = path + str + "-play.gif";
		GifAnimationDef* def = new GifAnimationDef;
		def->loops = time;						// 循环次数
		def->filePath = path;				// 文件路径
		def->delayPerUnit = 1.0 / 30;			// 每帧间隔
		def->restoreOriginalFrame = back;	// 还原初始状态

											// 创建动画
		auto temp = GifAnimation::getInstance()->createAnimation(*def);
		actionVector.pushBack(temp);
}
void ObjectMy::changeObjectAction(int i, bool back, int times_) {
	auto times = times_;
	std::stringstream ss;
	std::string str;
	ss << i;
	ss >> str;
	auto path = "object//" + Name + "//0";
	path = path + str + "-play.gif";
	GifAnimationDef* def = new GifAnimationDef;
	def->loops = times;						// 循环次数
	def->filePath = path;				// 文件路径
	def->delayPerUnit = 1.0 / 30;			// 每帧间隔
	def->restoreOriginalFrame = back;	// 还原初始状态

										// 创建动画
	actionplay = GifAnimation::getInstance()->createAnimation(*def);
}

Animation* ObjectMy::getActionbyindex(int i) {
	return actionVector.at(i);
}

void ObjectMy::setState(int i) {
	state = i;
}

int ObjectMy::getState() {
	return state;
}

void ObjectMy::preloadVoice() {
	string voicePath = "object//" + Name + "//voice.mp3";
	auto acPath = voicePath.c_str();
	SimpleAudioEngine::getInstance()->preloadEffect(acPath);
}
void ObjectMy::playVoice() {
	string voicePath = "object//" + Name + "//voice.mp3";
	auto acPath = voicePath.c_str();
	SimpleAudioEngine::getInstance()->playEffect(acPath);
}