#include "Construct.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
Construct::Construct(){

}
Construct::Construct(string _ConstructorNmae, int _ConstructorNumber) {
	ConstructorNmae = _ConstructorNmae;
	ConstructorNumber = _ConstructorNumber;
	state = 0;
}
string Construct::getConstructName() {
	return ConstructorNmae;
}
int Construct::getConstructNumber() {
	return ConstructorNumber;
}
int Construct::getState() {
	return state;
}
void Construct::setState(int state_) {
	state = state_;
}
