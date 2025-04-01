#include "date.h"

Date::Date() : day_(1), month_(1), year_(1) {}

Date::Date(int day, int month, int year) {
    day_ = 1;
    month_ = 1;
    year_ = 1;

    if (!Date::CheckDate(day, month, year)) {
        throw "Wrong Date Format";
    }

    day_ = day;
    month_ = month;
    year_ = year;
}

Date::Date(const QString& date) {
    day_ = 1;
    month_ = 1;
    year_ = 1;

    if (!Date::CheckDate(date)) {
        throw "Wrong Date Format";
    }
    QStringList spliteded_string = date.split('.');

    day_ = spliteded_string[0].toInt();
    month_ = spliteded_string[1].toInt();
    year_ = spliteded_string[2].toInt();
}


// NOT STATIC METHODS

int Date::GetDay() const {
    return day_;
}

int Date::GetMonth() const {
    return month_;
}

int Date::GetYear() const {
    return year_;
}

QString Date::GetDate() const {
    return QString("%1.%2.%3")
        .arg(day_, 2, kTen, QChar('0'))
        .arg(month_, 2, kTen, QChar('0'))
        .arg(year_, 4, kTen, QChar('0'));
}

bool Date::IsLeap() const {
    return (year_ % 4 == 0) &&
           (!(year_ % kHundread == 0) || (year_ % (4 * kHundread) == 0));
}

int Date::DaysInMonth() const {
    if (month_ == 2 && Date::IsLeap(year_)) {
        return kFebLeapDayInMonth;
    }


    if (month_ == 2) {
        return kFebDayInMonth;
    }

    if ((month_ <= kMaxMonthInYear / 2 + 1 && month_ % 2 == 1) ||
        (month_ >= kMaxMonthInYear / 2 + 2 && month_ % 2 == 0)) {
        return kMaxDayInMonth;
    }

    return kLessDayInMonth;
}

int Date::DaysInYear() const {
    if (this->IsLeap()) {
        return kDaysInYear + 1;
    } else {
        return kDaysInYear;
    }
}

Date Date::NextDay() const {
    if (day_ == this->DaysInMonth() && month_ == kMaxMonthInYear &&
        year_ == kMaxYear) {
        Date next(1, 1, 1);
        return next;
    }

    else if (day_ == this->DaysInMonth() && month_ == kMaxMonthInYear) {
        Date next(1, 1, year_ + 1);
        return next;
    }

    else if (day_ == this->DaysInMonth()) {
        Date next(1, month_ + 1, year_);
        return next;
    }

    else {
        Date next(day_ + 1, month_, year_);
        return next;
    }

    return Date(1, 1, 1);
}

Date Date::PreviousDay() const {


    if (day_ == 1 && month_ == 1 && year_ == 1) {
        Date previous(kMaxDayInMonth, kMaxMonthInYear, kMaxYear);
        return previous;
    }


    else if (day_ == 1 && month_ == 1) {
        Date previous(Date::DaysInMonth(kMaxMonthInYear, year_),
                      kMaxMonthInYear, year_ - 1);
        return previous;
    }


    else if (day_ == 1) {
        Date previous(Date::DaysInMonth(month_ - 1, year_), month_ - 1, year_);
        return previous;
    }

    else {
        Date previous(day_ - 1, month_, year_);
        return previous;
    }
}

int Date::DayOfWeek() const {
    int new_year, new_month;


    if (month_ < 3) {
        new_year = year_ - 1;
        new_month = month_ + kTen;
    } else {
        new_year = year_;
        new_month = month_ - 2;
    }

    int week =
        (day_ + kMaxDayInMonth * new_month / kMaxMonthInYear + new_year +
         new_year / 4 - new_year / kHundread + new_year / (4 * kHundread)) %
        kDaysInWeek;

    return week;
}

QString Date::DayOfWeekString() const {
    int day_of_week = this->DayOfWeek();


    if (day_of_week == kMonday) {
        return QString("Monday");
    }


    if (day_of_week == kTuesday) {
        return QString("Tuesday");
    }


    if (day_of_week == kWednesday) {
        return QString("Wednesday");
    }


    if (day_of_week == kThursday) {
        return QString("Thursday");
    }


    if (day_of_week == kFriday) {
        return QString("Friday");
    }


    if (day_of_week == kSaturday) {
        return QString("Saturday");
    }


    if (day_of_week == kSunday) {
        return QString("Sunday");
    }

    return QString("ERROR");
}

int Date::DayOfYear() const {
    int result = 0;
    result += day_;


    for (int i = 1; i < month_; i++) {
        result += Date::DaysInMonth(i, year_);
    }

    return result;
}

int Date::WeekOfYear() const {
    return ((Date::DayOfYear(day_, month_, year_) +
             Date::DayOfWeek(1, 1, year_) - 2) /
            kDaysInWeek) +
           1;
}

int Date::DurationToDate(Date date) const {
    int day_span = 0;

    if (year_ == date.GetYear()) {
        bool positive = date.DayOfYear() > this->DayOfYear();
        Date max_date = positive ? date : *this;
        Date min_date = (!positive) ? date : *this;

        return max_date.DayOfYear() - min_date.DayOfYear();
    }

    bool positive = date.GetYear() > year_;
    Date max_date = positive ? date : *this;
    Date min_date = (!positive) ? date : *this;

    day_span +=
        max_date.DayOfYear() + (min_date.DaysInYear() - min_date.DayOfYear());

    for (int year = min_date.GetYear() + 1; year < max_date.GetYear(); year++) {
        day_span += Date::DaysInYear(year);
    }

    return day_span;
}

int Date::DurationToDay(int day, int month) const {
    if (!Date::CheckDate(day, month, 1)) {
        throw "Frong Date Format";
    }

    int day_span = 0;

    if (day == this->GetDay() && month == this->GetMonth()) {
        return day_span;
    }


    if (day == kMaxDayInMonth - 2 && month == 2) {
        if (this->IsLeap() &&
            Date::DayOfYear(day, month, this->GetYear()) > this->DayOfYear()) {
            day_span = Date::DayOfYear(day, month, this->GetYear()) -
                       this->DayOfYear();
        } else {
            day_span += this->DaysInYear() - this->DayOfYear();
            for (int year = this->GetYear() + 1; !Date::IsLeap(year); year++) {
                day_span += Date::DaysInYear(year);
            }
            day_span += Date::DayOfYear(day, month, 4);
        }
    } else {
        if (Date::DayOfYear(day, month, this->GetYear()) > this->DayOfYear()) {
            day_span = Date::DayOfYear(day, month, this->GetYear()) -
                       this->DayOfYear();
        } else {
            day_span += this->DaysInYear() - this->DayOfYear();
            day_span += Date::DayOfYear(day, month, this->GetYear() + 1);
        }
    }

    return day_span;
}

int Date::DurationTillBirthday(Date birthday) const {
    return this->DurationToDay(birthday.GetDay(), birthday.GetMonth());
}

// STATIC METHODS
bool Date::CheckDate(int day, int month, int year) {
    if (day < 1 || day > Date::DaysInMonth(month, year)) {
        return false;
    }


    if (month < 1 || month > kMaxMonthInYear) {
        return false;
    }


    if (year < 1 || year > kMaxYear) {
        return false;
    }

    return true;
}

bool Date::CheckDate(const QString& date) {
    QStringList spliteded_string = date.split('.');

    if (spliteded_string.size() != 3) {
        return false;
    }

    bool day_ok = false, month_ok = false, year_ok = false;
    int day = spliteded_string[0].toInt(&day_ok);
    int month = spliteded_string[1].toInt(&month_ok);
    int year = spliteded_string[2].toInt(&year_ok);


    if (day_ok && month_ok && year_ok) {
        return Date::CheckDate(day, month, year);
    } else {
        return false;
    }
}

Date Date::Now() {
    return Date(QDateTime::currentDateTime().toString("dd.MM.yyyy"));
}

bool Date::IsLeap(int year) {
    if (!Date::CheckDate(1, 1, year)) {
        throw "Frong Date Format";
    }

    return (year % 4 == 0) &&
           (!(year % kHundread == 0) || (year % 4 * kHundread == 0));
}

int Date::DaysInMonth(int month, int year) {
    if (month == 2 && Date::IsLeap(year)) {
        return kFebLeapDayInMonth;
    }


    if (month == 2) {
        return kFebDayInMonth;
    }

    if ((month <= kMaxMonthInYear / 2 + 1 && month % 2 == 1) ||
        (month >= kMaxMonthInYear / 2 + 2 && month % 2 == 0)) {
        return kMaxDayInMonth;
    }

    return kLessDayInMonth;
}

int Date::DaysInYear(int year) {
    if (!Date::CheckDate(1, 1, year)) {
        throw "Frong Date Format";
    }

    if (Date::IsLeap(year)) {
        return kDaysInYear + 1;
    } else {
        return kDaysInYear;
    }
}

int Date::DayOfWeek(int day, int month, int year) {
    if (!Date::CheckDate(day, month, year)) {
        throw "Frong Date Format";
    }

    int new_year, new_month;


    if (month < 3) {
        new_year = year - 1;
        new_month = month + kTen;
    } else {
        new_year = year;
        new_month = month - 2;
    }

    int week =
        (day + kMaxDayInMonth * new_month / kMaxMonthInYear + new_year +
         new_year / 4 - new_year / kHundread + new_year / (4 * kHundread)) %
        kDaysInWeek;


    if (week == 0) {
        return kDaysInWeek;
    }

    return week;
}

int Date::DayOfYear(int day, int month, int year) {
    if (!Date::CheckDate(day, month, year)) {
        throw "Frong Date Format";
    }

    int result = 0;
    result += day;


    for (int i = 1; i < month; i++) {
        result += Date::DaysInMonth(i, year);
    }

    return result;
}

int Date::WeekOfYear(int day, int month, int year) {
    if (!Date::CheckDate(day, month, year)) {
        throw "Frong Date Format";
    }

    return ((Date::DayOfYear(day, month, year) + Date::DayOfWeek(1, 1, year) -
             2) /
            kDaysInWeek) +
           1;
}

int Date::DurationToBirthday(Date burthday) {
    return Date::Now().DurationToDay(burthday.GetDay(), burthday.GetMonth());
}
