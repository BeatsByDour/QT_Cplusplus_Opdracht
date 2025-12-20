#pragma once


#include <QWidget>
//#include "ui_choicescreen.h"

namespace Ui {
class ChoiceScreen;
}
class ChoiceScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ChoiceScreen(QWidget *parent = nullptr);
    ~ChoiceScreen();
    void setStage(int stage);
    void setPlayerStats(const QString &text);

signals:
    void partyRequested();
    void storeRequested();
    void encounterStartRequested();
    void quitRequested();

private slots:
    void on_btnParty_clicked();
    void on_btnStore_clicked();
    void on_btnStartEncounter_clicked();
    void on_btnQuit_clicked();

private:
    Ui::ChoiceScreen *ui;
};

