#pragma once

#include <QWidget>
#include "ui_startscreen.h"

class StartScreen : public QWidget
{
    Q_OBJECT

public:
    explicit StartScreen(QWidget *parent = nullptr);
    ~StartScreen();

signals:
    void OpenOptionScreen();
    void StartGame();
    void quitGame();

private slots:
    void on_btnOptionScreen_clicked();
    void on_btnStartGame_clicked();
     void on_btnQuitGame_clicked();

private:
    Ui::StartScreen *ui;
};

