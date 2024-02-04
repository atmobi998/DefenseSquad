#ifndef __WAVE_MODEL_H__
#define __WAVE_MODEL_H__

#include <vector>
enum DiseaseId;

class WaveModel {
public:
    // Constructor of waveModel
    WaveModel(){
        hugeWave = false;
    }
    ~WaveModel();
    bool isHugeWave();
    void setHugeWave(bool);
    void add(DiseaseId);
    double getTime();
    void setTime(double time);
    std::vector<DiseaseId>& getEnemies();
private:
    double time;
    bool hugeWave;
    std::vector<DiseaseId> enemies;
};

#endif // !__WAVE_MODEL_H__