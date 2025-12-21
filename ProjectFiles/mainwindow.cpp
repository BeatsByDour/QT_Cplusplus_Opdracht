#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Load stylesheet
    loadStylesheet();
    startScreen = ui->StartScreen;
    choiceScreen = ui->ChoiceScreen;
    battleScreen = ui->BattleScreen;
    partyScreen  = ui->PartyScreen;
    storeScreen  = ui->StoreScreen;

    // gebruikt van "this" operator

    // StartScreen: StartGame -> ChoiceScreen
    connect(startScreen, &StartScreen::StartGame,
            this,        &MainWindow::showChoiceScreen);

    // StartScreen: QuitGame (als je die hebt) -> app afsluiten
    connect(startScreen, &StartScreen::quitGame,
            qApp,        &QCoreApplication::quit);

    connect(choiceScreen, &ChoiceScreen::quitRequested,
            qApp,        &QCoreApplication::quit);


    // ChoiceScreen: naar Battle
    connect(choiceScreen, &ChoiceScreen::encounterStartRequested,
            this,         &MainWindow::showBattleScreen);

    // ChoiceScreen: naar Party
    connect(choiceScreen, &ChoiceScreen::partyRequested,
            this,         &MainWindow::showPartyScreen);

    // ChoiceScreen: naar Store
    connect(choiceScreen, &ChoiceScreen::storeRequested,
            this,         &MainWindow::showStoreScreen);
    connect(choiceScreen, &ChoiceScreen::restartRequested,
            this, &MainWindow::restartGame);
    // PartyScreen: terug naar Choice
    connect(partyScreen, &PartyScreen::returnToHomeScreen,
            this,        &MainWindow::showChoiceScreen);

    // StoreScreen: terug naar Choice
    connect(storeScreen, &StoreScreen::returnToHomeScreen,
            this,        &MainWindow::showChoiceScreen);

    // BattleScreen: als encounter stopt, terug naar Choice (optioneel)
    connect(battleScreen, &BattleScreen::Escape,    // of een eigen "battleFinished"
            this,         &MainWindow::showChoiceScreen);
    connect(battleScreen, &BattleScreen::Attack,
            this, &MainWindow::onBattleAttack);
    connect(battleScreen, &BattleScreen::Catch,
            this, &MainWindow::onBattleCatch);



    // Begin op StartScreen
    showStartScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::showStartScreen()
{
    ui->ScreenStack->setCurrentWidget(startScreen);
}
void MainWindow::restartGame()
{
        // Reset game manager
        gameManager.resetGame();

        // Reset battle variabelen
        m_round = 1;
        m_currentEnemy = CreatureClass();

        // Update UI
        showChoiceScreen();
}

void MainWindow::showChoiceScreen()
{
    PlayerClass &player = gameManager.GetPlayer();

    // Check of player dood is
    bool isPlayerDead = (player.GetCurrentHP() <= 0);

    // Update ChoiceScreen met player status
    choiceScreen->setPlayerDead(isPlayerDead);

    // Tel het aantal beasts
    int beastCount = 0;
    for (const auto& beast : player.GetParty()) {
        if (!beast.IsEmpty()) {
            beastCount++;
        }
    }

    choiceScreen->setBeastCount(beastCount);

    // Update andere stats alleen als player niet dood is
    if (!isPlayerDead) {
        int curHp = player.GetCurrentHP();
        int maxHp = player.GetMaxHP();
        int pDmg  = player.GetPDamage();
        int mDmg  = player.GetMDamage();
        int pArm  = player.GetPArmor();
        int mArm  = player.GetMArmor();
        int spd   = player.GetSpeed();
        int lvl   = player.GetLevel();
        int exp   = player.GetExperience();
        int neededForNext = lvl * 100 - exp;
        if (neededForNext < 0) neededForNext = 0;

        int stage = gameManager.GetStage();

        auto lblHp    = ui->ChoiceScreen->findChild<QLabel*>("lbl_Hp_Value");
        auto lblDmg   = ui->ChoiceScreen->findChild<QLabel*>("lbl_Dmg_Value");
        auto lblArm   = ui->ChoiceScreen->findChild<QLabel*>("lbl_Armor_Value");
        auto lblSpd   = ui->ChoiceScreen->findChild<QLabel*>("lblSpeed_Value");
        auto lblLvl   = ui->ChoiceScreen->findChild<QLabel*>("lbl_Level_Value");
        auto lblExp   = ui->ChoiceScreen->findChild<QLabel*>("lbl_Exp_Value");
        auto lblStage = ui->ChoiceScreen->findChild<QLabel*>("lbl_StageValue");

        if (lblHp)    lblHp->setText(QString("%1/%2").arg(curHp).arg(maxHp));
        if (lblDmg)   lblDmg->setText(QString("P:%1  M:%2").arg(pDmg).arg(mDmg));
        if (lblArm)   lblArm->setText(QString("P:%1  M:%2").arg(pArm).arg(mArm));
        if (lblSpd)   lblSpd->setText(QString::number(spd));
        if (lblLvl)   lblLvl->setText(QString::number(lvl));
        if (lblExp)   lblExp->setText(
                QString("%1  (next: %2)").arg(exp).arg(neededForNext));
        if (lblStage) choiceScreen->setStage(stage);
    } else {
        // Toon "DEAD" in de stats als player dood is
        auto lblHp = ui->ChoiceScreen->findChild<QLabel*>("lbl_Hp_Value");
        if (lblHp) lblHp->setText("DEAD");
        lblHp->setStyleSheet("color: red; font-weight: bold;");
    }

    ui->ScreenStack->setCurrentWidget(choiceScreen);
}
// werkt nog niet
void MainWindow::loadStylesheet()
{
    QFile file("gameStyle.qss");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open stylesheet file:" << file.errorString();
        return;
    }

    QString styleSheet = QString::fromUtf8(file.readAll());
    file.close();

    this->setStyleSheet(styleSheet);
    qDebug() << "Stylesheet applied";
}


void MainWindow::showPartyScreen()
{
    // Update de party display met huidige player
    partyScreen->updatePartyDisplay(gameManager.GetPlayer());

    ui->ScreenStack->setCurrentWidget(partyScreen);
}

void MainWindow::showStoreScreen()
{
    ui->ScreenStack->setCurrentWidget(storeScreen);
}

void MainWindow::showBattleScreen()
{
    PlayerClass &player = gameManager.GetPlayer();

    CreatureClass enemy = gameManager.GenerateRandomEnemy();
    m_currentEnemy = enemy; // kopie bewaren voor het gevecht

    CreatureClass *activeBeast = nullptr; // nullptr usage
    auto &party = player.GetParty();
    for (int i = 0; i < static_cast<int>(party.size()); ++i) {
        if (!party[i].IsEmpty()) {
            activeBeast = &const_cast<CreatureClass&>(party[i]);
            break;
        }
    }

    battleScreen->setupBattle(player, activeBeast, m_currentEnemy);
    ui->ScreenStack->setCurrentWidget(battleScreen);
}

void MainWindow::onBattleAttack()
{
    // Clear vorige acties
    battleScreen->clearActionText();

    PlayerClass &player = gameManager.GetPlayer();
    int playerMoveIdx = battleScreen->selectedPlayerMoveIndex();
    int beastMoveIdx  = battleScreen->selectedBeastMoveIndex();

    GameManager::ActionLog log;
    bool finished = gameManager.ResolveAction(m_currentEnemy,
                                              playerMoveIdx,
                                              beastMoveIdx,
                                              log);

    m_round++;

    // Lambda voor UI updates
    auto updateUI = [this](const QString& text) {
        battleScreen->appendActionText(text);
        QCoreApplication::processEvents(); // Update UI
    };

    // Toon eerste actie
    if (!log.actions[0].text.isEmpty()) {
        updateUI(log.actions[0].text);
    }

    // Update HP - ALLE bars
    battleScreen->updatePlayerHP(player.GetCurrentHP(), player.GetMaxHP());
    battleScreen->updateEnemyHP(m_currentEnemy.GetCurrentHP(),
                                m_currentEnemy.GetMaxHP());

    // Update beast HP
    CreatureClass *activeBeast = nullptr;
    auto &party = player.GetParty();
    for (int i = 0; i < static_cast<int>(party.size()); ++i) {
        if (!party[i].IsEmpty()) {
            activeBeast = &const_cast<CreatureClass&>(party[i]);
            break;
        }
    }
    if (activeBeast && !activeBeast->IsEmpty()) {
        // Voeg eerst updateBeastHP toe aan BattleScreen!
        battleScreen->updateBeastHP(activeBeast->GetCurrentHP(),
                                    activeBeast->GetMaxHP());
    }

    battleScreen->setRound(m_round);

    // Toon acties 2 en 3 met vertraging
    int delay = 1500;
    for (int i = 1; i < 3; i++) {
        if (!log.actions[i].text.isEmpty()) {
            QTimer::singleShot(delay, this, [this, updateUI, i, log]() {
                updateUI("\n" + log.actions[i].text);

                // Update ALLE HP bars na elke actie
                PlayerClass &player = gameManager.GetPlayer();
                battleScreen->updatePlayerHP(player.GetCurrentHP(), player.GetMaxHP());
                battleScreen->updateEnemyHP(m_currentEnemy.GetCurrentHP(),
                                            m_currentEnemy.GetMaxHP());

                // Update beast HP
                CreatureClass *activeBeast = nullptr;
                auto &party = player.GetParty();
                for (int i = 0; i < static_cast<int>(party.size()); ++i) {
                    if (!party[i].IsEmpty()) {
                        activeBeast = &const_cast<CreatureClass&>(party[i]);
                        break;
                    }
                }
                if (activeBeast && !activeBeast->IsEmpty()) {
                    battleScreen->updateBeastHP(activeBeast->GetCurrentHP(),
                                                activeBeast->GetMaxHP());
                }
            });
            delay += 1500; // Extra vertraging voor volgende actie
        }
    }

    // Check of battle voorbij is na alle acties
    QTimer::singleShot(delay, this, [this, updateUI]() {
        PlayerClass &player = gameManager.GetPlayer();
        if (m_currentEnemy.GetCurrentHP() <= 0 || player.GetCurrentHP() <= 0) {
            updateUI("\nBattle finished!");
            finishBattle();
        }
    });
}
void MainWindow::finishBattle()
{
    m_round = 0;
    PlayerClass &player = gameManager.GetPlayer();
    if (m_currentEnemy.GetCurrentHP() <= 0) {
        player.RewardAfterBeastDefeat(m_currentEnemy, m_currentEnemy.GetCatchRate() * player.GetLevel(),m_currentEnemy.GetCatchRate() * player.GetLevel());
        battleScreen->appendActionText("Enemy defeated! Reward received.");
    } else {
        battleScreen->appendActionText("You were defeated...");
    }

    QTimer::singleShot(1500, this, [this]() {
        gameManager.NextStage();
        showChoiceScreen();
    });
}


void MainWindow::onBattleCatch()
{
    PlayerClass &player = gameManager.GetPlayer();

    bool caught = player.TryCatchBeast(m_currentEnemy);
    if (caught) {
        player.AddToParty(m_currentEnemy);
        battleScreen->setActionText("Beast caught! Reward: new beast.");

        // 1 seconde wachten
        QTimer::singleShot(1000, this, [this]() {
            gameManager.NextStage();
            showChoiceScreen();
        });
    } else {
        battleScreen->appendActionText("Catch failed!");
    }
}

