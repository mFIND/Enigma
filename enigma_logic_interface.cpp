#include "enigma_logic_interface.h"

void enigmaLogic::starting(){
    introduction();
    setRotors();
    myCMD.clearScreen();
    menu();
}
inline void enigmaLogic::introduction(){
    myCMD.print("Witaj w programie ENIGMA!\n");
    myCMD.print("Ten program sluzy do symulacji dzialania enigmy, zeby wybrac rodzaj enigmy, prosze wybrac odpowiednie wirniki.\n");
    myCMD.print("Domyslny klucz wiadomosci to 'AAA'.\n");
    myCMD.print("Obracanie wirnikow przy wyborze klucza wymaga tylko nacisniecia klawiszy - wirnik automatycznie sie obroci.\n");
    myCMD.print("Oznaczenia ktora litera obraca dany wirnik sa obok strzalek nad i pod wirnikami.\n");
    myCMD.print("Zeby wpisac komende, wpisujemy ja, a nastepnie klikamy enter.\n");
    myCMD.print("\n");
    myCMD.print("W przypadku jakich kolwiek problemow z programem prosze pisac pod adres:\n");
    myCMD.print("mat_fin@interia.eu\n");
    myCMD.print("\n");
    myCMD.print("===================\n");
}
void enigmaLogic::menu(){
    myCMD.help();
    std::string Command;
    for(;;){
        myCMD.print("$> ");
        myCMD.getFromUser(&Command);
        for(int i = 0;Command[i];i++)
            Command[i] = toupper(Command[i]);
        if(Command == "KEY"){setKey(); myCMD.clearScreen(); myCMD.help(); continue;}
        if(Command == "TEXT"){myCMD.print(getMessage(Command)); myCMD.print('\n'); continue;}
        if(Command == "SAVE"){saveFile(); continue;}
        if(Command == "OPEN"){openFile(); continue;}
        if(Command == "HELP"){myCMD.help(); continue;}
        if(Command == "CLEAR"){myCMD.clearScreen(); continue;}
        if(Command == "EXIT" || Command == "Q"){break;}
        if(Command == ""){continue;}
        myCMD.print("Nie rozpoznano komendy. Wpisz \"HELP\" zeby wyswietlic wszystkie opcje.\n");
    }
}
void enigmaLogic::setRotors(){
    myCMD.print("Wybierz ktore trzy wirniki chcesz wlozyc do maszyny, od lewej do prawej:\n");
    int rotor;
    int firstChoice = 0, secondChoice = 0;
    for(int i = 0; i < 3;){
        myCMD.print("Nr.:  ");
        for(int j = 1; j < 6; j++){
            if(j != firstChoice && j != secondChoice){
                myCMD.print(j);
                myCMD.print("  ");
            }
        }
        myCMD.print("\n");
        for(;;){
            myCMD.getFromUser(&rotor);
            if(rotor != firstChoice && rotor != secondChoice && rotor >= 1 && rotor <= 5){
                if(firstChoice == 0){
                    firstChoice = rotor;
                    rotor_III = insertRotors(rotor);
                    i++;
                    break;
                }
                if(secondChoice == 0){
                    secondChoice = rotor;
                    rotor_II = insertRotors(rotor);
                    i++;
                    break;
                }
                rotor_I = insertRotors(rotor);
                i++;
                break;
            } else {
                myCMD.print("Ten rotor juz zostal wstawiony lub taki nie istnieje! Wybierz inny:\n");
            }
        }
    }
}
inline rotor<char>* enigmaLogic::insertRotors(int i){
    switch(i){
        case 1:
            return new rotor<char>(set_I);
        case 2:
            return new rotor<char>(set_II);
        case 3:
            return new rotor<char>(set_III);
        case 4:
            return new rotor<char>(set_IV);
        case 5:
            return new rotor<char>(set_V);
        default:
            return NULL;
    }
}
void enigmaLogic::setKey(){
    char option;
    for(;;){
        displayingEnigma();
        myCMD.print("Ustaw kod Twojej wiadomosci za pomoca liter A-F. Litera Q zatwierdza klucz.\n");
        option = toupper(myCMD.myGetChar());
        switch(option){
            case 'A':
                rotor_III->moveDisplay(1);    break;
            case 'B':
                rotor_III->moveDisplay(-1);   break;
            case 'C':
                rotor_II->moveDisplay(1);   break;
            case 'D':
                rotor_II->moveDisplay(-1);  break;
            case 'E':
                rotor_I->moveDisplay(1);  break;
            case 'F':
                rotor_I->moveDisplay(-1); break;
            case 'Q':
                return;
            default:
                displayingEnigma();
        }
    }
}
std::string enigmaLogic::getMessage(std::string message){
    bool validMessage = 1;
    myCMD.print("Podaj wiadomosc:\n");
    myCMD.getFromUser(&message);
    validMessage = isValidMessage(message);
    if(validMessage){
        for(int i = 0; message[i]; i++)
            message[i] = toupper(message[i]);
        encrypt(&message);
        displayingEnigma();
        return message;
    }
    return "Z powodu bledow twoja wiadomosc nie zostala zakodowana!\n";
}
inline void enigmaLogic::openFile(){
    myCMD.print("Podaj nazwe pliku z wiadomoscia:\n");
    std::string fileNameAndMessage;
    myCMD.getFromUser(&fileNameAndMessage);
    std::ifstream myFile;
    myFile.open (fileNameAndMessage);
    {
        do{
        getline(myFile,fileNameAndMessage);
        } while (fileNameAndMessage == "");
        myFile.close();
    }
    if(isValidMessage(fileNameAndMessage)){
        for(int i = 0; fileNameAndMessage[i]; i++)
            fileNameAndMessage[i] = toupper(fileNameAndMessage[i]);
        encrypt(&fileNameAndMessage);
        displayingEnigma();
        myCMD.print(fileNameAndMessage);
        myCMD.print('\n');
    } else {
        myCMD.print("Nie udalo sie odczytaj poprawnie pliku.\n");
    }
}
inline void enigmaLogic::saveFile(){
    myCMD.print("Podaj nazwe pliku wynikowego:\n");
    std::string fileName;
    myCMD.getFromUser(&fileName);
    std::ofstream myFile;
    myFile.open (fileName);
    myFile << getMessage(fileName);
    myFile.close();
    myCMD.print("Zapis wiadomosci do pliku zakonczony.\n");
}
void enigmaLogic::encrypt(std::string *message){
    for(int i = 0; (*message)[i]; i++){
        /// wykonanie wszystkich danej litery
        /// ->A oznacza przejscie z prawej na lewa strone rotora
        (*message)[i] = rotor_I->A((*message)[i]);
        (*message)[i] = rotor_II->A((*message)[i]);
        (*message)[i] = rotor_III->A((*message)[i]);
        /// rotor_B jest symetryczny: rotor_B->A == rotor_B->B
        (*message)[i] = rotor_B->A((*message)[i]);
        /// ->B oznacza przejscie z lewej na prawa strone rotora
        (*message)[i] = rotor_III->B((*message)[i]);
        (*message)[i] = rotor_II->B((*message)[i]);
        (*message)[i] = rotor_I->B((*message)[i]);
        /// przesuwanie wirnikow, prawego po kazdym uderzeniu klawisza, srodkowego co 26 uderzen klawisza, lewego co 26*26 uderzen klawisza
        rotor_I->moveDisplay(1);
        if(i%26 == 25)
            rotor_II->moveDisplay(1);
        if(i%676 == 675)
            rotor_III->moveDisplay(1);
    }
}
bool enigmaLogic::isValidMessage(std::string message){
    for(int i = 0; message[i]; i++){
        if(message[i] == ' '){
            myCMD.print("W ENIGMIE nie uzywano spacji!\n");
            return 0;
        }
        if(message[i] == ','){
            myCMD.print("W ENIGMIE nie uzywano przecinkow! Zamiast tego uzywano litery X!\n");
            return 0;
        }
        if(message[i] == '.'){
            myCMD.print("W ENIGMIE nie uzywano kropek! Zamiast tego uzywano litery X!\n");
            return 0;
        }
        if(message[i] == '?'){
            myCMD.print("W ENIGMIE nie uzywano znakow zapytania! Zamiast tego uzywano frazy FRAGE lub FRAQ!\n");
            return 0;
        }
        if(message[i] == '!'){
            myCMD.print("W ENIGMIE nie uzywano wykrzyknikow!\n");
            return 0;
        }
        if(isdigit(message[i])){
            myCMD.print("W ENIGMIE nie uzywano cyfr!\n");
            return 0;
        }
    }
    return 1;
}
inline void enigmaLogic::displayingEnigma(){
    myCMD.printEnigma(rotor_III->getDisplay(),rotor_II->getDisplay(),rotor_I->getDisplay());
}
