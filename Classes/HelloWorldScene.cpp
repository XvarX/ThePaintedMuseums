#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GifAnimation.h"
#include "ObjectMy.h"
#include "math\CCMath.h"
#include "Construct.h"
#include <math.h>
#include "SimpleAudioEngine.h"
#include "HelloWorlD.h"
#include "Actor.h"
#include "AudioEngine.h"
#include"PopScene.h"

USING_NS_CC;
using namespace CocosDenshion;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	auto layer = HelloWorld::create();
	layer->setPhyWorld(scene->getPhysicsWorld());
	// 'layer' is an autorelease object
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void HelloWorld::setScene() {
	//set the background
	auto frontground = Sprite::create("frontGround1//front(always).png");
	frontground->setPosition(frontground->getContentSize() / 2);
	m_UI_Frontground->addChild(frontground);

	stairground_1 = Sprite::create("frontGround2//front(stage).png");
	stairground_1->setPosition(stairground_1->getContentSize() / 2);

	background = Sprite::create("background05-09.jpg");
	background->setPosition(background->getContentSize() / 2);

	//set the jugement background

	m_UI_Background->addChild(background);

}

void HelloWorld::setGame() {
	player->setAnchorPoint(Vec2(0.514, 0.5));

	//init player animation, play stand
	auto playerActionStand = ((Player*)player->getUserData())->getActionStand();
	actorContinuousAction(player, playerActionStand, 0);

	//初始方向朝左
	player->runAction(FlipX::create(true));
	princess->setName("princess");
	//去掉studio中的背景
	auto backgroundTemp = static_cast<Sprite*>(rootNode->getChildByName("background1_1out"));
	backgroundTemp->removeFromParentAndCleanup(true);
	//添加studio中的对象物体
	auto Contact = rootNode->getChildByName("Contact");
	contactVector = Contact->getChildren();

	auto Event = rootNode->getChildByName("Event");
	Event->setVisible(false);
	eventVector = Event->getChildren();
	for (int i = 0; i < eventVector.size(); i++) {
		Sprite *projectile = (CCSprite *)eventVector.at(i);
		Construct *newObject = new Construct(projectile->getName(), i);
		projectile->setUserData(newObject);
	}

	auto Door = rootNode->getChildByName("Door");
	doorsVector = Door->getChildren();

	auto Object = rootNode->getChildByName("Object");
	Object->setVisible(false);
	objectsVector = Object->getChildren();
	for (int i = 0; i < objectsVector.size(); i++) {
		Sprite *projectile = (CCSprite *)objectsVector.at(i);
		Construct *newObject = new Construct(projectile->getName(), i);
		projectile->setUserData(newObject);
	}

	auto uselessObject = rootNode->getChildByName("UselessObject");
	uselessObjectsVector = uselessObject->getChildren();
	for (int i = 0; i < uselessObjectsVector.size(); i++) {
		Sprite *projectile = (CCSprite *)uselessObjectsVector.at(i);
		ObjectMy *newObject;
		if (projectile->getName() == "Object013") {
			newObject = new ObjectMy(projectile->getName(), i, false, false);
		}
		else {
			newObject = new ObjectMy(projectile->getName(), i, true, false);
		}
		projectile->setUserData(newObject);
	}

	auto scareObject = rootNode->getChildByName("ScareObject");
	scareObjectsVector = scareObject->getChildren();
	for (int i = 0; i < scareObjectsVector.size(); i++) {
		Sprite *projectile = (CCSprite *)scareObjectsVector.at(i);
		ObjectMy *newObject = new ObjectMy(projectile->getName(), i, false, false);
		projectile->setUserData(newObject);
	}

	auto doorObject = rootNode->getChildByName("DoorObject");
	doorObjectsVector = doorObject->getChildren();
	for (int i = 0; i < doorObjectsVector.size(); i++) {
		Sprite *projectile = (CCSprite *)doorObjectsVector.at(i);
		ObjectMy *newObject = new ObjectMy(projectile->getName(), i, false, false);
		projectile->setUserData(newObject);
	}

	auto damageObject = rootNode->getChildByName("DamageObject");
	damageObjectsVector = damageObject->getChildren();
	for (int i = 0; i < damageObjectsVector.size(); i++) {
		Sprite *projectile = (CCSprite *)damageObjectsVector.at(i);
		ObjectMy *newObject;
		newObject = new ObjectMy(projectile->getName(), i, false, true);
		projectile->setUserData(newObject);
	}

	usefulObject = rootNode->getChildByName("UsefulObject");
	usefulObjectsVector = usefulObject->getChildren();
	for (int i = 0; i < usefulObjectsVector.size(); i++) {
		Sprite *projectile = (CCSprite *)usefulObjectsVector.at(i);
		ObjectMy *newObject;
		if (projectile->getName() == "Object016" || projectile->getName() == "Object031") {
			newObject = new ObjectMy(projectile->getName(), i, false, false, -1);
		}
		else {
			newObject = new ObjectMy(projectile->getName(), i, false, false);
		}
		projectile->setUserData(newObject);
		if (projectile->getName() == "Object025") {
			newObject->pushActionVector(2, false, 1);
			newObject->pushActionVector(3, false, -1);
		}
	}

	auto Stair = rootNode->getChildByName("Stair");
	stairsVector = Stair->getChildren();
	for (int i = 0; i < stairsVector.size(); i++) {
		Sprite *projectile = (CCSprite *)stairsVector.at(i);
		Construct *newObject = new Construct(projectile->getName(), i);
		if (projectile->getName() == "Stair02") {
			newObject->setState(-1);
		}
		projectile->setUserData(newObject);
	}
	Stair->setVisible(false);

	auto StandBy = rootNode->getChildByName("StandBy");
	StandBysVector = StandBy->getChildren();
	StandBy->setVisible(false);

	auto Xiepo = rootNode->getChildByName("Xiepo");
	XieposVector = Xiepo->getChildren();
	Xiepo->setVisible(false);

	auto Zone = rootNode->getChildByName("Zone");
	//init position
	auto zone001 = rootNode->getChildByName("Zone")->getChildByName("Zone001");
	auto zone002 = rootNode->getChildByName("Zone")->getChildByName("Zone002");
	setPlayerPositionByZone(player, zone001);
	setPlayerPositionByZone(princess, zone002);
	camera = Sprite::create("camera.jpg");
	camera->setPosition(player->getPosition() + Vec2(384, 216));
	//player->setPosition(Vec2(2200, 1200));

	dad->setName("Dad");
	auto zone006 = rootNode->getChildByName("Zone")->getChildByName("Zone006");
	setPlayerPositionByZone(dad, zone006);
	actorPlayAction(dad, dadstand, 1);

	mom->setName("mom");
	mom->setPosition(-100, -100);

	m_UI_Game->addChild(mom);
	m_UI_Game->addChild(rootNode);
	m_UI_Game->addChild(player);
	m_UI_Game->addChild(princess);
	m_UI_Game->addChild(dad);
	m_UI_Game->addChild(camera);
	m_UI_Game->addChild(stairground_1);
	Zone->setVisible(false);
}

void HelloWorld::configPhy() {
	//init door physicsbody
	for (int i = 0; i < doorsVector.size(); i++) {
		Sprite *projectile = (CCSprite *)doorsVector.at(i);
		projectile->setVisible(false);
		auto doorBody = PhysicsBody::createBox(projectile->getContentSize());
		doorBody->setDynamic(true);
		doorBody->setGravityEnable(false);
		doorBody->setRotationEnable(false);
		doorBody->setDynamic(false);
		projectile->setPhysicsBody(doorBody);
	}

	//init edge physicsbody
	auto body = PhysicsBody::createEdgeBox(background->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	body->setGravityEnable(true);
	edgeNode->setPosition(background->getContentSize() / 2);
	edgeNode->setPhysicsBody(body);
	this->addChild(edgeNode);

	//init player physicsbody
	auto playerBody = PhysicsBody::createBox(Size(26, 313));
	playerBody->setRotationEnable(false);
	playerBody->setGravityEnable(false);
	player->setPhysicsBody(playerBody);

	//init camera physicsbody
	auto cameraBody = PhysicsBody::create();
	cameraBody->setGravityEnable(false);
	camera->setPhysicsBody(cameraBody);
	camera->setVisible(false);
	//physics background init
	/*auto backgroundBody = PhysicsBody::createBox(Size(0, 0), PhysicsMaterial::PhysicsMaterial(0, 0, 0));
	backgroundBody->setGravityEnable(false);
	backgroundBody->setDynamic(false);
	const char* testPlistPath = "museum2.plist";
	CCDictionary* plistDic = CCDictionary::createWithContentsOfFile(testPlistPath);
	CCDictionary* bodyDic = dynamic_cast<CCDictionary*>(plistDic->objectForKey("bodies"));
	CCDictionary* backgroundDic = dynamic_cast<CCDictionary*>(bodyDic->objectForKey("background1_1in"));
	CCArray* fixturesArr = dynamic_cast<CCArray*>(backgroundDic->objectForKey("fixtures"));

	for (int fixtureNum = 0; fixtureNum < fixturesArr->count(); fixtureNum++) {
	CCDictionary* eachDic = dynamic_cast<CCDictionary*>(fixturesArr->getObjectAtIndex(fixtureNum));
	CCArray* polygonsArr = dynamic_cast<CCArray*>(eachDic->objectForKey("polygons"));
	for (int polygonsNum = 0; polygonsNum < polygonsArr->count(); polygonsNum++) {
	CCArray* pointArr = dynamic_cast<CCArray*>(polygonsArr->getObjectAtIndex(polygonsNum));
	int num = pointArr->count();
	Point *points = new Point[num];
	for (int pointNum = 0; pointNum < pointArr->count(); pointNum++) {
	CCString* point_string = (CCString*)pointArr->objectAtIndex(pointNum);
	Point point = PointFromString(point_string->getCString());
	points[pointNum] = point;
	}
	backgroundBody->addShape(PhysicsShapePolygon::create(points, num));
	}
	}*/
}

void HelloWorld::configSchedule() {
	//fix update to avoid body pass through
	scheduleOnce(CC_SCHEDULE_SELECTOR(HelloWorld::updateStart), 0);
	//playerMove schedule
	schedule(schedule_selector(HelloWorld::playerMove), 1.0 / 60, kRepeatForever, 0);
	schedule(schedule_selector(HelloWorld::changeLocation), 1.0 / 120, kRepeatForever, 0);
	schedule(schedule_selector(HelloWorld::conTact), 1.0 / 60, kRepeatForever, 0);
	schedule(schedule_selector(HelloWorld::canMove), 1.0 / 60, kRepeatForever, 0);
	schedule(schedule_selector(HelloWorld::showDialog), 1.0 / 60, kRepeatForever, 0);
	//schedule(schedule_selector(HelloWorld::cameraMove), 1.0 / 60, kRepeatForever, 0);
	//schedule(schedule_selector(HelloWorld::itemMenuMove), 1.0 / 60, kRepeatForever, 0);
}

void HelloWorld::configEventListener() {
	auto keylistener = EventListenerKeyboard::create();
	keylistener->setEnabled(true);
	keylistener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	keylistener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithFixedPriority(keylistener, -100);
}

bool HelloWorld::initLayer() {
	auto origin = Director::getInstance()->getVisibleOrigin();

	m_UI_Movie = Layer::create();
	m_UI_Movie->setPosition(origin);
	this->addChild(m_UI_Movie, 60);

	m_UI_Dialog = Layer::create();
	m_UI_Dialog->setPosition(origin);
	this->addChild(m_UI_Dialog, 50);

	m_UI_Tool = Layer::create();
	m_UI_Tool->setPosition(origin);
	this->addChild(m_UI_Tool, 40);

	m_UI_Frontground = Layer::create();
	m_UI_Frontground->setPosition(origin);
	this->addChild(m_UI_Frontground, 30);

	m_UI_Game = Layer::create();
	m_UI_Game->setPosition(origin);
	this->addChild(m_UI_Game, 20);

	m_UI_Background = Layer::create();
	m_UI_Background->setPosition(origin);
	this->addChild(m_UI_Background, 10);

	m_UI_Afterall = Layer::create();
	m_UI_Afterall->setPosition(origin);
	this->addChild(m_UI_Afterall, 5);

	m_UI_preLoad = Layer::create();
	m_UI_preLoad->setPosition(origin);
	this->addChild(m_UI_preLoad, 0);
	return true;
}

void HelloWorld::initDialog() {
}

bool HelloWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}
	moveV = -200 * 1.3*1.5;
	rotation = 0;
	playerState = 0;
	dropspeed = 0;
	arrowTimes = 0;
	bigArrowTimes = 0;
	droping = false;
	kailouti = false;
	cameramove = false;
	jumping = false;
	onStair = false;
	standBy = false;
	die = false;
	onxiepo = false;
	canmove = true;
	end = false;
	Location = false;
	playingAction = false;
	changingTool = false;
	rootNode = CSLoader::createNode("MainScene.csb");
	CCSpriteFrameCache *pFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	pFrameCache->addSpriteFramesWithFile("UI//Plist1.plist");
	initLayer();
	initAnimate();
	initItemMenu();
	initActor();
	setScene();
	setJudgement();
	setGame();
	configPhy();
	
	configSchedule();
	configEventListener();
	preloadMusic();
	initop();
	preLoad();
	auto object = (Sprite*)rootNode->getChildByName("UsefulObject")->getChildByName("Object016");
	auto objectData = (ObjectMy*)(((Sprite*)object)->getUserData());
	auto objectAction = objectData->objectplay();
	Animate* objectPlay = Animate::create(objectAction);
	object->runAction(objectPlay);
	auto object031 = (Sprite*)rootNode->getChildByName("UsefulObject")->getChildByName("Object031");
	auto objectData031 = (ObjectMy*)(((Sprite*)object031)->getUserData());
	auto objectAction031 = objectData031->objectplay();
	Animate* objectPlay031 = Animate::create(objectAction031);
	object031->runAction(objectPlay031);

	//background follow
	//auto follow = Follow::create(camera);
	//this->runAction(follow);
	//event listener

	return true;
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_A) {
		left = false;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
		right = false;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_W) {
		up = false;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
		down = false;
	}
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
	if (m_UI_Movie->getChildByTag(1) != NULL) {
		m_UI_Movie->removeChildByTag(1);
		auto follow = Follow::create(camera);
		auto object = (Sprite*)rootNode->getChildByName("UsefulObject")->getChildByName("Object030");
		auto objectData = (ObjectMy*)(((Sprite*)object)->getUserData());
		auto objectAction = objectData->objectplay();
		Animate* objectPlay = Animate::create(objectAction);
		object->runAction(objectPlay);
		this->runAction(follow);
		SimpleAudioEngine::getInstance()->stopAllEffects();
		SimpleAudioEngine::getInstance()->playBackgroundMusic("Music//BGM.mp3", true);
	}
	if (m_UI_Movie->getChildByTag(2) != NULL || m_UI_Movie->getChildByTag(3) != NULL || m_UI_Movie->getChildByTag(4) != NULL) {
		reStartGame();
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_ENTER) {
		if (catalog->isVisible()) {
			if (arrowTimes == 2) {
				reStartGame();
			}
			else if (arrowTimes == 3) {
				exit(0);
			}
		}
		if (endChoice->isVisible()) {
			if (arrowTimes == 1) {
				showend2();
			}
			else if (arrowTimes == 0) {
				showend1();
			}
			endChoice->setVisible(false);
		}
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
		if (catalog->isVisible()) {
			if (arrowTimes != 0) {
				arrowTimes--;
			}
			if (arrowTimes == 1) {
				arrow->setPosition(camera->getPosition() + Vec2(-205, 185) + Vec2(0, -142));
			}
			else if (arrowTimes == 2) {
				arrow->setPosition(camera->getPosition() + Vec2(-205, 185) + Vec2(0, -290));
			}
			else if (arrowTimes == 3) {
				arrow->setPosition(camera->getPosition() + Vec2(-205, 185) + Vec2(0, -403));
			}
			else if (arrowTimes == 0) {
				arrow->setPosition(camera->getPosition() + Vec2(-205, 185));
			}
		}
		if (endChoice->isVisible()) {
			if (arrowTimes != 0) {
				arrowTimes--;
			}
			if (arrowTimes == 1) {
				bigArrow->setPosition(camera->getPosition() + Vec2(-400, 118) + Vec2(0, -260));
			}
			else if (arrowTimes == 0) {
				bigArrow->setPosition(camera->getPosition() + Vec2(-400, 118));
			}
		}
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		if (catalog->isVisible()) {
			if (arrowTimes != 3) {
				arrowTimes++;
			}
			if (arrowTimes == 1) {
				arrow->setPosition(camera->getPosition() + Vec2(-205, 185) + Vec2(0, -142));
			}
			else if (arrowTimes == 2) {
				arrow->setPosition(camera->getPosition() + Vec2(-205, 185) + Vec2(0, -290));
			}
			else if (arrowTimes == 3) {
				arrow->setPosition(camera->getPosition() + Vec2(-205, 185) + Vec2(0, -403));
			}
			else if (arrowTimes == 0) {
				arrow->setPosition(camera->getPosition() + Vec2(-205, 185));
			}
		}
		if (endChoice->isVisible()) {
			if (arrowTimes != 1) {
				arrowTimes++;
			}
			if (arrowTimes == 1) {
				bigArrow->setPosition(camera->getPosition() + Vec2(-400, 118) + Vec2(0, -260));
			}
			else if (arrowTimes == 0) {
				bigArrow->setPosition(camera->getPosition() + Vec2(-400, 118));
			}
		}
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
		if (catalog->isVisible()) {
			catalog->setVisible(false);
			arrow->setVisible(false);
			MusicTimer->setVisible(false);
			SoundTimer->setVisible(false);
			canmove = true;
		}
		else {
			if (canmove) {
				catalog->setPosition(camera->getPosition());
				arrow->setPosition(camera->getPosition() + Vec2(-205, 185));
				MusicTimer->setPosition(camera->getPosition() + Vec2(70, 182));
				SoundTimer->setPosition(camera->getPosition() + Vec2(70, 42));
				catalog->setVisible(true);
				arrow->setVisible(true);
				MusicTimer->setVisible(true);
				SoundTimer->setVisible(true);
				arrowTimes = 0;
				canmove = false;
			}
		}
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_Q) {
		if (!changingTool) {
			auto playerdata = (Player*)player->getUserData();
			playerdata->turnHoldingTool(0);
			auto tool = playerdata->getHoldingTool();
			if (tool != NULL) {
				showTool(tool->getToolName());
			}
		}
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_E) {
		if (!changingTool) {
			auto playerdata = (Player*)player->getUserData();
			playerdata->turnHoldingTool(1);
			auto tool = playerdata->getHoldingTool();
			if (tool != NULL) {
				showTool(tool->getToolName());
			}
		}
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_A) {
		left = true;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
		right = true;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_W) {
		if (canmove) {
			auto actionMoveDone = CallFuncN::create([&](Ref* sender) {
				jumping = false;
				stopAnimate();
			});
			if (!jumping&&!droping && (!onStair || standBy)) {
				jumping = true;
				auto jumpBy = JumpBy::create(0.5, Vec2(0, 200), 0, 1);
				auto action = Sequence::create(jumpBy, actionMoveDone, NULL);
				player->runAction(action);

				auto playerActionJump = ((Player*)player->getUserData())->getActionPlayerJump();
				actorContinuousAction(player, playerActionJump, 5);
				playerState = 5;

				Vec2 speed = player->getPhysicsBody()->getVelocity();
				speed.y = 0;
				player->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
			}
			if (onStair) {
				up = true;
			}
		}
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_S) {
		if (onStair || standBy) {
			down = true;
		}
	}
	bool newdialog = false;
	if (keyCode == EventKeyboard::KeyCode::KEY_J) {
		for (int i = 0; i < itemsVectorInMap.size(); i++) {
			Sprite *projectile = (CCSprite *)itemsVectorInMap.at(i);
			if (player->boundingBox().intersectsRect(projectile->boundingBox()) && (abs(player->getPosition().x - projectile->getPosition().x) < 100)) {
				if (itemsVectorInPlayer.find(projectile) == itemsVectorInPlayer.end()) {
					m_UI_Game->removeChild(projectile);
					player->addChild(projectile);
					itemsVectorInPlayer.pushBack(projectile);
					showItem(projectile->getName());
					playerGetTool(projectile);
					auto playerActionGet = ((Player*)player->getUserData())->getActionPlayerGet();
					playerAction(playerActionGet, 18);
					playerState = 18;

					auto PlayerData = (Player*)player->getUserData();
					auto Tool = CCSprite::createWithSpriteFrameName("UI/" + projectile->getName() + ".png");
					Tool->setPosition(Vec2(505 + ((PlayerData->getHoldingToolsNum() - 1) * 130), 80));
					itemMenu->addChild(Tool);

					SimpleAudioEngine::getInstance()->playEffect("Music//A.mp3");
					rootNode->getChildByName("Door")->removeChildByName("Wall_TEMP_12");
					itemsVectorInMap.eraseObject(projectile);
				}
			}
		}

		for (int i = 0; i < objectsVector.size(); i++) {
			Sprite *projectile = (CCSprite *)objectsVector.at(i);
			string HoldingToolName = "";
			if (((Player*)player->getUserData())->getHoldingToolsNum() > 0) {
				HoldingToolName = ((Player*)player->getUserData())->getHoldingTool()->getToolName();
			}
			if (player->boundingBox().intersectsRect(projectile->boundingBox()) && (abs(player->getPosition().x - projectile->getPosition().x) < 100)) {
				if (projectile->getName() == "Object001") {
					if (HoldingToolName == "hairpin") {
						auto object = (Construct*)projectile->getUserData();
						if (object->getState() != -1) {
							object->setState(-1);
							rootNode->getChildByName("Door")->removeChildByName("Door001");
							auto posZone4 = rootNode->getChildByName("Zone")->getChildByName("Zone004");
							auto princessMoveDone = CallFuncN::create([&](Ref* sender) {
								Animate* prstand_ = Animate::create(prstand);
								princess->stopAllActions();
								princess->runAction(prstand_);
							});
							Animate* prstand_ = Animate::create(prstand);
							princess->stopAllActions();
							princess->setFlipX(true);
							auto princessWalk = Animate::create(((Princess*)princess->getUserData())->getActionWalk());
							princess->runAction(princessWalk);
							auto moveTo = MoveTo::create(5.0, Point(posZone4->getPosition().x, princess->getPosition().y));
							auto seq = Sequence::create(moveTo, princessMoveDone, NULL);
							princess->runAction(seq);

							auto window = (Sprite*)rootNode->getChildByName("UsefulObject")->getChildByName("Object001");
							auto delayaction = DelayTime::create(1);
							auto actionDone = CallFuncN::create([&](Ref* sender) {

								auto delayaction = DelayTime::create(2);
								auto windowData = (ObjectMy*)(((Sprite*)sender)->getUserData());
								windowData->playVoice();
								auto windowAction = windowData->objectplay();
								Animate* windowOpen = Animate::create(windowAction);
								auto sqaction = Sequence::create(delayaction, windowOpen, NULL);
								((Sprite*)sender)->runAction(sqaction);
							});
							auto sqaction = Sequence::create(delayaction, actionDone, NULL);
							window->runAction(sqaction);

							auto playerActionOpenWindow = ((Player*)player->getUserData())->getActionPlayerWindowOpen();
							playerAction(playerActionOpenWindow, 9);
						}
					}
					else {
						auto object = (Construct*)projectile->getUserData();
						if (object->getState() != -1) {
							auto playerActionNoidea = ((Player*)player->getUserData())->getActionPlayerNoIdea();
							playerAction(playerActionNoidea, 8);
						}
					}
				}
				if (projectile->getName() == "Object008") {
					auto object = (Construct*)projectile->getUserData();
					if (object->getState() != -1) {
						object->setState(-1);
						//addNewItem("umbrella", Point(4640, 1801), 2291, 926, 155, 155);
						auto playerActionSearch = ((Player*)player->getUserData())->getActionPlayerSearch();
						playerAction(playerActionSearch, 17, "umbrella");
					}
				}
				if (projectile->getName() == "Object009") {
					auto object = (Construct*)projectile->getUserData();
					if (object->getState() != -1) {
						object->setState(-1);
						int y = 2454 - projectile->getContentSize().height / 2 + 155 / 2;
						//addNewItem("bucket", Point(5250, y), 2520, 926, 155, 155);
						auto object = (Sprite*)rootNode->getChildByName("UsefulObject")->getChildByName("Object009");
						auto objectData = (ObjectMy*)(((Sprite*)object)->getUserData());
						auto objectAction = objectData->objectplay();
						Animate* objectPlay = Animate::create(objectAction);
						object->runAction(objectPlay);

						auto playerActionSearch = ((Player*)player->getUserData())->getActionPlayerSearch();
						playerAction(playerActionSearch, 17, "bucket");
					}
				}
				if (projectile->getName() == "Object012") {
					auto object = (Construct*)projectile->getUserData();
					if (object->getState() != -1) {
						if (HoldingToolName == "umbrella") {
							object->setState(-1);
							//play
							Sprite *stair02 = (CCSprite *)rootNode->getChildByName("Stair")->getChildByName("Stair02");
							auto eventobject = (Construct*)stair02->getUserData();
							eventobject->setState(0);
							kailouti = true;

							auto actionDone = CallFuncN::create([&](Ref* sender) {
								canmove = true;
								kailouti = false;
								auto object = (Sprite*)rootNode->getChildByName("UsefulObject")->getChildByName("Object012");
								auto objectData = (ObjectMy*)(((Sprite*)object)->getUserData());
								auto objectAction = objectData->objectplay();
								Animate* objectPlay = Animate::create(objectAction);
								object->runAction(objectPlay);
							});
							auto playerActionAtticOpen = ((Player*)player->getUserData())->getActionPlayerAtticOpen();
							Animate* playerAction = Animate::create(playerActionAtticOpen);
							canmove = false;
							stopAnimate();
							auto action = Sequence::create(playerAction, actionDone, NULL);
							action->setTag(10);
							player->runAction(action);
							playerState = 10;
						}
						else {
							auto playerActionNoidea = ((Player*)player->getUserData())->getActionPlayerNoIdea();
							playerAction(playerActionNoidea, 8);
							PopScene * popLayer = PopScene::create("UI//A.png", "我得想办法把阁楼的楼梯放下来，可是我的手够不着，我需要一个长长的带勾的东西。", 1);
							popLayer->setPosition(camera->getPosition() + Vec2(0, -250));
							if (m_UI_Dialog->getChildrenCount() == 0) {
								m_UI_Dialog->addChild(popLayer);
								newdialog = true;
							}
						}
					}
				}
				if (projectile->getName() == "Object013") {
					auto object = (Construct*)projectile->getUserData();
					if (object->getState() != -1) {
						object->setState(-1);
						int y = 2454 - projectile->getContentSize().height / 2 + 155 / 2;
						//addNewItem("oilbucket", Point(6680, 5158), 2071, 1127, 155, 155);
						auto playerActionSearch = ((Player*)player->getUserData())->getActionPlayerSearch();
						playerAction(playerActionSearch, 17, "oilbucket");
						projectile->setVisible(false);

						auto object = (Sprite*)rootNode->getChildByName("UsefulObject")->getChildByName("Object013");
						auto objectData = (ObjectMy*)(((Sprite*)object)->getUserData());
						auto objectAction = objectData->objectplay();
						Animate* objectPlay = Animate::create(objectAction);
						object->runAction(objectPlay);


					}
				}
				if (projectile->getName() == "Object015") {
					auto object = (Construct*)projectile->getUserData();
					if (object->getState() != -1) {
						if (HoldingToolName == "bucket") {
							object->setState(-1);
							rootNode->getChildByName("Door")->removeChildByName("Door002");
							auto playerActionOutFire = ((Player*)player->getUserData())->getActionPlayerOutFire();
							playerAction(playerActionOutFire, 11);
							auto fadeout = FadeOut::create(2);
							auto fadeout2 = FadeOut::create(2);
							auto object016 = (Sprite*)rootNode->getChildByName("UsefulObject")->getChildByName("Object016");
							auto object015 = (Sprite*)rootNode->getChildByName("UsefulObject")->getChildByName("Object015");
							object016->runAction(fadeout);
							object015->runAction(fadeout2);


						}
						else {
							auto playerActionNoidea = ((Player*)player->getUserData())->getActionPlayerNoIdea();
							playerAction(playerActionNoidea, 8);
							PopScene * popLayer = PopScene::create("UI//A.png", "瓜瓜:烟太呛了，我不可能下得去，我需要水把火给浇灭。", 1);
							popLayer->setPosition(camera->getPosition() + Vec2(0, -250));
							if (m_UI_Dialog->getChildrenCount() == 0) {
								newdialog = true;
								m_UI_Dialog->addChild(popLayer);
							}
						}
					}
				}
				if (projectile->getName() == "Object018") {
					auto object = (Construct*)projectile->getUserData();
					if (object->getState() != -1) {
						object->setState(-1);
						//addNewItem("roomKey", projectile->getPosition(), 2290, 1127, 155, 155);
						auto playerActionSearch = ((Player*)player->getUserData())->getActionPlayerSearch();
						playerAction(playerActionSearch, 17, "roomKey");

						auto object = (Sprite*)rootNode->getChildByName("UsefulObject")->getChildByName("Object018");
						auto objectData = (ObjectMy*)(((Sprite*)object)->getUserData());
						auto objectAction = objectData->objectplay();
						Animate* objectPlay = Animate::create(objectAction);
						object->runAction(objectPlay);

					}
				}
				if (projectile->getName() == "Object020") {
					auto object = (Construct*)projectile->getUserData();
					if (object->getState() != -1) {
						if (HoldingToolName == "roomKey") {
							object->setState(-1);
							//play
							rootNode->getChildByName("Door")->removeChildByName("Door004");

							auto playerActionDoorOpen = ((Player*)player->getUserData())->getActionPlayerDoorOpen();
							playerAction(playerActionDoorOpen, 12);

							auto object = (Sprite*)rootNode->getChildByName("UsefulObject")->getChildByName("Object019");
							auto objectData = (ObjectMy*)(((Sprite*)object)->getUserData());
							auto objectAction = objectData->objectplay();
							Animate* objectPlay = Animate::create(objectAction);
							object->runAction(objectPlay);
						}
						else {
							auto playerActionNoidea = ((Player*)player->getUserData())->getActionPlayerNoIdea();
							playerAction(playerActionNoidea, 8);
							PopScene * popLayer = PopScene::create("UI//B.png", "太好了，你进来了。但是我没办法打开房间的门，你去找一下钥匙吧，我猜他们把钥匙藏在了他们房间里。", 1);
							popLayer->setPosition(camera->getPosition() + Vec2(0, -250));
							if (m_UI_Dialog->getChildrenCount() == 0) {
								newdialog = true;
								m_UI_Dialog->addChild(popLayer);
							}
						}
					}
				}
				if (projectile->getName() == "Object022") {
					auto object = (Construct*)projectile->getUserData();
					if (object->getState() != -1) {
						object->setState(-1);
						//addNewItem("match", projectile->getPosition(), 2520, 1127, 155, 155);
						auto playerActionSearch = ((Player*)player->getUserData())->getActionPlayerSearch();
						playerAction(playerActionSearch, 17, "match");

						auto object = (Sprite*)rootNode->getChildByName("UsefulObject")->getChildByName("Object022");
						auto objectData = (ObjectMy*)(((Sprite*)object)->getUserData());
						auto objectAction = objectData->objectplay();
						Animate* objectPlay = Animate::create(objectAction);
						object->runAction(objectPlay);
					}
				}
				if (projectile->getName() == "Object025") {
					auto object = (Construct*)projectile->getUserData();
					if (object->getState() != -1) {
						if (object->getState() == 0) {
							if (HoldingToolName == "oilbucket") {
								object->setState(1);
								//play
								auto playerActionOilPour = ((Player*)player->getUserData())->getActionPlayerOilPour();

								auto actionDone = CallFuncN::create([&](Ref* sender) {
									canmove = true;
									auto object = (Sprite*)rootNode->getChildByName("UsefulObject")->getChildByName("Object025");
									auto objectData = (ObjectMy*)(((Sprite*)object)->getUserData());
									auto objectAction = objectData->objectplay();
									Animate* objectPlay = Animate::create(objectAction);
									object->runAction(objectPlay);
								});
								Animate* playerAction = Animate::create(playerActionOilPour);
								canmove = false;
								stopAnimate();
								auto action = Sequence::create(playerAction, actionDone, NULL);
								action->setTag(13);
								player->runAction(action);
								playerState = 13;
							}
							else {
								auto playerActionNoidea = ((Player*)player->getUserData())->getActionPlayerNoIdea();
								playerAction(playerActionNoidea, 8);
							}
						}
						else if (object->getState() == 1) {
							if (HoldingToolName == "match") {
								Sprite *event008 = (CCSprite *)rootNode->getChildByName("Event")->getChildByName("Event008");
								auto eventobject = (Construct*)event008->getUserData();
								eventobject->setState(1);
								object->setState(-1);
								//play
								auto posZone7 = rootNode->getChildByName("Zone")->getChildByName("Zone007");

								dad->stopAllActions();
								Animate* dadAction1 = Animate::create(((Dad*)dad->getUserData())->getActionDadStandBy());
								Animate* dadAction2 = Animate::create(((Dad*)dad->getUserData())->getActionWalk());
								dad->setFlippedX(true);
								dad->runAction(Sequence::create(dadAction1, dadAction2, NULL));
								auto move = MoveTo::create(5.0, Point(posZone7->getPosition().x, dad->getPosition().y));
								auto moveDone = CallFuncN::create([&](Ref* sender) {
									actorPlayAction(dad, ((Dad*)dad->getUserData())->getActionDadoutFire(), 5);
								});
								auto dadaction = Sequence::create(move, moveDone, NULL);
								dad->runAction(dadaction);

								auto playerActionIgnite = ((Player*)player->getUserData())->getActionPlayerIgnite();
								auto actionDone = CallFuncN::create([&](Ref* sender) {
									canmove = true;
									auto object = (Sprite*)rootNode->getChildByName("UsefulObject")->getChildByName("Object025");
									auto objectData = (ObjectMy*)(((Sprite*)object)->getUserData());
									auto fireaction1 = Animate::create(objectData->getActionbyindex(0));
									auto fireaction2 = Animate::create(objectData->getActionbyindex(1));
									auto seq = Sequence::create(fireaction1, fireaction2, NULL);
									object->runAction(seq);
									playerState = -1;
								});
								Animate* playerAction = Animate::create(playerActionIgnite);
								canmove = false;
								stopAnimate();
								auto action = Sequence::create(playerAction, actionDone, NULL);
								action->setTag(14);
								player->runAction(action);
								playerState = 14;

								PopScene * popLayer1 = PopScene::create("UI//C.png", "不一一一一一一一一一！！我的书啊！！！", 1);
								popLayer1->setPosition(camera->getPosition() + Vec2(0, -250));
								PopScene * popLayer2 = PopScene::create("UI//B.png", "太棒了，我才不在乎书房会烧成什么样呢，爸爸以前就一直在书房里看书不陪我玩。", 1);
								popLayer2->setPosition(camera->getPosition() + Vec2(0, -250));
								PopScene * popLayer3 = PopScene::create("UI//B.png", "不过我妈妈还在楼下洗澡，你再帮我一下呗~在下水道里应该可以把洗澡水一下变冷呢，这样她就得疯上一会了。", 1);
								popLayer3->setPosition(camera->getPosition() + Vec2(0, -250));
								dialogStack.pushBack(popLayer3);
								dialogStack.pushBack(popLayer2);
								dialogStack.pushBack(popLayer1);

							}
							else {
								auto playerActionNoidea = ((Player*)player->getUserData())->getActionPlayerNoIdea();
								playerAction(playerActionNoidea, 8);
							}
						}
					}
				}
				if (projectile->getName() == "Object026") {
					auto object = (Construct*)projectile->getUserData();
					if (object->getState() != -1) {
						object->setState(-1);
						rootNode->getChildByName("Door")->removeChildByName("Door006");
						Sprite *event010 = (CCSprite *)rootNode->getChildByName("Event")->getChildByName("Event010");
						auto eventobject = (Construct*)event010->getUserData();
						eventobject->setState(1);
						auto playerActionWheelTurn = ((Player*)player->getUserData())->getActionPlayerWheelTurn();
						playerAction(playerActionWheelTurn, 15);
						PopScene * popLayer1 = PopScene::create("UI//D.png", "呀啊啊啊~~~~~！", 1);
						popLayer1->setPosition(camera->getPosition() + Vec2(0, -250));
						PopScene * popLayer2 = PopScene::create("UI//B.png", "嘿嘿，妈妈平时老是泡在浴缸里，怎么不变成胖大海呢？", 1);
						popLayer2->setPosition(camera->getPosition() + Vec2(0, -250));
						dialogStack.pushBack(popLayer2);
						dialogStack.pushBack(popLayer1);

						auto object = (Sprite*)rootNode->getChildByName("UsefulObject")->getChildByName("Object026");
						auto objectData = (ObjectMy*)(((Sprite*)object)->getUserData());
						auto objectAction = objectData->objectplay();
						Animate* objectPlay = Animate::create(objectAction);
						object->runAction(objectPlay);
					}
				}
			}
		}

		for (int i = 0; i < uselessObjectsVector.size(); i++) {
			Sprite *projectile = (CCSprite *)uselessObjectsVector.at(i);
			if (player->boundingBox().intersectsRect(projectile->boundingBox()) && (abs(player->getPosition().x - projectile->getPosition().x) < 100)) {
				auto object = (ObjectMy*)projectile->getUserData();
				projectile->stopAllActions();
				auto a = object->objectplay();
				auto action = Animate::create(a);
				projectile->stopAllActions();
				projectile->runAction(action);
			}
		}

		for (int i = 0; i < scareObjectsVector.size(); i++) {
			Sprite *projectile = (CCSprite *)scareObjectsVector.at(i);
			if (player->boundingBox().intersectsRect(projectile->boundingBox()) && (abs(player->getPosition().x - projectile->getPosition().x) < 100)) {
				auto object = (ObjectMy*)projectile->getUserData();
				projectile->stopAllActions();
				auto a = object->objectplay();
				auto action = Animate::create(a);
				projectile->stopAllActions();
				projectile->runAction(action);
			}
		}

		for (int i = 0; i < damageObjectsVector.size(); i++) {
			Sprite *projectile = (CCSprite *)damageObjectsVector.at(i);
			if (player->boundingBox().intersectsRect(projectile->boundingBox()) && (abs(player->getPosition().x - projectile->getPosition().x) < 100)) {
				auto object = (ObjectMy*)projectile->getUserData();
				projectile->stopAllActions();
				auto a = object->objectplay();
				auto action = Animate::create(a);
				projectile->stopAllActions();
				projectile->runAction(action);
				object->playVoice();
				playerGetHurt();
			}
		}

		if (player->boundingBox().intersectsRect(dad->boundingBox()) && (abs(player->getPosition().x - dad->getPosition().x) < 100)) {
			if (rootNode->getChildByName("Door")->getChildByName("Door004") != NULL) {
				PopScene * popLayer = PopScene::create("UI//C.png", "嘿，你好呀，你是糕糕的朋友吧？很抱歉，她现在在门禁呢，不过你可以到处逛逛~", 1);
				popLayer->setPosition(camera->getPosition() + Vec2(0, -250));
				int a = m_UI_Dialog->getChildrenCount();
				if (m_UI_Dialog->getChildrenCount() == 0) {
					newdialog = true;
					m_UI_Dialog->addChild(popLayer);
				}
			}
			else {
				PopScene * popLayer = PopScene::create("UI//C.png", "你想找我玩吗？哈哈哈，抱歉小淑女，我现在很忙，除非有什么突发状况，比如说我的宝贝书房烧起来了什么的，不然我现在可走不开。", 1);
				popLayer->setPosition(camera->getPosition() + Vec2(0, -250));
				if (m_UI_Dialog->getChildrenCount() == 0) {
					newdialog = true;
					m_UI_Dialog->addChild(popLayer);
				}
			}
		}
		if (player->boundingBox().intersectsRect(mom->boundingBox()) && (abs(player->getPosition().x - mom->getPosition().x) < 100)) {
			PopScene * popLayer = PopScene::create("UI//D.png", "??~~?(浴室哼唱)", 1);
			popLayer->setPosition(camera->getPosition() + Vec2(0, -250));
			if (m_UI_Dialog->getChildrenCount() == 0) {
				newdialog = true;
				m_UI_Dialog->addChild(popLayer);
			}
		}
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_J) {
		if (m_UI_Dialog->getChildrenCount() > 0 && newdialog == false) {
			m_UI_Dialog->removeAllChildren();
			if (dialogStack.empty()) {
				if (!end) {
					canmove = true;
				}
				cameramove = false;
			}
			if (end) {
				endChoice->setPosition(camera->getPosition());
				bigArrow->setPosition(camera->getPosition() + Vec2(-400, 118));
				endChoice->setVisible(true);
				bigArrow->setVisible(true);
				canmove = false;
				arrowTimes = 0;
				cameramove = true;
			}
		}
	}
}

void HelloWorld::updateStart(float delta)
{
	m_world->setAutoStep(false);
	scheduleUpdate();
}

void HelloWorld::canMove(float delta) {
	if (m_UI_Dialog->getChildrenCount() > 0) {
		canmove = false;
	}
}

void HelloWorld::conTact(float delta) {
	find->setVisible(false);
	for (int i = 0; i < itemsVectorInMap.size(); i++) {
		Sprite *projectile = (CCSprite *)itemsVectorInMap.at(i);
		if (player->boundingBox().intersectsRect(projectile->boundingBox()) && (abs(player->getPosition().x - projectile->getPosition().x) < 100)) {
			find->setVisible(true);
		}
	}

	for (int i = 0; i < objectsVector.size(); i++) {
		Sprite *projectile = (CCSprite *)objectsVector.at(i);
		if (player->boundingBox().intersectsRect(projectile->boundingBox()) && (abs(player->getPosition().x - projectile->getPosition().x) < 100)) {
			auto object = (Construct*)projectile->getUserData();
			if (object->getState() != -1) {
				find->setVisible(true);
			}
		}
	}

	for (int i = 0; i < uselessObjectsVector.size(); i++) {
		Sprite *projectile = (CCSprite *)uselessObjectsVector.at(i);
		if (player->boundingBox().intersectsRect(projectile->boundingBox()) && (abs(player->getPosition().x - projectile->getPosition().x) < 100)) {
			find->setVisible(true);
		}
	}

	for (int i = 0; i < scareObjectsVector.size(); i++) {
		Sprite *projectile = (CCSprite *)scareObjectsVector.at(i);
		if (player->boundingBox().intersectsRect(projectile->boundingBox()) && (abs(player->getPosition().x - projectile->getPosition().x) < 100)) {
			find->setVisible(true);
		}
	}

	for (int i = 0; i < damageObjectsVector.size(); i++) {
		Sprite *projectile = (CCSprite *)damageObjectsVector.at(i);
		if (player->boundingBox().intersectsRect(projectile->boundingBox()) && (abs(player->getPosition().x - projectile->getPosition().x) < 100)) {
			find->setVisible(true);
		}
	}

	if (player->boundingBox().intersectsRect(dad->boundingBox()) && (abs(player->getPosition().x - dad->getPosition().x) < 100)) {
		find->setVisible(true);
	}

	if (player->boundingBox().intersectsRect(mom->boundingBox()) && (abs(player->getPosition().x - mom->getPosition().x) < 100)) {
		find->setVisible(true);
	}

	for (auto& object : doorObjectsVector) {
		Sprite *projectile = (Sprite*)object;
		if (player->boundingBox().intersectsRect(projectile->boundingBox())) {
			auto objectData = (ObjectMy*)projectile->getUserData();
			if (objectData->getState() == 0) {
				objectData->setState(-1);
				auto objectAnimation = objectData->objectplay();
				auto action = Animate::create(objectAnimation);
				projectile->stopAllActions();
				projectile->runAction(action);
			}
		}
	}

	for (int i = 0; i < eventVector.size(); i++) {
		Sprite *projectile = (CCSprite *)eventVector.at(i);
		if (player->boundingBox().intersectsRect(projectile->boundingBox()) && (abs(player->getPosition().x - projectile->getPosition().x) < 100)) {
			if (projectile->getName() == "Event001") {
				auto object = (Construct*)projectile->getUserData();
				if (object->getState() == 0) {
					object->setState(-1);
					canmove = false;
					princesscomming();
				}
			}

			if (projectile->getName() == "Event005") {
				auto object = (Construct*)projectile->getUserData();
				if (object->getState() == 0) {
					object->setState(-1);
					rootNode->getChildByName("Door")->removeChildByName("Door003");
					auto object = (Sprite*)rootNode->getChildByName("UsefulObject")->getChildByName("Object029");
					auto objectData = (ObjectMy*)(((Sprite*)object)->getUserData());
					auto objectAction = objectData->objectplay();
					Animate* objectPlay = Animate::create(objectAction);
					object->runAction(objectPlay);
				}
			}

			if (projectile->getName() == "Event008") {
				auto object = (Construct*)projectile->getUserData();
				if (object->getState() == 1) {
					object->setState(-1);
					rootNode->getChildByName("Object")->removeChildByName("Object011");
					auto zone009 = rootNode->getChildByName("Zone")->getChildByName("Zone009");
					setPlayerPositionByZone(mom, zone009);

					auto actionDone = CallFuncN::create([&](Ref* sender) {
						auto actionDone = CallFuncN::create([&](Ref* sender) {
							auto actionDone = CallFuncN::create([&](Ref* sender) {
								princess->stopAllActions();
								auto princessStand = Animate::create(((Princess*)princess->getUserData())->getActionStand());
								princess->runAction(princessStand);
							});
							princess->stopAllActions();
							princess->setFlipX(false);
							auto princessWalk = Animate::create(((Princess*)princess->getUserData())->getActionWalk());
							princess->runAction(princessWalk);
							auto moveto2 = MoveTo::create(1.5, rootNode->getChildByName("Zone")->getChildByName("Zone008")->getPosition());
							auto seq = Sequence::create(moveto2, actionDone, NULL);
							princess->runAction(seq);
						});
						princess->stopAllActions();
						auto princessDownStair = Animate::create(((Princess*)princess->getUserData())->getActionPriDownStair());
						princess->runAction(princessDownStair);
						auto moveto2 = MoveTo::create(3, rootNode->getChildByName("Zone")->getChildByName("Zone015")->getPosition());
						auto seq = Sequence::create(moveto2, actionDone, NULL);
						princess->runAction(seq);
					});
					princess->stopAllActions();
					auto princessWalk = Animate::create(((Princess*)princess->getUserData())->getActionWalk());
					princess->runAction(princessWalk);
					auto moveto1 = MoveTo::create(1, rootNode->getChildByName("Zone")->getChildByName("Zone014")->getPosition());
					auto seq = Sequence::create(moveto1, actionDone, NULL);
					princess->runAction(seq);

				}
			}
			if (projectile->getName() == "Event010") {
				auto object = (Construct*)projectile->getUserData();
				if (object->getState() == 1) {
					object->setState(-1);
					auto zone011 = rootNode->getChildByName("Zone")->getChildByName("Zone011");
					auto princess = (Sprite*)m_UI_Game->getChildByName("princess");
					setPlayerPositionByZone(princess, zone011);
				}
			}

			if (projectile->getName() == "Event012") {
				auto object = (Construct*)projectile->getUserData();
				if (object->getState() == 0) {
					princess->setPosition(rootNode->getChildByName("Zone")->getChildByName("Zone016")->getPosition());
					princess->stopAllActions();
					Animate* princessWalk = Animate::create(((Princess*)princess->getUserData())->getActionWalk());
					princess->runAction(princessWalk);

					auto actionDone = CallFuncN::create([&](Ref* sender) {
						princess->stopAllActions();
						Animate* princessStand = Animate::create(((Princess*)princess->getUserData())->getActionStand());
						princess->runAction(princessStand);
						PopScene * popLayer = PopScene::create("UI//B.png", "千金:那么我们就在这里分别吧，我要从那边的树林捷径里穿过去，再见啦大姐姐~", 1);
						popLayer->setPosition(camera->getPosition() + Vec2(0, -250));
						m_UI_Dialog->addChild(popLayer);

					});
					auto moveTo = MoveTo::create(3, rootNode->getChildByName("Zone")->getChildByName("Zone017")->getPosition());
					auto seq = Sequence::create(moveTo, actionDone, NULL);
					princess->runAction(seq);

					player->stopAllActions();
					Animate* playerStand = Animate::create(((Player*)player->getUserData())->getActionStand());
					player->runAction(playerStand);
					object->setState(-1);
					playerState = -1;
					end = true;
					canmove = false;
					unschedule(schedule_selector(HelloWorld::changeLocation));
					unschedule(schedule_selector(HelloWorld::cameraMove));
					cameramove = true;
					auto moveBy = MoveBy::create(3, Vec2(500, 0));
					camera->runAction(moveBy);
					player->setFlippedX(true);
				}
			}

		}
	}
	onStair = false;
	for (int i = 0; i < stairsVector.size(); i++) {
		Sprite *projectile = (CCSprite *)stairsVector.at(i);
		if (player->boundingBox().intersectsRect(projectile->boundingBox()) && (abs(player->getPosition().x - projectile->getPosition().x) < 150)) {
			auto object = (Construct*)projectile->getUserData();
			if (object->getState() == 0) {
				if (abs(player->getPosition().x - projectile->getPosition().x) < 150) {
					onStair = true;
				}
			}
		}
	}
	if (onStair == false && standBy == false) {
		if (playerState == 16) {
			playerState = -1;
		}
	}
	bool tempstandBy = standBy;
	standBy = false;
	for (int i = 0; i < StandBysVector.size(); i++) {
		Sprite *projectile = (CCSprite *)StandBysVector.at(i);
		if (player->boundingBox().intersectsRect(projectile->boundingBox()) && (abs(player->getPosition().x - projectile->getPosition().x) < 100)) {
			if (abs(player->getPosition().x - projectile->getPosition().x) < 30) {
				standBy = true;
				droping = false;
			}
		}
	}
	if (tempstandBy == true && standBy == false) {
		playerState = -1;
	}
	onxiepo = false;
	rotation = 0;
	for (int i = 0; i < XieposVector.size(); i++) {
		Sprite *projectile = (CCSprite *)XieposVector.at(i);
		if (player->boundingBox().intersectsRect(projectile->boundingBox())) {
			auto distancex = abs(player->getPosition().x - projectile->getPosition().x);
			auto xiepohalflength = projectile->getContentSize().width*projectile->getScaleX() / 2 * cos(CC_DEGREES_TO_RADIANS(projectile->getRotation()));
			auto xiepoheightbegin = projectile->getPosition().y - abs(projectile->getContentSize().width*projectile->getScaleX() / 2 * sin(CC_DEGREES_TO_RADIANS(projectile->getRotation())));
			if (distancex < xiepohalflength) {
				auto sign = projectile->getRotation() > 0 ? 1 : -1;
				auto xiepoX = projectile->getPosition().x + sign*xiepohalflength;
				auto temp_x = xiepoX - player->getPosition().x;
				auto temp_y = temp_x*tan(CC_DEGREES_TO_RADIANS(projectile->getRotation()));

				auto fix_y = temp_y + xiepoheightbegin;
				auto footposition = player->getPosition().y - player->getContentSize().height / 2;
				if (abs(player->getPosition().y - player->getContentSize().height / 2 - fix_y) < 55) {
					onxiepo = true;
					rotation = projectile->getRotation();
				}
			}
		}
	}
	if (onxiepo == true) {
		stairground_1->setVisible(true);
	}
	else {
		stairground_1->setVisible(false);
	}
}
void HelloWorld::playerMove(float delta) {
	//drop when it is not on the floor
	if (!die) {
		if (!jumping&&!onStair&&!standBy&&!kailouti) {
			drop();
		}
		playerWalk();
		if (!standBy) {
			if (!jumping) {
				fixPosition();
			}
		}
	}
}

void HelloWorld::cameraMove(float delta) {
	auto a = player->getPosition() + Vec2(384.0, 216.0) + (!Location)*Vec2(-768, 0);
	auto camearPos = camera->getPosition();
	if (!cameramove) {
		camera->setPosition(a);
	}
}

void HelloWorld::itemMenuMove(float delta) {
	auto cameraPos = camera->getPosition();
	auto itemMenuPos = cameraPos + Vec2(0, -440);
	auto findPos = player->getPosition() + Vec2(72, 130);
	itemMenu->setPosition(itemMenuPos);
	find->setPosition(findPos);
}

void HelloWorld::playerWalk() {
	if (left == true && canmove) {
		Location = false;
		if ((playerState == 0 || playerState == -1 || playerState == 3 || playerState == 4) && !onxiepo) {
			auto playerActionWalk = ((Player*)player->getUserData())->getActionWalk();
			actorContinuousAction(player, playerActionWalk, 1);
			playerState = 1;
		}
		if (onxiepo) {
			if (playerState == 0 || playerState == -1 || playerState == 1 || playerState == 3 || playerState == 4) {
				if (rotation > 0 && playerState != 4) {
					auto playerActionUpStair = ((Player*)player->getUserData())->getActionPlayerUpStair();
					actorContinuousAction(player, playerActionUpStair, 4);
					playerState = 4;
				}
				else if (rotation< 0 && playerState != 3) {
					auto playerActionDownStair = ((Player*)player->getUserData())->getActionPlayerDownStair();
					actorContinuousAction(player, playerActionDownStair, 3);
					playerState = 3;
				}
			}
		}
		Vec2 speed = player->getPhysicsBody()->getVelocity();
		if (speed.x >= 0) {
			speed.x = moveV;

		}
		int haha = wallBesideLeft();
		if (haha == 1) {
			speed.x = 0;
		}

		player->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
		//camera->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
	}
	else if (right == true && canmove) {
		Location = true;
		if ((playerState == 0 || playerState == -1 || playerState == 4 || playerState == 3) && !onxiepo) {
			auto playerActionWalk = ((Player*)player->getUserData())->getActionWalk();
			actorContinuousAction(player, playerActionWalk, 1);
			playerState = 1;
		}
		if (onxiepo) {
			if (playerState == 0 || playerState == -1 || playerState == 1 || playerState == 4 || playerState == 3) {
				if (rotation > 0 && playerState != 3) {
					auto playerActionDownStair = ((Player*)player->getUserData())->getActionPlayerDownStair();
					actorContinuousAction(player, playerActionDownStair, 3);
					playerState = 3;
				}
				else if (rotation < 0 && playerState != 4) {
					auto playerActionUpStair = ((Player*)player->getUserData())->getActionPlayerUpStair();
					actorContinuousAction(player, playerActionUpStair, 4);
					playerState = 4;
				}
			}
		}
		Vec2 speed = player->getPhysicsBody()->getVelocity();
		if (speed.x <= 0) {
			speed.x = 200 * 1.3*1.5;
		}
		int haha = wallBesideRight();
		if (haha == 1) {
			speed.x = 0;
		}
		player->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
		//camera->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
	}
	if (right == left && canmove) {
		Vec2 speed = player->getPhysicsBody()->getVelocity();
		speed.x = 0;
		player->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
		//camera->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
		if (playerState == 1 || playerState == -1 || playerState == 3 || playerState == 4) {
			auto playerActionStand = ((Player*)player->getUserData())->getActionStand();
			actorContinuousAction(player, playerActionStand, 0);
			playerState = 0;
		}
	}
	if (onStair) {
		if (up == true) {
			Vec2 speed = player->getPhysicsBody()->getVelocity();
			//speed.x = 0;
			speed.y = 200 * 1.3;
			player->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
			if (playerState != 16) {
				auto playerActionClimb = ((Player*)player->getUserData())->getActionPlayerClimb();
				actorContinuousAction(player, playerActionClimb, 16);
				playerState = 16;
			}
			//camera->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
		}
		if (down == true) {
			Vec2 speed = player->getPhysicsBody()->getVelocity();
			//speed.x = 0;
			speed.y = moveV;
			player->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
			if (playerState != 16) {
				auto playerActionClimb = ((Player*)player->getUserData())->getActionPlayerClimb();
				actorContinuousAction(player, playerActionClimb, 16);
				playerState = 16;
			}
			//camera->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
		}
		if (up == down&&!standBy) {
			Vec2 speed = player->getPhysicsBody()->getVelocity();
			player->getPhysicsBody()->setVelocity(Vec2(speed.x, 0));

			//camera->getPhysicsBody()->setVelocity(Vec2(speed.x, 0));
		}
	}
	if (standBy) {
		if (down == true) {
			Vec2 speed = player->getPhysicsBody()->getVelocity();
			speed.x = 0;
			speed.y = moveV;
			player->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
			//camera->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
		}
		else if (up != true) {
			Vec2 speed = player->getPhysicsBody()->getVelocity();
			speed.y = 0;
			player->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
			//camera->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
			if (playerState == 6) {
				playerState = -1;
			}
		}

	}
	if (!canmove) {
		Vec2 speed = player->getPhysicsBody()->getVelocity();
		speed.x = 0;
		player->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
		//camera->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
	}
}
void HelloWorld::update(float dt)
{
	for (int i = 0; i < 6; ++i)
	{
		m_world->step(1 / 360.0f);
	}
	auto a = player->getPosition() + Vec2(384.0, 66.0) + (!Location)*Vec2(-768, 0);
	auto camearPos = camera->getPosition();
	if (!cameramove) {
		camera->setPosition(a);
	}
	auto itemMenuPos = camearPos + Vec2(0, -440);
	auto lifeSlotPos = camearPos + Vec2(-755, 410);
	itemMenu->setPosition(itemMenuPos);
	lifeSlot->setPosition(lifeSlotPos);
	auto HPPos = lifeSlot->getPosition();
	HPTimer->setPosition(HPPos);

	auto findPos = player->getPosition() + Vec2(80, 140);
	itemMenu->setPosition(itemMenuPos);
	find->setPosition(findPos);

}
void HelloWorld::changeLocation(float dt) {
	if (Location != player->isFlippedX()) {
		if (Location) {
			auto actionDone = CallFuncN::create([&](Ref* sender) {
				cameramove = false;
				canmove = true;
			});
			auto a = player->getPosition() + Vec2(384.0, 66) + (!Location)*Vec2(-768, 0);
			auto moveto = MoveTo::create(0.5, a);

			auto action = Sequence::create(moveto, actionDone, NULL);
			auto sineOut = EaseSineOut::create(action);
			if (!jumping&&!droping) {
				cameramove = true;
				canmove = false;
				camera->runAction(sineOut);
			}

		}
		else {
			auto actionDone = CallFuncN::create([&](Ref* sender) {
				cameramove = false;
				canmove = true;
			});
			auto moveby = MoveBy::create(0.5, Vec2(-768, 0));
			auto action = Sequence::create(moveby, actionDone, NULL);
			auto sineOut = EaseSineOut::create(action);
			if (!jumping&&!droping) {
				cameramove = true;
				canmove = false;
				camera->runAction(sineOut);
			}
		}
	}
	player->setFlippedX(Location);
}
void HelloWorld::drop() {
	Point playerPosition = player->getPosition();
	unsigned int image_front_x = player->getPosition().x;
	auto a = player->getContentSize();
	unsigned int image_front_y = background->getContentSize().height - (player->getPosition().y - player->getContentSize().height / 2) + 5;
	unsigned int image_after_x = image_front_x + 40;
	unsigned int image_after_y = image_front_y;
	ccColor4B c_front = getPixelColorByPoint(Point(image_front_x, image_front_y));
	ccColor4B c_after = getPixelColorByPoint(Point(image_after_x, image_after_y));
	if (c_front.a == 0) {
		droping = true;
		Vec2 speed = player->getPhysicsBody()->getVelocity();
		if (onxiepo) {
			speed.y = -250 * 1.3*1.5;
		}
		else {
			if (speed.y > -1000) {
				if (speed.y > -300) {
					speed.y = -300;
				}
				speed.y += -20;
			}
		}
		player->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
		//camera->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
		if (playerState != 6 && !onxiepo) {
			auto playerActionFall = ((Player*)player->getUserData())->getActionPlayerFall();
			actorContinuousAction(player, playerActionFall, 6);
			playerState = 6;
		}
	}
	else {
		Vec2 speed = player->getPhysicsBody()->getVelocity();
		speed.y = 0;
		player->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
		//camera->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
		if (droping == true) {
			droping = false;
			if (playerState != 7 && (playerState == 6 || playerState == 5)) {
				auto playerActionRecovery = ((Player*)player->getUserData())->getActionPlayerRecovery();
				actorSingleAction(player, playerActionRecovery, 7);
				playerState = 7;
			}
		}
	}
}
//To fix position when player is in floor or wall
void HelloWorld::fixPosition() {
	if (!onStair&&!jumping&&!droping) {
		Point playerPosition = player->getPosition();
		unsigned int image_x = player->getPosition().x;
		unsigned int image_y = background->getContentSize().height -
			(player->getPosition().y - player->getContentSize().height / 2);
		ccColor4B leftBottom = getPixelColorByPoint(Point(image_x, image_y));
		Vec2 speed = player->getPhysicsBody()->getVelocity();
		if (leftBottom.a == 255 && leftBottom.g < 100) {
			speed.y = 200 * 1.3*1.5;
			player->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
			//camera->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
			if (playerState == 5) {
				playerState = -1;
			}
		}
	}
	Point playerPosition = player->getPosition();
	unsigned int image_x = player->getPosition().x;
	unsigned int image_y = background->getContentSize().height -
		(player->getPosition().y - player->getContentSize().height / 2);
	ccColor4B leftBottom = getPixelColorByPoint(Point(image_x, image_y));
	leftBottom = getPixelColorByPoint(Point(image_x, image_y + 20));
}
int HelloWorld::wallBesideLeft() {
	Point playerPosition = player->getPosition();
	unsigned int image_x = player->getPosition().x - 10;
	unsigned int image_y = background->getContentSize().height -
		(player->getPosition().y - player->getContentSize().height / 2) - 10;
	ccColor4B leftBottom = getPixelColorByPoint(Point(image_x, image_y));
	image_y -= 20;
	ccColor4B leftTop = getPixelColorByPoint(Point(image_x, image_y));
	if (leftBottom.a >= 225) {
		if (leftTop.a >= 225) {
			return 1;
		}
		else {
			return 2;
		}
	}
	return 3;
}

int HelloWorld::wallBesideRight() {
	Point playerPosition = player->getPosition();
	unsigned int image_x = player->getPosition().x + 10;
	unsigned int image_y = background->getContentSize().height -
		(player->getPosition().y - player->getContentSize().height / 2) - 10;
	ccColor4B leftBottom = getPixelColorByPoint(Point(image_x, image_y));
	image_y -= 20;
	ccColor4B leftTop = getPixelColorByPoint(Point(image_x, image_y));
	if (leftBottom.a == 255) {
		if (leftTop.a == 255) {
			return 1;
		}
		else {
			return 2;
		}
	}
	return 3;
}
ccColor4B HelloWorld::getPixelColorByPoint(Point pos) {
	unsigned int image_x = pos.x;
	unsigned int image_y = pos.y;
	ccColor4B c = { 0, 0, 0 ,0 };
	unsigned int *pixel = (unsigned int *)c_data;
	pixel = pixel + (image_y * (int)background->getContentSize().width) * 1 + image_x * 1;
	c.r = *pixel & 0xff;
	c.g = (*pixel >> 8) & 0xff;
	c.b = (*pixel >> 16) & 0xff;
	c.a = (*pixel >> 24) & 0xff;
	return c;
}
void HelloWorld::addNewItem(string itemName, Point pos, int a, int b, int c, int d) {
	bool findit = false;
	for (int j = 0; j < itemsVectorInMap.size(); j++) {
		Sprite *itemile = (CCSprite *)itemsVectorInMap.at(j);
		if (itemile->getName() == itemName) {
			findit = true;
			break;
		}
	}
	if (!findit) {
		string path = "item//" + itemName + ".png";
		Sprite* item = Sprite::create(path);
		item->setName(itemName);
		item->setPosition(pos);
		m_UI_Game->addChild(item);
		itemsVectorInMap.pushBack(item);
	}
}
//move finish
void HelloWorld::setPlayerPositionByZone(Sprite* player, Node* zone) {
	Point pos = zone->getPosition();
	pos.y = pos.y - zone->getContentSize().height / 2 + player->getContentSize().height / 2;
	player->setPosition(pos);
}

void HelloWorld::initAnimate() {
	/*ptemp = loadAnimate("playertemp.gif", 1, false);
	princessStand = loadAnimate("pricness.gif", -1, false);
	princessTemp = loadAnimate("temp.gif", 1, false);
	pStand = loadAnimate("gif//000-stand.gif", -1, false);
	pWalk = loadAnimate("gif//001-walk.gif", -1, false);
	pjump = loadAnimate("gif//005-jump.gif", 1, false);
	pfall = loadAnimate("gif//006-fall.gif", 1, false);
	precovery = loadAnimate("gif//007-recovery.gif", 1, false);
	pdownStair = loadAnimate("gif//003-down-stair.gif", -1, false);
	pupStair = loadAnimate("gif//004-up-stair.gif", -1, false);
	popenWindow = loadAnimate("gif//009-window-open.gif", 1, false);
	pnoidea = loadAnimate("gif//008-no-idea.gif", 1, false);
	patticopen = loadAnimate("gif//010-attic-open.gif", 1, false);
	poutfire = loadAnimate("gif//011-outfire.gif", 1, false);
	pdooropen = loadAnimate("gif//012-door-open.gif", 1, false);
	poilthrow = loadAnimate("gif//013-oil-throw.gif", 1, false);
	pfire = loadAnimate("gif//014-fire.gif", 1, false);
	pturn = loadAnimate("gif//015-turn.gif", 1, false);
	pclimb = loadAnimate("gif//016-climb.gif", -1, false);
	pget = loadAnimate("gif//018-get.gif", 1, false);
	psearch = loadAnimate("gif//017-search.gif", 1, false);*/

	prstand = loadAnimate("gifByPricness//000-stand.gif", -1, false);
	prkao = loadAnimate("gifByPricness//001-kao.gif", 1, false);
	prtalk = loadAnimate("gifByPricness//002-talk.gif", 1, false);
	prthrow = loadAnimate("gifByPricness//003-throw.gif", 1, false);

	dadstand = loadAnimate("gifByDad//001-stand.gif", -1, false);
	dadtalk = loadAnimate("gifByDad//002-talk.gif", 1, false);
	dadrun = loadAnimate("gifByDad//003-run.gif", -1, false);
	dadstanby = loadAnimate("gifByDad//004-standby.gif", 1, false);
	dadoutfire = loadAnimate("gifByDad//005-outfire.gif", -1, false);
	//fall
}
void HelloWorld::playerAction() {
	auto actionDone = CallFuncN::create([&](Ref* sender) {
		canmove = true;
		stopAnimate();
		Animate* aStand = Animate::create(pStand);
		aStand->setTag(0);
		player->runAction(aStand);
		playerState = 0;
	});
	canmove = false;
	Animate* playerTempAction = Animate::create(ptemp);
	stopAnimate();
	auto action = Sequence::create(playerTempAction, actionDone, NULL);
	action->setTag(66);
	player->runAction(action);
}
Animation* HelloWorld::loadAnimateByTime(string path, double time, bool back) {
	GifAnimationDef* def = new GifAnimationDef;
	def->loops = 1;
	def->filePath = path;
	def->delayPerUnit = 1.0 / 30;
	def->restoreOriginalFrame = back;
	auto newresult = GifAnimation::getInstance()->createAnimation(*def);
	return newresult;
}

Animation* HelloWorld::loadAnimate(string path, int times, bool back) {
	GifAnimationDef* def = new GifAnimationDef;
	def->loops = times;						// 循环次数
	def->filePath = path;				// 文件路径
	def->delayPerUnit = 1.0 / 30;			// 每帧间隔
	def->restoreOriginalFrame = back;	// 还原初始状态

										// 创建动画
	auto result = GifAnimation::getInstance()->createAnimation(*def);
	return result;
}
void HelloWorld::stopAnimate() {
	for (int i = 0; i <= 20; i++) {
		player->stopActionByTag(i);
	}
	playerState = -1;
}
void HelloWorld::playerAction(Animation* paction, int i) {
	auto actionDone = CallFuncN::create([&](Ref* sender) {
		canmove = true;
		stopAnimate();
		kailouti = false;
		playerState = -1;
		if (((Sequence*)sender)->getTag() == 12) {
			PopScene * popLayer = PopScene::create("UI//B.png", "哈哈太好啦，我现在能逃出去了！不对…糟了，我爸爸在楼下呢！你能想点办法支开他吗？", 1);
			popLayer->setPosition(camera->getPosition() + Vec2(0, -250));
			m_UI_Dialog->addChild(popLayer);
		}
	});
	canmove = false;
	Animate* playerTempAction = Animate::create(paction);
	stopAnimate();
	auto action = Sequence::create(playerTempAction, actionDone, NULL);
	action->setTag(i);
	player->runAction(action);
	playerState = i;
}
void HelloWorld::showItem(string Name) {
	string path = "item//" + Name + ".png";
	Sprite* item = Sprite::create(path);
	tempitem = item;
	item->setName(Name);
	auto pos = player->getPosition() + Vec2(0, player->getContentSize().height / 2);
	item->setPosition(pos);
	m_UI_Game->addChild(item);
	auto actionDone = CallFuncN::create([&](Ref* sender) {
		if (itemsVectorInPlayer.find(tempitem) == itemsVectorInPlayer.end()) {
			m_UI_Game->removeChild(tempitem);
			player->addChild(tempitem);
			itemsVectorInPlayer.pushBack(tempitem);
		}
	});
	auto delay = DelayTime::create(0.5);
	auto action = Sequence::create(delay, actionDone, NULL);
	item->runAction(action);
}
void HelloWorld::showTool(string Name) {
	string path = "item//" + Name + ".png";
	Sprite* item = Sprite::create(path);
	tempitem = item;
	item->setName(Name);
	auto pos = player->getPosition() + Vec2(0, player->getContentSize().height / 2);
	item->setPosition(pos);
	m_UI_Game->addChild(item);
	auto actionDone = CallFuncN::create([&](Ref* sender) {
		changingTool = false;
		((Sprite*)sender)->removeFromParent();
	});
	auto delay = DelayTime::create(0.5);
	auto action = Sequence::create(delay, actionDone, NULL);
	changingTool = true;
	item->runAction(action);
}
void HelloWorld::playerAction(Animation* paction, int i, string Name) {
	auto actionDone = CallFuncN::create([&](Ref* sender) {
		stopAnimate();
		auto getactionDone = CallFuncN::create([&](Ref* sender) {
			canmove = true;
			stopAnimate();
			playerState = -1;
			auto tempSprite = Sprite::create();
			tempSprite->setName(itemName);
			playerGetTool(tempSprite);
			auto PlayerData = (Player*)player->getUserData();
			auto Tool = CCSprite::createWithSpriteFrameName("UI/" + tempSprite->getName() + ".png");
			Tool->setPosition(Vec2(505 + ((PlayerData->getHoldingToolsNum() - 1) * 130), 80));
			itemMenu->addChild(Tool);

		});
		auto PlayerActionGet = ((Player*)player->getUserData())->getActionPlayerGet();
		Animate* getAction = Animate::create(PlayerActionGet);
		auto allaction = Sequence::create(getAction, getactionDone, NULL);
		player->runAction(allaction);
		showItem(itemName);

	});
	canmove = false;
	Animate* playerTempAction = Animate::create(paction);
	stopAnimate();
	auto action = Sequence::create(playerTempAction, actionDone, NULL);
	action->setTag(i);
	itemName = Name;
	player->runAction(action);
	playerState = i;
}
void HelloWorld::princesscomming() {
	auto cameraMoveDone = CallFuncN::create([&](Ref* sender) {
		auto actionDone = CallFuncN::create([&](Ref* sender) {
			addNewItem("hairpin", Vec2(2734, 3947), 1, 2, 3, 4);
			Animate* princessStand = Animate::create(prstand);
			princess->stopAllActions();
			princess->runAction(princessStand);
			canmove = true;
		});
		canmove = false;
		princess->stopAllActions();
		Animate* princessKao = Animate::create(prkao);
		Animate* princessTalk = Animate::create(prtalk);
		Animate* princessThrow = Animate::create(prthrow);
		auto action = Sequence::create(princessKao, princessTalk, princessThrow, actionDone, NULL);
		PopScene * popLayer1 = PopScene::create("UI//B.png", "啊，那边的姐姐，请帮帮我！", 1);
		popLayer1->setPosition(camera->getPosition() + Vec2(0, -250));
		PopScene * popLayer2 = PopScene::create("UI//A.png", "你怎么了？", 1);
		popLayer2->setPosition(camera->getPosition() + Vec2(0, -250));
		PopScene * popLayer3 = PopScene::create("UI//B.png", "我想离家出走，但是我爸妈把我锁在房间里了，请一定要帮帮我。", 1);
		popLayer3->setPosition(camera->getPosition() + Vec2(0, -250));
		PopScene * popLayer4 = PopScene::create("UI//B.png", "拿着这个，希望你能找到方法进来。", 1);
		popLayer4->setPosition(camera->getPosition() + Vec2(0, -250));
		m_UI_Afterall->addChild(popLayer1);
		m_UI_Afterall->addChild(popLayer2);
		m_UI_Afterall->addChild(popLayer3);
		m_UI_Afterall->addChild(popLayer4);
		dialogStack.pushBack(popLayer4);
		string dialogpath4 = "ActorVoice//GaoGao//GaoGao03.mp3";
		dialogPath.push_back(dialogpath4);
		dialogStack.pushBack(popLayer3);
		string dialogpath3 = "ActorVoice//GaoGao//GaoGao02.mp3";
		dialogPath.push_back(dialogpath3);
		dialogStack.pushBack(popLayer2);
		string dialogpath2 = "ActorVoice//GuaGua//GuaGua01.mp3";
		dialogPath.push_back(dialogpath2);
		dialogStack.pushBack(popLayer1);
		string dialogpath1 = "ActorVoice//GaoGao//GaoGao01.mp3";
		dialogPath.push_back(dialogpath1);
		princess->runAction(action);
	});
	auto pos = (player->getPosition() + princess->getPosition()) / 2;
	auto cameraaction = MoveTo::create(0.5, pos);
	auto caction = Sequence::create(cameraaction, cameraMoveDone, NULL);
	cameramove = true;
	camera->runAction(caction);
}
void HelloWorld::actorPlayAction(Sprite* actor, Animation* paction, int actionnum) {
	actor->stopAllActions();
	Animate* playerTempAction = Animate::create(paction);
	playerTempAction->setTag(actionnum);
	actor->runAction(playerTempAction);
}

void HelloWorld::initItemMenu() {
	itemMenu = CCSprite::createWithSpriteFrameName("UI/toolMenu.png");
	lifeSlot = CCSprite::createWithSpriteFrameName("UI/lifeslot.png");
	catalog = CCSprite::createWithSpriteFrameName("UI/catalog.png");
	arrow = CCSprite::createWithSpriteFrameName("UI/arrow.png");
	find = CCSprite::createWithSpriteFrameName("UI/find.png");
	bigArrow = CCSprite::createWithSpriteFrameName("UI/bigArrow.png");
	endChoice = CCSprite::createWithSpriteFrameName("UI/endChoice.png");
	find->setVisible(false);
	catalog->setVisible(false);
	arrow->setVisible(false);
	bigArrow->setVisible(false);
	endChoice->setVisible(false);
	CCSprite *progress2Sprite = CCSprite::createWithSpriteFrameName("UI/HP.png");
	CCSprite *progress2Sprite_ = CCSprite::createWithSpriteFrameName("UI/EXP.png");
	HPTimer = ProgressTimer::create(progress2Sprite);
	HPTimer->setType(kCCProgressTimerTypeBar);
	/*auto test = CCSprite::createWithSpriteFrameName("UI/roomKey.png");
	test->setPosition(Vec2(505, 80));
	itemMenu->addChild(test,60);*/
	HPTimer->setMidpoint(ccp(0, 0));
	HPTimer->setBarChangeRate(ccp(1, 0));
	HPTimer->setPercentage(100);
	SoundTimer = ProgressTimer::create(progress2Sprite_);
	MusicTimer = ProgressTimer::create(progress2Sprite_);

	SoundTimer->setType(kCCProgressTimerTypeBar);
	SoundTimer->setMidpoint(ccp(0, 0));
	SoundTimer->setBarChangeRate(ccp(1, 0));
	SoundTimer->setPercentage(100);
	SoundTimer->setVisible(false);

	MusicTimer->setType(kCCProgressTimerTypeBar);
	MusicTimer->setMidpoint(ccp(0, 0));
	MusicTimer->setBarChangeRate(ccp(1, 0));
	MusicTimer->setPercentage(100);
	MusicTimer->setVisible(false);
	m_UI_Tool->addChild(itemMenu);
	m_UI_Tool->addChild(lifeSlot);
	m_UI_Tool->addChild(HPTimer);
	m_UI_Tool->addChild(catalog);
	m_UI_Tool->addChild(arrow);
	m_UI_Tool->addChild(SoundTimer);
	m_UI_Tool->addChild(MusicTimer);
	m_UI_Tool->addChild(find);
	m_UI_Tool->addChild(endChoice);
	m_UI_Tool->addChild(bigArrow);
}

void HelloWorld::initActor() {
	player = Sprite::create("player1.png");
	princess = Sprite::create("princess.png");
	dad = Sprite::create("dad.png");
	mom = Sprite::create("mom.png");
	Player* newPlayer = new Player("Player", 0);
	Princess* newPrincess = new Princess("Princess", 1);
	Dad* newDad = new Dad("Dad", 2);
	player->setUserData(newPlayer);
	princess->setUserData(newPrincess);

	Animate* prstand_ = Animate::create(prstand);
	princess->stopAllActions();
	princess->runAction(prstand_);

	dad->setUserData(newDad);
}

void HelloWorld::actorSingleAction(Sprite* actor, Animation* action, int actionnum) {
	auto actionDone = CallFuncN::create([&](Ref* sender) {
		canmove = true;
		stopAnimate();
		kailouti = false;
		playerState = -1;
	});
	canmove = false;
	stopAnimate();
	Animate* playerTempAction = Animate::create(action);
	auto allAction = Sequence::create(playerTempAction, actionDone, NULL);
	allAction->setTag(actionnum);
	actor->runAction(allAction);
	auto actorData = (Actor*)actor->getUserData();
	actorData->setState(actionnum);
}

void HelloWorld::actorContinuousAction(Sprite* actor, Animation* action, int actionnum) {
	if (actor == player) {
		stopAnimate();
	}
	Animate* aAction = Animate::create(action);
	aAction->setTag(actionnum);
	actor->runAction(aAction);
	auto actorData = (Actor*)actor->getUserData();
	actorData->setState(actionnum);
}
void HelloWorld::playerGetTool(Sprite* tool) {
	auto playerData = (Player*)player->getUserData();
	int num = playerData->getHoldingToolsNum();
	num++;
	string name = tool->getName();
	Tool* newTool = new Tool(num, name);
	playerData->addNewTool(newTool);
}

void HelloWorld::showDialog(float delta) {
	if (m_UI_Dialog->getChildrenCount() == 0) {
		if (!dialogStack.empty()) {
			PopScene* dia = dialogStack.back();
			m_UI_Afterall->removeChild(dia);
			m_UI_Dialog->addChild(dia);
			dialogStack.popBack();
			auto voicepath = dialogPath.back().c_str();
			SimpleAudioEngine::getInstance()->playEffect(voicepath);
			dialogPath.pop_back();
		}
	}
}
void HelloWorld::preloadMusic() {
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music//BGM.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("MovieMusic//op01.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("MovieMusic//standby.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music//A.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music//B.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music//C.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music//D.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music//E.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music//F.mp3");

	SimpleAudioEngine::getInstance()->preloadEffect("Music//V01.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music//V02.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music//V04.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music//V05.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music//V09.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music//V10.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music//V11.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music//V12.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music//V14.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music//V16.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music//V23.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music//V24.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music//V25.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music//V27.mp3");

	SimpleAudioEngine::getInstance()->preloadEffect("ActorVoice//GaoGao//GaoGao01.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("ActorVoice//GuaGua//GuaGua01.mp3");
}
void HelloWorld::playerGetHurt() {
	auto playerData = (Player*)player->getUserData();
	playerData->reduceHp();
	HPTimer->setPercentage(playerData->getHP() * 10);
	if (playerData->getHP() > 0) {
		auto playerActionShake = ((Player*)player->getUserData())->getActionPlayerShake();
		playerAction(playerActionShake, 20);
		if (playerData->getHP() > 3 && playerData->getHP() <= 6) {
			playerData->changeStand(1);
		}
		else if (playerData->getHP() <= 3) {
			playerData->changeStand(2);
		}
	}
	else {
		auto playerActionShake = ((Player*)player->getUserData())->getActionPlayerShake();
		auto playerActionComa = ((Player*)player->getUserData())->getActionPlayerComa();
		auto action1 = Animate::create(playerActionShake);
		auto action2 = Animate::create(playerActionComa);
		auto actionDone = CallFuncN::create([&](Ref* sender) {
			showdie();
		});
		auto delay = DelayTime::create(3);
		auto seqAction = Sequence::create(action1, action2, delay, actionDone, NULL);
		stopAnimate();
		player->runAction(seqAction);
		playerState = 21;
		die = true;
	}
}

void HelloWorld::reStartGame() {
	_eventDispatcher->removeAllEventListeners();
	this->removeAllChildren();
	moveV = -200 * 1.3*1.5;
	rotation = 0;
	playerState = 0;
	dropspeed = 0;
	arrowTimes = 0;
	bigArrowTimes = 0;
	droping = false;
	kailouti = false;
	cameramove = false;
	jumping = false;
	onStair = false;
	standBy = false;
	die = false;
	onxiepo = false;
	canmove = true;
	end = false;
	Location = false;
	playingAction = false;
	changingTool = false;
	rootNode = CSLoader::createNode("MainScene.csb");
	CCSpriteFrameCache *pFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	pFrameCache->addSpriteFramesWithFile("UI//Plist1.plist");
	initLayer();
	initAnimate();
	initItemMenu();
	initActor();
	setScene();
	setGame();
	configPhy();

	configSchedule();
	configEventListener();
	preloadMusic();
	//initop();
	//preLoad();
	auto object = (Sprite*)rootNode->getChildByName("UsefulObject")->getChildByName("Object016");
	auto objectData = (ObjectMy*)(((Sprite*)object)->getUserData());
	auto objectAction = objectData->objectplay();
	Animate* objectPlay = Animate::create(objectAction);
	object->runAction(objectPlay);
	auto object031 = (Sprite*)rootNode->getChildByName("UsefulObject")->getChildByName("Object031");
	auto objectData031 = (ObjectMy*)(((Sprite*)object031)->getUserData());
	auto objectAction031 = objectData031->objectplay();
	Animate* objectPlay031 = Animate::create(objectAction031);
	object031->runAction(objectPlay031);

	auto a = player->getPosition() + Vec2(384.0, 216.0) + (!Location)*Vec2(-768, 0);
	camera->setPosition(a);
	auto follow = Follow::create(camera);
	this->runAction(follow);
	//event listener

}
void HelloWorld::initop() {
	Sprite* movie = Sprite::create();
	movie->setTag(1);
	movie->setPosition(Vec2(960, 540));
	m_UI_Movie->addChild(movie);
	auto op01 = Animate::create(loadAnimateByTime("movie//01_op//01-op-01.gif", 2, false));
	auto times = op01->getAnimation()->getTotalDelayUnits();
	auto repeattime01 = 5.0 / (times*(1.0 / 30));
	auto repeat01 = Repeat::create(op01, repeattime01);

	auto op02 = Animate::create(loadAnimateByTime("movie//01_op//01-op-02.gif", 2, false));
	times = op02->getAnimation()->getTotalDelayUnits();
	auto repeattime02 = 4.0 / (times*(1.0 / 30));
	auto repeat02 = Repeat::create(op02, repeattime02);

	auto op03 = Animate::create(loadAnimateByTime("movie//01_op//01-op-03.gif", 2, false));
	times = op03->getAnimation()->getTotalDelayUnits();
	auto repeattime03 = 3.7 / (times*(1.0 / 30));
	auto repeat03 = Repeat::create(op03, repeattime03);

	auto op04 = Animate::create(loadAnimateByTime("movie//01_op//01-op-04.gif", 2, false));
	times = op04->getAnimation()->getTotalDelayUnits();
	auto repeattime04 = 7.0 / (times*(1.0 / 30));
	auto repeat04 = Repeat::create(op04, repeattime04);

	auto op05 = Animate::create(loadAnimateByTime("movie//01_op//01-op-05.gif", 2, false));
	times = op05->getAnimation()->getTotalDelayUnits();
	auto repeattime05 = 5.0 / (times*(1.0 / 30));
	auto repeat05 = Repeat::create(op05, repeattime05);

	auto op06 = Animate::create(loadAnimateByTime("movie//01_op//01-op-06.gif", 2, false));
	times = op06->getAnimation()->getTotalDelayUnits();
	auto repeattime06 = 3.3 / (times*(1.0 / 30));
	auto repeat06 = Repeat::create(op06, repeattime06);

	auto op07 = Animate::create(loadAnimateByTime("movie//01_op//01-op-07.gif", 2, false));
	times = op07->getAnimation()->getTotalDelayUnits();
	auto repeattime07 = 1.0 / (times*(1.0 / 30));
	auto repeat07 = Repeat::create(op07, repeattime07);

	auto op08 = Animate::create(loadAnimateByTime("movie//01_op//01-op-08.gif", 2, false));
	times = op08->getAnimation()->getTotalDelayUnits();
	auto repeattime08 = 0.4 / (times*(1.0 / 30));
	auto repeat08 = Repeat::create(op08, repeattime08);

	auto op09 = Animate::create(loadAnimateByTime("movie//01_op//01-op-09.gif", 2, false));
	times = op09->getAnimation()->getTotalDelayUnits();
	auto repeattime09 = 7.3 / (times*(1.0 / 30));
	auto repeat09 = Repeat::create(op09, repeattime09);

	auto start = Animate::create(loadAnimateByTime("movie//02_start//02_start.gif", 2, false));
	times = start->getAnimation()->getTotalDelayUnits();
	auto starttime = 120.0 / (times*(1.0 / 30));
	auto startrepeat = Repeat::create(start, starttime);

	auto seqa = Sequence::create(repeat01, repeat02, repeat03, repeat04, repeat05, repeat06, repeat07, repeat08, repeat09, startrepeat, NULL);
	auto repeatForever = RepeatForever::create(seqa);
	movie->runAction(repeatForever);
	SimpleAudioEngine::getInstance()->playEffect("MovieMusic//op01.mp3");
}
void HelloWorld::showend1() {
	Sprite* movie = Sprite::create();
	movie->setTag(2);
	movie->setPosition(camera->getPosition());
	m_UI_Movie->addChild(movie);

	auto endA01 = Animate::create(loadAnimateByTime("movie//03_end_1//03-endA-01.gif", 1, false));
	auto times = endA01->getAnimation()->getTotalDelayUnits();
	auto repeattime01 = 2.0 / (times*(1.0 / 30));
	auto repeat01 = Repeat::create(endA01, repeattime01);

	auto endA02 = Animate::create(loadAnimateByTime("movie//03_end_1//03-endA-02.gif", 1, false));
	times = endA02->getAnimation()->getTotalDelayUnits();
	auto repeattime02 = 2.0 / (times*(1.0 / 30));
	auto repeat02 = Repeat::create(endA02, repeattime02);

	auto endA03 = Animate::create(loadAnimateByTime("movie//03_end_1//03-endA-03.gif", 1, false));
	times = endA03->getAnimation()->getTotalDelayUnits();
	auto repeattime03 = 2.0 / (times*(1.0 / 30));
	auto repeat03 = Repeat::create(endA03, repeattime03);

	auto endA04 = Animate::create(loadAnimateByTime("movie//03_end_1//03-endA-04.gif", 1, false));
	times = endA04->getAnimation()->getTotalDelayUnits();
	auto repeattime04 = 200.0 / (times*(1.0 / 30));
	auto repeat04 = Repeat::create(endA04, repeattime04);

	auto seqa = Sequence::create(repeat01, repeat02, repeat03, repeat04, NULL);
	auto repeatForever = RepeatForever::create(seqa);
	movie->runAction(repeatForever);
}

void HelloWorld::showend2() {
	Sprite* movie = Sprite::create();
	movie->setTag(3);
	movie->setPosition(camera->getPosition());
	m_UI_Movie->addChild(movie);

	auto endA01 = Animate::create(loadAnimateByTime("movie//04_end_2//04-endB-01.gif", 1, false));
	auto times = endA01->getAnimation()->getTotalDelayUnits();
	auto repeattime01 = 2.0 / (times*(1.0 / 30));
	auto repeat01 = Repeat::create(endA01, repeattime01);

	auto endA02 = Animate::create(loadAnimateByTime("movie//04_end_2//04-endB-02.gif", 1, false));
	times = endA02->getAnimation()->getTotalDelayUnits();
	auto repeattime02 = 2.0 / (times*(1.0 / 30));
	auto repeat02 = Repeat::create(endA02, repeattime02);

	auto endA03 = Animate::create(loadAnimateByTime("movie//04_end_2//04-endB-02.gif", 1, false));
	times = endA03->getAnimation()->getTotalDelayUnits();
	auto repeattime03 = 2.0 / (times*(1.0 / 30));
	auto repeat03 = Repeat::create(endA03, repeattime03);

	auto endA04 = Animate::create(loadAnimateByTime("movie//04_end_2//04-endB-04.gif", 1, false));
	times = endA04->getAnimation()->getTotalDelayUnits();
	auto repeattime04 = 2.0 / (times*(1.0 / 30));
	auto repeat04 = Repeat::create(endA04, repeattime04);

	auto endA05 = Animate::create(loadAnimateByTime("movie//04_end_2//04-endB-05.gif", 1, false));
	times = endA05->getAnimation()->getTotalDelayUnits();
	auto repeattime05 = 2.0 / (times*(1.0 / 30));
	auto repeat05 = Repeat::create(endA05, repeattime05);

	auto endA06 = Animate::create(loadAnimateByTime("movie//04_end_2//04-endB-06.gif", 1, false));
	times = endA06->getAnimation()->getTotalDelayUnits();
	auto repeattime06 = 2.0 / (times*(1.0 / 30));
	auto repeat06 = Repeat::create(endA06, repeattime06);

	auto endA07 = Animate::create(loadAnimateByTime("movie//04_end_2//04-endB-07.gif", 1, false));
	times = endA07->getAnimation()->getTotalDelayUnits();
	auto repeattime07 = 200.0 / (times*(1.0 / 30));
	auto repeat07 = Repeat::create(endA07, repeattime07);

	auto seqa = Sequence::create(repeat01, repeat02, repeat03, repeat04, repeat05, repeat06, repeat07, NULL);
	movie->runAction(seqa);
}
void HelloWorld::showdie() {
	Sprite* movie = Sprite::create();
	movie->setTag(4);
	movie->setPosition(camera->getPosition());
	m_UI_Movie->addChild(movie);

	auto die = Animate::create(loadAnimateByTime("movie//05_lose//05-lose.gif", 1, false));
	auto repeat = RepeatForever::create(die);
	movie->runAction(repeat);
}
void HelloWorld::preLoad() {
	PopScene * popLayer1 = PopScene::create("UI//A.png", "啊，那边的姐姐，请帮帮我！", 1);
	popLayer1->setPosition(camera->getPosition() + Vec2(0, -250));
	PopScene * popLayer2 = PopScene::create("UI//B.png", "你怎么了？", 1);
	popLayer2->setPosition(camera->getPosition() + Vec2(0, -250));
	PopScene * popLayer3 = PopScene::create("UI//C.png", "我想离家出走，但是我爸妈把我锁在房间里了，请一定要帮帮我。", 1);
	popLayer3->setPosition(camera->getPosition() + Vec2(0, -250));
	PopScene * popLayer4 = PopScene::create("UI//D.png", "拿着这个，希望你能找到方法进来。", 1);
	popLayer4->setPosition(camera->getPosition() + Vec2(0, -250));
	m_UI_preLoad->addChild(popLayer1);
	m_UI_preLoad->addChild(popLayer2);
	m_UI_preLoad->addChild(popLayer3);
	m_UI_preLoad->addChild(popLayer4);
}
void HelloWorld::setJudgement() {
	auto sp = Sprite::create("background1_1_1in.png");
	this->addChild(sp);
	auto a = sp->getTexture();
	Image* backgroundImage = new Image();
	backgroundImage->initWithImageFile("background1_1_1in.png");
	c_data = backgroundImage->getData();
}