#include "engineeringcalculator.h"
#include "ui_engineeringcalculator.h"
#include "calculator.h" // Для возврата к основному калькулятору
#include <QPushButton>
#include <QDebug>
#include <cmath>

EngineeringCalculator::EngineeringCalculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EngineeringCalculator)
    , divTrigger(false)
    , multTrigger(false)
    , addTrigger(false)
    , subTrigger(false)
{
    ui->setupUi(this);
    setFixedSize(size());

    // Подключаем цифровые кнопки
    connect(ui->Button0, &QPushButton::released, this, &EngineeringCalculator::NumPressed);
    connect(ui->Button1, &QPushButton::released, this, &EngineeringCalculator::NumPressed);
    connect(ui->Button2, &QPushButton::released, this, &EngineeringCalculator::NumPressed);
    connect(ui->Button3, &QPushButton::released, this, &EngineeringCalculator::NumPressed);
    connect(ui->Button4, &QPushButton::released, this, &EngineeringCalculator::NumPressed);
    connect(ui->Button5, &QPushButton::released, this, &EngineeringCalculator::NumPressed);
    connect(ui->Button6, &QPushButton::released, this, &EngineeringCalculator::NumPressed);
    connect(ui->Button7, &QPushButton::released, this, &EngineeringCalculator::NumPressed);
    connect(ui->Button8, &QPushButton::released, this, &EngineeringCalculator::NumPressed);
    connect(ui->Button9, &QPushButton::released, this, &EngineeringCalculator::NumPressed);

    // Основные операции
    connect(ui->Add, &QPushButton::released, this, &EngineeringCalculator::MathButtonPressed);
    connect(ui->Subtract, &QPushButton::released, this, &EngineeringCalculator::MathButtonPressed);
    connect(ui->Multiply, &QPushButton::released, this, &EngineeringCalculator::MathButtonPressed);
    connect(ui->Divide, &QPushButton::released, this, &EngineeringCalculator::MathButtonPressed);
    connect(ui->Equals, &QPushButton::released, this, &EngineeringCalculator::EqualButtonPressed);
    connect(ui->Clear, &QPushButton::released, this, &EngineeringCalculator::ClearButtonPressed);
    connect(ui->ButtonDot, &QPushButton::released, this, &EngineeringCalculator::DotPressed);
    connect(ui->ButtonPi, &QPushButton::released, this, &EngineeringCalculator::PiPressed);
    connect(ui->ButtonE, &QPushButton::released, this, &EngineeringCalculator::EulerPressed);
    // Инженерные функции
    connect(ui->Sin, &QPushButton::released, this, &EngineeringCalculator::TrigFunctionPressed);
    connect(ui->Cos, &QPushButton::released, this, &EngineeringCalculator::TrigFunctionPressed);
    connect(ui->Log, &QPushButton::released, this, &EngineeringCalculator::LogFunctionPressed);
    connect(ui->Sqrt, &QPushButton::released, this, &EngineeringCalculator::SqrtPressed);
    connect(ui->Power, &QPushButton::released, this, &EngineeringCalculator::PowerPressed);
    connect(ui->ChangeSignButton, &QPushButton::released,
            this, &EngineeringCalculator::EngineeringChangeNumberSign);

    // Кнопка возврата
    connect(ui->ReturnButton, &QPushButton::released, this, &EngineeringCalculator::ReturnToBasic);
}

EngineeringCalculator::~EngineeringCalculator()
{
    delete ui;
}

void EngineeringCalculator::NumPressed()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString buttonVal = button->text();
    QString displayVal = ui->Display->text();

    if (displayVal == "0" || displayVal == "0.0") {
        ui->Display->setText(buttonVal);
    } else {
        ui->Display->setText(displayVal + buttonVal);
    }
}

// ... Реализации MathButtonPressed, EqualButtonPressed аналогичны Calculator
void EngineeringCalculator::PowerPressed()
{
    // Реализация функции
    calcValue = ui->Display->text().toDouble();
    powerTrigger = true;
    ui->Display->clear();
}


void EngineeringCalculator::TrigFunctionPressed()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    double value = ui->Display->text().toDouble();
    double result = 0;
    QString funcName;

    if (button == ui->Sin) {
        result = sin(value * M_PI / 180.0);
        funcName = "sin";
    } else if (button == ui->Cos) {
        result = cos(value * M_PI / 180.0);
        funcName = "cos";
    }

    ui->Display->setText(QString::number(result));
    QString historyEntry = QString("%1(%2°) = %3")
                               .arg(funcName)
                               .arg(value)
                               .arg(result);
    addToHistory(historyEntry);
}

void EngineeringCalculator::ReturnToBasic()
{
    this->close();
    Calculator *basicCalc = new Calculator();
    basicCalc->show();
}
void EngineeringCalculator::MathButtonPressed()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    QString buttonVal = button->text();
    QString displayVal = ui->Display->text();
    calcValue = displayVal.toDouble();

    // Сбрасываем все триггеры
    divTrigger = multTrigger = addTrigger = subTrigger = false;
    powerTrigger = false;

    if (buttonVal == "+") {
        addTrigger = true;
    } else if (buttonVal == "-") {
        subTrigger = true;
    } else if (buttonVal == "*") {
        multTrigger = true;
    } else if (buttonVal == "/") {
        divTrigger = true;
    }

    ui->Display->clear();
}
void EngineeringCalculator::SqrtPressed()
{
    double displayVal = ui->Display->text().toDouble();
    if (displayVal >= 0) {
        double result = sqrt(displayVal);
        ui->Display->setText(QString::number(result));

        // Добавляем в историю
        QString historyEntry = QString("√%1 = %2")
                                   .arg(displayVal)
                                   .arg(result);
        addToHistory(historyEntry);
    } else {
        ui->Display->setText("Error");
    }
}
void EngineeringCalculator::LogFunctionPressed()
{
    if (!logTrigger) {
        logBase = ui->Display->text().toDouble();
        logTrigger = true;
        ui->Display->clear();
    } else {
        double number = ui->Display->text().toDouble();
        if (logBase > 0 && logBase != 1 && number > 0) {
            double result = log(number) / log(logBase);
            ui->Display->setText(QString::number(result));

            // Добавляем в историю
            QString historyEntry = QString("log%1(%2) = %3")
                                       .arg(logBase)
                                       .arg(number)
                                       .arg(result);
            addToHistory(historyEntry);
        } else {
            ui->Display->setText("Error");
        }
        logTrigger = false;
    }
}
void EngineeringCalculator::EqualButtonPressed()
{
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    QString operationSymbol = "";  // Объявляем переменную в начале функции

    if (powerTrigger) {
        solution = pow(calcValue, dblDisplayVal);
        operationSymbol = "^";
    }
    else if (addTrigger) {
        solution = calcValue + dblDisplayVal;
        operationSymbol = "+";
    }
    else if (subTrigger) {
        solution = calcValue - dblDisplayVal;
        operationSymbol = "-";
    }
    else if (multTrigger) {
        solution = calcValue * dblDisplayVal;
        operationSymbol = "×";
    }
    else if (divTrigger) {
        solution = dblDisplayVal != 0 ? calcValue / dblDisplayVal : 0;
        operationSymbol = "÷";
    }

    // Сброс всех триггеров
    powerTrigger = addTrigger = subTrigger = multTrigger = divTrigger = false;
    ui->Display->setText(QString::number(solution));

    // Добавляем запись в историю только если была операция
    if (!operationSymbol.isEmpty()) {
        QString historyEntry = QString("%1 %2 %3 = %4")
        .arg(calcValue)
            .arg(operationSymbol)
            .arg(dblDisplayVal)
            .arg(solution);
        addToHistory(historyEntry);
    }
}
void EngineeringCalculator::EngineeringChangeNumberSign()
{
    QString displayVal = ui->Display->text();
    if(displayVal.isEmpty()) return;

    bool ok;
    double val = displayVal.toDouble(&ok);
    if(ok) {
        ui->Display->setText(QString::number(-val));
    }
}

void EngineeringCalculator::DotPressed()
{
    QString currentText = ui->Display->text();

    if(!currentText.contains('.')) {
        ui->Display->setText(currentText + ".");
    }

    if(currentText.isEmpty()) {
        ui->Display->setText("0.");
    }
}
void EngineeringCalculator::PiPressed()
{
    // Если на дисплее пусто или 0, заменяем значением π
    if(ui->Display->text().isEmpty() || ui->Display->text() == "0") {
        ui->Display->setText(QString::number(M_PI));
    }
    // Иначе добавляем π к текущему значению (для умножения и т.д.)
    else {
        ui->Display->setText(ui->Display->text() + QString::number(M_PI));
    }
}

void EngineeringCalculator::EulerPressed()
{
    // Аналогично для числа e
    if(ui->Display->text().isEmpty() || ui->Display->text() == "0") {
        ui->Display->setText(QString::number(M_E));
    } else {
        ui->Display->setText(ui->Display->text() + QString::number(M_E));
    }
}
void EngineeringCalculator::ClearButtonPressed()
{
    ui->Display->setText("0");
    calcValue = 0;

    // Сбрасываем все триггеры
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    logTrigger = false;
    logBase = false;
    // sqrtTrigger = false;
    // logTrigger = false;
    // lnTrigger = false;
    // sinTrigger = false;
    // cosTrigger = false;
    // tanTrigger = false;
    // powerTrigger = false;
}

void EngineeringCalculator::addToHistory(const QString& entry)
{
    history.prepend(entry);
    ui->historyList->insertItem(0, entry);  // Добавляем в начало списка

    if (history.size() > 50) {
        ui->historyList->takeItem(history.size()-1);
        history.removeLast();
    }
}
