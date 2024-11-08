#include <stdio.h>
#include <stdbool.h>

bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int calculateStartingDay(int year, int month)
{
    int dayOfWeek = 0; // 0: Sunday, 1: Monday, ..., 6: Saturday
    if (month <= 2)
    {
        month += 12;
        year--;
    }
    dayOfWeek = (year + year / 4 - year / 100 + year / 400 + (31 * month) / 12) % 7;
    return dayOfWeek;
}

void displayCalendar(int year)
{
    const char *months[] = {
        "January", "February", "March", "April",
        "May", "June", "July", "August",
        "September", "October", "November", "December"
    };

    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if (isLeapYear(year))
    {
        daysInMonth[1] = 29; // February has 29 days in a leap year
    }

    printf("\nCalendar for year %d:\n", year);
    
    for (int month = 0; month < 12; ++month)
    {
        printf("\n\t%s:\n", months[month]);
        printf(" Sun Mon Tue Wed Thu Fri Sat\n");

        int startingDay = calculateStartingDay(year, month + 1);

        // Print leading spaces for the starting day
        for (int i = 0; i < startingDay; ++i)
        {
            printf("    ");
        }

        // Print the days of the month
        for (int day = 1; day <= daysInMonth[month]; ++day)
        {
            printf("%4d ", day);
            if ((startingDay + day) % 7 == 0) // Wrap to the next line after Saturday
            {
                printf("\n");
            }
        }

        printf("\n\n");
    }
}

int main()
{
    int year;
    printf("Enter a year to display the calendar (e.g. 2023): ");
    scanf("%d", &year);

    if (year < 0)
    {
        printf("Invalid year!\n");
        return 1;
    }

    if (year < 100)
    {
        year += 2000; // Assume years less than 100 are in the 2000s
    }

    // Range where Gregorian calendar can be shown without accuracies and overflows.
    if (year < 1582 || year > 4902)
    {
        printf("Invalid year!\n");
        return 1;
    }

    displayCalendar(year);
    return 0;
}
