#include "functions.h"

int main() {
    int mode = 0;
    while (mode < 1 || mode > 3){
        printf("Do you you want to be the code cracker - Press 1\n"
               "Let the computer be the code cracker - Press 2\n"
               "Or let the computer play vs itself? - Press 3\n");
        cin >> mode;
        if (cin.fail())
        {
            printf("Please type in a number between 1 and 3 to select your mode.\n");
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    if (mode == 1){
        player_cpu();
    }
    else if (mode == 2){
        cpu_player();
    }
    else if (mode == 3){
        int loops;
        while(true) {
            printf("how many times?\n");
            cin >> loops;
            if (cin.fail() || loops <= 0)
            {
                printf("Please type in a number larger than 0.\n");
                cin.clear();
                cin.ignore();
            }
            if (loops > 0){
                break;
            }
        }
        for (int i = 0; loops > i; i++){
            cpu_cpu();
        }
    }
    return 0;
}