#include <iostream>
#include <algorithm>
#include <string>
#include <tuple>
#include <iterator>
#include <random>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;
const int NUM_LEN = 4;

const string NUMBERS = "1234567890";

string generate_digits() {
    //**** Seed generation - AKA LITERAL BLACK MAGIC
    random_device r;
    seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
    mt19937 eng(seed);
    //Dupe NUMBERS (could probably just use NUMBERS directly, but this is more future proof in case we need to reuse it)
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
        if (guess.length() != NUM_LEN || guess.find_first_not_of(NUMBERS) != string::npos){
            cout << "invalid input\n";
            continue;
        }
        return guess;
    }
}

tuple<int, int> calculate_score(const string &answer, string guess){
    int bulls = 0, cows = 0;
    for (int i = 0; i != NUM_LEN; i++){
        if (answer.find(guess[i]) == i){
            ++bulls;
        }
        else if (answer.find(guess[i]) != string::npos){
            ++cows;
        }
    }
    return make_tuple(cows, bulls);
}

void high_score(int turns, const string &number){
    ofstream output;
    output.open("High_score.txt", ios_base::app);
    output << "Turns: " << turns << "\nNumber: " << number << "\n============\n";
    output.close();
}

bool check_dupe(string str)
{
    sort(str.begin(), str.end());
    return adjacent_find(str.begin(), str.end()) != str.end();
}

vector <string> generate_list(){
    vector<string> number_vector;
    for (int x = pow(10, NUM_LEN-1); x < pow(10, NUM_LEN); x++)
    {
        int temp;
        temp = x;
        if(!check_dupe(to_string(temp))) {
            number_vector.push_back(to_string(temp));
        }
    }
    return number_vector;
}

int main() {
    int cows = 0, bulls = 0, turn = 0;
    string answer = generate_digits();
    cout << answer << endl; //cheat to make it easier to test.
    while (bulls != NUM_LEN) {
        turn++;
        string guess = player_guess();
        tuple<int, int> de_tuple = calculate_score(answer, guess);
        cows = get<0>(de_tuple);
        bulls = get<1>(de_tuple);
        cout << "Turn:  " << turn << "\nCows:  " << cows << "\nBulls: " << bulls << endl;
    }
    cout << "You win!\n";
    high_score(turn, answer);
    generate_list();
    return 0;
}