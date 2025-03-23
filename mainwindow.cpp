#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
    ui_->setupUi(this);

    ui_->table->setColumnCount(n_colloms_);
    ui_->table->setRowCount(n_rows_);
    ui_->table->setHorizontalHeaderLabels(
        {"Day", "Month", "Year", "Day of Week", "Week Number", "Is Leap",
         "Next Day", "Previous Day", "To Next Date"});
    ui_->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui_->table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui_->table->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(ui_->buttonOpenFile, &QPushButton::clicked, this,
            &MainWindow::OpenFile);
    connect(ui_->buttonBirthday, &QPushButton::clicked, this,
            &MainWindow::CountDaysToBirthday);
    connect(ui_->buttonChangeDate, &QPushButton::clicked, this,
            &MainWindow::ChangeDate);
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

void MainWindow::AddDateToTable(const Date& date, int number,
                                const Date& next_date) {
    QTableWidgetItem* item;

    item = new QTableWidgetItem(QString::number(date.GetDay()));
    item->setTextAlignment(Qt::AlignCenter);
    ui_->table->setItem(number, 0, item);

    item = new QTableWidgetItem(QString::number(date.GetMonth()));
    item->setTextAlignment(Qt::AlignCenter);
    ui_->table->setItem(number, 1, item);

    item = new QTableWidgetItem(QString::number(date.GetYear()));
    item->setTextAlignment(Qt::AlignCenter);
    ui_->table->setItem(number, 2, item);

    item = new QTableWidgetItem(date.DayOfWeekString());
    item->setTextAlignment(Qt::AlignCenter);
    ui_->table->setItem(number, 3, item);

    item = new QTableWidgetItem(QString::number(date.WeekOfYear()));
    item->setTextAlignment(Qt::AlignCenter);
    ui_->table->setItem(number, 4, item);

    if (date.IsLeap()) {
        item = new QTableWidgetItem(QString("YES"));
    } else {
        item = new QTableWidgetItem(QString("NO"));
    }
    item->setTextAlignment(Qt::AlignCenter);
    ui_->table->setItem(number, n_colloms_ - 4, item);

    item = new QTableWidgetItem(date.NextDay().GetDate());
    item->setTextAlignment(Qt::AlignCenter);
    ui_->table->setItem(number, n_colloms_ - 3, item);

    item = new QTableWidgetItem(date.PreviousDay().GetDate());
    item->setTextAlignment(Qt::AlignCenter);
    ui_->table->setItem(number, n_colloms_ - 2, item);

    item =
        new QTableWidgetItem(QString::number(date.DurationToDate(next_date)));
    item->setTextAlignment(Qt::AlignCenter);
    ui_->table->setItem(number, n_colloms_ - 1, item);
}

void MainWindow::OpenFile() {

    path_ = QFileDialog::getOpenFileName(this, "Choose Text File",
                                         "/home/roma/Documents/Tables",
                                         "Text File(*.txt)");

    QFile* file = new QFile(path_);

    if (!file->open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::warning(this, "File Not Open", "Failed to open file");
        return;
    }

    QTextStream in(file);


    if (dates_ != nullptr) {
        delete[] dates_;
        dates_ = nullptr;
    }
    dates_ = ReadDates(in, n_rows_);

    ui_->table->clearContents();
    ui_->table->setRowCount(n_rows_);


    for (int i = 0; i < n_rows_; i++) {
        if (i == n_rows_ - 1) {
            AddDateToTable(dates_[i], i, dates_[0]);
        } else {
            AddDateToTable(dates_[i], i, dates_[i + 1]);
        }
    }

    file->close();
    delete file;
}

void MainWindow::CountDaysToBirthday() {
    if (ui_->table->selectedItems().empty()) {
        QMessageBox::warning(this, "Can't Find Days to Birtday",
                             "No selected Dates");
        return;
    }

    QTableWidgetItem* selected_item = ui_->table->selectedItems().first();
    int selected_row = selected_item->row();
    QString birthday = ui_->lineBirthday->text();
    if (!Date::CheckDate(birthday)) {
        QMessageBox::warning(this, "Can't Find Days to Birtday",
                             "Wrong Birthday Format");
        return;
    }

    int day_till_birthday =
        dates_[selected_row].DurationTillBirthday(Date(birthday));
    QMessageBox mess;
    mess.setText("Birthday");
    mess.setInformativeText(
        QString("Days till your birtday: %1").arg(day_till_birthday));
    mess.setStandardButtons(QMessageBox::Ok);
    mess.exec();
}

void MainWindow::ChangeDate() {
    if (ui_->table->selectedItems().empty()) {
        QMessageBox::warning(this, "Can't Change Date", "No selected Dates");
        return;
    }

    QTableWidgetItem* selected_item = ui_->table->selectedItems().first();
    int selected_row = selected_item->row();
    QString new_date_string = ui_->lineNewDate->text();
    if (!Date::CheckDate(new_date_string)) {
        QMessageBox::warning(this, "Can't Change Date",
                             "Wrong New Date Format");
        return;
    }

    QFile* file = new QFile(path_);
    if (!file->open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::warning(this, "File Not Open", "Failed to open file");
        return;
    }


    for (int i = 0; i < selected_row; i++) {
        file->readLine();
    }
    QTextStream out(file);
    out << new_date_string;

    Date new_date = Date(new_date_string);
    dates_[selected_row] = new_date;


    if (selected_row == n_rows_ - 1) {
        AddDateToTable(new_date, selected_row, dates_[0]);
    } else {
        AddDateToTable(new_date, selected_row, dates_[selected_row + 1]);
    }
}
