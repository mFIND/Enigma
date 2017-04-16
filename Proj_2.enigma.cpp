#include "enigma_logic_interface.h"
#define P(x) std::cerr << #x " = " << (x) << std::endl

int main(){
    enigmaLogic *myEnigma;
    myEnigma = new enigmaLogic;
    myEnigma->starting();
    delete myEnigma;
    return 0;
}
