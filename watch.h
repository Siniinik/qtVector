#ifndef WATCH_H
#define WATCH_H

#include <QObject>
#include <QDebug>
#include <QString>

/**
 * Класс часов
 * @brief The watch class
 */
class watchRow{
public:

    char    company[50];    // фирма
    char    country[50];    // страна
    char    model[50];      // модель
    int     year;           // год
    double  price;          // цена
    int     num;            // номер по порядку

    //конструктор записи о часах
    //значения по умолчанию
    watchRow(){
        strcpy(company, (""));
        strcpy(model,   (""));
        year=1900;
        price=0.00;
        strcpy(country,  (""));
    }

};

/**
 * Класс набора часов
 * @brief The watch class
 */
class watch : public QObject  //класс наследник для сигнал слотов
{
    Q_OBJECT
private:
    QVector <watchRow> vector;

public:
    //Активная запись в наборе
    int pos = 0;
    /**
     * запрос записи по номеру
     * @brief get
     * @param i
     * @return
     */
    watchRow get(int i)
    {
        return vector.at(i);
    }
    /**
     * Редактированеи записи
     * @brief edit
     */
    void set(int pos, const watchRow &rowElem ){
        watchRow *data = vector.data();
        strcpy(data[pos].company, rowElem.company);
        strcpy(data[pos].country, rowElem.country);
        strcpy(data[pos].model, rowElem.model);
        data[pos].year      = rowElem.year;
        data[pos].price     = rowElem.price;
    }
    /**
     * Количество записей в наборе
     * @brief count
     * @return
     */
    int count(){
        return vector.count();
    }

    /**
     * Удаление записи из вектора
     * @brief del
     */
    void del(int pos){
        vector.removeAt(pos);
    }
    /**
     * Дебаг содержимого набора
     * @brief dump
     */
    void dump(){
        int i=0;
        qDebug()<< "******* Содержимое вектора watchRow ";
        for(watchRow elem: vector){
            qDebug()<< QString::number(i) + ") номер:       " << elem.num;
            qDebug()<< QString::number(i) + ") компания:    " << elem.company;
            qDebug()<< QString::number(i) + ") страна:      " << elem.country;
            qDebug()<< QString::number(i) + ") модель:      " << elem.model;
            qDebug()<< QString::number(i) + ") цена:        " << elem.price;
            qDebug()<< QString::number(i) + ") год:         " << elem.year;
            i++;
        };
        qDebug()<<"************************************ ";
    };
    /**
     * Дебаг записи
     * @brief dump
     */
    void dump(int pos){
        qDebug()<< "******* Содержимое записи:" ;
        qDebug()<< QString::number(pos) + ") номер:     " << vector.value(pos).num;
        qDebug()<< QString::number(pos) + ") компания:  " << vector.value(pos).company;
        qDebug()<< QString::number(pos) + ") страна:    " << vector.value(pos).country;
        qDebug()<< QString::number(pos) + ") модель:    " << vector.value(pos).model;
        qDebug()<< QString::number(pos) + ") цена:      " << vector.value(pos).price;
        qDebug()<< QString::number(pos) + ") год:       " << vector.value(pos).year;
        qDebug()<<"************************************ ";
    };

public slots:
    /**
     * Добавление новой записи со значениями по умолчанию
     * @brief add
     */
    void add(){
       watchRow elem;
       strcpy(elem.company, (""));
       strcpy(elem.model,   (""));
       strcpy(elem.country,  (""));
       elem.year=1900;
       elem.price=0.00;
       elem.num = vector.count();
       vector.prepend(elem);
    }

};

#endif // WATCH_H
