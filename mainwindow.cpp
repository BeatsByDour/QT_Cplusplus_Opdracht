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
    // Player ophalen uit GameManager
    PlayerClass &player = gameManager.GetPlayer();

    // CharacterClass-getters gebruiken
    int hp   = player.GetMaxHP();
    int dmg  = player.GetPDamage();      // voeg zo'n getter toe als je die nog niet hebt
    int arm  = player.GetPArmor();       // idem
    int spd  = player.GetSpeed();
    int lvl  = player.GetLevel();
    int exp  = player.GetExperience();

    // Labels in de ChoiceScreen bijwerken
    ui->ChoiceScreen->findChild<QLabel*>("lbl_Hp_Value")->setText(QString::number(hp));
    ui->ChoiceScreen->findChild<QLabel*>("lbl_Dmg_Value")->setText(QString::number(dmg));
    ui->ChoiceScreen->findChild<QLabel*>("lbl_Armor_Value")->setText(QString::number(arm));
    ui->ChoiceScreen->findChild<QLabel*>("lblSpeed_Value")->setText(QString::number(spd));
    ui->ChoiceScreen->findChild<QLabel*>("lbl_Level_Value")->setText(QString::number(lvl));
    ui->ChoiceScreen->findChild<QLabel*>("lbl_Exp_Value")->setText(QString::number(exp));

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


