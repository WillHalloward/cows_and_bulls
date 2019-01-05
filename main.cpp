#include <iostream>
#include <algorithm>
#include <tuple>
#include <iterator>
#include <random>
#include <fstream>
#include <sstream>
#include <ctime>
#include <chrono>

const int NUM_LEN = 4;
const std::string NUMBERS = "1234567890";

//shuffle NUMBERS and grab the first 4
std::string generate_digits() {
    std::string answer = NUMBERS;
    shuffle(answer.begin(), answer.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
    answer = answer.substr(0, NUM_LEN);
    std::cout << "secret number generated\n";
    return answer;
}

bool check_dupe(std::string str) {
    sort(str.begin(), str.end());
    return adjacent_find(str.begin(), str.end()) != str.end();
}

//currently not used, will be needed later.
std::string player_guess() {
    std::string guess;
    //loop until we get a valid answer.
    while(true) {
        std::cout << "Whats your guess?\n";
        getline(std::cin, guess);
        if (guess.length() != NUM_LEN ||
            guess.find_first_not_of(NUMBERS) != std::string::npos ||
            check_dupe(guess)){
            std::cout << "invalid input\n";
            continue;
        }
        return guess;
    }
}

bool calculate_score(const std::string &answer, std::string guess, std::pair<int, int> &cb){
    cb.first = 0, cb.second = 0;
    for (int i = 0; i != NUM_LEN; i++){
        if (answer.find(guess[i]) == i){
            cb.second++;
        }
        else if (answer.find(guess[i]) != std::string::npos){
            cb.first++;
        }
    }
    return cb.second == NUM_LEN;
}

std::string generate_guess(std::vector<std::string> &list){
    if( list.empty() ) return "";
    return list[rand() % list.size()];
}

void high_score(int turns, const std::string &number){
    std::ofstream output;
    output.open("High_score.txt", std::ios_base::app);
    output << "Turns: " << turns << "\nNumber: " << number << "\n============\n";
    output.close();
}

std::vector <std::string> generate_list(){
    std::vector<std::string> number_vector;
    for (int x = pow(10, NUM_LEN-2); x < pow(10, NUM_LEN)-1; x++)
    {
        //to make sure we include 0123, 0124, etc
        unsigned long long int number_of_zeros = NUM_LEN - std::to_string(x).length();
        std::string temp = std::string(number_of_zeros, '0').append(std::to_string(x));
        if(!check_dupe(temp)) {
            number_vector.push_back(temp);
        }
    }
    std::cout << number_vector.size() << " - Number of possible guesses.\n";
    return number_vector;
}

void filter(const std::string &guess, std::pair<int, int> cb, std::vector<std::string> &list){
    auto it = list.begin();
    std::pair<int, int> filter_cb;
    while(it != list.end()){
        calculate_score(*it, guess, filter_cb);
        if (filter_cb.first < cb.first || filter_cb.second < cb.second || *it == guess){
            list.erase(it);
        }
        else{
            it++;
        }
    }
    std::cout << list.size() << " - Number of possible guesses remaining\n";
}

int main() {
    std::pair <int, int> cows_bulls;
    int turn = 0;
    std::string answer = generate_digits();
    std::vector<std::string> list = generate_list();
    std::cout << answer << " - The secret answer.\n"; //cheat to make it easier to test.
    while (!list.empty()) {
        turn++;
        //std::string guess = player_guess();
        std::string guess = generate_guess(list);
        std::cout << guess << " - Guess\n";
        if (calculate_score(answer, guess, cows_bulls)) {
            break;
        }
        std::cout << "Turn:  " << turn << "\nCows:  " << cows_bulls.first << "\nBulls: " << cows_bulls.second << std::endl;
        filter(guess, cows_bulls, list);
        std::cout << "========================================\n";
    }
    if (cows_bulls.second == NUM_LEN) {
        std::cout << "You win! the secret number was: " << answer << "\nIt took: " << turn << " turns\n";
        high_score(turn, answer);
    }
    else if (list.empty()){
        std::cout << "ye filthy cheat\n";
    }
    else{
        std::cout << "something went horribly wrong\n";
    }
    return 0;
}