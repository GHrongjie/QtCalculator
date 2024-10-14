#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <QKeyEvent>
#include <QMap>
#include <QPushButton>

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
    QString operand="0";
    QString opcode;
    QStack<QString> operands;
    QStack<QString> opcodes;
    QMap<int,QPushButton*> btnNums;
    QMap<int,QPushButton*> btnOperators;

    QString calculation();

private slots:
    virtual void keyPressEvent(QKeyEvent *event);

    void btnNumClick();
    void btnOperatorClick();
    void btnUnaryOperatorClick();

    void on_periodButton_clicked();

    void on_delButton_clicked();

    void on_acButton_clicked();

    void on_equalButton_clicked();

    void on_signButton_clicked();

    void on_ceButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
