#ifndef __CONSTRUCT_H__
#define __CONSTRUCT_H__
#include <string>
using namespace std;
class Construct {
public:
	Construct();
	Construct(string ConstructorNmae, int ConstructorNumber);
	string getConstructName();
	int getConstructNumber();
private:
	string ConstructorNmae;
	int ConstructorNumber;
};
#endif