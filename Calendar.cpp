#include "Calendar.hpp"

using namespace std;

// Canlendar class constructor series
Calendar::Calendar(){
    // Get time now 
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm local = *std::localtime(&t);

    // Set month year day month to time now
    year  = local.tm_year + 1900;  // years since 1900
    month = local.tm_mon + 1;      // 0-11 → 1-12
    day   = local.tm_mday;
} 

Calendar::Calendar(int month, int day, int year):
        // Key word args constructor
        month(month), day(day), year(year){}

Calendar::Calendar(int month, int year):
        // Canlendar Credit Card date constructor
        month(month), day(01), year(year){}

Calendar::Calendar(const Calendar& otherCalendar):
        // Calendar copy constructor
        month(otherCalendar.month), // copy month
        day(otherCalendar.day), // copy day
        year(otherCalendar.year) {} // copy year

/* Calendar getter series */
int Calendar::getMonth(){
    // Calendar get month. returns month
    return month; // return month
}

int Calendar::getDay(){
    // Calendar get day object. returns day
    return day; // return day
}

int Calendar::getYear(){
    // Calendar get year object. returns years
    return year; // return year
}

/* Calendar Computational Series */
bool Calendar::after(Calendar otherCalendar) const {
    // Calendar before function. Checks if a calendar object is before
    // the other
    return *this > otherCalendar;
}

bool Calendar::before(Calendar otherCalendar) const {
    // Calendar after method. chekcs if a calendar date is after another
    return *this < otherCalendar;
}

/* Calendar Formatter series */
string Calendar::printDate(){
    // Calendar print date method. prints a formatted string of the date
    return to_string(month) + "/" + // print month
           to_string(day) + "/" + // print day
           to_string(year); // print year
}

/* Calendar Overloaded operator series */
static int daysInMonth(int month, int year){
    // Calendar days In month method. returns the days in a particular month
    if (month == 2){
        // Account for number of days in february
        bool leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        return leap ? 29 : 28; // return number of february days
    }
    if (month == 4 || month == 6 || month == 9 || month == 11){
        return 30; // april, june, september, november
    }
    return 31; // 31 days
}

bool Calendar::operator<(const Calendar& otherCalendar) const{
    // Calendar class overloaded < operator method
    if (year != otherCalendar.year){
        // Check year
        return year < otherCalendar.year;
    }
    if (month != otherCalendar.month){
        // check month
        return month < otherCalendar.month;
    }
    // check day
    return day < otherCalendar.day;
}

bool Calendar::operator>(const Calendar& otherCalendar) const{
    // Calendar class overloaded > operator
    if (year!= otherCalendar.year){
        // check year
        return year > otherCalendar.year;
    }
    if (month != otherCalendar.month){
        // check month
        return month > otherCalendar.month;
    }
    // check day 
    return day > otherCalendar.day;
}

bool Calendar::operator<=(const Calendar& otherCalendar) const{
    // Calendar class overloaded <= operator
    return!(*this > otherCalendar);
}

bool Calendar::operator>=(const Calendar& otherCalendar) const{
    // Calendar class Overloaded >= operator
    return!(*this < otherCalendar);
}

bool Calendar::operator==(const Calendar& otherCalendar) const{
    // Calendar class overloaded == operator
    return year == otherCalendar.year && // years equal
           month == otherCalendar.month && // month equal
           day == otherCalendar.day; // day equal
}

bool Calendar::operator!=(const Calendar& otherCalendar) const {
    // Calendar class overloaded != operator
    return !(*this == otherCalendar);
}

Calendar Calendar::operator+(int months) const {
    // Calendar class overload + operator. Adds months and returns
    // new calendar object
    int newMonth = month + months; // compute new month
    int newYear = year; // copy year
    // Compute year
    while (newMonth > 12){
        newMonth -= 12;
        newYear++; 
    }
    // Compute number of days in month
    int newDay = day; // copy day
    int maxDay = daysInMonth(newMonth, newYear);
    if(newDay > maxDay){
        newDay = maxDay;
    }
    // Return new Calendar
    return Calendar(newMonth, newDay, newYear);
}

Calendar Calendar::operator-(int months) const {
    // Calendar Class overloaded - operator. subtracts months and
    // returns a new calendar object
    int newMonth = month - months; // subtract month
    int newYear  = year; // copy year
    // compute year
    while (newMonth <= 0) {
        newMonth += 12; // add months
        newYear--; // subtract year
    }
    // Compyte number of days in month
    int newDay = day; // copy day
    int maxDay = daysInMonth(newMonth, newYear);
    if (newDay > maxDay){
        newDay = maxDay;
    }
    // return new calendar
    return Calendar(newMonth, newDay, newYear);
}

/* Unit Testing Series */
static void testDate(){
    // create test calendar
    Calendar testDate = Calendar(01, 01, 2026);
    // assert
    ASSERT(testDate.getMonth() == 1);
    ASSERT(testDate.getDay() == 1);
    ASSERT(testDate.getYear() == 2026);
}

static void testAfter(){
    // Unit test for calendar after method
    Calendar testDate = Calendar(2, 15, 2025);
    Calendar otherTestDate = Calendar(7, 18, 2024);
    // Assert
    ASSERT(testDate.after(otherTestDate) == true);
}

static void testBefore(){
    // Unit test for calendar before method
    Calendar testDate = Calendar(8, 22, 2025); 
    Calendar otherTestDate = Calendar(7, 13, 2026);
    // Assert
    ASSERT(testDate.before(otherTestDate));
}

static void testOperators(){
    // Calendar class unit test for operators
    Calendar a(1, 15, 2025); // test calendar
    Calendar b(1, 15, 2025);
    Calendar c(2, 1, 2025);
    // Assert
    ASSERT(a == b);
    ASSERT(c > a);
    ASSERT(a < c);
    ASSERT(a <= b);
    ASSERT(a >= b);
}

void testCalendar(){
    // Unit Test for Calendar class
    TEST(testDate); // test date
    TEST(testAfter); // test after function
    TEST(testBefore); // test before function
    TEST(testOperators); // test operators
}