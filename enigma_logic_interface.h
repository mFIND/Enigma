#include "enigma_semi-graphic_interface.h"
#include "enigma_rotor.h"

class enigmaLogic{
    /// Tu jest alfabet, dla porownania:  {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'}
    std::array<const char, 26> set_I =   {{'E','K','M','F','L','G','D','Q','V','Z','N','T','O','W','Y','H','X','U','S','P','A','I','B','R','C','J'}};
    std::array<const char, 26> set_II =  {{'A','J','D','K','S','I','R','U','X','B','L','H','W','T','M','C','Q','G','Z','N','P','Y','F','V','O','E'}};
    std::array<const char, 26> set_III = {{'B','D','F','H','J','L','C','P','R','T','X','V','Z','N','Y','E','I','W','G','A','K','M','U','S','Q','O'}};
    std::array<const char, 26> set_IV =  {{'E','S','O','V','P','Z','J','A','Y','Q','U','I','R','H','X','L','N','F','T','G','K','D','C','M','W','B'}};
    std::array<const char, 26> set_V =   {{'V','Z','B','R','G','I','T','Y','U','P','S','D','N','H','L','X','A','W','M','J','Q','O','F','E','C','K'}};

    std::array<const char, 26> set_A =   {{'E','J','M','Z','A','L','Y','X','V','B','W','F','C','R','Q','U','O','N','T','S','P','I','K','H','G','D'}};
    std::array<const char, 26> set_B =   {{'Y','R','U','H','Q','S','L','D','P','X','N','G','O','K','M','I','E','B','F','Z','C','W','V','J','A','T'}};
    std::array<const char, 26> set_C =   {{'F','V','P','J','I','A','O','Y','E','D','R','Z','X','W','G','C','T','K','U','Q','S','B','N','M','H','L'}};
  public:
    enigmaLogic()
        {
            rotor_B = new rotor<char>(set_B);
        }
   ~enigmaLogic(){
            delete rotor_I;
            delete rotor_II;
            delete rotor_III;
            delete rotor_B;
        }
    void starting();
  private:
    void introduction();
    void menu();
    void setRotors();
    std::string getMessage(std::string);
    bool isValidMessage(std::string);
    void encrypt(std::string*);
    rotor<char>* insertRotors(int);
    void setKey();
    void displayingEnigma();
    void openFile(); /// wczytywania pliku jeszcze nie ma
    void saveFile();
    /// wskazniki na rotory tu wymienione od lewej do prawej
    rotor<char> *rotor_I;
    rotor<char> *rotor_II;
    rotor<char> *rotor_III;
    /// wskaznik na rotor odwracajacy, rotory A i C byly bardzo rzadko uzywane
    rotor<char> *rotor_B;
    /// komunikacja ze swiatem zewnetrznym: myCMD
    enigmaInterface myCMD;
};
