#include <iostream>
#include <algorithm>
#include <string>
#include <tuple>
#include <iterator>
#include <random>

using namespace std;
const int NUM_LEN = 4;

const string NUMBERS = "1234567890";

string generate_digits() {
    //**** Seed generation - AKA LITERAL BLACK MAGIC
    random_device r;
    seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
    mt19937 eng(seed);
    //Dupe NUMBERS
    string answer = NUMBERS;
    //shuffle and grab the first 4
    shuffle(answer.begin(), answer.end(), eng);
    answer = answer.substr(0, NUM_LEN);

    cout << "secret number generated\n";
    return answer;
}

string player_guess() {
    string guess;
    //loop until we get a valid answer.
    while(true) {
        cout << "Whats your guess?\n";
        getline(cin, guess);
        //Check if the input is as long as NUM_LEN and does not contain a letter.
        if (guess.length() != NUM_LEN || guess.find_first_not_of(NUMBERS) != string::npos){
            cout << "invalid input\n";
            continue;
        }
        return guess;
    }
}

tuple<int, int> calculate_score(string answer, string guess){
    int bulls = 0;
    int cows = 0;
    for (int i = 0; i != NUM_LEN; i++){
        int pos = answer.find(guess[i]);
        if (pos == i){
            ++bulls;
        }
        else if (pos != string::npos){
            ++cows;
        }
    }
    return make_tuple(cows, bulls);
}

int main() {
    int cows = 0, bulls = 0;
    string answer = generate_digits();
    cout << answer << endl; //cheat to make it easier to test.
    while (bulls != NUM_LEN) {
        string guess = player_guess();
        tuple<int, int> de_tuple = calculate_score(answer, guess);
        cows = get<0>(de_tuple);
        bulls = get<1>(de_tuple);
        cout << "Cows:  " << cows << "\nBulls: " << bulls << endl;
    }
    if (bulls == NUM_LEN) {
        cout << "You win!\n";
    }
    return 0;
}