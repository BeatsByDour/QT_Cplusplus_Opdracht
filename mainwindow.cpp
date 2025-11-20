#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "gamemanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect( ui->StartGameButton,&QPushButton::clicked, this, &MainWindow::onStartGameClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::onStartGameClicked()
{
    gameManager.SetupGame(); // Call your GameManager function here.
}
