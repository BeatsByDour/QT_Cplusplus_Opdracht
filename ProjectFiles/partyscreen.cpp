#include "partyscreen.h"
#include "ui_partyscreen.h"
#include <QLabel>
#include <QProgressBar>
#include <QGroupBox>

PartyScreen::PartyScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PartyScreen)
{
    ui->setupUi(this);

    // Connect de return knop
    connect(ui->btnReturn, &QPushButton::clicked,
            this, &PartyScreen::on_btnReturn_clicked);

    // Stel vaste afmetingen in voor de afbeeldingen
    ui->lbl_Beast1_Image->setFixedSize(150, 150);
    ui->lbl_Beast2_Image->setFixedSize(150, 150);
    ui->lbl_Beast3_Image->setFixedSize(150, 150);
    ui->lbl_Beast4_Image->setFixedSize(150, 150);

    // Maak de afbeeldingen scalen
    ui->lbl_Beast1_Image->setScaledContents(true);
    ui->lbl_Beast2_Image->setScaledContents(true);
    ui->lbl_Beast3_Image->setScaledContents(true);
    ui->lbl_Beast4_Image->setScaledContents(true);
}

PartyScreen::~PartyScreen()
{
    delete ui;
}

void PartyScreen::updatePartyDisplay(const PlayerClass& player)
{
    const auto& party = player.GetParty();

    // Update elk slot
    for (int i = 0; i < 4; ++i) {
        if (!party[i].IsEmpty()) {
            updateBeastSlot(i, party[i]);
        } else {
            clearBeastSlot(i);
        }
    }
}

void PartyScreen::updateBeastSlot(int slotIndex, const CreatureClass& beast)
{
    // Bepaal welke UI elementen bij dit slot horen
    QLabel* imageLabel = nullptr;
    QLabel* nameLabel = nullptr;
    QLabel* statsLabel = nullptr;
    QProgressBar* hpBar = nullptr;
    QGroupBox* groupBox = nullptr;

    switch (slotIndex) {
    case 0:
        imageLabel = ui->lbl_Beast1_Image;
        nameLabel = ui->lbl_Beast1_Name;
        statsLabel = ui->lbl_Beast1_Stats;
        hpBar = ui->progressBar_Beast1;
        groupBox = ui->groupBox_Beast1;
        break;
    case 1:
        imageLabel = ui->lbl_Beast2_Image;
        nameLabel = ui->lbl_Beast2_Name;
        statsLabel = ui->lbl_Beast2_Stats;
        hpBar = ui->progressBar_Beast2;
        groupBox = ui->groupBox_Beast2;
        break;
    case 2:
        imageLabel = ui->lbl_Beast3_Image;
        nameLabel = ui->lbl_Beast3_Name;
        statsLabel = ui->lbl_Beast3_Stats;
        hpBar = ui->progressBar_Beast3;
        groupBox = ui->groupBox_Beast3;
        break;
    case 3:
        imageLabel = ui->lbl_Beast4_Image;
        nameLabel = ui->lbl_Beast4_Name;
        statsLabel = ui->lbl_Beast4_Stats;
        hpBar = ui->progressBar_Beast4;
        groupBox = ui->groupBox_Beast4;
        break;
    }

    if (!imageLabel || !nameLabel || !statsLabel || !hpBar || !groupBox) {
        return;
    }

    // Update afbeelding
    QPixmap pixmap = beast.GetVisualImage();
    if (!pixmap.isNull()) {
        imageLabel->setPixmap(pixmap.scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        imageLabel->setText("No Image");
    }

    // Update naam en level
    QString nameText = QString("%1\nLv. %2")
                           .arg(QString::fromStdString(beast.GetName()))
                           .arg(beast.GetLevel());
    nameLabel->setText(nameText);

    // Update stats
    QString statsText = QString("HP: %1/%2\n"
                                "P.DMG: %3\n"
                                "M.DMG: %4\n"
                                "Speed: %5")
                            .arg(beast.GetCurrentHP())
                            .arg(beast.GetMaxHP())
                            .arg(beast.GetPhysicalDamage())
                            .arg(beast.GetMagicalDamage())
                            .arg(beast.GetSpeed());
    statsLabel->setText(statsText);

    // Update HP bar
    hpBar->setRange(0, beast.GetMaxHP());
    hpBar->setValue(beast.GetCurrentHP());

    // Kleur op basis van HP percentage
    double hpPercent = (static_cast<double>(beast.GetCurrentHP()) / beast.GetMaxHP()) * 100.0;
    QString style;
    if (hpPercent > 50) {
        style = "QProgressBar::chunk { background-color: #00ff00; }";
    } else if (hpPercent > 25) {
        style = "QProgressBar::chunk { background-color: #ffff00; }";
    } else {
        style = "QProgressBar::chunk { background-color: #ff0000; }";
    }
    hpBar->setStyleSheet(style);

    // Update groupbox titel met type
    Type primaryType = beast.GetPrimaryType();
    QString typeString;
    switch (primaryType) {
    case Type::Earth: typeString = "Earth"; break;
    case Type::Water: typeString = "Water"; break;
    case Type::Fire: typeString = "Fire"; break;
    case Type::Ice: typeString = "Ice"; break;
    case Type::Flying: typeString = "Flying"; break;
    default: typeString = "Unknown"; break;
    }

    groupBox->setTitle(QString("Slot %1 - %2").arg(slotIndex + 1).arg(typeString));
}

void PartyScreen::clearBeastSlot(int slotIndex)
{
    QLabel* imageLabel = nullptr;
    QLabel* nameLabel = nullptr;
    QLabel* statsLabel = nullptr;
    QProgressBar* hpBar = nullptr;
    QGroupBox* groupBox = nullptr;

    switch (slotIndex) {
    case 0:
        imageLabel = ui->lbl_Beast1_Image;
        nameLabel = ui->lbl_Beast1_Name;
        statsLabel = ui->lbl_Beast1_Stats;
        hpBar = ui->progressBar_Beast1;
        groupBox = ui->groupBox_Beast1;
        break;
    case 1:
        imageLabel = ui->lbl_Beast2_Image;
        nameLabel = ui->lbl_Beast2_Name;
        statsLabel = ui->lbl_Beast2_Stats;
        hpBar = ui->progressBar_Beast2;
        groupBox = ui->groupBox_Beast2;
        break;
    case 2:
        imageLabel = ui->lbl_Beast3_Image;
        nameLabel = ui->lbl_Beast3_Name;
        statsLabel = ui->lbl_Beast3_Stats;
        hpBar = ui->progressBar_Beast3;
        groupBox = ui->groupBox_Beast3;
        break;
    case 3:
        imageLabel = ui->lbl_Beast4_Image;
        nameLabel = ui->lbl_Beast4_Name;
        statsLabel = ui->lbl_Beast4_Stats;
        hpBar = ui->progressBar_Beast4;
        groupBox = ui->groupBox_Beast4;
        break;
    }

    if (!imageLabel || !nameLabel || !statsLabel || !hpBar || !groupBox) {
        return;
    }

    // Clear alle velden
    imageLabel->clear();
    imageLabel->setText("Empty Slot");
    nameLabel->setText("Empty");
    statsLabel->setText("No beast");
    hpBar->setValue(0);
    groupBox->setTitle(QString("Slot %1 - Empty").arg(slotIndex + 1));
}

void PartyScreen::on_btnReturn_clicked()
{
    emit returnToHomeScreen();
}
