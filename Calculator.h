#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

namespace Ui {
class Calculator;  // Изменили MainWindow на Calculator
}

class Calculator : public QMainWindow  // Изменили MainWindow на Calculator
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void NumPressed();
    void MathButtonPressed();
    void EqualButtonPressed();
    void ChangeNumberSign();
    void ClearButtonPressed();
    void OpenEngineeringCalculator();
    void DotPressed();
    void openConverter();
    void addToHistory(const QString& entry);

private:
    Ui::Calculator *ui;  // Изменили MainWindow на Calculator
    double calcValue;
    bool divTrigger;
    bool multTrigger;
    bool addTrigger;
    bool subTrigger;
    bool powerTrigger;
     QList<QString> calculationHistory;//1
};

#endif // CALCULATOR_H
