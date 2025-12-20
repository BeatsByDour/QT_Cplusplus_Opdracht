#include "partyscreen.h"
#include "ui_partyscreen.h"

PartyScreen::PartyScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PartyScreen)
{
    ui->setupUi(this);
    connect(ui->btnReturn, &QPushButton::clicked,this, &PartyScreen::on_btnReturn_Clicked);

}

PartyScreen::~PartyScreen()
{
    delete ui;
}
void PartyScreen::on_btnReturn_Clicked()
{
    emit returnToHomeScreen();
}
