#include "storescreen.h"
#include "ui_storescreen.h"

StoreScreen::StoreScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StoreScreen)
{
    ui->setupUi(this);

    connect(ui->btnReturn, &QPushButton::clicked,this, &StoreScreen::on_btnReturn_Clicked);
}

StoreScreen::~StoreScreen()
{
    delete ui;
}
void StoreScreen::on_btnReturn_Clicked()
{
    emit returnToHomeScreen();
}
