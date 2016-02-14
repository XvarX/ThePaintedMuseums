#include "Construct.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
Construct::Construct(){

}
Construct::Construct(string _ConstructorNmae, int _ConstructorNumber) {
	ConstructorNmae = _ConstructorNmae;
	ConstructorNumber = _ConstructorNumber;
}
string Construct::getConstructName() {
	return ConstructorNmae;
}
int Construct::getConstructNumber() {
	return ConstructorNumber;
}
