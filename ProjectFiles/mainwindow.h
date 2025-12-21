#pragma once

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "gamemanager.h"
#include "QMainWindow"
#include "startscreen.h"
#include "choicescreen.h"
#include "partyscreen.h"
#include "battlescreen.h"
#include "storescreen.h"
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showStartScreen();
    void showChoiceScreen();
    void showBattleScreen();
    void showPartyScreen();
    void showStoreScreen();
    void onBattleAttack();
    void onBattleCatch();
    void finishBattle();
    void loadStylesheet();
    void restartGame();

private:
    Ui::MainWindow *ui;
    ChoiceScreen *choiceScreen;
    StartScreen *startScreen;
    BattleScreen *battleScreen;
    PartyScreen  *partyScreen;
    StoreScreen  *storeScreen;
    GameManager gameManager; // Punt 6: Useful and correct object composition - MainWindow bevat een GameManager om de spel-logica te beheren.
    CreatureClass m_currentEnemy;
    int m_round{1};

};
#endif // MAINWINDOW_H
