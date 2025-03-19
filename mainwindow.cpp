#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
    ui_->setupUi(this);

    connect(ui_->buttonOpenFile, &QPushButton::clicked, this,
            &MainWindow::OpenFile);
}

MainWindow::~MainWindow() {
    delete ui_;
}

Date* MainWindow::ReadDates(QTextStream& in, int& size) {
    Date* dates = nullptr;
    size = 0;

    while (!in.atEnd()) {
        size++;
        QString temp_str = in.readLine();
        if (!Date::CheckDate(temp_str)) {
            QMessageBox::warning(
                this, "Frong Date",
                QString(
                    "Frong Date Format. Date №%1 Will Be Standart (01.01.0001)")
                    .arg(size));
        }

        Date new_date(temp_str);
        Date* temp_dates = new Date[size];


        for (int i = 0; i < size - 1; i++) {
            temp_dates[i] = dates[i];
        }
        temp_dates[size - 1] = new_date;

        delete[] dates;
        dates = temp_dates;
        temp_dates = nullptr;
    }

    return dates;
}

void MainWindow::AddDateToTable(Date date, int number) {
    table_->setItem(number, 0, new QTableWidgetItem(date.GetDate()));
}

void MainWindow::OpenFile() {
    QString path;

    path = QFileDialog::getOpenFileName(this, "Choose Text File",
                                        "/home/roma/Documents/Tables",
                                        "Text File(*.txt)");

    file_ = new QFile(path);

    if (!file_->open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::warning(this, "File Not Open", "Failed to open file");
        return;
    }

    QTextStream in(file_);


    if (dates_ != nullptr) {
        delete[] dates_;
        dates_ = nullptr;
    }
    dates_ = ReadDates(in, n_rows_);

    table_ = new QTableWidget(n_rows_, n_colloms_);
    table_->setHorizontalHeaderLabels({"Day", "Month", "Year"});


    for (int i = 0; i < n_rows_; i++) {
        AddDateToTable(dates_[i], i);
    }
    // table_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(table_);
    QWidget* central = new QWidget(this);
    central->setLayout(layout);

    setCentralWidget(central);
}
