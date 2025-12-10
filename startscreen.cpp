#include "startscreen.h"
#include "ui_startscreen.h"

StartScreen::StartScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StartScreen)
{
    ui->setupUi(this);


    connect(ui->btnOpenChoiceScreen,          &QPushButton::clicked,
            this, &StartScreen::on_btnChoiceScreen_clicked);
    connect(ui->btnStartGame, &QPushButton::clicked,
            this, &StartScreen::on_btnStartGame_clicked);
}

StartScreen::~StartScreen()
{
    delete ui;
}
void StartScreen::on_btnChoiceScreen_clicked()
{
    emit OpenChoiceScreen();
}
void StartScreen::on_btnStartGame_clicked()
{
    emit StartGame();
}
