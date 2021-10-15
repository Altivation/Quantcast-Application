# Quantcast-Application

Hello, this is my submission for my Quantcast internship application

All functionality that processes the cookies are stored in the CookieLogger class in
'CookieLogger.h' and 'CookieLogger.cpp'. The language is C++.
--------------------------------------------------------------------------------------
--------------------------------CookieLogger SUMMARY----------------------------------
It's a class that represents a processed cookie log file. Because vectors and maps are
in different libraries, CookieLogger stores the processed data using dynamically
allocated arrays. Since the task specifies there's enough memory for the task, this
class tries to prioritize minimizing runtime.

To prevent the constant need to reallocate arrays, the program starts by trying to
figure out the max size of the data, which it stores as LogSize. This takes Big-O(n)
time, where n is the lines of the data.

Then, it stores each cookie log line as pairs (string names, string dates) and stores
it in cookieLines. This takes Big-O(n).

The class doesn't actually process the lines until the user gives it a date. This is
to minimize the runtime, so the program doesn't process irrelevant data.

To find a cookie with the given date in cookieLines, the class uses binarySearch
since the cookie log file is sorted. This takes Big-O(log n).

However, this doesn't guarantee that the found cookie is the first cookie with the
selected date, so it runs the while loop in findFirstDate() to find it. This takes
Big-O(c), where c is the number of cookies in a given day.

Then, the program parses through each cookieLines of the selected date and stores
those cookies (with their frequencies) in cookieFrequency. This takes Big-O(c * d),
where d is the number of different-named cookies in a given day.

Then, it logs the file into a user specified ofile. This takes Big-O(d) time.

In total, constructing this object takes Big-O(n) time. But calling a date takes
Big-O(log n + cd) runtime, making it time efficent if we are trying to access
multiple dates from the same timestamp. Since most timestamps are stored in 1 file,
it is common to do the latter.
------------------------------------------------------------------------------------
------------------------------------Test Cases--------------------------------------
test_BIG tests the class's ability to run decently sized timestamps.
    2018-10-10 << N/A
    2018-10-09 << uNvwqct5Jq5iaoNh (12)
                    FhYrK39qxDvmHIe9 (6)
                    BUjxvMVfLJAk0h23 (6)
                    7QKrceXIWu65q5Ps (4)
                    NYMclTeaj1qXPhXJ (4)
                    DZUXaeLYpHI6ZwFD (4)
                    fZ5VByYUncBNQY2f (4)
                    24q2wrp6CglRld97 (3)
                    TIgeFD72pINFoPt1 (3)
    2018-10-08 << BUjxvMVfLJAk0h23 (5)
                    uNvwqct5Jq5iaoNh (4)
                    NYMclTeaj1qXPhXJ (2)
                    FhYrK39qxDvmHIe9 (2)
                    fZ5VByYUncBNQY2f (2)
                    DZUXaeLYpHI6ZwFD (2)
                    24q2wrp6CglRld97 (1)
                    TIgeFD72pINFoPt1 (1)
    2018-10-07 << uNvwqct5Jq5iaoNh (9)
                    TIgeFD72pINFoPt1 (6)
                    BUjxvMVfLJAk0h23 (6)
                    NYMclTeaj1qXPhXJ (5)
                    fZ5VByYUncBNQY2f (4)
                    FhYrK39qxDvmHIe9 (3)
                    DZUXaeLYpHI6ZwFD (2)
                    24q2wrp6CglRld97 (2)
    2018-10-06 << uNvwqct5Jq5iaoNh (2)
               << 24q2wrp6CglRld97 (2)
                    BUjxvMVfLJAk0h23 (1)
    2018-10-05 << BUjxvMVfLJAk0h23 (4)
                    24q2wrp6CglRld97 (2)
                    DZUXaeLYpHI6ZwFD (2)
                    TIgeFD72pINFoPt1 (1)
                    uNvwqct5Jq5iaoNh (1)
                    fZ5VByYUncBNQY2f (1)
                    NYMclTeaj1qXPhXJ (1)
                    FhYrK39qxDvmHIe9 (1)
    2018-10-04 << uNvwqct5Jq5iaoNh (6)
                    BUjxvMVfLJAk0h23 (3)
                    NYMclTeaj1qXPhXJ (3)
                    FhYrK39qxDvmHIe9 (2)
                    TIgeFD72pINFoPt1 (1)
                    24q2wrp6CglRld97 (1)
                    fZ5VByYUncBNQY2f (1)
                    wNZXzu3n9LthF7ui (1)
                    DZUXaeLYpHI6ZwFD (1)
    2018-10-03 << uNvwqct5Jq5iaoNh (4)
                    24q2wrp6CglRld97 (1)
                    TIgeFD72pINFoPt1 (1)
                    FhYrK39qxDvmHIe9 (1)
                    DZUXaeLYpHI6ZwFD (1)
                    BUjxvMVfLJAk0h23 (1)
                    NYMclTeaj1qXPhXJ (1)
                    wNZXzu3n9LthF7ui (1)
    2018-10-02 << N/A
test_1PerDay is a timestamp where there's only 1 cookie per day
    2018-10-09 << 7QKrceXIWu65q5Ps (1)
    2018-10-08 << uNvwqct5Jq5iaoNh (1)
    2018-10-07 << FhYrK39qxDvmHIe9 (1)
    2018-10-06 << fZ5VByYUncBNQY2f (1)
    2018-10-05 << DZUXaeLYpHI6ZwFD (1)
    2018-10-04 << TIgeFD72pINFoPt1 (1)
    2018-10-03 << wNZXzu3n9LthF7ui (1)
    2018-10-02 << NYMclTeaj1qXPhXJ (1)
    2018-10-01 << 24q2wrp6CglRld97 (1)
    2018-09-29 << BUjxvMVfLJAk0h23 (1)
test_Only1Day is a timestamp of only 1 day
    2018-10-09 << DZUXaeLYpHI6ZwFD (4)
               << 24q2wrp6CglRld97 (4)
               << TIgeFD72pINFoPt1 (4)
                    BUjxvMVfLJAk0h23 (3)
                    fZ5VByYUncBNQY2f (3)
test_Only1DaySame is a timestamp where its only 1 day but every cookie is the same for that day
    2018-10-09 << fZ5VByYUncBNQY2f (77)
test_Only1DayDifferent is a timestamp where every cookie is unique and different for that day
    2018-10-09 << 7QKrceXIWu65q5Ps (1)
               << uNvwqct5Jq5iaoNh (1)
               << FhYrK39qxDvmHIe9 (1)
               << fZ5VByYUncBNQY2f (1)
               << DZUXaeLYpHI6ZwFD (1)
               << TIgeFD72pINFoPt1 (1)
               << wNZXzu3n9LthF7ui (1)
               << NYMclTeaj1qXPhXJ (1)
               << 24q2wrp6CglRld97 (1)
               << BUjxvMVfLJAk0h23 (1)
