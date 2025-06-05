#include "calculator.h"  // Изменили mainwindow.h на calculator.h
#include "ui_calculator.h"  // Изменили ui_mainwindow.h на ui_calculator.h
#include <QPushButton>
#include <QDebug>
#include "EngineeringCalculator.h"
#include "ui_engineeringcalculator.h"
#include "converter.h"

Calculator::Calculator(QWidget *parent)  // Изменили MainWindow на Calculator
    : QMainWindow(parent)
    , ui(new Ui::Calculator)  // Изменили MainWindow на Calculator
{
    ui->setupUi(this);
    setFixedSize(size());
    // Подключаем цифровые кнопки
    connect(ui->Button0, SIGNAL(released()), this, SLOT(NumPressed()));
    connect(ui->Button1, SIGNAL(released()), this, SLOT(NumPressed()));
    connect(ui->Button2, SIGNAL(released()), this, SLOT(NumPressed()));
    connect(ui->Button3, SIGNAL(released()), this, SLOT(NumPressed()));
    connect(ui->Button4, SIGNAL(released()), this, SLOT(NumPressed()));
    connect(ui->Button5, SIGNAL(released()), this, SLOT(NumPressed()));
    connect(ui->Button6, SIGNAL(released()), this, SLOT(NumPressed()));
    connect(ui->Button7, SIGNAL(released()), this, SLOT(NumPressed()));
    connect(ui->Button8, SIGNAL(released()), this, SLOT(NumPressed()));
    connect(ui->Button9, SIGNAL(released()), this, SLOT(NumPressed()));

    connect(ui->EngineeringButton, &QPushButton::released,
            this, &Calculator::OpenEngineeringCalculator);
    connect(ui->converterButton, &QPushButton::clicked,
            this, &Calculator::openConverter);

    // Подключаем математические операции
    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonPressed()));

    // Подключаем остальные кнопки
    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualButtonPressed()));
    connect(ui->ChangeNumberSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));
    connect(ui->Clear, SIGNAL(released()), this, SLOT(ClearButtonPressed()));
    connect(ui->ButtonDot, &QPushButton::released, this, &Calculator::DotPressed);
}

Calculator::~Calculator()  // Изменили MainWindow на Calculator
{
    delete ui;
}

void Calculator::NumPressed()
{
    QPushButton *button = (QPushButton *)sender();
    QString buttonVal = button->text();
    QString displayVal = ui->Display->text();

    if (displayVal.toDouble() == 0 || displayVal.toDouble() == 0.0) {
        ui->Display->setText(buttonVal);
    } else {
        QString newVal = displayVal + buttonVal;
        ui->Display->setText(newVal);
    }
}

void Calculator::MathButtonPressed()
{
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;

    QString displayVal = ui->Display->text();
    calcValue = displayVal.toDouble();

    QPushButton *button = (QPushButton *)sender();
    QString buttonVal = button->text();

    if (QString::compare(buttonVal, "/", Qt::CaseInsensitive) == 0) {
        divTrigger = true;
    } else if (QString::compare(buttonVal, "*", Qt::CaseInsensitive) == 0) {
        multTrigger = true;
    } else if (QString::compare(buttonVal, "+", Qt::CaseInsensitive) == 0) {
        addTrigger = true;
    } else if (QString::compare(buttonVal, "-", Qt::CaseInsensitive) == 0) {
        subTrigger = true;
    }

    ui->Display->setText("");
}


void Calculator::ChangeNumberSign()
{
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    double dblDisplayValSign = -1 * dblDisplayVal;
    ui->Display->setText(QString::number(dblDisplayValSign));
}

void Calculator::ClearButtonPressed()
{
    ui->Display->setText("0");
    calcValue = 0;
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
}
void Calculator::OpenEngineeringCalculator()
{
    this->close(); // Закрываем базовый калькулятор
    EngineeringCalculator *engCalc = new EngineeringCalculator();
    engCalc->show();
}
void Calculator::DotPressed()
{
    QString currentText = ui->Display->text();

    // Если точка уже есть, не добавляем новую
    if(!currentText.contains('.')) {
        ui->Display->setText(currentText + ".");
    }

    // Если поле пустое, добавляем "0."
    if(currentText.isEmpty()) {
        ui->Display->setText("0.");
    }
}

void Calculator::openConverter()
{
    this->hide();
    Converter *converter = new Converter();
    converter->show();
}

void Calculator::addToHistory(const QString& entry)
{
    calculationHistory.prepend(entry);  // Добавляем в начало

    // Ограничиваем историю (например, 50 записей)
    if (calculationHistory.size() > 50) {
        calculationHistory.removeLast();
    }

    // Обновляем отображение
    ui->historyList->clear();
    ui->historyList->addItems(calculationHistory);
}

void Calculator::EqualButtonPressed()//1
{
    // 1. Получаем текущее значение с дисплея
    QString displayVal = ui->Display->text();
    bool ok;
    double dblDisplayVal = displayVal.toDouble(&ok);

    if (!ok) {
        ui->Display->setText("Error");
        return;
    }

    // 2. Вычисляем результат
    double solution = 0.0;
    QString operationSymbol = "";

    if (addTrigger) {
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
        if (dblDisplayVal == 0) {
            ui->Display->setText("Ошибка: Деление на 0");
            return;
        }
        solution = calcValue / dblDisplayVal;
        operationSymbol = "÷";
    }
    else if (powerTrigger) {
        solution = pow(calcValue, dblDisplayVal);
        operationSymbol = "^";
    }
    else {
        // Если нет активной операции, просто возвращаем текущее значение
        return;
    }

    // 3. Отображаем результат
    ui->Display->setText(QString::number(solution));

    // 4. Формируем запись для истории
    QString historyEntry;
    if (powerTrigger) {
        historyEntry = QString("%1 %2 %3 = %4")
        .arg(calcValue)
            .arg(operationSymbol)
            .arg(dblDisplayVal)
            .arg(solution);
    } else {
        historyEntry = QString("%1 %2 %3 = %4")
        .arg(calcValue)
            .arg(operationSymbol)
            .arg(dblDisplayVal)
            .arg(solution);
    }

    // 5. Добавляем в историю
    addToHistory(historyEntry);

    // 6. Сбрасываем флаги операций
    addTrigger = false;
    subTrigger = false;
    multTrigger = false;
    divTrigger = false;
    powerTrigger = false;
}
