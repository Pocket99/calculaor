#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setMaximumSize(402,398);
    this->setMinimumSize(402,398);
    this->setWindowTitle("Calculator");

    QFont f("Microsoft Yahei",14);

    ui->mainLineEdit->setFont(f);

    //put images on icon
    QIcon con("C:\\Users\\leo\\Documents\\Qt\\calculaor\\delete.png");
    ui->deletButton->setIcon(con);
    //change button background color
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_oneButton_2_clicked()
{
    expression += "1";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_leftButton_clicked()
{
    expression += "(";
    ui->mainLineEdit->setText(expression);
}


void Widget::on_zeroButton_clicked()
{
    expression += "0";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_rightButton_clicked()
{
    expression += ")";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_twoButton_clicked()
{
    expression += "2";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_threeButton_clicked()
{
    expression += "3";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_fourButton_clicked()
{
    expression += "4";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_fiveButton_clicked()
{
    expression += "5";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_sixButton_clicked()
{
    expression += "6";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_sevenButton_clicked()
{
    expression += "7";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_eightButton_clicked()
{
    expression += "8";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_nineButton_clicked()
{
    expression += "9";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_plusButton_clicked()
{
    expression += "+";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_minusButton_clicked()
{
    expression += "-";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_multiButton_clicked()
{
    expression += "*";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_divideButton_clicked()
{
    expression += "/";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_clearButton_clicked()
{
    expression.clear();
    ui->mainLineEdit->clear();
}

void Widget::on_deletButton_clicked()
{
    expression.chop(1);
    ui->mainLineEdit->setText(expression);
}

void Widget::on_equalButton_clicked()
{
    QStack<int> s_num,s_opt;

    char opt[128] = {0};
    int i = 0, temp = 0, num1 , num2;

    //convert expression intto char array
    //convert QString to char
    QByteArray ba;
    ba.append(expression);//convert QString to QByteArray
    strcpy(opt, ba.data());//data() used to convert QByteArray to char*

    while (opt[i] != '\0' || s_opt.empty() != true) {
        if(opt[i] >= '0' && opt[i] <= '9'){
            temp = temp *10 +opt[i] - '0';//char to int
            i++;
            if(opt[i]<'0'||opt[i]>'9'){
                s_num.push(temp);
                temp = 0;
            }
        }else{
            if(s_opt.empty() == true || priority(opt[i]) > priority(s_opt.top())||
                    (s_opt.top()=='(' && opt[i] != ')')){
                s_opt.push(opt[i]);
                i++;
                continue;
            }
            if(s_opt.top() == '(' && opt[i] == ')'){
                s_opt.pop();
                i++;
                continue;
            }
            if(priority(opt[i])<=priority(s_opt.top())
                    ||(opt[i]==')' && s_opt.top() != '(')
                    || (opt[i] == '\0' && s_opt.empty() != true)){
                char ch = s_opt.top();
                s_opt.pop();
                switch(ch){
                    case'+':
                        num1 = s_num.top();
                        s_num.pop();
                        num2 = s_num.top();
                        s_num.pop();
                        s_num.push(num1 + num2);
                        break;
                    case '-':
                        num1 = s_num.top();
                        s_num.pop();
                        num2 = s_num.top();
                        s_num.pop();
                        s_num.push(num2 - num1);
                        break;
                    case '*':
                        num1 = s_num.top();
                        s_num.pop();
                        num2 = s_num.top();
                        s_num.pop();
                        s_num.push(num1 * num2);
                        break;
                    case '/':
                        num1 = s_num.top();
                        s_num.pop();
                        num2 = s_num.top();
                        s_num.pop();
                        s_num.push(num2 / num1);
                        break;
                }
            }
        }
    }
    ui->mainLineEdit->setText(QString::number(s_num.top()));
}

int Widget::priority(char ch){
    switch (ch) {
    case '(':
        return 3;
    case '*':
    case '/':
        return 2;
    case '+':
    case '-':
        return 1;
    default:
        return 0;

    }
}
