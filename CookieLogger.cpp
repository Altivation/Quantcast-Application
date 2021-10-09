#include "CookieLogger.h"

CookieLogger::CookieLogger(std::ifstream& ifile) {

    extractGarbage(ifile); //gets rid of garbage headers
    
    logSize = findLogSize(ifile);
    
    cookieLines = new std::pair<std::string, std::string>[logSize];
    //since there are logSize lines in the list, then cookieLines
    //would have logSize members, since each member of cookieLines
    //represents a line in the cookie log file.

    //parses every line of the file, which sets the values of cookieLines
    for (int i = 0; i < logSize; i++) {
        parseLine(ifile, i);
    }
}

CookieLogger::CookieLogger(const CookieLogger& other) {
    *this = other;
}

CookieLogger CookieLogger::operator=(const CookieLogger& other) {
    if (this == &other) {
        return *this;
    }
    this->logSize = other.logSize;
    this->cookieLines = new std::pair<std::string, std::string>[this->logSize];
    for (int i = 0; i < this->logSize; i++) {
        this->cookieLines[i] = other.cookieLines[i];
    }
    return *this;
}

CookieLogger::~CookieLogger() {
    delete[] cookieLines;
    cookieLines = nullptr;
}

//outputs the most active cookie in the cookie log file into ofile    
void CookieLogger::logPopularCookie(const std::string& date, std::ofstream& ofile) {

    std::pair<std::string, int>* cookieFrequency = new std::pair<std::string, int>[logSize];
    //cookieFrequency stores the frequency of cookies found on a specified date
    //cookieFrequency.first = the cookie's name, cookieFrequency.second = the cookie's frequency
    //Because there are logSize lines in the cookie log file, the worst case
    //number of cookies with different names is logSize. Since we have enough memory,
    //declaring a very large array is better than re-sizing the array constantly
    int cookieFrequencyNum = 0;
    //stores the number of used members in cookieFrequency

    int cookieIndex = findFirstDate(date);
    //stores the index of the currently analyzed cookie that occurs on the specified date

    while (AddCookie(cookieIndex, date, cookieFrequency, cookieFrequencyNum)) {
        cookieIndex++;
    }
    
    logMostActive(cookieFrequency, cookieFrequencyNum, ofile);

    delete[] cookieFrequency;
}

//removes useless "cookie,timestamp\n" at the head of the file
void CookieLogger::extractGarbage(std::ifstream& ifile) const {
    std::string temp;
    std::getline(ifile, temp);
}

//returns the number of lines left in ifile
const int CookieLogger::findLogSize(std::ifstream& ifile) const {
    int count = 0;
    std::string temp; //used to extract lines from ifile
    int origPosition = ifile.tellg();

    while (!ifile.eof()) {
        std::getline(ifile, temp);
        count++;
    }

    ifile.clear();
    ifile.seekg(origPosition);

    return count;
}

//extracts a line from ifile and stores it in cookieLines[index]
void CookieLogger::parseLine(std::ifstream& ifile, const int& index) {
    
    std::string temp;

    std::getline(ifile, temp, ',');
    //the name of the cookie is the first set of characters in the line until it reaches ','
    cookieLines[index].first = temp;

    std::getline(ifile, temp, 'T');
    //the date of the cookie is the next set of characters in the line until it reaches 'T'
    cookieLines[index].second = temp;
    
    std::getline(ifile, temp);
    //the rest of the line is unneeded, and therefore it is discarded
}

//finds the first member in cookieFrequency that has the specified date
//returns -1 if there is no date in cookieFrequency
int CookieLogger::findFirstDate(const std::string& date) {
    //can use binarySearch because cookieFrequency should be sorted by chronological order
    //since the cookie log file is sorted from most recent to least recent
    int founddate = binarySearch(0, logSize - 1, date);
    //however, we don't know if this is the first date in cookieFrequency
    //so we do this to find the first date in cookieFrequency
    while (founddate > 0 && cookieLines[founddate - 1].second == date) {
        founddate--;
    }
    return founddate;
}

//Uses binary search to find the location of any pair with cookieLines[index].second == date
int CookieLogger::binarySearch(int low, int high, const std::string& date) {
    if (low <= high) {
        int mid = (low + high) / 2;
        
        if (cookieLines[mid].second == date) {
            return mid;
        }
        
        //since cookieLines members with lower indexes are more recent,
        //their.second should be greater than cookieLines[mid].second
        if (cookieLines[mid].second < date) {
            return binarySearch(low, mid - 1, date);
        }

        //since cookieLines members with higher indexes are less recent,
        //their.second should be less than cookieLines[mid].second
        if (cookieLines[mid].second > date) {
            return binarySearch(mid + 1, high, date);
        }
    }
    return -1;
}

//adds a cookie from cookieLines into cookieFrequency
//returns true if it successfully does it
//returns false if it does not or the specified index is out of bounds or has a different date
const bool CookieLogger::AddCookie(const int& index, const std::string& date,
            std::pair<std::string, int>* cookieFrequency, int& cookieFrequencyNum) {

    if (index >= logSize || index < 0) {
        return false;
    }
    
    if (cookieLines[index].second == date) {
        
        for (int i = 0; i < cookieFrequencyNum; i++) {
            if (cookieFrequency[i].first == cookieLines[index].first) {
                //found a cookie in cookieFrequency with the same name as cookieLines[index]
                //therefore, we increment its frequency
                cookieFrequency[i].second++;
                return true;
            }
        }
        
        cookieFrequencyNum++;
        cookieFrequency[cookieFrequencyNum - 1].first = cookieLines[index].first;
        cookieFrequency[cookieFrequencyNum - 1].second = 1;

        return true;

    } else {
        return false;
    }
}

//logs the most active cookie(s) from cookieFrequency into ofile
void CookieLogger::logMostActive(const std::pair<std::string, int>* cookieFrequency,
            const int& cookieFrequencyNum, std::ofstream& ofile) const {
    
    int highestFrequency = 0;

    for (int i = 0; i < cookieFrequencyNum; i++) {
        if (cookieFrequency[i].second > highestFrequency) {
            highestFrequency = cookieFrequency[i].second;
        }
    }
    for (int i = 0; i < cookieFrequencyNum; i++ ) {
        if (cookieFrequency[i].second >= highestFrequency) {
            ofile << cookieFrequency[i].first << "\n";
            std::cout << cookieFrequency[i].first << "\n";
        }
    }
}