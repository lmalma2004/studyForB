#include <iostream>
#include <deque>
#define LEFT    'l'
#define RIGHT   'r'
#define UP      'u'
#define DOWN    'd'
using namespace std;
int T;
int N;
char S[6];
 
void merge(deque<int>& map, deque<int>& buffer, char direc) {
    if (buffer.front() == buffer.back()) {
        if (direc == LEFT)
            map.push_back(buffer.front() * 2);
        else if (direc == RIGHT)
            map.push_front(buffer.front() * 2);
        buffer.clear();
    }
    else {
        if (direc == LEFT)
            map.push_back(buffer.front());
        else if (direc == RIGHT)
            map.push_front(buffer.front());
        buffer.pop_front();
    }
}
void solve(deque<int> map[]) {
    if (S[0] == LEFT || S[0] == UP) {
        for (int i = 0; i < N; i++) {
            deque<int> buffer;
            int lineSize = map[i].size();
            for (int j = 0; j < lineSize; j++) {
                if (j < 2) {
                    buffer.push_back(map[i].front());
                    map[i].pop_front();
                    if (buffer.size() == 2)
                        merge(map[i], buffer, LEFT);
                    continue;
                }
                buffer.push_back(map[i].front());
                map[i].pop_front();
                if (buffer.size() == 2)
                    merge(map[i], buffer, LEFT);
            }
            while (!buffer.empty()) {
                map[i].push_back(buffer.front());
                buffer.pop_front();
            }
        }
    }
    else if (S[0] == RIGHT || S[0] == DOWN) {
        for (int i = 0; i < N; i++) {
            deque<int> buffer;
            int lineSize = map[i].size();
            for (int j = 0; j < lineSize; j++) {
                if (j < 2) {
                    buffer.push_back(map[i].back());
                    map[i].pop_back();
                    if (buffer.size() == 2)
                        merge(map[i], buffer, RIGHT);
                    continue;
                }
                buffer.push_back(map[i].back());
                map[i].pop_back();
                if (buffer.size() == 2)
                    merge(map[i], buffer, RIGHT);
            }
            while (!buffer.empty()) {
                map[i].push_front(buffer.front());
                buffer.pop_front();
            }
        }
    }
 
    //print
    if (S[0] == LEFT) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (map[i].empty()) {
                    printf("0 ");
                    continue;
                }
                cout << map[i].front() << " ";
                map[i].pop_front();
            }
            cout << endl;
        }
    }
    else if (S[0] == RIGHT) {
        for (int i = 0; i < N; i++) {
            int rowSize = map[i].size();
            for (int j = 0; j < N - rowSize; j++)
                printf("0 ");
            while (!map[i].empty()) {
                cout << map[i].front() << " ";
                map[i].pop_front();
            }
            cout << endl;
        }
    }
    else if (S[0] == UP) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (map[j].empty()) {
                    printf("0 ");
                    continue;
                }
                cout << map[j].front() << " ";
                map[j].pop_front();
            }
            cout << endl;
        }
    }
    else if (S[0] == DOWN) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int colSize = map[j].size();
                if (N - i == colSize) {
                    cout << map[j].front() << " ";
                    map[j].pop_front();
                }
                else
                    cout << "0 ";
            }
            cout << endl;
        }
    }
    //cout << endl;
}
int main() {
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++) {
        scanf("%d ", &N);
        scanf("%s ", S);
        deque<int> map[20];
        if (S[0] == LEFT || S[0] == RIGHT) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    int num;
                    scanf("%d", &num);
                    if (num != 0)
                        map[i].push_back(num);
                }
            }
        }
        else if (S[0] == UP || S[0] == DOWN) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    int num;
                    scanf("%d", &num);
                    if (num != 0)
                        map[j].push_back(num);
                }
            }
        }
 
        printf("#%d\n", tc);
        solve(map);
    }
    return 0;
}
