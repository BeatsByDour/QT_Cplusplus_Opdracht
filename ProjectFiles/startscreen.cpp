#include "startscreen.h"
#include "ui_startscreen.h"

StartScreen::StartScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StartScreen)
{
    ui->setupUi(this);


    connect(ui->btnOpenOptionScreen,          &QPushButton::clicked,
            this, &StartScreen::on_btnOptionScreen_clicked);
    connect(ui->btnStartGame, &QPushButton::clicked,
            this, &StartScreen::on_btnStartGame_clicked);
    connect(ui->btnQuitGame, &QPushButton::clicked,
            this, &StartScreen::on_btnQuitGame_clicked);
}

StartScreen::~StartScreen()
{
    delete ui;
}
void StartScreen::on_btnOptionScreen_clicked()
{
    emit OpenOptionScreen();
}
void StartScreen::on_btnStartGame_clicked()
{
    emit StartGame();
}
void StartScreen::on_btnQuitGame_clicked()
{
    emit quitGame();
}
