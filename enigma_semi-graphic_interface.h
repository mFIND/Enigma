#include <iostream>
#include <array>
#include <string>
#include <fstream>

#ifdef __linux__
  #include <termios.h>
  #include <unistd.h>
#elif defined(_WIN32) || defined(WIN32)
  #include <conio.h>   /// getch()
#else
  puts("OS not completely supported!");
#endif

class enigmaInterface{
  public:
    void print(std::string);
    void print(char);
    void print(int);
    void getFromUser(std::string *);
    void getFromUser(int *);
    void printEnigma(char, char, char);
    void clearScreen();
    void help();
    char myGetChar();
};
