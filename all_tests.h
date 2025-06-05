#ifndef ALL_TESTS_H
#define ALL_TESTS_H

#include <QtTest>
#include <QObject>

class Calculator;
class EngineeringCalculator;
class Converter;

class AllTests : public QObject
{
    Q_OBJECT

public:
    explicit AllTests(QObject *parent = nullptr);

private slots:
    // Basic Calculator Tests
    void testBasicCalculatorOperations();
    void testSignChangeAndClear();

    // Engineering Calculator Tests
    void testEngineeringFunctions();
    void testConstants();

    // Converter Tests
    void testLengthConversion();
    void testMassConversion();
    void testTemperatureConversion();

    // Navigation Tests
    void testNavigationToEngineering();
    void testNavigationToConverter();
    void testReturnFromEngineering();
};

#endif // ALL_TESTS_H
