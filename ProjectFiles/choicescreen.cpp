#include "choicescreen.h"
#include "ui_choicescreen.h"

ChoiceScreen::ChoiceScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChoiceScreen)
{
    ui->setupUi(this);


  connect(ui->btnParty,     &QPushButton::clicked,this, &ChoiceScreen::on_btnParty_clicked);
  connect(ui->btnEncounter, &QPushButton::clicked,this, &ChoiceScreen::on_btnStartEncounter_clicked);
  connect(ui->btnStore,     &QPushButton::clicked,this, &ChoiceScreen::on_btnStore_clicked);
  connect(ui->btnQuit,      &QPushButton::clicked,this, &ChoiceScreen::on_btnQuit_clicked);
}

ChoiceScreen::~ChoiceScreen()
{
    delete ui;
}

void ChoiceScreen::setBeastCount(int count)
{
    ui->lbl_BeastValue->setText(QString::number(count));
}
void ChoiceScreen::on_btnParty_clicked()
{
    emit partyRequested();
}
void ChoiceScreen::setPlayerDead(bool isDead)
{
    // Toon/verberg restart knop
    ui->btnRestart->setVisible(isDead);

    // Schakel andere knoppen uit als player dood is
    ui->btnParty->setEnabled(!isDead);
    ui->btnStore->setEnabled(!isDead);
    ui->btnEncounter->setEnabled(!isDead);

    // Quit knop blijft altijd enabled
    ui->btnQuit->setEnabled(true);

    // Verander tekst op basis van status
    if (isDead) {
        ui->btnRestart->setText("Restart Game");
        // Optioneel: voeg een doodmelding toe
        if (auto lblStatus = findChild<QLabel*>("lbl_Status")) {
            lblStatus->setText("YOU DIED! Restart the game.");
            lblStatus->setStyleSheet("color: red; font-weight: bold;");
        }
    }
}
void ChoiceScreen::on_btnRestart_clicked()
{
    emit restartRequested();
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

