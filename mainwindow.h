#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "gamemanager.h"
#include "QMainWindow"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onStartGameClicked();   // Slot to handle button click.

private:
    Ui::MainWindow *ui;
    GameManager gameManager; // Punt 6: Useful and correct object composition - MainWindow bevat een GameManager om de spel-logica te beheren.
};
#endif // MAINWINDOW_H
