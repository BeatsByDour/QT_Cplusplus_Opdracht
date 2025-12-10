#ifndef CHOICESCREEN_H
#define CHOICESCREEN_H

#include <QWidget>


namespace Ui {
class ChoiceScreen;
}

class ChoiceScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ChoiceScreen(QWidget *parent = nullptr);
    ~ChoiceScreen();

signals:
    void partyRequested();
    void encounterStartRequested();
    void encounterStopRequested();

private slots:
    void on_btnParty_clicked();
    void on_btnStartEncounter_clicked();
    void on_btnStopEncounter_clicked();

private:
    Ui::ChoiceScreen *ui;
};

#endif // CHOICESCREEN_H
