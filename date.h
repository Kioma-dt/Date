#ifndef DATE_H
#define DATE_H

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
    Date(int day, int month, int year);
    explicit Date(const QString& date);

    int GetDay() const;
    int GetMonth() const;
    int GetYear() const;

    bool IsLeap();
    int DayInMonth();
    Date NextDay();
    Date PreviousDay();
    int DayOfWeek();
    int DayOfYear();

    static bool CheckDate(int day, int month, int year);
    static bool CheckDate(const QString& date);
    static bool IsLeap(int year);
    static int DayInMonth(int month, int year);
    static int DayOfWeek(int day, int month, int year);
    static int DayOfYear(int day, int month, int year);
    static int WeekOfYear(int day, int month, int year);

   private:
    static const int kHundread = 100;
    static const int kTen = 10;
    static const int kMaxDayInMonth = 31;
    static const int kLessDayInMonth = 30;
    static const int kFebLeapDayInMonth = 29;
    static const int kFebDayInMonth = 28;
    static const int kMaxMonthInYear = 12;
    static const int kMaxYear = 9999;
    static const int kDayInWeek = 7;
};

#endif	// DATE_H
