#ifndef DATE_H
#define DATE_H

#include <QDateTime>
#include <QString>
#include <QStringList>

enum DaysOfWeek {
    kMonday = 1,
    kTuesday,
    kWednesday,
    kThursday,
    kFriday,
    kSaturday,
    kSunday = 0,
};

class Date {
   private:
    int day_, month_, year_;

   public:
    Date();
    Date(int day, int month, int year);
    explicit Date(const QString& date);

    int GetDay() const;
    int GetMonth() const;
    int GetYear() const;
    QString GetDate() const;

    bool IsLeap() const;
    int DaysInMonth() const;
    int DaysInYear() const;
    Date NextDay() const;
    Date PreviousDay() const;
    int DayOfWeek() const;
    QString DayOfWeekString() const;
    int DayOfYear() const;
    int WeekOfYear() const;
    int DurationToDate(Date date) const;
    int DurationToDay(int day, int month) const;
    int DurationTillBirthday(Date birthday) const;

    static bool CheckDate(int day, int month, int year);
    static bool CheckDate(const QString& date);
    static Date Now();
    static bool IsLeap(int year);
    static int DaysInMonth(int month, int year);
    static int DaysInYear(int year);
    static int DayOfWeek(int day, int month, int year);
    static int DayOfYear(int day, int month, int year);
    static int WeekOfYear(int day, int month, int year);
    static int DurationToNow(Date date);


   private:
    static const int kHundread = 100;
    static const int kTen = 10;
    static const int kMaxDayInMonth = 31;
    static const int kLessDayInMonth = 30;
    static const int kFebLeapDayInMonth = 29;
    static const int kFebDayInMonth = 28;
    static const int kMaxMonthInYear = 12;
    static const int kMaxYear = 9999;
    static const int kDaysInWeek = 7;
    static const int kDaysInYear = 365;
};

#endif	// DATE_H
