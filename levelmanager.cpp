#include "levelmanager.h"

QVector<LevelData> LevelManager::getLevels()
{
    QVector<LevelData> list;

    // 春夏秋冬每个季节两关
    list << // 在 LevelManager::getLevels() 中，替换第一关的定义：
        list << LevelData{
            1,                          // 关卡ID
            "立春",                     // 关卡名称
            "春",                       // 所属季节
            5,                          // 网格大小（5×5）
            // 行线索（从上到下）
            {{1,1,1}, {3}, {2}, {2}, {1}},
            // 列线索（从左到右）
            {{1}, {1,1}, {5}, {2}, {1}},
            // 解矩阵（1=涂黑，0=空白）
            {
                {1, 0, 1, 0, 1},
                {0, 1, 1, 1, 0},
                {0, 0, 1, 1, 0},
                {0, 1, 1, 0, 0},
                {0, 0, 1, 0, 0}
            }
        };
    list << LevelData{2,"清明","春",7};
    list << LevelData{3,"夏至","夏",5,{},{},{{1,1,1,1,1}}};
    list << LevelData{4,"大暑","夏",7};
    list << LevelData{5,"立秋","秋",5,{},{},{{1,1,1,1,1}}};
    list << LevelData{6,"秋分","秋",7};
    list << LevelData{7,"小雪","冬",5,{},{},{{1,1,1,1,1}}};
    list << LevelData{8,"冬至","冬",7};

    return list;
}
