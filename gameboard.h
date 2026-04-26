//游戏界面
// GameBoard.h
#include <QWidget>
#include <QVector>
#include <QPainter>
#include <QTimer> // 计时器

class GameBoard : public QWidget
{
    Q_OBJECT
public:
    explicit GameBoard(int levelId, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;

private:
    int m_size;
    QVector<QVector<bool>> m_answer;
    QVector<QVector<int>> m_user; // 0=空 1=黑 2=叉
    bool checkWin();
    QVector<QVector<int>> m_rowHints;//储存当前关卡的行列线索
    QVector<QVector<int>> m_colHints;
    // 计时器和点击数
    QTimer *m_timer;
    int m_seconds = 0;
    int m_clickCount = 0;
private slots:
    void updateTimer(); //计时器更新槽函数
};
