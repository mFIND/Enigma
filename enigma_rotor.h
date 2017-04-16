#include "enigma_rotor_list-of-connections.h"
template <class T>
class rotor{
    static const T ALPHA[26];
  public:
    rotor(std::array<const T,26> setting)
        :   code(setting)   {
            displayedValue = 'A';
            setupList();
    }
   ~rotor(){
        permut *temp = first;
        for(; temp->next != first ;){
            temp = temp->next;
            delete temp->prev;
        }
        temp->prev = NULL;
        temp->next = NULL;
        delete temp;
   }
    T A(T);
    T B(T);
    ///T fromAtoBside(T);
    ///T fromBtoAside(T);
    T getDisplay();
    void setupList();
    void setDisplay(T);
    void moveDisplay(int);
  private:
    std::array<const T, 26> code;
    T displayedValue;
    permut *first = NULL;
};

template <class T>
const T rotor<T>::ALPHA[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

template <class T>
void rotor<T>::setupList(){
permut *prev, *temp;
    int i;
    for(i = 0; i<26; i++){
        prev = temp;
        temp = new permut;
        if(!first){
            first = temp;
            first->next = first;
            first->prev = first;
        }else{
            first->prev = temp;
            prev->next = temp;
            temp->prev = prev;
            temp->next = first;
        }
        temp->a = ALPHA[i];
        temp->b = code[i];
    }
}

template <class T>
T rotor<T>::A(T current){
    permut *temp = first;
    for(int i = 0; i<26; i++){
        if(temp->a == current)
            break;
        temp = temp->next;
    }
    for(int shift = displayedValue - 'A'; shift > 0 ; shift--)
        temp = temp->next;
    return temp->b;
}
template <class T>
T rotor<T>::B(T current){
    permut *temp = first;
    for(int i = 0; i<26; i++){
        if(temp->b == current)
            break;
        temp = temp->next;
    }
    for(int shift = displayedValue - 'A'; shift > 0 ; shift--)
        temp = temp->prev;
    return temp->a;
}


template <class T>
T rotor<T>::getDisplay(){
    return displayedValue;
}
template <class T>
void rotor<T>::setDisplay(T current){
    displayedValue = current;
}
template <class T>
void rotor<T>::moveDisplay(int i){
    displayedValue += i;
    if(displayedValue > 'Z')
        displayedValue -= 26;
    if(displayedValue < 'A')
        displayedValue += 26;
    return;

}
