#pragma once
#ifndef PARTYSCREEN_H
#define PARTYSCREEN_H

#include <QWidget>
#include "playerclass.h"

namespace Ui {
class PartyScreen;
}

class PartyScreen : public QWidget
{
    Q_OBJECT

public:
    explicit PartyScreen(QWidget *parent = nullptr);
    ~PartyScreen();

    // Update de UI met party informatie
    void updatePartyDisplay(const PlayerClass& player);

signals:
    void returnToHomeScreen();

private slots:
    void on_btnReturn_clicked();

private:
    Ui::PartyScreen *ui;

    // Helper functie om één beast slot te updaten
    void updateBeastSlot(int slotIndex, const CreatureClass& beast);
    void clearBeastSlot(int slotIndex);
};

#endif // PARTYSCREEN_H
