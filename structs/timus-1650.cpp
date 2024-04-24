#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <string>

using namespace std;

int main() {
    unordered_map<string, pair<long long, string>> billionaires;           // name -> (net worth, curr city)
    unordered_map<string, long long> city_sums;                            // city -> city_sum
    map<long long, unordered_set<string>, greater<>> money_sums;           // city_sum -> city
    map<string, int> amounts;                                              // city_name -> amount of max days

    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        string name, city;
        long long net_worth;
        cin >> name >> city >> net_worth;

        billionaires[name] = {net_worth, city};
        city_sums[city] += net_worth;
    }
    
    for (auto& it : city_sums)
        money_sums[it.second].insert(it.first);

    int days; int registered;
    cin >> days >> registered;
    int prev_day = 0;
    for (int i = 0; i < registered; i++) {
        int day; string name; string city;
        cin >> day >> name >> city;

        if (money_sums.begin()->second.size() == 1) {
            auto elem = money_sums.begin()->second.begin();
            amounts[*elem] += (day - prev_day);                                                                                    
        }

        long long start_city_sum = city_sums[billionaires[name].second];
        long long start_new_city_sum = start_city_sum - billionaires[name].first;

        city_sums[billionaires[name].second] -= billionaires[name].first;       // move net worth to city
        city_sums[city] += billionaires[name].first;

        money_sums[start_city_sum].erase(billionaires[name].second);    // move money_sums to decremented value
        if (money_sums[start_city_sum].size() == 0) money_sums.erase(start_city_sum);
        
        long long new_sum_value = city_sums[city];
        money_sums[new_sum_value].insert(city);

        money_sums[start_new_city_sum].insert(billionaires[name].second);
        billionaires[name].second = city;
        prev_day = day;                 
    }
    
    if (money_sums.begin()->second.size() == 1) {
        auto elem = money_sums.begin()->second.begin();
        amounts[*elem] += (days - prev_day);                                                                                    
    }
    
    for (auto& it : amounts) {
        cout << it.first << " " << it.second << endl;
    }
}

// 5
// Abramovich ABCD 15
// Deripaska abcd 10
// Potanin abcd 5
// Berezovsky ABCD 2
// Khodorkovsky Chita 1
// 25 9
// 1 Abramovich Anadyr
// 5 Potanin Courchevel
// 10 Abramovich abcd
// 11 Abramovich ABCD
// 11 Deripaska StPetersburg
// 15 Potanin Norilsk
// 20 Berezovsky Tbilisi
// 21 Potanin StPetersburg
// 22 Berezovsky ABCD