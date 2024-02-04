#include "Models/models.h"
#include "WaveModel.h"
using namespace std;

/*
WaveModel destructor
*/
WaveModel::~WaveModel() {

}

/*
Return if the wave is a huge wave
*/
bool WaveModel::isHugeWave() {
    return hugeWave;
}

/*
Set if the wave is a huge wave
*/
void WaveModel::setHugeWave(bool _hugeWave) {
    hugeWave = _hugeWave;
}

/*
Add a DiseaseModel to list of enemies
*/
void WaveModel::add(DiseaseId enemy) {
    enemies.push_back(enemy);
}

/* 
Return the start time of the wave
*/
double WaveModel::getTime() {
    return time;
}

/*
Set the start time of the wave
*/
void WaveModel::setTime(double time) {
    this->time = time;
}

/*
*/
vector<DiseaseId>& WaveModel::getEnemies() {
    return enemies;
}