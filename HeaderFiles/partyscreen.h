#pragma once
#ifndef PARTYSCREEN_H
#define PARTYSCREEN_H

#include <QWidget>

namespace Ui {
class PartyScreen;
}

class PartyScreen : public QWidget
{
    Q_OBJECT

public:
    explicit PartyScreen(QWidget *parent = nullptr);
    ~PartyScreen();

signals:
    void returnToHomeScreen();

private slots:
    void on_btnReturn_Clicked();

private:
    Ui::PartyScreen *ui;
};

#endif // PARTYSCREEN_H
