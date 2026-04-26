// Widget.cpp
#include "Widget.h"
#include "LevelSelect.h"
#include "Gallery.h"

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("数织四季 · 二十四节气");
    setFixedSize(500, 400);

    //为主窗口设计背景图：
QLabel *bgLabel = new QLabel(this);
    bgLabel->setGeometry(0, 0, 500, 400); // 匹配窗口大小
    bgLabel->setPixmap(QPixmap(":/images/open.jpg").scaled(400, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    bgLabel->setScaledContents(true);
    bgLabel->lower(); // 背景置底
    //  添加游戏标题标签1）
    QLabel *titleLabel = new QLabel("数织四季 · 二十四节气", this);
    titleLabel->setGeometry(0, 20, this->width(), 60); // 位置：顶部居中，宽400高50
    titleLabel->setAlignment(Qt::AlignCenter); // 文字居中
    // 标题样式（国风书法风，适配背景）2）
    titleLabel->setStyleSheet(R"(
    QLabel {
        font-family: "STKaiti", "KaiTi", "PingFang SC";
        font-size: 36px;
        font-weight: 900;
        color: #FFF8DC;
        background-color: transparent;
        /* 渐变边框 */
        border: 3px solid;
        border-radius: 18px;
        border-color: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #FFD700, stop:1 #8B4513);
        padding: 8px 20px;
        qproperty-textShadow:
            2px 2px 4px rgba(0,0,0,0.8),
            0px 0px 10px rgba(255,215,0,0.7);
    }
)");

    titleLabel->raise(); // 置顶显示，不被遮挡




    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);

    QPushButton *btnStart = new QPushButton("开始游戏");
    QPushButton *btnGallery = new QPushButton("节气图鉴");
    QPushButton *btnExit = new QPushButton("退出游戏");
    //设置按钮样式
    QString btnStyle = R"(
    QPushButton {
        background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #fff8e8, stop:1 #f0e0c8);
        border: 1px solid #c8b898;
        border-radius: 16px;
        border-top: 1px solid #fff0d8;
        border-left: 1px solid #fff0d8;
        border-right: 1px solid #d8c8a8;
        border-bottom: 2px solid #b8a888;
        font-family: "STKaiti", "KaiTi", "SimHei";
        font-size: 16px;
        font-weight: bold;
        color: #8b5a2b;
        padding: 12px 30px;
    }
    QPushButton:hover {
        background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #fff8e8, stop:1 #f5e8d0);
        border-bottom: 3px solid #a89878;
    }
    QPushButton:pressed {
        background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #e8d8b8, stop:1 #f5e8d0);
        border-top: 2px solid #b8a888;
        border-left: 2px solid #b8a888;
        border-right: 1px solid #fff0d8;
        border-bottom: 1px solid #fff0d8;
        padding-top: 13px;
        padding-bottom: 11px;
    }
)";

    btnStart->setStyleSheet(btnStyle);
    btnGallery->setStyleSheet(btnStyle);
    btnExit->setStyleSheet(btnStyle);

    layout->addWidget(btnStart);
    layout->addWidget(btnGallery);
    layout->addWidget(btnExit);
    //连接信号与槽：
    connect(btnStart, &QPushButton::clicked, this, &Widget::startGame);
    connect(btnGallery, &QPushButton::clicked, this, &Widget::openGallery);
    connect(btnExit, &QPushButton::clicked, this, &QWidget::close);
}

void Widget::startGame()
{
    LevelSelect *w = new LevelSelect;
    w->show();
    this->close();
}

void Widget::openGallery()
{
    Gallery *g = new Gallery;
    g->show();
    this->close();
}
