#include "win.h"
#include <QHBoxLayout>

Win::Win(QWidget *parent):QWidget(parent)
{
    /*
     * объект класса QTextCodec – для русификации интерфейса
    */
    codec = QTextCodec::codecForName("Windows-1251");

    /*
     * Устанавливаем заголовок
    */
    this->setWindowTitle(codec->toUnicode("Счетчик"));

    /*
     * Создаем метки
     * метод toUnicode необходим для перекодировки в Unicode
    */
    label1 = new QLabel(codec->toUnicode("Cчет по 1"), this);
    label2 = new QLabel(codec->toUnicode("Cчет по 5"), this);

    /*
     * Создаем 2 счетчика с начальными значениями, равными 0 и указываем, что они являются виджетами-детьми
     * виджета Win
    */
    edit1 = new Counter("0", this);
    edit2 = new Counter("0", this);

    /*
     * Создание кнопок
    */
    calcbutton=new QPushButton("+1", this);
    exitbutton=new QPushButton(codec->toUnicode("Выход"), this);

    /*
     * Выполняем компоновку приложения
     */

    /*
     * QHBoxLayout – горизонтальный компоновщик – управляет расположением
     * виджетов в окне по горизонтали;
    */
    QHBoxLayout *layout1 = new QHBoxLayout();
    /*
     * Добавляем виджеты - метки
    */
    layout1->addWidget(label1);
    layout1->addWidget(label2);

    /*
     * QHBoxLayout – горизонтальный компоновщик – управляет расположением
     * виджетов в окне по горизонтали;
    */
    QHBoxLayout *layout2 = new QHBoxLayout();

    /*
     * Добавляем виджеты - счетчики
    */
    layout2->addWidget(edit1);
    layout2->addWidget(edit2);

    /*
     * QHBoxLayout – горизонтальный компоновщик – управляет расположением
     * виджетов в окне по горизонтали;
    */
    QHBoxLayout *layout3 = new QHBoxLayout();

    /*
     * Добавляем виджеты - кнопки
    */
    layout3->addWidget(calcbutton);
    layout3->addWidget(exitbutton);

    /*
     * QVBoxLayout – вертикальны компоновщик – управляет расположением
     * виджетов в окне по вертикали;
     *
     * Cоздание элемента компоновки для управления размещением остальных элементов компоновки в окне win
    */
    QVBoxLayout *layout4 = new QVBoxLayout(this);

    /*
     * Добавляем ячейки, содержащие другие QLayout
    */
    layout4->addLayout(layout1);
    layout4->addLayout(layout2);
    layout4->addLayout(layout3);

    /*
     * Связываем сигнал нажатия на кнопку "+1" со слотом add_one первого счетчика
    */
    connect(calcbutton, SIGNAL(clicked(bool)), edit1, SLOT(add_one()));

    /*
     * Связываем сигнал tick_signal, генерируемый первым счетчиком со слотом add_one второго счетчика
    */
    connect(edit1, SIGNAL(tick_signal()), edit2, SLOT(add_one()));

    /*
     * Связываем сигнал нажатия на кнопку "Выход" со слотом close()
    */
    connect(exitbutton, SIGNAL(clicked(bool)), this, SLOT(close()));
}
