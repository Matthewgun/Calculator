#ifndef ENGINEERINGCALCULATOR_H
#define ENGINEERINGCALCULATOR_H

#include <QMainWindow>

namespace Ui {
class EngineeringCalculator;
}

class EngineeringCalculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit EngineeringCalculator(QWidget *parent = nullptr);
    ~EngineeringCalculator();

private slots:
    // Основные функции
    void NumPressed();
    void MathButtonPressed();
    void EqualButtonPressed();
    void EngineeringChangeNumberSign();
    void ClearButtonPressed();

    // Инженерные функции
    void TrigFunctionPressed();
    void LogFunctionPressed();
    void SqrtPressed();
    void PowerPressed();
    void ReturnToBasic();
    void DotPressed();
    void PiPressed();
    void EulerPressed();
    void addToHistory(const QString& entry);

private:
    Ui::EngineeringCalculator *ui;
    double calcValue;

    // Только используемые триггеры
    bool divTrigger;
    bool multTrigger;
    bool addTrigger;
    bool subTrigger;
    bool powerTrigger;
    bool logTrigger = false;
    double logBase = 0;
    QList<QString> history;
};

#endif // ENGINEERINGCALCULATOR_H
