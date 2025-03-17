#include "date.h"

Date::Date(int day, int month, int year)
    : day_(day), month_(month), year_(year) {}

Date::Date(const QString& date) {
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

bool Date::IsLeap() {
    return (year_ % 4 == 0) &&
           (!(year_ % kHundread == 0) || (year_ % 4 * kHundread == 0));
}

int Date::DayInMonth() {
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

Date Date::NextDay() {
    if (day_ == this->DayInMonth() && month_ == kMaxMonthInYear &&
        year_ == kMaxYear) {
        Date next(1, 1, 1);
        return next;
    }

    else if (day_ == this->DayInMonth() && month_ == kMaxMonthInYear) {
        Date next(1, 1, year_ + 1);
        return next;
    }

    else if (day_ == this->DayInMonth()) {
        Date next(1, month_ + 1, year_);
        return next;
    }

    else {
        Date next(day_ + 1, month_, year_);
        return next;
    }
}

Date Date::PreviousDay() {


    if (day_ == 1 && month_ == 1 && year_ == 1) {
        Date previous(kMaxDayInMonth, kMaxMonthInYear, kMaxYear);
        return previous;
    }


    else if (day_ == 1 && month_ == 1) {
        Date previous(1, kMaxDayInMonth, year_ - 1);
        return previous;
    }


    else if (day_ == 1) {
        Date previous(Date::DayInMonth(month_ - 1, year_), month_ - 1, year_);
        return previous;
    }

    else {
        Date previous(day_ - 1, month_, year_);
        return previous;
    }
}

int Date::DayOfWeek() {
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
        kDayInWeek;

    return week;
}

int Date::DayOfYear() {
    int result = 0;
    result += day_;


    for (int i = 1; i < month_; i++) {
        result += Date::DayInMonth(i, year_);
    }

    return result;
}


// STATIC METHODS
bool Date::CheckDate(int day, int month, int year) {
    if (day < 1 || day > Date::DayInMonth(month, year)) {
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

    int day = spliteded_string[0].toInt();
    int month = spliteded_string[1].toInt();
    int year = spliteded_string[2].toInt();

    return Date::CheckDate(day, month, year);
}

bool Date::IsLeap(int year) {
    return (year % 4 == 0) &&
           (!(year % kHundread == 0) || (year % 4 * kHundread == 0));
}

int Date::DayInMonth(int month, int year) {
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


int Date::DayOfWeek(int day, int month, int year) {
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
        kDayInWeek;


    if (week == 0) {
        return kDayInWeek;
    }

    return week;
}

int Date::DayOfYear(int day, int month, int year) {
    int result = 0;
    result += day;


    for (int i = 1; i < month; i++) {
        result += Date::DayInMonth(i, year);
    }

    return result;
}

int Date::WeekOfYear(int day, int month, int year) {
    return ((Date::DayOfYear(day, month, year) + Date::DayOfWeek(1, 1, year) -
             2) /
            kDayInWeek) +
           1;
}
