#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QFileDialog>
#include <QFont>
#include <QIODevice>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QString>
#include <QTableView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTextStream>
#include "date.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

   private:
    Ui::MainWindow* ui_;
    Date* dates_ = nullptr;
    QTableWidget* table_ = nullptr;
    QString path_ = "";
    int n_rows_ = 0;
    const int n_colloms_ = 9;

    Date* ReadDates(QTextStream& in, int& size);
    void AddDateToTable(const Date& date, int number, const Date& next_date);
    void ChangeDurationToNext();

   private slots:
    void OpenFile();
    void CountDaysToBirthday();
    void ChangeDate();
    void AddDate();
};
#endif	// MAINWINDOW_H
