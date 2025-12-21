#include "battlescreen.h"
#include "ui_battlescreen.h"

BattleScreen::BattleScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BattleScreen)
{
    ui->setupUi(this);

   // static int connectAttackCount = 0;
   // qDebug() << "Connecting Attack, count =" << ++connectAttackCount;
   // connect(ui->btnAttack, &QPushButton::clicked,this,&BattleScreen::on_btnAttack_clicked);
   // connect(ui->btnCatch, &QPushButton::clicked,this,&BattleScreen::on_btnCatch_clicked);
//    connect(ui->btnRun, &QPushButton::clicked,this,&BattleScreen::on_btnEscape_clicked);

}

BattleScreen::~BattleScreen()
{
    delete ui;
}
void BattleScreen::on_btnAttack_clicked()
{
    emit Attack();
}
void BattleScreen::on_btnCatch_clicked()
{
    emit Catch();
}
void BattleScreen::on_btnRun_clicked()
{
    emit Escape();
}


void BattleScreen::setupBattle(const PlayerClass &player,
                               const CreatureClass *activeBeast,
                               const CreatureClass &enemy)
{
    // Player naam + lvl
    QString playerNameLvl = QString("%1  Lv.%2")
                                .arg(QString::fromStdString(player.GetName()))
                                .arg(player.GetLevel());
    ui->lbl_P_Name->setText(playerNameLvl);
    ui->lbl_P_Image->setPixmap(player.GetVisualImage().scaled(100,100,Qt::KeepAspectRatio));

    // Player HP bar + tekst
    ui->pbr_Player->setMaximum(player.GetMaxHP());
    ui->pbr_Player->setValue(player.GetCurrentHP());
    ui->lbl_P_Hp_Value->setText(
        QString("%1/%2").arg(player.GetCurrentHP()).arg(player.GetMaxHP()));

    // Beast (actieve party-creature)
    if (activeBeast && !activeBeast->IsEmpty())
    {

        ui->BeastsMoves->setVisible(true);
        ui->pbr_Beasts->setVisible(true);
        ui->lbl_B_Name->setVisible(true);
        ui->lbl_B_hp_Value->setVisible(true);
          ui->lbl_Beasts_Moves_Text->setVisible(true);
        QString beastNameLvl = QString("%1  Lv.%2")
                                   .arg(QString::fromStdString(activeBeast->GetName()))
                                   .arg(activeBeast->GetLevel());
        ui->lbl_B_Name->setText(beastNameLvl);

        ui->lbl_B_Image->setPixmap(activeBeast->GetVisualImage().scaled(100,100,Qt::KeepAspectRatio));
        ui->pbr_Beasts->setMaximum(activeBeast->GetMaxHP());
        ui->pbr_Beasts->setValue(activeBeast->GetCurrentHP());
        ui->lbl_B_hp_Value->setText(
            QString("%1/%2").arg(activeBeast->GetCurrentHP())
                .arg(activeBeast->GetMaxHP()));
    }
    else
    {
        // geen beast in party → UI verbergen
        ui->BeastsMoves->setVisible(false);
        ui->pbr_Beasts->setVisible(false);
        ui->lbl_B_Name->setVisible(false);
        ui->lbl_B_hp_Value->setVisible(false);
        ui->lbl_Beasts_Moves_Text->setVisible(false);
    }

    // Enemy naam + lvl
    QString enemyNameLvl = QString("%1  Lv.%2")
                               .arg(QString::fromStdString(enemy.GetName()))
                               .arg(enemy.GetLevel());
    ui->lbl_E_Name->setText(enemyNameLvl);
    ui->lbl_E_Image->setPixmap(enemy.GetVisualImage().scaled(100,100,Qt::KeepAspectRatio));
    ui->pbr_Enemy->setMaximum(enemy.GetMaxHP());
    ui->pbr_Enemy->setValue(enemy.GetCurrentHP());

    // Ronde en actions
    m_round = 1;
    ui->lbl_Round->setText(QString("Round: %1").arg(m_round));
    ui->lbl_actions->setText("Actions: 0");

    // ComboBoxen vullen met moves
    ui->PlayerMoves->clear();
    ui->BeastsMoves->clear();

    // speler-moves (2 stuks in m_playerMoves)
    for (int i = 0; i < 2; ++i) {
        const Move &m = player.GetPlayerMove(i);
        if (!m.name.empty())
            ui->PlayerMoves->addItem(QString::fromStdString(m.name), i);
    }

    // beast-moves (4 moves in creature)
    if (activeBeast && !activeBeast->IsEmpty()) {
        for (int i = 0; i < 4; ++i) {
            const Move &m = activeBeast->GetMove(i);
            if (!m.name.empty())
                ui->BeastsMoves->addItem(QString::fromStdString(m.name), i);
        }
        ui->BeastsMoves->setVisible(true);
    } else {
        ui->BeastsMoves->setVisible(false);
    }
}
int BattleScreen::selectedPlayerMoveIndex() const
{
    return ui->PlayerMoves->currentData().toInt();
}
int BattleScreen::selectedBeastMoveIndex() const
{
    return ui->BeastsMoves->currentData().toInt();
}
QString BattleScreen::selectedPlayerMoveName() const
{
    return ui->PlayerMoves->currentText();
}
void BattleScreen::updateBeastHP(int current, int max)
{
    if (ui->pbr_Beasts->isVisible()) {
        ui->pbr_Beasts->setMaximum(max);
        ui->pbr_Beasts->setValue(current);
        ui->lbl_B_hp_Value->setText(
            QString("%1/%2").arg(current).arg(max));
    }
}
void BattleScreen::updateEnemyHP(int current, int max, const QString &actionText)
{
    ui->pbr_Enemy->setMaximum(max);
    ui->pbr_Enemy->setValue(current);
    ui->lbl_actions->setText(actionText);
    // Round++ mag je hier of in MainWindow doen
}
void BattleScreen::appendActionText(const QString &line)
{
    QString currentText = ui->lbl_actions->text();

    if (currentText.isEmpty()) {
        // Als er nog geen tekst is, zet de nieuwe tekst
        ui->lbl_actions->setText(line);
    } else {
        // Anders voeg toe op een nieuwe regel
        ui->lbl_actions->setText(currentText + "\n" + line);
    }
}

void BattleScreen::updatePlayerHP(int current, int max)
{
    ui->pbr_Player->setMaximum(max);
    ui->pbr_Player->setValue(current);
    ui->lbl_P_Hp_Value->setText(
        QString("%1/%2").arg(current).arg(max));
}

void BattleScreen::updateEnemyHP(int current, int max)
{
    ui->pbr_Enemy->setMaximum(max);
    ui->pbr_Enemy->setValue(current);
}

void BattleScreen::setRound(int r)
{
    ui->lbl_Round->setText(QString("Round: %1").arg(r));
}

void BattleScreen::setActionText(const QString &txt)
{
    ui->lbl_actions->setText(txt);
}
void BattleScreen::clearActionText()
{
    ui->lbl_actions->setText(" ");
}




