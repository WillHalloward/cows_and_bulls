#include "functions.h"

int main() {
    int mode = 0;
    printf("Do you you want to be the code cracker - Press 1\n"
           "Let the computer be the code cracker - Press 2\n"
           "Or let the computer play vs itself? - Press 3\n");
    while(mode < 1 || mode > 3){
        cin >> mode;
        switch (mode){
            case 1: player_cpu(); break;
            case 2: cpu_player(); break;
            case 3:
                int loops;
                printf("How many times?\n");
                while(!(cin >> loops) || loops <= 0) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Error, please try again.\n";
                }
                for (int i = 0; loops > i; i++) {
                    cpu_cpu();
                }; break;
            default: printf("Please type in a number between 1 and 3 to select your mode.\n");
        }
        cin.clear();
        cin.ignore();
    }
}