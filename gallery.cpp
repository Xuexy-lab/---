// Gallery.cpp
#include "Gallery.h"
#include "LevelManager.h"

Gallery::Gallery(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("二十四节气图鉴");
    setFixedSize(700, 600);

    QGridLayout *layout = new QGridLayout(this);
    auto levels = LevelManager::getLevels();

    int row = 0, col = 0;
    for (auto &lv : levels) {
        QLabel *lab = new QLabel(lv.name);
        lab->setAlignment(Qt::AlignCenter);
        layout->addWidget(lab, row, col);

        col++;
        if (col >= 6) { col=0; row++; }
    }
}
