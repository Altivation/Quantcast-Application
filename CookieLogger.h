#ifndef COOKIE_LOGGER_INCLUDED
#define COOKIE_LOGGER_INCLUDED

#include <fstream>
#include <string>
//these libraries are used to parse command line streams and log output files

#include <iostream>
//used for testing

//CookieLogger represents a processed cookie log file
//that contains data and methods to interact with that file
class CookieLogger {
public:
    CookieLogger(std::ifstream& ifile);

    CookieLogger(const CookieLogger& other);
    CookieLogger operator=(const CookieLogger& other);
    virtual ~CookieLogger();

    void logPopularCookie(const std::string& date, std::ofstream& ofile);
    //logs the most popular cookie(s) of a given day into ofile
private:
    std::pair<std::string, std::string>* cookieLines;
    //a dynamically allocated array of every cookie in the cookie log file
    //each pair represents a line: cookieLines.first = the cookie's name, cookieLines.second = the date
    int logSize;
    //represents the size of the Cookie
    //size of cookieLines; should always equal the number of used cookieLines

    void extractGarbage(std::ifstream &ifile) const;
    //removes the garbage header files from the top of an ifile

    const int findLogSize(std::ifstream& ifile) const;
    //used in the constructor
    //returns the number of lines in ifile

    void parseLine(std:: ifstream& ifile, const int& index);
    //used in the constructor
    //parses through an indexed line of the cookie log file and adds it to cookieLines

    int findFirstDate(const std::string& date);
    //used in logPopularCookie()
    //searches for the first date (with lowest index) in cookieLines using binarySearch()

    int binarySearch(int low, int high, const std::string& date);
    //used as a helper function in findFirstDate()
    //searches for an instance of date in the array of cookieLines with a fast runtime

    const bool AddCookie(const int& index, const std::string& date,
                std::pair<std::string, int>* cookieFrequency, int& cookieFrequencyNum);
    //Used in logPopularCookie()
    //checks if there's a cookie of the given date at an index of cookieLines
    //if there is, it returns true, and records the found cookie in cookieFrequency and/or increments it
    //cookieFrequency.first = the cookie's name, cookieFrequency.second = the frequency it appears
    //cookieFrequencyNum is the total number of members in the array of cookieFrequency
    //otherwise, it returns false

    void logMostActive(const std::pair<std::string, int>* cookieFrequency,
                const int& cookieFrequencyNum, std::ofstream& ofile) const;
    //Used in logPopularCookie()
    //finds the most popular cookie(s) in cookieFrequency and outputs them to ofile
};

#endif

