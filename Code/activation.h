#ifndef ACTIVATION_H
#define ACTIVATION_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Activation; }
QT_END_NAMESPACE

class Activation : public QMainWindow
{
    Q_OBJECT

public:
    Activation(QWidget *parent = nullptr);
    ~Activation();

    void autosystem();

    QString getkey();

    int checkOS();

private slots:
    void on_activate_clicked();

    void on_windows_check_stateChanged(int arg1);

    void on_input_check_stateChanged(int arg1);

    void on_activate_bar_triggered();

    void on_exit_triggered();

    void on_contact_triggered();

    void on_about_triggered();

private:
    Ui::Activation *ui;
};
#endif // ACTIVATION_H
