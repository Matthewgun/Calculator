#include "all_tests.h"
#include "calculator.h"
#include "engineeringcalculator.h"
#include "converter.h"
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <cmath>

AllTests::AllTests(QObject *parent) : QObject(parent) {}

void AllTests::testBasicCalculatorOperations()
{
    Calculator calc;
    calc.show();
    QVERIFY(QTest::qWaitForWindowExposed(&calc));
    QTest::mouseClick(calc.findChild<QPushButton*>("Button5"), Qt::LeftButton);
    QTest::mouseClick(calc.findChild<QPushButton*>("Add"), Qt::LeftButton);
    QTest::mouseClick(calc.findChild<QPushButton*>("Button3"), Qt::LeftButton);
    QTest::mouseClick(calc.findChild<QPushButton*>("Equals"), Qt::LeftButton);
    QCOMPARE(calc.findChild<QLineEdit*>("Display")->text(), QString("8"));

    QTest::mouseClick(calc.findChild<QPushButton*>("Button9"), Qt::LeftButton);
    QTest::mouseClick(calc.findChild<QPushButton*>("Divide"), Qt::LeftButton);
    QTest::mouseClick(calc.findChild<QPushButton*>("Button3"), Qt::LeftButton);
    QTest::mouseClick(calc.findChild<QPushButton*>("Equals"), Qt::LeftButton);
    //QCOMPARE(calc.findChild<QLineEdit*>("Display")->text(), QString("3"));
}

void AllTests::testSignChangeAndClear()
{
    Calculator calc;
    calc.show();

    QTest::mouseClick(calc.findChild<QPushButton*>("Button7"), Qt::LeftButton);
    QTest::mouseClick(calc.findChild<QPushButton*>("ChangeNumberSign"), Qt::LeftButton);
    QCOMPARE(calc.findChild<QLineEdit*>("Display")->text(), QString("-7"));

    //calc.ClearButtonPressed();
    //QCOMPARE(calc.findChild<QLineEdit*>("Display")->text(), QString("0"));
}

void AllTests::testEngineeringFunctions()
{
    EngineeringCalculator engCalc;
    engCalc.show();

    QTest::mouseClick(engCalc.findChild<QPushButton*>("Button9"), Qt::LeftButton);
    QTest::mouseClick(engCalc.findChild<QPushButton*>("Sqrt"), Qt::LeftButton);
    QCOMPARE(engCalc.findChild<QLineEdit*>("Display")->text(), QString("3"));

    //engCalc.ClearButtonPressed();
    QTest::mouseClick(engCalc.findChild<QPushButton*>("Button2"), Qt::LeftButton);
    QTest::mouseClick(engCalc.findChild<QPushButton*>("Power"), Qt::LeftButton);
    QTest::mouseClick(engCalc.findChild<QPushButton*>("Button3"), Qt::LeftButton);
    QTest::mouseClick(engCalc.findChild<QPushButton*>("Equals"), Qt::LeftButton);

    //engCalc.ClearButtonPressed();
    QTest::mouseClick(engCalc.findChild<QPushButton*>("Button3"), Qt::LeftButton);
    QTest::mouseClick(engCalc.findChild<QPushButton*>("Button0"), Qt::LeftButton);
    QTest::mouseClick(engCalc.findChild<QPushButton*>("Sin"), Qt::LeftButton);
    QString result = engCalc.findChild<QLineEdit*>("Display")->text();
}



void AllTests::testConstants() //Значение π (пи)
{
    EngineeringCalculator engCalc;
    engCalc.show();
    QVERIFY(QTest::qWaitForWindowExposed(&engCalc));

    QTest::mouseClick(engCalc.findChild<QPushButton*>("ButtonPi"), Qt::LeftButton);
    QString piValue = engCalc.findChild<QLineEdit*>("Display")->text();
    QVERIFY2(qAbs(piValue.toDouble() - M_PI) < 0.0001, "Pi value incorrect");


    // Test E constant
    QTest::mouseClick(engCalc.findChild<QPushButton*>("Clear"), Qt::LeftButton);
    QTest::mouseClick(engCalc.findChild<QPushButton*>("ButtonE"), Qt::LeftButton);
    QString eValue = engCalc.findChild<QLineEdit*>("Display")->text();
    QVERIFY2(qAbs(eValue.toDouble() - M_E) < 0.0001, "E value incorrect");
    engCalc.close();
}

void AllTests::testNavigationToEngineering() //проверяет переход из базового калькулятора в инженерный
{
    Calculator calc;
    calc.show();

    QTest::mouseClick(calc.findChild<QPushButton*>("EngineeringButton"), Qt::LeftButton);
    QVERIFY(calc.isHidden());
}

void AllTests::testNavigationToConverter() //проверяет переход из базового калькулятора в конвертер
{
    Calculator calc;
    calc.show();

    QTest::mouseClick(calc.findChild<QPushButton*>("converterButton"), Qt::LeftButton);
    QVERIFY(calc.isHidden());
}

void AllTests::testReturnFromEngineering()
{
    EngineeringCalculator engCalc;
    engCalc.show();

    QTest::mouseClick(engCalc.findChild<QPushButton*>("ReturnButton"), Qt::LeftButton);
    QVERIFY(engCalc.isHidden());
}

void AllTests::testLengthConversion() //проверяет конвертацию длины
{
    Converter conv;
    conv.show();
    QComboBox* typeCombo = conv.findChild<QComboBox*>("conversionType");
    typeCombo->setCurrentIndex(0);

    QLineEdit* input = conv.findChild<QLineEdit*>("inputValue");
    input->setText("1000");

    QComboBox* fromUnit = conv.findChild<QComboBox*>("fromUnit");
    QComboBox* toUnit = conv.findChild<QComboBox*>("toUnit");
    fromUnit->setCurrentIndex(0);
    toUnit->setCurrentIndex(1);
    QCOMPARE(conv.findChild<QLineEdit*>("resultValue")->text(), QString("1"));
}

void AllTests::testMassConversion() //проверяет конвертацию массы
{
    Converter conv;
    conv.show();

    QComboBox* typeCombo = conv.findChild<QComboBox*>("conversionType");
    typeCombo->setCurrentIndex(1);

    QLineEdit* input = conv.findChild<QLineEdit*>("inputValue");
    input->setText("2");

    QComboBox* fromUnit = conv.findChild<QComboBox*>("fromUnit");
    QComboBox* toUnit = conv.findChild<QComboBox*>("toUnit");
    fromUnit->setCurrentIndex(0);
    toUnit->setCurrentIndex(1);

    //conv.convertValue();
    QCOMPARE(conv.findChild<QLineEdit*>("resultValue")->text(), QString("2000"));
}

void AllTests::testTemperatureConversion() //проверяет конвертацию температуры
{
    Converter conv;
    conv.show();

    QComboBox* typeCombo = conv.findChild<QComboBox*>("conversionType");
    typeCombo->setCurrentIndex(2);

    QLineEdit* input = conv.findChild<QLineEdit*>("inputValue");
    input->setText("20");

    QComboBox* fromUnit = conv.findChild<QComboBox*>("fromUnit");
    QComboBox* toUnit = conv.findChild<QComboBox*>("toUnit");
    fromUnit->setCurrentIndex(0);
    toUnit->setCurrentIndex(1);

    //conv.convertValue();
    QCOMPARE(conv.findChild<QLineEdit*>("resultValue")->text(), QString("68"));
}
//QTEST_MAIN(AllTests)
