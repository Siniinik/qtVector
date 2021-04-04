#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <watch.h>
#include <QTableWidgetItem>
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    watch watchObject;                                  // объект класса набора часов
    watchRow watchRowObject;                            // объект класса часов

private slots:
    void editActive();                                  // функциядоступность для редактирования
    void update_watch();                                // функция редактирования записи

    void on_add_clicked();                              // клик по кнопке добавить запись
    void on_table_itemSelectionChanged();               // событие смены строки в таблице
    void on_company_textEdited(const QString &arg1);    // событие редактирования компании
    void on_model_textEdited(const QString &arg1);      // событие редактирования модели
    void on_country_textEdited(const QString &arg1);    // событие редактирования страны
    void on_year_valueChanged(int arg1);                // событие редактирования года
    void on_price_valueChanged(double arg1);            // событие редактирования цены
    void on_del_clicked();                              // клик по кнопке удалить запись
    void on_clear_clicked();                            // клик по кнопке удалить все записи
    void on_next_clicked();                             // клик по кнопке вправо на один
    void on_end_clicked();                              // клик по кнопке вправо последний
    void on_prev_clicked();                             // клик по кнопке вправо предыдущий
    void on_start_clicked();                            // клик по кнопке вправо в начало
    void on_save_clicked();                             // клик по кнопке сохранить

    void on_open_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
