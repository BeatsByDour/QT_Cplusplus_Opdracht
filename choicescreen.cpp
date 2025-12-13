#include "choicescreen.h"
#include "ui_choicescreen.h"

ChoiceScreen::ChoiceScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChoiceScreen)
{
    ui->setupUi(this);


    connect(ui->btnParty,          &QPushButton::clicked,
            this, &ChoiceScreen::on_btnParty_clicked);
    connect(ui->btnEncounter, &QPushButton::clicked,
            this, &ChoiceScreen::on_btnStartEncounter_clicked);
    connect(ui->btnStore,  &QPushButton::clicked,
            this, &ChoiceScreen::on_btnStore_clicked);
    connect(ui->btnQuit,  &QPushButton::clicked,
            this, &ChoiceScreen::on_btnQuit_clicked);
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

void ChoiceScreen::on_btnStore_clicked()
{
    emit storeRequested();
}
void ChoiceScreen::on_btnQuit_clicked()
{
    emit quitRequested();
}
void ChoiceScreen::setStage(int stage)
{
    ui->lbl_StageValue->setText(QString("Stage: %1").arg(stage));
}

void ChoiceScreen::setPlayerStats(const QString &text)
{
    ui->lbl_PlayerStats->setText(text);
}
