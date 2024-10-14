#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    btnNums={
        {Qt::Key_0,ui->num_0},
        {Qt::Key_1,ui->num_1},
        {Qt::Key_2,ui->num_2},
        {Qt::Key_3,ui->num_3},
        {Qt::Key_4,ui->num_4},
        {Qt::Key_5,ui->num_5},
        {Qt::Key_6,ui->num_6},
        {Qt::Key_7,ui->num_7},
        {Qt::Key_8,ui->num_8},
        {Qt::Key_9,ui->num_9},
    };

    btnOperators={
        {Qt::Key_Backspace,ui->delButton},
        {Qt::Key_Plus,ui->addButton},
        {Qt::Key_Minus,ui->subButton},
        {Qt::Key_Asterisk,ui->mulButton},
        {Qt::Key_Slash,ui->divButton}
    };
    foreach(auto btn,btnNums)
        connect(btn,SIGNAL(clicked(bool)),this,SLOT(btnNumClick()));

    foreach(auto btn,btnOperators)
        connect(btn,SIGNAL(clicked(bool)),this,SLOT(btnOperatorClick()));

    // connect(ui->num_0,SIGNAL(clicked(bool)),this,SLOT(btnNumClick()));
    // connect(ui->num_1,SIGNAL(clicked(bool)),this,SLOT(btnNumClick()));
    // connect(ui->num_2,SIGNAL(clicked(bool)),this,SLOT(btnNumClick()));
    // connect(ui->num_3,SIGNAL(clicked(bool)),this,SLOT(btnNumClick()));
    // connect(ui->num_4,SIGNAL(clicked(bool)),this,SLOT(btnNumClick()));
    // connect(ui->num_5,SIGNAL(clicked(bool)),this,SLOT(btnNumClick()));
    // connect(ui->num_6,SIGNAL(clicked(bool)),this,SLOT(btnNumClick()));
    // connect(ui->num_7,SIGNAL(clicked(bool)),this,SLOT(btnNumClick()));
    // connect(ui->num_8,SIGNAL(clicked(bool)),this,SLOT(btnNumClick()));
    // connect(ui->num_9,SIGNAL(clicked(bool)),this,SLOT(btnNumClick()));

    // connect(ui->mulButton,SIGNAL(clicked(bool)),this,SLOT(btnOperatorClick()));
    // connect(ui->divButton,SIGNAL(clicked(bool)),this,SLOT(btnOperatorClick()));
    // connect(ui->addButton,SIGNAL(clicked(bool)),this,SLOT(btnOperatorClick()));
    // connect(ui->subButton,SIGNAL(clicked(bool)),this,SLOT(btnOperatorClick()));
    connect(ui->modButton,SIGNAL(clicked(bool)),this,SLOT(btnUnaryOperatorClick()));
    connect(ui->squButton,SIGNAL(clicked(bool)),this,SLOT(btnUnaryOperatorClick()));
    connect(ui->sqrtButton,SIGNAL(clicked(bool)),this,SLOT(btnUnaryOperatorClick()));
    connect(ui->cbButton,SIGNAL(clicked(bool)),this,SLOT(btnUnaryOperatorClick()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btnNumClick()
{
    QString digit=qobject_cast<QPushButton *>(sender())->text();
    if(digit=="0"&&operand=="0")
        operand=digit;
    else if(digit!="0"&&operand=="0")
        operand=digit;
    else
        operand+=digit;
    ui->display->setText(operand);
    ui->statusbar->showMessage(qobject_cast<QPushButton *>(sender())->text()+" click");

}

void MainWindow::on_periodButton_clicked()
{
    if(!operand.contains("."))
        operand+=qobject_cast<QPushButton *>(sender())->text();
    ui->display->setText(operand);
}

void MainWindow::on_signButton_clicked()
{
    if(operand!="")
    {
        double res=operand.toDouble();
            res=-1*res;
        operand=QString::number(res);
        ui->display->setText(QString::number(res));
    }
}

void MainWindow::on_delButton_clicked()
{
    operand=operand.left(operand.length()-1);
    ui->display->setText(operand);
}

void MainWindow::on_acButton_clicked()
{
    operand="";
    opcode="";
    operands.clear();
    opcodes.clear();
    ui->display->setText("");
}

void MainWindow::on_ceButton_clicked()
{
    operand="";
}

void MainWindow::btnOperatorClick()
{
    ui->statusbar->showMessage(qobject_cast<QPushButton *>(sender())->text()+" click");
    opcode=qobject_cast<QPushButton *>(sender())->text();
    if(operand!="")
    {
        operands.push_back(operand);
        operand="";
        opcodes.push_back(opcode);
    }
    else if(operands.size()==1)
        opcodes.push_back(opcode);
    QString res=calculation();

    ui->display->setText(res);

}

void MainWindow::btnUnaryOperatorClick()
{
    if(operand!="")
    {
        double res=operand.toDouble();
        operand="";

        QString op=qobject_cast<QPushButton *>(sender())->text();

        if(op=="%")
        {
            res/=100.0;
        }else if(op=="1/x")
        {
            res=1/res;
        }
        else if(op=="x^2")
        {
            res*=res;
        }else if(op=="√x")
        {
            res=sqrt(res);
        }

        ui->display->setText(QString::number(res));
    }
}

void MainWindow::on_equalButton_clicked()
{
    ui->statusbar->showMessage(qobject_cast<QPushButton *>(sender())->text()+" click");

    if(operands.size()==1&&opcodes.size()==1)
    {
        if(operand!="")
        {
            operands.push_back(operand);
            operand="";
            QString res=calculation();

            ui->display->setText(res);
        }
    }
}

QString MainWindow::calculation()
{
    double res=0;
    if(operands.size()==2&&opcode.size()>0)
    {
        double operand1=operands.front().toDouble();
        operands.pop_front();
        double operand2=operands.front().toDouble();
        operands.pop_front();

        QString op=opcodes.front();
        opcodes.pop_front();

        if(op=="+")
        {
            res=operand1+operand2;
        }else if(op=="-")
        {
            res=operand1-operand2;
        }else if(op=="*")
        {
            res=operand1*operand2;
        }else if(op=="/")
        {
            res=operand1/operand2;
        }

        operands.push_back(QString::number(res));

        ui->statusbar->showMessage("calculation in progress");
    }
    else
    {
        ui->statusbar->
            showMessage(QString("operands is %1,opcode is %2").arg(operands.size()).arg(opcode.size()));
    }
    return QString::number(res);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<event->key();
    foreach (auto btnkey, btnNums.keys()) {
        if(event->key()==btnkey)
        {
            btnNums[btnkey]->animateClick();
            return;
        }
    }
    foreach (auto btnkey, btnOperators.keys()) {
        if(event->key()==btnkey)
        {
            btnOperators[btnkey]->animateClick();
            return;
        }
    }
}







