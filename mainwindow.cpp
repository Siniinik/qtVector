#include <ui_mainwindow.h>              // хедерник формы
#include <mainwindow.h>                 // хедерник событий формы
#include <QFileDialog>                  // диалог файла
#include <fstream>                      // чтения/записи данных из/в файл


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

#include <QTableWidgetItem>

/**
 * Добавление строки
 * @brief MainWindow::on_add_clicked
 */
void MainWindow::on_add_clicked()
{
    // Добавляем пустую строку в таблицу
    ui->table->insertRow(0);
    ui->table->selectRow(0);
    // Добавляем новую запись в начало вектора
    watchObject.add();
    // Запрашиваем первую (новую) запись вектора
    watchRow row = watchObject.get(0);
    // Запись новых значений в таблицу
    ui->table->setItem(0, 0, new QTableWidgetItem(QString::fromLocal8Bit(row.company)));
    ui->table->setItem(0, 1, new QTableWidgetItem(QString::fromLocal8Bit(row.model)) );
    ui->table->setItem(0, 2, new QTableWidgetItem(QString::number(row.year)) );
    ui->table->setItem(0, 3, new QTableWidgetItem(QString::fromLocal8Bit(row.country)) );
    ui->table->setItem(0, 4, new QTableWidgetItem(QString::number(row.price)) );
    // Искуственно вызываем событие выбора строки в таблице после обновления вектора
    on_table_itemSelectionChanged();
    // Доступность редактирования
    editActive();
}


MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * Функция проверки наличия записи в массиве для редактирования
 * @brief editActive
 */
void MainWindow::editActive(){
    if (watchObject.count()>0){
        ui->company ->setEnabled(true);     // тектовое поле компания
        ui->country ->setEnabled(true);     // тектовое поле страна
        ui->model   ->setEnabled(true);     // тектовое поле модель
        ui->year    ->setEnabled(true);     // тектовое поле год
        ui->price   ->setEnabled(true);     // тектовое поле цена
        ui->del     ->setEnabled(true);     // кнопка удалить запись
        ui->clear   ->setEnabled(true);     // кнопка очистить записи
        ui->save    ->setEnabled(true);     // кнопка сохранить записи
    } else {
        ui->company ->setEnabled(false);    // тектовое поле компания
        ui->country ->setEnabled(false);    // тектовое поле страна
        ui->model   ->setEnabled(false);    // тектовое поле модель
        ui->year    ->setEnabled(false);    // тектовое поле год
        ui->price   ->setEnabled(false);    // тектовое поле цена
        ui->del     ->setEnabled(false);    // кнопка удалить запись
        ui->clear   ->setEnabled(false);    // кнопка очистить записи
        ui->save    ->setEnabled(false);    // кнопка сохранить записи
        ui->next    ->setEnabled(false);    // отключаем кн. следующая
        ui->end     ->setEnabled(false);    // отключаем кн. последняя
    }
    // запрашиваем номер выбранной строки
    int currentRow = ui->table->currentRow();
    // для последней записи
    if (currentRow == ui->table->rowCount()-1){
        ui->next->setEnabled(false);        // отключаем кн. следующая
        ui->end->setEnabled(false);         // отключаем кн. последняя
    } else {
        ui->next->setEnabled(true);         // включаем кн. следующая
        ui->end->setEnabled(true);          // включаем кн. последняя
    }
    // для первой записи
    if (0 == currentRow){
        ui->prev->setEnabled(false);        // отключаем кн. предыдущая
        ui->start->setEnabled(false);       // отключаем кн. первая
    } else {
        ui->prev->setEnabled(true);         // включаем кн. предыдущая
        ui->start->setEnabled(true);          // включаем кн. первая
    }
}
/**
 * Событие выбора строки в таблице
 * @brief MainWindow::on_table_itemSelectionChanged
 */
void MainWindow::on_table_itemSelectionChanged()
{
    if (watchObject.count()>0){
        // запрашиваем номер выбранной строки
        int currentRow = ui->table->currentRow();
        // устанавливаем активную запись в наборе часов
        watchObject.pos = currentRow;
        // записываем номер в пагинацию
        ui->pos->setText(QString::number(currentRow+1));
        // запрос данных о часах из вектора
        watchRow row = watchObject.get(currentRow);
        watchObject.dump(currentRow);
        // передаем запись о фирме в текстовое поле для редактирования
        ui->company->setText(QString::fromLocal8Bit(row.company));
        // передаем запись о модели в текстовое поле для редактирования
        ui->model->setText(QString::fromLocal8Bit(row.model));
        // передаем запись о годе в текстовое поле для редактирования
        ui->year->setValue(row.year);
        // передаем запись о стране в текстовое поле для редактирования
        ui->country->setText(QString::fromLocal8Bit(row.country));
        // передаем запись о цене в текстовое поле для редактирования
        ui->price->setValue(row.price);
        // проверка состояний кнопок
        editActive();
    }
}


/**
 * функция редактирования
 * @brief MainWindow::update_watch
 */
void MainWindow::update_watch(){
    watchRow row;
    memcpy(row.company,  ui->company->text().toStdString().c_str(), 50);
    memcpy(row.country,  ui->country->text().toStdString().c_str(), 50);
    memcpy(row.model,  ui->model->text().toStdString().c_str(), 50);
    row.price   = ui->price->value();
    row.year    = ui->year->value();
    // сохраняем значения текстовых полей в векторе
    watchObject.set(watchObject.pos, row);
    // сохраняем знчения текстовых полей в таблице
    // фирма
    ui->table->setItem(watchObject.pos, 0, new QTableWidgetItem(ui->company->text()));
    // модель
    ui->table->setItem(watchObject.pos, 1, new QTableWidgetItem(ui->model->text()));
    // год
    ui->table->setItem(watchObject.pos, 2, new QTableWidgetItem(QString::number(ui->year->value())));
    // страна
    ui->table->setItem(watchObject.pos, 3, new QTableWidgetItem(ui->country->text()));
    // цена
    ui->table->setItem(watchObject.pos, 4, new QTableWidgetItem(QString::number(ui->price->value())));
}

/**
 * Редактирование записи компании часов
 * @brief MainWindow::on_company_textChanged
 * @param arg1
 */
void MainWindow::on_company_textEdited(const QString &arg)
{
    update_watch();
}

/**
 * Редактирование модели часов
 * @brief MainWindow::on_model_textEdited
 * @param arg1
 */
void MainWindow::on_model_textEdited(const QString &arg1)
{
   update_watch();
}

/**
 * Редактирование страны изготовителя часов
 * @brief MainWindow::on_country_textEdited
 * @param arg1
 */
void MainWindow::on_country_textEdited(const QString &arg1)
{
    update_watch();
}

/**
 * Редактирование года часов
 * @brief MainWindow::on_year_valueChanged
 * @param arg1
 */
void MainWindow::on_year_valueChanged(int arg1)
{
    update_watch();
}

/**
 * Редактирование цены часов
 * @brief MainWindow::on_price_valueChanged
 * @param arg1
 */
void MainWindow::on_price_valueChanged(double arg1)
{
    update_watch();
}

/**
 * Удаление выбранной строки
 * @brief MainWindow::on_del_clicked
 */
void MainWindow::on_del_clicked()
{
    // запрашиваем номер выбранной строки
    int currentRow = ui->table->currentRow();
    if (watchObject.count()>1){
        // удаление записи из таблицы
        ui->table->removeRow(currentRow);
        // удаление записи из вектора
        watchObject.del(currentRow);
        // Проверка активности после удаления
        editActive();
    } else {
        // TODO::БАГ
        // вместо удаления последеней записи очищаем таблицу
        ui->table->clearContents();
        ui->company->setText("");
        ui->model->setText("");
        ui->year->setValue(0);
        ui->country->setText("");
        ui->price->setValue(0);
    }


}

/**
 * Удаление всех записей
 * @brief MainWindow::on_clear_clicked
 */
void MainWindow::on_clear_clicked()
{
    // удаление записей из таблицы
    ui->table->clearContents();
    //TODO:: БАГ с удалением последей записи ui->table->rowCount()-1
    ui->table->model()->removeRows(0, ui->table->rowCount()-1);
    // удаление записей из вектора
    watchObject.clear();
    // очищаем текстовые поля
    ui->company->setText("");
    ui->model->setText("");
    ui->year->setValue(0);
    ui->country->setText("");
    ui->price->setValue(0);
}

/**
 * Шаг вправо
 * @brief MainWindow::on_next_clicked
 */
void MainWindow::on_next_clicked()
{
    int currentRow = ui->table->currentRow();
    ui->table->selectRow(currentRow+1);
}
/**
 * Последняя запись
 * @brief MainWindow::on_end_clicked
 */
void MainWindow::on_end_clicked()
{
   ui->table->selectRow(ui->table->rowCount()-1);
}

/**
 * Предыдущая запись
 * @brief MainWindow::on_prev_clicked
 */
void MainWindow::on_prev_clicked()
{
    int currentRow = ui->table->currentRow();
    ui->table->selectRow(currentRow-1);
}

/**
 * Последняя запись
 * @brief MainWindow::on_start_clicked
 */
void MainWindow::on_start_clicked()
{
    ui->table->selectRow(0);
}

/**
 * Сохранить записи
 * @brief MainWindow::on_save_clicked
 */
void MainWindow::on_save_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(NULL, "test", "", "*");
    qDebug()<< " сохранение в файл: " <<fileName;
    /**
     * Сохранение в файл проверка перегрузки оператора <<
     */
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        for(int i=0; i<watchObject.count(); i++) {
            watchRow row = watchObject.get(i);
            //Запишет - company country model num price year
            stream << QString::fromLocal8Bit(row.company)<< ";"
                   << QString::fromLocal8Bit(row.country)<< ";"
                   << QString::fromLocal8Bit(row.model)<< ";"
                   << QString::number(row.year)<< ";"
                   << QString::number(row.price)<< ";"
                   << QString::number(row.num)<< ";"
                   << endl;
        }
        file.close();
        if (stream.status() != QTextStream::Ok)
        {
            qDebug() << "Ошибка записи файла";
        }
    }

}
/**
 * Чтение записей из файла
 * @brief MainWindow::on_open_clicked
 */
void MainWindow::on_open_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(NULL, "", "", "*");
    qDebug()<< " чтение из файла: " <<fileName;
    QFile file (fileName);
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString str;
        while (!stream.atEnd())
        {
            str = stream.readLine();
            QStringList data = str.split(";");
            // Добавляем запись в вектор
            // Добавляем запись в таблицу
            on_add_clicked();
            // Сохраняем значения записи на форме
            ui->company->setText(data.value(0));
            ui->country->setText(data.value(1));
            ui->model->setText(data.value(2));
            ui->year->setValue(QString(data.value(3)).toInt());
            ui->price->setValue(QString(data.value(4)).toDouble());
            // Сохраняем значения в векторе
            update_watch();
            qDebug() << data;
        }
        if(stream.status()!= QTextStream::Ok)
        {
            qDebug() << "Ошибка чтения файла";
        }
        file.close();
    }
}
