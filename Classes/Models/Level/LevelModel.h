#ifndef __LEVEL_MODEL_H__
#define __LEVEL_MODEL_H__

#include <vector>
#include <list>
#include "LevelModelDefinitions.h"
#include "cocos2d.h"

class CharacterModel;
class WaveModel;
class CellModel;
class DiseaseModel;
class ProjectileModel;
class NumericModel;
class CellBarModel;
class UIProgressor;
class UIPause;
class UIRemove;
class GSTutorial;

class LevelModel {
public:
    // Default constructor of LevelModel
    LevelModel(){};
    LevelModel(int level, cocos2d::Scene* scene);
    ~LevelModel();

    // Return the map of the level
    std::vector< std::vector<MapPosition> > getMap() {return map;}

    // Return the map of the level. Should not be used outside models.
    std::vector< std::vector<MapPosition> >& __getMap() {return map;}

    // Return the list of waves
    std::vector<WaveModel> getWaveList() {return waveList;}

    // Reset the timeCounter to 0 and start to count
    void startCounting() {
        timeCounter = 0.0;
        isCounting = true;
    }

    // Return current time counter value
    double getTimeCounter() {
        return timeCounter;
    }

    void update();
    void addCell(CellModel*, int, int);
    void addDisease(DiseaseModel*);
    void addProjectile(ProjectileModel*);
    void dumpCell(CellModel*);
    void dumpDisease(DiseaseModel*);
    void dumpProjectile(ProjectileModel*);
    void addEnergyObject(double, double);
    void addEnergyValue(int);
    void addGoldValue(int);
    void printLevelState();
    void emphasizeEnergy();
    int getEnergyValue();
    void pause();
    void resume();
    void win();
    void lose();

    // Get diseaseList of the level. Should not be used outside Models.
    std::list<DiseaseModel*>& __getDiseaseList() {return diseaseList;}

    // Get cellList of the level. Should not be used outside Models.
    std::list<CellModel*>& __getCellList() {return cellList;}
    std::vector< std::vector<int> >* __getEnemyPath();
    std::vector< std::vector<int> > getEndPaths() {return endPaths;}
    std::vector< std::vector<int> > getBeginPaths() {return beginPaths;}

    // Set lose
    void setLose() {loseCheck = true;}

    // Set win
    void setWin() {winTimeCounter = 1.5;}

    // Get levelId
    int getLevelId() {return levelId;}

    int getReward();
    void findAndRemoveCell(int, int);
private:
    int levelId;
    std::vector< std::vector<MapPosition> > map;
    std::vector< std::vector< std::vector<int> > > enemyPaths;
    std::vector< std::vector<int> > endPaths;
    std::vector< std::vector<int> > beginPaths;
    std::vector<WaveModel> waveList;
    std::vector<WaveModel>::iterator currentWave;
    std::list<CellModel*> cellList;
    std::list<DiseaseModel*> diseaseList;
    std::list<ProjectileModel*> projectileList;
    std::vector<CellBarModel*> cellBarList;
    cocos2d::Vector<cocos2d::Node*> pausedNodes;

    double timeCounter;
    bool isCounting;
    NumericModel energy;
    NumericModel gold;

    std::list<CellModel*> cellDump;
    std::list<DiseaseModel*> diseaseDump;
    std::list<ProjectileModel*> projectileDump;
    void garbageCollect();
    void addEnemiesOnWave();

    cocos2d::Scene* scene;

    void readLevelFromJson(int level);

    UIProgressor* progressor;
    UIPause* pauser;
    UIRemove* remover;

    double winTimeCounter;
    bool loseCheck;

    GSTutorial* layer;
};

#endif // !__LEVEL_MODEL_H__