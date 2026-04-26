// LevelSelect.cpp
#include "LevelSelect.h"
#include "GameBoard.h"
#include "LevelManager.h"
#include <QLabel>

LevelSelect::LevelSelect(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("选择节气关卡");
    setFixedSize(600, 500);
    QLabel *bgLabel = new QLabel(this);
    bgLabel->setGeometry(0, 0, 600, 500); // 匹配窗口大小
    bgLabel->setPixmap(QPixmap(":/images/open.jpg").scaled(400, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    bgLabel->setScaledContents(true);
    bgLabel->lower(); // 背景置底

    QGridLayout *layout = new QGridLayout(this);
    auto levels = LevelManager::getLevels();
    //按钮排版
    int row = 0, col = 0;
    for (auto &level : levels) {
        auto btn = new QPushButton(level.name);
        layout->addWidget(btn, row, col);
        connect(btn, &QPushButton::clicked, this, [=]() {
            openGameBoard(level.id);
        });

        col++;
        //每两个为一行
        if (col >= 2) { col = 0; row++; }
    }
}

void LevelSelect::openGameBoard(int levelId)
{
    GameBoard *g = new GameBoard(levelId);
    g->show();
    this->close();
}
