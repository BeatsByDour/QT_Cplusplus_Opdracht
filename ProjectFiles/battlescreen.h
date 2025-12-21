#pragma once
#ifndef BATTLESCREEN_H
#define BATTLESCREEN_H
#include "gamemanager.h"

#include <QWidget>

namespace Ui {
class BattleScreen;
}

class BattleScreen : public QWidget
{
    Q_OBJECT

public:
    explicit BattleScreen(QWidget *parent = nullptr);
    //desturctor
    ~BattleScreen();

    void setupBattle(const PlayerClass &player,
                     const CreatureClass *activeBeast, // nullptr als geen beast
                     const CreatureClass &enemy);
    int selectedPlayerMoveIndex() const;
    int selectedBeastMoveIndex() const;
    QString  selectedPlayerMoveName() const;
    void updateEnemyHP(int current, int max, const QString &actionText);
    void appendActionText(const QString &line);
    void updatePlayerHP(int current, int max);
    void updateEnemyHP(int current, int max);
    void updateBeastHP(int current, int max);
    void setRound(int r);
    void setActionText(const QString &txt);
    void clearActionText();

    signals:
    void Escape();
    void Attack();
    void Catch();

    private slots:
    void on_btnRun_clicked();
    void on_btnAttack_clicked();
    void on_btnCatch_clicked();

private:
    Ui::BattleScreen *ui;
    int m_round{1};
};

#endif // BATTLESCREEN_H
