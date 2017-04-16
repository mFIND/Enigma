#include "enigma_semi-graphic_interface.h"

void enigmaInterface::print(std::string toPrint){
    std::cout<<toPrint;
}
void enigmaInterface::print(char toPrint){
    std::cout<<toPrint;
}
void enigmaInterface::print(int toPrint){
    std::cout<<toPrint;
}
void enigmaInterface::getFromUser(std::string *toGet){
    getline(std::cin,*toGet);
}
void enigmaInterface::getFromUser(int *toGet){
    std::cin>>*toGet;
}
void enigmaInterface::printEnigma(const char a, const char b, const char c){
    clearScreen();
    std::cout<<"==== USTAWIENIE WIRNIKOW ====\n";
    std::cout<<"\n";
    std::cout<<"  A /\\    C /\\    E /\\\n";
    std::cout<<"    __      __      __\n";
    std::cout<<"   /  \\    /  \\    /  \\\n";
    std::cout<<"   |"<<a<<" |    |"<<b<<" |    |"<<c<<" |\n";
    std::cout<<"   \\__/    \\__/    \\__/\n";
    std::cout<<"\n";
    std::cout<<"  B \\/    D \\/    F \\/\n";
    std::cout<<"\n";
}
void enigmaInterface::help(){
    print("=== OPCJE ===\n");
    print("KEY - ustawia klucz wiadomosci\n");
    print("TEXT - pobiera od uzytkownika tekst do za-/od- szyfrowania\n");
    print("SAVE - szyfruje wiadomosc a nastepnie zapisuje ja w pliku\n");
    print("OPEN - wczytuje wiadomosc z pliku\n");
    print("HELP - wyswietla te opcje\n");
    print("CLEAR - czysci ekran\n");
    print("Q/EXIT - konczy prace programu\n");
}
void enigmaInterface::clearScreen(){
#ifdef __linux__
    system("clear");
#elif defined(_WIN32) || defined(WIN32)
    system("cls");
#else
    puts("OS not completely supported!");
#endif
}
char enigmaInterface::myGetChar(){
#ifdef __linux__
	/// *************************************
    /// odpowniednik getch() z windowsa na linuxa,
    /// dziala poprzez bawienie sie flagami konsoli w trakcie trwania dzialania programu
	/// source: http://stackoverflow.com/questions/7469139/what-is-equivalent-to-getch-getche-in-linux
	/// *************************************
    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    printf("%c\n",buf);
    return buf;
#elif defined(_WIN32) || defined(WIN32)
    return getch();
#else
    return getchar();
#endif
}
