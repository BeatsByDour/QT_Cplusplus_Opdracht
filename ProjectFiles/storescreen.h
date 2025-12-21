#pragma once
#ifndef STORESCREEN_H
#define STORESCREEN_H

#include <QWidget>

namespace Ui {
class StoreScreen;
}

class StoreScreen : public QWidget
{
    Q_OBJECT

public:
    explicit StoreScreen(QWidget *parent = nullptr);
    ~StoreScreen();

signals:
    void returnToHomeScreen();

private slots:
    void on_btnReturn_Clicked();

private:
    Ui::StoreScreen *ui;
};

#endif // STORESCREEN_H
