#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int k, m;
unordered_map<unsigned long long, int> pattern;

int main() {
    // Please write your code here.
    ios_base::sync_with_stdio(0); cin.tie(0);
    string digital_logic;
    cin >> digital_logic >> k >> m;
    int n = digital_logic.length();
    
    if (n < k) {
        cout << 0 << '\n';
        return 0;
    }

    unsigned long long hash_val = 0;
    unsigned long long base = 3;
    unsigned long long highest_power = 1;

    for (int i=0; i<k-1; i++) 
        highest_power *= base;
    for (int i=0; i<k; i++) 
        hash_val = hash_val * base + (digital_logic[i] - '0');
    
    pattern[hash_val]++;
    if (pattern[hash_val] >= m) {
        cout << 1 << '\n';
        return 0;
    }

    for (int i=k; i<n; i++) {
        hash_val = hash_val - (digital_logic[i-k] - '0') * highest_power;
        hash_val = hash_val * base + (digital_logic[i] - '0');
        pattern[hash_val]++;
        if (pattern[hash_val] >= m) {
            cout << 1 << '\n';
            return 0;
        }
    }
    cout << 0 << '\n';
    return 0;
}
