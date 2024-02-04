#include "Models/models.h"
#include "LevelModel.h"
#include <random>
#include <ctime>
#include <cmath>
#include <iostream>
#include "UIObjects/uiobj.h"
#include "Database/LevelReader/LevelReader.h"
#include "fstream"
#include "UIControl/UIControlCellBar/UIControlCellBar.h"
#include "UIControl/UIControlEnergy/UIControlEnergy.h"
#include "UINumeric/UINumeric.h"
#include "UIComponents/UIProgressor/UIProgressor.h"
#include "UIControl/UIPause/UIPause.h"
#include "UIControl/UIResultLayer/UIWinLayer.h"
#include "UIControl/UIResultLayer/UILoseLayer.h"
#include "UIControl/UIRemove/UIRemove.h"
#include "SimpleAudioEngine.h"
#include "Scenes/GameScene/Components/GSTutorial.h"

using namespace std;
USING_NS_CC;
using namespace CocosDenshion;

/*
Constructor of LevelModel
*/
LevelModel::LevelModel(int level, Scene* scene) {
    srand(time(NULL));
    this->scene = scene;
    this->levelId = level;

    /*
    Set UIObject of energy, gold and CellBar
    */
    auto energyCounterUI = UINumeric::create();
    energyCounterUI->setScale(0.75 * Director::getInstance()->getVisibleSize().height / 8 / 90.0f);
    energyCounterUI->addToScene(scene);
    energy.setUIObject(energyCounterUI);
    energyCounterUI->setPosition(ENERGY_COUNTER_POS_X, ENERGY_COUNTER_POS_Y);

    readLevelFromJson(level);

    // Temporary data
    // gold.changeValue(200);
    auto data = UserDefault::getInstance();
    auto numOfCells = data->getIntegerForKey("CURRENT_CELL", 0);

    for (int i = 0; i <= numOfCells; i++) {
        cellBarList.push_back(new CellBarModel((CellId) i));
    }

    for (unsigned int i = 0; i < cellBarList.size(); i++) {
        cellBarList[i]->__setLevel(this);
        auto cellBarControl = UIControlCellBar::create(this, cellBarList[i]->getCellId(), cellBarList[i]->getCost(), cellBarList[i]->getDistance());
        cellBarList[i]->setUIObject(cellBarControl);
        cellBarControl->addToScene(scene);
        cellBarControl->setPosition(Vec2(CELLBAR_POSITION_X, CELLBAR_POSITION_Y(i)));
    }

    // UIProgressor initialization
    progressor = UIProgressor::create(&waveList);
    scene->addChild(progressor);
    progressor->setGlobalZOrder(9.0f);
    progressor->setPosition(PROGRESSOR_POS_X, PROGRESSOR_POS_Y);

    // UIPause initialization
    pauser = UIPause::create(this);
    scene->addChild(pauser);
    pauser->setGlobalZOrder(9.0f);
    pauser->setPosition(Vec2(PAUSE_BUTTON_POS_X, PAUSE_BUTTON_POS_Y));

    // UIRemove initialization
    remover = UIRemove::create(this);
    scene->addChild(remover);
    remover->setGlobalZOrder(9.0f);
    remover->setPosition(Vec2(REMOVE_BUTTON_POS_X, REMOVE_BUTTON_POS_Y));

    // Initialize properties
    timeCounter = 0.0;
    isCounting = false;

    winTimeCounter = -1.0f;
    loseCheck = false;
}

/*
Read level from json file
*/
void LevelModel::readLevelFromJson(int level) {
    // Read json
    string filename = "data/level/level" + to_string(level) + ".json";
    string content;
    FileUtils::getInstance()->getContents(filename, &content);
    json j = json::parse(content);

    // Get value of initial energy
    CCLOG("ok");
    energy.changeValue(j["initialEnergy"].get<int>());
    CCLOG("OK");

    // Get value of map
    json jmap = j["map"];
    for (auto it = jmap.begin(); it != jmap.end(); it++) {
        vector<MapPosition> temp;
        auto vec = it->get< vector<int> >();
        for (auto it2 = vec.begin(); it2 != vec.end(); it2++) {
            temp.push_back((MapPosition) *it2);
        }
        map.push_back(temp);
    }

    // Get enemy paths
    json jpaths = j["enemyPaths"];
    for (auto it1 = jpaths.begin(); it1 != jpaths.end(); it1++) {
        vector<vector<int> > temp1;
        vector<vector<int> > vec = it1->get< vector< vector<int> > >();
        for (auto it2 = vec.begin(); it2 != vec.end(); it2++) {
            vector<int> temp2;
            for (auto it3 = it2->begin(); it3 != it2->end(); it3++) {
                temp2.push_back(*it3);
            }
            temp1.push_back(temp2);
        }
        enemyPaths.push_back(temp1);
    }

    // Get begin paths
    json jbegin = j["beginPaths"];
    for (auto it = jbegin.begin(); it != jbegin.end(); it++) {
        vector<int> temp;
        auto vec = it->get< vector<int> >();
        for (auto it2 = vec.begin(); it2 != vec.end(); it2++) {
            temp.push_back(*it2);
        }
        beginPaths.push_back(temp);
    }

    // Get end paths
    json jend = j["endPaths"];
    for (auto it = jend.begin(); it != jend.end(); it++) {
        vector<int> temp;
        auto vec = it->get< vector<int> >();
        for (auto it2 = vec.begin(); it2 != vec.end(); it2++) {
            temp.push_back(*it2);
        }
        endPaths.push_back(temp);
    }

    // Get wave lists
    json jwaves = j["waves"];
    for (auto it1 = jwaves.begin(); it1 != jwaves.end(); it1++) {
        WaveModel temp1;
        temp1.setTime((*it1)["time"].get<double>());
        temp1.setHugeWave((*it1)["huge"].get<bool>());
        json jenemies = (*it1)["enemies"];
        for (auto it2 = jenemies.begin(); it2 != jenemies.end(); it2++) {
            temp1.add((DiseaseId) it2->get<int>());
        }
        waveList.push_back(temp1);
    }
    currentWave = waveList.begin();
}

/*
Get a enemy path of the level randomly. Should not be used outside Models.
*/
vector< vector<int> >* LevelModel::__getEnemyPath() {
    int index = rand() % enemyPaths.size();
    return &enemyPaths[index];
}

/*
Update state of level on updating
*/
void LevelModel::update() {
    if (this->isCounting) {
        // Update timeCounter
        timeCounter += UPDATING_FREQUENCY;

        // Update objects
        for (auto it = cellList.begin(); it != cellList.end();) {
            (*(it++))->update();
        }
        for (auto it = diseaseList.begin(); it != diseaseList.end();) {
            (*(it++))->update();
        }
        for (auto it = projectileList.begin(); it != projectileList.end();) {
            (*(it++))->update();
        }
        for (auto it = cellBarList.begin(); it != cellBarList.end();) {
            (*(it++))->update();
        }

        // Garbage collect
        garbageCollect();

        // Add enemies on current wave
        if (currentWave != waveList.end()) {
            if (abs(timeCounter - currentWave->getTime()) <= ACCEPTING_TIME_ERROR) {
                timeCounter = currentWave->getTime();
                addEnemiesOnWave();
                progressor->updateOnWave();
            }
        }

        // Lose condition
        if (loseCheck) {
            lose();
            return;
        }

        // Winning condition
        if (winTimeCounter < -0.5) {
            if (diseaseList.size() == 0 && currentWave == waveList.end()) {
                setWin();
            }
        }

        if (winTimeCounter > UPDATING_FREQUENCY / 2) {
            winTimeCounter -= UPDATING_FREQUENCY;
            if (abs(winTimeCounter) <= ACCEPTING_TIME_ERROR) {
                win();
            }
        }
        // // Temporary test
        // if (abs(timeCounter - 6.0) <= ACCEPTING_TIME_ERROR) {
        //     win();
        // }
    }
}

/* 
Destructor of LevelModel
*/
LevelModel::~LevelModel() {
    for (auto it = cellList.begin(); it != cellList.end(); it++) {
        delete (*it);
    }
    for (auto it = diseaseList.begin(); it != diseaseList.end(); it++) {
        delete (*it);
    }
    for (auto it = projectileList.begin(); it != projectileList.end(); it++) {
        delete (*it);
    }
    for (auto it = cellDump.begin(); it != cellDump.end(); it++) {
        delete (*it);
    }
    for (auto it = diseaseDump.begin(); it != diseaseDump.end(); it++) {
        delete (*it);
    }
    for (auto it = projectileDump.begin(); it != projectileDump.end(); it++) {
        delete (*it);
    }
    for (auto it = cellBarList.begin(); it != cellBarList.end(); it++) {
        delete (*it);
    }
}

/* 
Collect garbage after each updating
*/
void LevelModel::garbageCollect() {
    if (cellDump.size() >= DUMP_CAPACITY) {
        auto it = cellDump.begin();
        for (int i = 0; i < cellDump.size() / 2; i++, it++) {
            delete (*it);
        }
        cellDump.erase(cellDump.begin(), it);
    }

    if (diseaseDump.size() >= DUMP_CAPACITY) {
        auto it = diseaseDump.begin();
        for (int i = 0; i < diseaseDump.size() / 2; i++, it++) {
            delete (*it);
        }
        diseaseDump.erase(diseaseDump.begin(), it);
    }

    if (projectileDump.size() >= DUMP_CAPACITY) {
        auto it = projectileDump.begin();
        for (int i = 0; i < projectileDump.size() / 2; i++, it++) {
            delete (*it);
        }
        projectileDump.erase(projectileDump.begin(), it);
    }
}

/*
Send a CellModel to dump list
*/
void LevelModel::dumpCell(CellModel* obj) {
    for (auto it = cellList.begin(); it != cellList.end(); it++) {
        if (*it == obj) {
            cellList.erase(it);
            cellDump.push_back(obj);
            auto cellX = (int) obj->getPositionCellX();
            auto cellY = (int) obj->getPositionCellY();
            map[cellX][cellY] = (MapPosition) ((EMPTY_CAN_PUT - EMPTY_CAN_PUT_OCCUPIED) + (int) map[cellX][cellY]);
            break;
        }
    }
}

/*
Send a DiseaseModel to dump list
*/
void LevelModel::dumpDisease(DiseaseModel* obj) {
    for (auto it = diseaseList.begin(); it != diseaseList.end(); it++) {
        if (*it == obj) {
            diseaseList.erase(it);
            diseaseDump.push_back(obj);
            break;
        }
    }
}

/*
Send a ProjectileModel to dump list
*/
void LevelModel::dumpProjectile(ProjectileModel* obj) {
    for (auto it = projectileList.begin(); it != projectileList.end(); it++) {
        if (*it == obj) {
            projectileList.erase(it);
            projectileDump.push_back(obj);
            break;
        }
    }
}

/*
Add a CellModel to cellList
*/
void LevelModel::addCell(CellModel* obj, int cellX, int cellY) {
    if (obj->getCost() > energy.getValue()) {
        delete obj;
        return;
    }
    if (obj->canPutOn(this, cellX, cellY)) {
        SimpleAudioEngine::getInstance()->playEffect("audio/soundfx/use/add_cell.mp3");

        obj->setPosition(cellX, cellY);
        cellList.push_back(obj);
        obj->__setLevel(this);
        map[cellX][cellY] = (MapPosition) ((EMPTY_CAN_PUT_OCCUPIED - EMPTY_CAN_PUT) + (int) map[cellX][cellY]);

        // Draw UIObject on scene
        auto ui = UICell::create(obj->getCellId());
        obj->setUIObject(ui);
        ui->addToScene(this->scene);
        ui->setCellPosition(cellX, cellY);

        // Change value of energy
        addEnergyValue(0 - obj->getCost());

        // Reset recharging
        for (auto it = cellBarList.begin(); it != cellBarList.end(); it++) {
            if ((*it)->getCellId() == obj->getCellId()) {
                (*it)->resetCounter();
            }
        }

        // Tutorial
        if (UserDefault::getInstance()->getBoolForKey("TUTORIAL", true) && levelId == 1) {
            auto instructCell = CallFunc::create([this](){
                return [&](){
                    this->pause();
                    auto cell = *(this->cellList.begin());
                    this->layer = GSTutorial::create(
                        Rect(REMOVE_BUTTON_POS_X - 27.0f, REMOVE_BUTTON_POS_Y - 27.0f, 54.0f, 54.0f),
                        Rect(GRASS_ORIGIN_POSITION_X_R + SIZE_OF_SQUARE_R * cell->getPositionCellX(), GRASS_ORIGIN_POSITION_Y_R + SIZE_OF_SQUARE_R * (cell->getPositionCellY() + 0.25f), SIZE_OF_SQUARE_R, SIZE_OF_SQUARE_R),
                        TUTORIAL_5
                    );
                    this->scene->addChild(this->layer);

                    this->layer->setOkayEvent([this](){
                        return [&](){
                            this->layer->removeFromParent();

                            this->layer = GSTutorial::create(
                                Rect(0.0f, 0.0f, 1.0f, 1.0f),
                                TUTORIAL_6
                            );
                            this->scene->addChild(this->layer);

                            this->layer->setOkayEvent([this](){
                                return [&](){
                                    this->layer->removeFromParent();
                                    this->resume();
                                    UserDefault::getInstance()->setBoolForKey("TUTORIAL", false);
                                };
                            }());
                        };
                    }());
                };
            }());
            this->scene->runAction(instructCell);
        }
    }
    else {
        delete obj;
    }
}
/*
Add a DiseaseModel to diseaseList
*/
void LevelModel::addDisease(DiseaseModel* obj) {
    diseaseList.push_back(obj);
    obj->__setLevel(this);

    // Draw UIObject on scene
    auto ui = UIDisease::create(obj->getDiseaseId());
    obj->setUIObject(ui);
    ui->addToScene(this->scene);
    ui->setCellPosition(obj->getPositionCellX(), obj->getPositionCellY());
}

/*
Add a ProjectileModel to projectileList
*/
void LevelModel::addProjectile(ProjectileModel* obj) {
    projectileList.push_back(obj);
    obj->__setLevel(this);

    // Draw UIObject on scene
    auto ui = UIProjectile::create(obj->getProjectileId());
    obj->setUIObject(ui);
    ui->addToScene(this->scene);
    ui->setCellPosition(obj->getPositionCellX(), obj->getPositionCellY());
}

/*
Add enemies in the current wave
*/
void LevelModel::addEnemiesOnWave() {
    auto enemies = currentWave->getEnemies();
    for (auto it = enemies.begin(); it != enemies.end(); it++) {
        addDisease(DiseaseModel::create(*it));
    }
    currentWave++;
}

/*
Print the current state of the level
*/
void LevelModel::printLevelState() {
    cout << "================= TIME: " << timeCounter << endl;
    for (auto it = cellList.begin(); it != cellList.end(); it++) {
        cout << "==== CELL\n";
        cout << "X: " << (*it)->getPositionCellX() << endl;
        cout << "Y: " << (*it)->getPositionCellY() << endl;
    }
    for (auto it = diseaseList.begin(); it != diseaseList.end(); it++) {
        cout << "==== DISEASE\n";
        cout << "X: " << (*it)->getPositionCellX() << endl;
        cout << "Y: " << (*it)->getPositionCellY() << endl;
    }
    for (auto it = projectileList.begin(); it != projectileList.end(); it++) {
        cout << "==== PROJECTILE\n";
        cout << "X: " << (*it)->getPositionCellX() << endl;
        cout << "Y: " << (*it)->getPositionCellY() << endl;
    }
    cout << "================================================\n\n";
}

/*
Add a energy to scene
*/
void LevelModel::addEnergyObject(double cellX, double cellY) {
    if (scene != NULL) {
        // Add to scene a energy at (cellX, cellY)
        auto energy = UIControlEnergy::create(this);
        energy->addToScene(scene);
        energy->setCellPosition(cellX, cellY);
        energy->appearAnimate();
    }
}

/* 
Add more to the value of energy model
*/
void LevelModel::addEnergyValue(int add) {
    energy.changeValue(min(energy.getValue() + add, MAX_ENERGY));
}

/* 
Add more to the value of gold model
*/
void LevelModel::addGoldValue(int add) {
    gold.changeValue(min(gold.getValue() + add, MAX_GOLD));
}

/*
Get value of current energy
*/
int LevelModel::getEnergyValue() {
    return energy.getValue();
}

/*
Emphasize the energy counter
*/
void LevelModel::emphasizeEnergy() {
    energy.__getUIObject()->emphasizeAnimate();
}

/*
Pause the game
*/
void LevelModel::pause() {
    isCounting = false;
    if (scene != nullptr) {
        pausedNodes = Director::getInstance()->getActionManager()->pauseAllRunningActions();
        Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(scene, true);
    }
}

/*
Resume the game
*/
void LevelModel::resume()  {
    isCounting = true;
    if (scene != nullptr) {
        Director::getInstance()->getActionManager()->resumeTargets(pausedNodes);
        Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(scene, true);
    }
}

/*
Win the game
*/
void LevelModel::win() {
    isCounting = false;
    if (scene != nullptr) {
        SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        if (levelId < 8)
	        SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/background/GameScene/Win/win.mp3", true);
        else
        SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/background/GameScene/Boss/boss_die.mp3", true);

        pausedNodes = Director::getInstance()->getActionManager()->pauseAllRunningActions();
        Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(scene, true);

        auto winLayer = UIWinLayer::create(this);
        scene->addChild(winLayer);
        winLayer->setGlobalZOrder(12.0f);
    }
}

/*
Lose the game
*/
void LevelModel::lose() {
    isCounting = false;
    if (scene != nullptr) {
        SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	    SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/background/GameScene/Lose/lose.mp3", true);

        pausedNodes = Director::getInstance()->getActionManager()->pauseAllRunningActions();
        Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(scene, true);

        auto loseLayer = UILoseLayer::create(this);
        scene->addChild(loseLayer);
        loseLayer->setGlobalZOrder(12.0f);
    }
}

/*
Get reward of the level
*/
int LevelModel::getReward() {
    if (levelId >= 1 && levelId <= 3) {
        return levelId;
    }
    else if (levelId >= 5 && levelId <= 7) {
        return levelId - 1;
    }
    return -1;
}

/*
Find and remove cell
*/
void LevelModel::findAndRemoveCell(int x, int y) {
    for (auto it = cellList.begin(); it != cellList.end(); it++) {
        if (abs((*it)->getPositionCellX() - x) <= ACCEPTING_TIME_ERROR && abs((*it)->getPositionCellY() - y) <= ACCEPTING_TIME_ERROR) {
            SimpleAudioEngine::getInstance()->playEffect("audio/soundfx/use/delete_button.mp3");
            (*it)->__getUIObject()->removeFromParent();
            dumpCell(*it);
            return;
        }
    }
}