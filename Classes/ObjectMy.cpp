#include "ObjectMy.h"
#include<iostream>
using namespace std;

ObjectMy::ObjectMy() {

}
ObjectMy::ObjectMy(string ObjectNmae, int ObjectNumber, bool back) {
	Name = ObjectNmae;
	Number = ObjectNumber;
	auto times = 1;
	auto path = "object//" + Name + "//01-play.gif";
	GifAnimationDef* def = new GifAnimationDef;
	def->loops = times;						// 循环次数
	def->filePath = path;				// 文件路径
	def->delayPerUnit = 1.0 / 30;			// 每帧间隔
	def->restoreOriginalFrame = back;	// 还原初始状态

										// 创建动画
	actionplay = GifAnimation::getInstance()->createAnimation(*def);
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