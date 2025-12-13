#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    startScreen = ui->StartScreen;
    choiceScreen = ui->ChoiceScreen;
    battleScreen = ui->BattleScreen;
    partyScreen  = ui->PartyScreen;
    storeScreen  = ui->StoreScreen;

    // StartScreen: StartGame -> ChoiceScreen
    connect(startScreen, &StartScreen::StartGame,
            this,        &MainWindow::showChoiceScreen);

    // StartScreen: QuitGame (als je die hebt) -> app afsluiten
    connect(startScreen, &StartScreen::quitGame,
            qApp,        &QCoreApplication::quit);

    connect(choiceScreen, &ChoiceScreen::quitRequested,
            qApp,        &QCoreApplication::quit);


    // ChoiceScreen: naar Battle
    connect(choiceScreen, &ChoiceScreen::encounterStartRequested,
            this,         &MainWindow::showBattleScreen);

    // ChoiceScreen: naar Party
    connect(choiceScreen, &ChoiceScreen::partyRequested,
            this,         &MainWindow::showPartyScreen);

    // ChoiceScreen: naar Store
    connect(choiceScreen, &ChoiceScreen::storeRequested,
            this,         &MainWindow::showStoreScreen);

    // PartyScreen: terug naar Choice
    connect(partyScreen, &PartyScreen::returnToHomeScreen,
            this,        &MainWindow::showChoiceScreen);

    // StoreScreen: terug naar Choice
    connect(storeScreen, &StoreScreen::returnToHomeScreen,
            this,        &MainWindow::showChoiceScreen);

    // BattleScreen: als encounter stopt, terug naar Choice (optioneel)
    connect(battleScreen, &BattleScreen::Escape,    // of een eigen "battleFinished"
            this,         &MainWindow::showChoiceScreen);

    // Begin op StartScreen
    showStartScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::showStartScreen()
{
    ui->ScreenStack->setCurrentWidget(startScreen);
}

void MainWindow::showChoiceScreen()
{
    ui->ScreenStack->setCurrentWidget(choiceScreen);
}

void MainWindow::showBattleScreen()
{
    ui->ScreenStack->setCurrentWidget(battleScreen);
}

void MainWindow::showPartyScreen()
{
    ui->ScreenStack->setCurrentWidget(partyScreen);
}

void MainWindow::showStoreScreen()
{
    ui->ScreenStack->setCurrentWidget(storeScreen);
}


