#include "choicescreen.h"
#include "ui_choicescreen.h"

ChoiceScreen::ChoiceScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChoiceScreen)
{
    ui->setupUi(this);

    // knoppen verbinden met interne slots (als je geen auto-connect gebruikt)
    connect(ui->btnParty,          &QPushButton::clicked,
            this, &ChoiceScreen::on_btnParty_clicked);
    connect(ui->btnEncounter, &QPushButton::clicked,
            this, &ChoiceScreen::on_btnStartEncounter_clicked);
    connect(ui->btnQuit,  &QPushButton::clicked,
            this, &ChoiceScreen::on_btnStopEncounter_clicked);
}

ChoiceScreen::~ChoiceScreen()
{
    delete ui;
}

void ChoiceScreen::on_btnParty_clicked()
{
    emit partyRequested();
}

void ChoiceScreen::on_btnStartEncounter_clicked()
{
    emit encounterStartRequested();
}

void ChoiceScreen::on_btnStopEncounter_clicked()
{
    emit encounterStopRequested();
}
