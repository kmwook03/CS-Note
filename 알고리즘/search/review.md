## 삽질

```cpp
#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    // Please write your code here.
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N, K, idx;
    cin >> N >> K;

    while (cin >> idx);

    bool found = false;
    for (int i=1; i<=idx; i++) {
        if (i*K > N) {
            cout << i << '\n';
            found = true;
            break;
        }
    }

    if (!found) {
        for (int i=1; i<=idx; i++) {
            if (i*K >= idx) {
                cout << i << '\n';
                break;
            }
        }
    }

    return 0;
}
```
