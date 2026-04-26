// LevelSelect.h
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

class LevelSelect : public QWidget
{
    Q_OBJECT
public:
    explicit LevelSelect(QWidget *parent = nullptr);

private slots:
    void openGameBoard(int levelId);
};
