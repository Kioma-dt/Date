#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QFileDialog>
#include <QIODevice>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
#include <QString>
#include <QTableView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTextStream>
#include <QVBoxLayout>
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
    QFile* file_ = nullptr;
    Date* dates_ = nullptr;
    QTableWidget* table_ = nullptr;
    int n_rows_ = 0;
    int n_colloms_ = 3;

    Date* ReadDates(QTextStream& in, int& size);
    void AddDateToTable(Date date, int number);

   private slots:
    void OpenFile();
};
#endif	// MAINWINDOW_H
