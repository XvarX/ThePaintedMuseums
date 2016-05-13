#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__


#include "cocos2d.h"
#include <listeneradapter.h>
#include "Gif\GifBase.h"
#include "Gif\InstantGif.h"
#include"PopScene.h"
#include <string>
#include <vector>
USING_NS_CC;
using namespace std;
class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	void playerGetTool(Sprite* tool);
	void update(float dt) override;
	void setScene();
	void setGame();
	void configPhy();
	void configSchedule();
	void configEventListener();
	bool initLayer();
	void initActor();
	void initop();
	Animation* getAnimationByPath(string path);
	void initDialog();
	void initItemMenu();
	void stopAnimate();
	void reStartGame();
	void playerAction(Animation* action,int i);
	void playerAction(Animation* action, int i,string Name);
	void initAnimate();
	Animation* loadAnimate(string path, int times, bool back);
	Animation* loadAnimateByTime(string path, double time, bool back);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void setPhyWorld(PhysicsWorld* world) { m_world = world; }
	void drop();
	void playerWalk();
	void updateStart(float delta);
	int wallBesideLeft();
	void playerMove(float delta);
	void actorPlayAction(Sprite* actor, Animation* paction, int actionnum);
	void playerGetHurt();
	void actorContinuousAction(Sprite* actor, Animation* action, int actionnum);
	void actorSingleAction(Sprite* actor, Animation* action, int actionnum);

	void showend1();
	void showend2();
	void showdie();
	void preloadMusic();
	void princesscomming();
	void cameraMove(float delta);
	void cameraMoveLeft(float delta);
	void itemMenuMove(float delta);
	void conTact(float delta);
	void showDialog(float delta);
	void playerAction();
	void preLoad();
	void setJudgement();
	void canMove(float delta);
	void showItem(string ItemName);
	void showTool(string ItemName);
	void changeLocation(float delta);
	void addNewItem(string itemName, Point ItemPos, int a, int b, int c, int d);
	void fixPosition();
	void showTalk();
	void setPlayerPositionByZone(Sprite* player, Node* zone);
	int wallBesideRight();
	ccColor4B getPixelColorByPoint(Point pos);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	bool left;
	bool right;
	bool cameramove;
	bool up;
	bool die;
	bool down;
	double moveV;
	Node* rootNode;
	Sprite* player;
	Sprite* princess;
	Sprite* dad;
	Sprite* mom;
	Sprite* itemMenu;
	Sprite* lifeSlot;
	Sprite* catalog;
	Sprite* arrow;
	Sprite* bigArrow;
	Sprite* endChoice;
	Sprite* find;
	ProgressTimer* HPTimer;
	ProgressTimer* MusicTimer;
	ProgressTimer* SoundTimer;
	string itemName;
	Sprite* background;
	Sprite* stairground_1;
	PhysicsWorld* m_world;
	unsigned char *c_data;
	bool droping;
	bool jumping;
	bool canmove;
	bool kailouti;
	bool onStair;
	bool onxiepo;
	bool standBy;
	bool end;
	bool changingTool;
	bool Location; // false = left  right = true
	float rotation;
	bool playingAction;
	int playerState;
	int arrowTimes;
	int bigArrowTimes;
	double dropspeed;
	Animation* pStand;
	Animation* pWalk;
	Animation* pjump;
	Animation* ptemp;
	Animation* pfall;
	Animation* poutfire;
	Animation* pdooropen;
	Animation* poilthrow;
	Animation* pfire;
	Animation* pturn;
	Animation* precovery;
	Animation* pdownStair;
	Animation* pupStair;
	Animation *princessStand;
	Animation *princessTemp;
	Animation* popenWindow;
	Animation* patticopen;
	Animation* pnoidea;
	Animation* pget;
	Animation* psearch;
	Animation* pclimb;

	Animation* prstand;
	Animation* prkao;
	Animation* prtalk;
	Animation* prthrow;

	Animation* dadstand;
	Animation* dadtalk;
	Animation* dadrun;
	Animation* dadstanby;
	Animation* dadoutfire;

	Animation* object002;
	Animation* object004;
	Animation* object010;
	Animation* object013;

	ccColor4B stairBlue;
	Node* usefulObject;
	Vector<Node*> contactVector;
	Vector<Node*> eventVector;
	Vector<Node*> itemsVectorInMap;
	Vector<Node*> itemsVectorInPlayer;
	Vector<Node*> doorsVector;
	Vector<Node*> stairsVector;
	Vector<Node*> objectsVector;
	Vector<Node*> uselessObjectsVector;
	Vector<Node*> scareObjectsVector;
	Vector<Node*> damageObjectsVector;
	Vector<Node*> usefulObjectsVector;
	Vector<Node*> StandBysVector;
	Vector<Node*> XieposVector;
	Vector<Node*> doorObjectsVector;
	Vector<PopScene*> dialogStack;
	vector<string> dialogPath;
	Sprite* camera;
	Sprite* tempitem;
	Layer* m_UI_Movie;          //电影层 最最上层
	Layer* m_UI_Dialog;			//对话框层 最高层
	Layer* m_UI_Tool;			//工具栏层 次高层
	Layer* m_UI_Frontground;
	Layer* m_UI_Player;         //玩家层 再次高层
	Layer* m_UI_Game;			//游戏层 低层
	Layer* m_UI_Background;		//背景层 底层
	Layer* m_UI_Afterall;       //暗黑层 不应该存在层
	Layer* m_UI_preLoad;        //预处理层
};

#endif // __HELLOWORLD_SCENE_H__
