#include "battlescreen.h"
#include "ui_battlescreen.h"

BattleScreen::BattleScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BattleScreen)
{
    ui->setupUi(this);

    connect(ui->btnAttack, &QPushButton::clicked,this,&BattleScreen::on_btnAttack_clicked);
    connect(ui->btnCatch, &QPushButton::clicked,this,&BattleScreen::on_btnCatch_clicked);
    connect(ui->btnRun, &QPushButton::clicked,this,&BattleScreen::on_btnEscape_clicked);

}

BattleScreen::~BattleScreen()
{
    delete ui;
}
void BattleScreen::on_btnAttack_clicked()
{
    emit Attack();
}
void BattleScreen::on_btnCatch_clicked()
{
    emit Catch();
}
void BattleScreen::on_btnEscape_clicked()
{
    emit Escape();
}
