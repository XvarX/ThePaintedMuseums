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
	def->loops = times;						// ѭ������
	def->filePath = path;				// �ļ�·��
	def->delayPerUnit = 1.0 / 30;			// ÿ֡���
	def->restoreOriginalFrame = back;	// ��ԭ��ʼ״̬

										// ��������
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