#include <iostream>
#include <vector>

using namespace std;

int N, K;
vector<int> holes;

bool covered(int l) {
    int cnt = 1, i = holes[0];
    for (int j=1; j<N; j++) {
        if (i + l <= holes[j]) {
            cnt++;
            i = holes[j];
        }
    }

    return cnt <= K;
}

int search() {
    int left = 1, right = holes.back() - holes.front() + 1;
    int result = right;
    while (left<=right) {
        int mid = (left+right)/2;
        if (covered(mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        } 
    }
    return result;
}

int main() {
    // Please write your code here.
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> K;
    holes.resize(N);

    for (int i=0; i<N; i++)
        cin >> holes[i];

    int min_len = search();

    cout << min_len << '\n';

    return 0;
}
