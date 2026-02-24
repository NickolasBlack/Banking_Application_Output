#pragma once

#include "Stdafx.hpp"

/*
    Calendar Class
    This is a date object for transactions
    it contains a month, day and year variable.
    Users can test if a date is before or after another
*/
class Calendar{
    public:
        // Caendar constructor series
        Calendar(); // No args constructor
        Calendar(int month, int day, int year); // Keyword args constuctor
        Calendar(int month, int year); // credit car constructor
        Calendar(const Calendar& otherCalendar);

        // Get getter Series
        int getMonth(); // returns month
        int getDay(); // returns day
        int getYear(); // returns year

        // Calendar computational series
        bool before(Calendar otherCalendar) const; // checks before 
        bool after(Calendar otherCalander) const; // checks after

        // Formatter
        std::string printDate(); // returns {mm/dd/yyyy}

        // Calendar overloaded operators
        bool operator<(const Calendar& otherCalendar) const; // <
        bool operator>(const Calendar& otherCalendar) const; // >
        bool operator<=(const Calendar& otherCalendar) const; // <=
        bool operator>=(const Calendar& otherCalendar) const; // >=
        bool operator==(const Calendar& otherCalendar) const; // ==
        bool operator!=(const Calendar& otherCalendar) const; // !=
        Calendar operator+(int month) const; // +
        Calendar operator-(int month) const; // -

    private:
        int month; // month
        int day; // day
        int year; // year
};

// unit testing 
void testCalendar();