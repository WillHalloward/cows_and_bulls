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

long long int seed2 = std::chrono::system_clock::now().time_since_epoch().count();

std::string generate_digits() {
    //Dupe NUMBERS (could probably just use NUMBERS directly, but this is more future proof in case we need to reuse it)

    std::string answer = NUMBERS;
    //shuffle and grab the first 4
    shuffle(answer.begin(), answer.end(), std::default_random_engine(seed2));
    answer = answer.substr(0, NUM_LEN);
    std::cout << "secret number generated\n";
    return answer;
}

bool check_dupe(std::string str)
{
    sort(str.begin(), str.end());
    return adjacent_find(str.begin(), str.end()) != str.end();
}

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

void calculate_score(const std::string &answer, std::string guess, int &bulls, int &cows){
    cows = 0, bulls = 0;
    for (int i = 0; i != NUM_LEN; i++){
        if (answer.find(guess[i]) == i){
            ++bulls;
        }
        else if (answer.find(guess[i]) != std::string::npos){
            ++cows;
        }
    }
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
    std::cout << "Generating a list of possible guesses with " << NUM_LEN << " digits\n";
    std::cout << "Generating a list of possible guesses between " << pow(10, NUM_LEN-1) << " and " << pow(10, NUM_LEN)-1 << "\n";
    for (int x = pow(10, NUM_LEN-2); x < pow(10, NUM_LEN)-1; x++)
    {
        //to make sure we include 0123, 0124, etc
        unsigned int number_of_zeros = NUM_LEN - std::to_string(x).length();
        std::string temp = std::string(number_of_zeros, '0').append(std::to_string(x));
        if(!check_dupe(temp)) {
            number_vector.push_back(temp);
        }
    }
    std::cout << number_vector.size() << " - Number of possible guesses.\n";
    return number_vector;
}

void filter(std::string guess, int cows, int bulls, std::vector<std::string> &list){
    for (int i = 0; i < list.size(); i++){
        std::string str = list[i];
        int bull_counter = 0;
        int cow_counter = 0;
//        std::cout << str << "\n" << guess << "\n";
        if (str == guess){
            list.erase(list.begin() + i);
            std::cout << "removed - " << str << "\n";
            i--;
            continue;
        }
        //std::cout << str.size() << "\n" << str << "\n";
        for (int j = 0; j != NUM_LEN; j++){
            if (str.find(guess[j]) == j && bull_counter < bulls){
                bull_counter++;
            }
            else if (str.find(guess[j]) != std::string::npos && cow_counter < cows){
                cow_counter++;
            }
        }
        if (bull_counter < bulls || cow_counter < cows){
            //std::cout << list[i] << "\n";
            list.erase(list.begin() + i);
            std::cout << "removed - " << str << "\n";
            i--;
        }

    }
//    for (auto i = list.begin(); i != list.end(); ++i)
//        std::cout << *i << ' ';
//    std::cout << "\n";
    std::cout << list.size() << " - Number of possible guesses remaining\n";
}

int main() {
    int cows = 0, bulls = 0, turn = 0;
    std::string answer = generate_digits();
    std::vector<std::string> list = generate_list();
    std::cout << answer << " - The secret answer.\n"; //cheat to make it easier to test.
    while (bulls < NUM_LEN && !list.empty()) {
        turn++;
        //std::string guess = player_guess();
        std::string guess = generate_guess(list);
        std::cout << guess << " - Guess\n";
        calculate_score(answer, guess, bulls, cows);
        if (bulls == NUM_LEN){
            break;
        }
        std::cout << "Turn:  " << turn << "\nCows:  " << cows << "\nBulls: " << bulls << std::endl;
        filter(guess, cows, bulls, list);
    }
    if (bulls == NUM_LEN) {
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