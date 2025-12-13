#pragma once
#ifndef BATTLESCREEN_H
#define BATTLESCREEN_H

#include <QWidget>

namespace Ui {
class BattleScreen;
}

class BattleScreen : public QWidget
{
    Q_OBJECT

public:
    explicit BattleScreen(QWidget *parent = nullptr);
    ~BattleScreen();

    signals:
    void Escape();
    void Attack();
    void Catch();





    private slots:
    void on_btnEscape_clicked();
    void on_btnAttack_clicked();
    void on_btnCatch_clicked();

private:
    Ui::BattleScreen *ui;
};

#endif // BATTLESCREEN_H
