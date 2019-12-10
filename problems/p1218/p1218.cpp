#include <iostream>
#include <stack>

using namespace std;


int main() {
	for (int tc = 1; tc <= 10; tc++) {
		stack<char> s;
		int N;
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			char ch;
			cin >> ch;
			if (s.empty()) {
				s.push(ch);
			}
			else {
				char top = s.top();
				if (top == '(') {
					if (ch == ')')
						s.pop();
					else
						s.push(ch);
				}
				else if (top == '[') {
					if (ch == ']')
						s.pop();
					else
						s.push(ch);
				}
				else if (top == '{') {
					if (ch == '}')
						s.pop();
					else
						s.push(ch);
				}
				else if (top == '<') {
					if (ch == '>')
						s.pop();
					else
						s.push(ch);
				}
				else
					s.push(ch);
			}
		}
		if (s.empty())
			cout << "#" << tc << " 1" << endl;
		else
			cout << "#" <<tc << " 0" << endl;
	}
	return 0;
}


