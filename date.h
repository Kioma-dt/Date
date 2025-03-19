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
    kSunday,
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

    bool IsLeap();
    int DaysInMonth();
    int DaysInYear();
    Date NextDay();
    Date PreviousDay();
    int DayOfWeek();
    int DayOfYear();
    int DurationToDate(Date date);
    int DurationToDay(int day, int month);

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
    static int DurationTillBirthday(Date birthday);


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
