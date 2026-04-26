#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H
#include "LevelData.h"
#include <QVector>

class LevelManager
{
public:
    static QVector<LevelData> getLevels();
};

#endif // LEVELMANAGER_H
