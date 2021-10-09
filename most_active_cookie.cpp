#include <iostream> //used for testing
#include <fstream> //used for parsing command lines

#include "CookieLogger.h"

int main(int argc, char* argv[]) {

    char parameter[2] = {'-', 'd'};

    if (argc != 4 || argv[2] == parameter) {
        std::cout << "Incorrect Arguments.\n";
        std::cout << "Must be appended with -d YYYY-MM-DD\n";
        return 1;
    }

    std::string date = argv[3];
    std::ifstream ifile(argv[1]);
    std::ofstream ofile("cookie_log_output");

    CookieLogger testFile(ifile);
    testFile.logPopularCookie(date, ofile);

    ifile.close();
    ofile.close();
    
    return 0;
}