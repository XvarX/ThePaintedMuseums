#ifndef __PROP_H__
#define __PROP_H__
#include <string>
using namespace std;
class Prop{
public:
	Prop();
	Prop(string propName, int propNumber);
	bool getPropInPlayer();
	void getProp();
	void removeProp();
	int getPropNumber();
	string getPropName();
	void setPropNumber(int number);
	void setPropName(string propName);
private:
	string propName;
	int propNumber;
	bool inPlayers;
};
#endif
