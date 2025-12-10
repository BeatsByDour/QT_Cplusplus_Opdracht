#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "gamemanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Widgets uit de QStackedWidget halen (ze zijn gepromote)
    startScreen  = qobject_cast<StartScreen*>(ui->ScreenStack->widget(0));
    choiceScreen = qobject_cast<ChoiceScreen*>(ui->ScreenStack->widget(1));

    // Signalen van StartScreen verbinden
    connect(startScreen,  &StartScreen::StartGame,
            this,         &MainWindow::showChoiceScreen);

    // Eventueel terugknop op ChoiceScreen
    connect(choiceScreen, &ChoiceScreen::encounterStartRequested,
            this,         &MainWindow::showStartScreen);
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

