#include "Prop.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Prop::Prop() {

}
Prop::Prop(string _propName, int _propNumber) {
	propName = _propName;
	propNumber = _propNumber;
	inPlayers = false;
}
bool Prop::getPropInPlayer() {
	return inPlayers;
}
void Prop::getProp() {
	inPlayers = true;
}
void Prop::removeProp() {
	inPlayers = false;
}
int Prop::getPropNumber() {
	return propNumber;
}
string Prop::getPropName() {
	return propName;
}
void Prop::setPropNumber(int number) {
	propNumber = number;
}
void Prop::setPropName(string _propName) {
	propName = _propName;
}