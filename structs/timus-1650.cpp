#include <iostream>
#include <unordered_map>
#include <set>
#include <map>
#include <string>

using namespace std;

int main() {
    unordered_map<string, pair<long long, string>> billionaires; // name -> (new worth, city)
    unordered_map<string, long long> city_sums;                  // city -> city_sum
    map<long long, set<string>> money_sums;                      // city_sum -> city
    map<string, int> amounts;                                    // city_name -> amount of max days

    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        string name, city;
        long long net_worth;
        cin >> name >> city >> net_worth;

        billionaires[name] = {net_worth, city};
        if (city_sums.find(city) != city_sums.end())
            city_sums[city] += net_worth;
        else
            city_sums[city] = net_worth;
    }

    for (auto& it : city_sums)
        money_sums[it.second].insert(it.first);

    int days; int registered;
    cin >> days >> registered;
    int prev_day = 0;
    for (int i = 0; i < registered; i++) {
        int day; string name; string city;
        cin >> day >> name >> city;

        for (auto& it : money_sums.begin()->second) { // update days with max amount
            if (amounts.find(it) != amounts.end()) amounts[it] += (day - prev_day);
            else amounts[it] = (day - prev_day);
        }

        long long start_city_sum = city_sums[billionaires[name].second];
        long long old_new_city_sum = start_city_sum - billionaires[name].first;

        city_sums[billionaires[name].second] -= billionaires[name].first;        // move net worth to city
        city_sums[city] += billionaires[name].first;

        for (auto& it : money_sums[start_city_sum])  // move money_sums to decremented value
            money_sums[old_new_city_sum].insert(it);
        money_sums[old_new_city_sum].erase(billionaires[name].second);
        money_sums.erase(start_city_sum);
    
        long long new_sum_value = city_sums[city];
        money_sums[new_sum_value].insert(city);

        prev_day = day;
    }

    for (auto& it : money_sums.begin()->second) {     // add rest days
        if (amounts.find(it) != amounts.end()) amounts[it] += (days - prev_day);
        else amounts[it] = (days - prev_day);
    }

    for (auto& it : amounts) {
        cout << it.first << " " << it.second;
    }
}