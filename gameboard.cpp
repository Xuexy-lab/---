// GameBoard.cpp
#include "GameBoard.h"
#include "LevelManager.h"
#include <QMouseEvent>
#include <QMessageBox>

GameBoard::GameBoard(int levelId, QWidget *parent) : QWidget(parent)
{
    setFixedSize(500, 500);
    setWindowTitle("数织游戏");
    // 2. 初始化计时器
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &GameBoard::updateTimer);
    m_timer->start(1000); // 每秒更新一次

    // 加载关卡数据
    auto levels = LevelManager::getLevels();
    for (auto &l : levels) {
        if (l.id == levelId) {
            m_size = l.size;
            m_answer = l.answer;
            m_rowHints = l.rowHints;
            m_colHints = l.colHints;
            break;
        }
    }

    // 初始化用户棋盘
    m_user.resize(m_size);
    for (int i=0;i<m_size;i++) {
        m_user[i].resize(m_size, 0);
    }
}
// 计时器更新槽函数
void GameBoard::updateTimer()
{
    m_seconds++;
    update(); // 刷新界面，显示新的时间
}


void GameBoard::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    // 背景图
    QPixmap bg(":/images/board_1.jpg");
    p.drawPixmap(rect(), bg);
    // 半透明遮罩，防止背景太花看不清文字
    //p.fillRect(rect(), QColor(255,255,255,170));

    int cell = 50;
    int hintWidth = 80;   // 左边线索预留宽度
    int hintHeight = 80;  // 上边线索预留高度
    QFont hintFont("Arial", 14, QFont::Bold); // 设置线索字体
    p.setFont(hintFont);
    // 棋盘总尺寸
    int boardSize = m_size * cell;
    // 计算居中偏移（加上线索区域）
    int totalWidth = boardSize + hintWidth;
    int totalHeight = boardSize + hintHeight;
    int offsetX = (this->width() - totalWidth) / 2;
    int offsetY = (this->height() - totalHeight) / 2;
    // 3. 绘制右上角的计时器和点击数
    p.setPen(Qt::black);
    QFont infoFont("Arial", 12, QFont::Bold);
    p.setFont(infoFont);
    QString timeText = QString("时间: %1 秒").arg(m_seconds);
    QString clickText = QString("点击: %1 次").arg(m_clickCount);
    p.drawText(width() - 150, 30, timeText);
    p.drawText(width() - 150, 55, clickText);

    // 绘制左边行线索
    for (int i = 0; i < m_size; ++i) {
        // 安全检查：索引必须小于数组大小
        if (i < 0 || i >= m_rowHints.size()) continue;

        QString text;
        for (int num : m_rowHints[i]) {
            text += QString::number(num) + " ";
        }
        text = text.trimmed();

        int rectY = offsetY + hintHeight + i * cell;
        QRect rowHintRect(offsetX, rectY, hintWidth, cell);
        p.drawText(rowHintRect, Qt::AlignRight | Qt::AlignVCenter, text);
    }

    // 绘制上边列线索
    for (int j = 0; j < m_size; ++j) {
        // 安全检查：索引必须小于数组大小
        if (j < 0 || j >= m_colHints.size()) continue;

        QString text;
        for (int num : m_colHints[j]) {
            text += QString::number(num) + " ";
        }
        text = text.trimmed();

        int rectX = offsetX + hintWidth + j * cell;
        QRect colHintRect(rectX, offsetY, cell, hintHeight);
        p.drawText(colHintRect, Qt::AlignHCenter | Qt::AlignBottom, text);
    }
    // 绘制格子
    for (int i=0;i<m_size;i++) {
        for (int j=0;j<m_size;j++) {
            int x = offsetX + hintWidth + j * cell;
            int y = offsetY + hintHeight + i * cell;
            QRect r(x, y, cell, cell);
            p.setPen(QPen(QColor(100, 180, 100), 2)); // 春天主题：绿色边框
            p.drawRect(r);
            if (m_user[i][j] == 1) p.fillRect(r, Qt::black);
            else if (m_user[i][j] == 2) {
                p.drawRect(r);
                p.drawLine(r.topLeft(), r.bottomRight());
                p.drawLine(r.topRight(), r.bottomLeft());
            }
            else p.drawRect(r);
        }
    }
}

void GameBoard::mousePressEvent(QMouseEvent *e)
{
    int cell = 50;
    int hintWidth = 80;
    int hintHeight = 80;

    int boardSize = m_size * cell;
    int totalWidth = boardSize + hintWidth;
    int totalHeight = boardSize + hintHeight;
    int offsetX = (this->width() - totalWidth) / 2;
    int offsetY = (this->height() - totalHeight) / 2;

    double px = e->position().x();
    double py = e->position().y();

    int x = px - offsetX - hintWidth;
    int y = py - offsetY - hintHeight;

    if (x < 0 || y < 0 || x >= boardSize || y >= boardSize) {
        return;
    }

    int col = x / cell;
    int row = y / cell;

    // 关键安全检查
    if (row < 0 || row >= m_size || col < 0 || col >= m_size) {
        return;
    }
    // 点击计数+1
    m_clickCount++;
    //切换三种格子状态
    m_user[row][col] = (m_user[row][col] + 1) % 3;
    update();

    if (checkWin()) {
        QMessageBox::information(this, "恭喜", "节气解锁成功！");
    }
}
bool GameBoard::checkWin()//检查用户是否成功
{
    for (int i=0;i<m_size;i++)
        for (int j=0;j<m_size;j++)
            if ((m_user[i][j] == 1) != m_answer[i][j])
                return false;
    return true;
}
