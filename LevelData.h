#ifndef LEVELDATA_H
#define LEVELDATA_H
#include <QString>
#include <QVector>

struct LevelData
{
    int id;
    QString name;
    QString season;
    int size;

    QVector<QVector<int>> rowHints;  // ✅ 二维，支持多行多线索
    QVector<QVector<int>> colHints;  // ✅ 二维，支持多列多线索
    QVector<QVector<bool>> answer;
};

#endif // LEVELDATA_H

