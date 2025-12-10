#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QWidget>

namespace Ui {
class StartScreen;
}

class StartScreen : public QWidget
{
    Q_OBJECT

public:
    explicit StartScreen(QWidget *parent = nullptr);
    ~StartScreen();

signals:
    void OpenChoiceScreen();
    void StartGame();

private slots:
    void on_btnChoiceScreen_clicked();
    void on_btnStartGame_clicked();

private:
    Ui::StartScreen *ui;
};

#endif // STARTSCREEN_H
