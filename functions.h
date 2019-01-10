//
// Created by Axel on 2019-01-09.
//

#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <algorithm>
#include <tuple>
#include <iterator>
#include <random>
#include <fstream>
#include <sstream>
#include <ctime>
#include <chrono>

using namespace std;

string generate_digits();
string player_guess();
string cpu_guess(vector<string> &list);
vector <string> generate_list();
bool check_dupe(string str);
void calculate_score(const string &answer, string guess, pair<int, int> &cb);
void high_score(int turns, const string &number, string mode);
void filter(const string &guess, pair<int, int> cows_bulls, vector<string> &list);
void player_cpu();
void cpu_player();
void cpu_cpu();

#endif //HEADER_H
