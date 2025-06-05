#include "converter.h"
#include "ui_converter.h"
#include "calculator.h"
#include <QDebug>

Converter::Converter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Converter)
{
    ui->setupUi(this);
    setFixedSize(size());

    // Настройка интерфейса
    setupConverters();

    // Подключение кнопки возврата
    connect(ui->returnButton, &QPushButton::clicked,
            this, &Converter::returnToBasic);

    // Подключение конвертации
    connect(ui->convertButton, &QPushButton::clicked,
            this, &Converter::convertValue);
    connect(ui->inputValue, &QLineEdit::textChanged,
            this, &Converter::convertValue);
}

void Converter::updateUnits(int conversionType)
{
    ui->fromUnit->clear();
    ui->toUnit->clear();

    switch(conversionType) {
    case 0: // Длина
        ui->fromUnit->addItems({"Метры", "Километры", "Футы", "Дюймы"});
        ui->toUnit->addItems({"Метры", "Километры", "Футы", "Дюймы"});
        break;
    case 1: // Масса
        ui->fromUnit->addItems({"Килограммы", "Граммы", "Фунты", "Унции"});
        ui->toUnit->addItems({"Килограммы", "Граммы", "Фунты", "Унции"});
        break;
    case 2: // Температура
        ui->fromUnit->addItems({"Цельсий", "Фаренгейт", "Кельвин"});
        ui->toUnit->addItems({"Цельсий", "Фаренгейт", "Кельвин"});
        break;
    }
}

void Converter::setupConverters()
{
    // Добавляем типы конвертации
    ui->conversionType->addItem("Длина", QVariant::fromValue(0));
    ui->conversionType->addItem("Масса", QVariant::fromValue(1));
    ui->conversionType->addItem("Температура", QVariant::fromValue(2));

    // Заполняем единицы измерения
    updateUnits(0);

    // Связываем изменение типа конвертации
    connect(ui->conversionType, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this](int index){ updateUnits(index); });
}



void Converter::convertValue()
{
    // В конструкторе Converter добавьте валидатор:
    ui->inputValue->setValidator(new QDoubleValidator(this));

    // При получении значения:
    bool ok;
    double value = ui->inputValue->text().toDouble(&ok);
    if (!ok) {
        ui->resultValue->setText("Ошибка ввода");
        return;
    }
    int conversionType = ui->conversionType->currentIndex();
    QString fromUnit = ui->fromUnit->currentText();
    QString toUnit = ui->toUnit->currentText();

    double result = 0;

    // Конвертация длины
    if(conversionType == 0) {
        // Сначала переводим в метры (базовая единица)
        double meters=0;
        if(fromUnit == "Метры") meters = value;
        else if(fromUnit == "Километры") meters = value * 1000;
        else if(fromUnit == "Футы") meters = value * 0.3048;
        else if(fromUnit == "Дюймы") meters = value * 0.0254;

        // Затем конвертируем в целевую единицу
        if(toUnit == "Метры") result = meters;
        else if(toUnit == "Километры") result = meters / 1000;
        else if(toUnit == "Футы") result = meters / 0.3048;
        else if(toUnit == "Дюймы") result = meters / 0.0254;
    }
    // Конвертация массы
    else if(conversionType == 1) {
        // Сначала переводим в килограммы (базовая единица)
        double kilograms=0;
        if(fromUnit == "Килограммы") kilograms = value;
        else if(fromUnit == "Граммы") kilograms = value / 1000;
        else if(fromUnit == "Фунты") kilograms = value * 0.453592;
        else if(fromUnit == "Унции") kilograms = value * 0.0283495;

        // Конвертируем в целевую единицу
        if(toUnit == "Килограммы") result = kilograms;
        else if(toUnit == "Граммы") result = kilograms * 1000;
        else if(toUnit == "Фунты") result = kilograms / 0.453592;
        else if(toUnit == "Унции") result = kilograms / 0.0283495;
    }
    // Конвертация температуры
    else if(conversionType == 2) {
        // Сначала переводим в Цельсии (базовая единица)
        double celsius=0;
        if(fromUnit == "Цельсий") celsius = value;
        else if(fromUnit == "Фаренгейт") celsius = (value - 32) * 5/9;
        else if(fromUnit == "Кельвин") celsius = value - 273.15;

        // Затем конвертируем в целевую единицу
        if(toUnit == "Цельсий") result = celsius;
        else if(toUnit == "Фаренгейт") result = celsius * 9/5 + 32;
        else if(toUnit == "Кельвин") result = celsius + 273.15;
    }

    ui->resultValue->setText(QString::number(result, 'f', 4)); // Вывод с 4 знаками после запятой
}

void Converter::returnToBasic()
{
    this->close();
    Calculator *basicCalc = new Calculator();
    basicCalc->show();
}
Converter::~Converter()
{
    delete ui;
}
