#ifndef CONVERTER_H
#define CONVERTER_H

#include <QMainWindow>

namespace Ui {
class Converter;
}

class Converter : public QMainWindow
{
    Q_OBJECT

public:
    explicit Converter(QWidget *parent = nullptr);
    ~Converter();

private slots:
    void convertValue();
    void returnToBasic();

private:
    Ui::Converter *ui;
    void setupConverters();
    void updateUnits(int conversionType);
};

#endif // CONVERTER_H
