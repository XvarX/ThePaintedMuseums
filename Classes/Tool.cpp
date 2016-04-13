#include"Tool.h"
Tool::Tool(int _toolNum, string _toolName) {
	toolNum = _toolNum;
	toolName = _toolName;
}
string Tool::getToolName() {
	return toolName;
}
int Tool::getToolNum() {
	return toolNum;
}