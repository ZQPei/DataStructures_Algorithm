/*
原题链接：https://pintia.cn/problem-sets/1010070491934568448/problems/1037889290772254723

02-线性结构4 Pop Sequence （25 分）
Given a stack which can keep M numbers at most. Push N numbers in the order of 1, 2, 3, ..., N and pop randomly. You are supposed to tell if a given sequence of numbers is a possible pop sequence of the stack. For example, if M is 5 and N is 7, we can obtain 1, 2, 3, 4, 5, 6, 7 from the stack, but not 3, 2, 1, 7, 5, 6, 4.

Input Specification:
Each input file contains one test case. For each case, the first line contains 3 numbers (all no more than 1000): M (the maximum capacity of the stack), N (the length of push sequence), and K (the number of pop sequences to be checked). Then K lines follow, each contains a pop sequence of N numbers. All the numbers in a line are separated by a space.

Output Specification:
For each pop sequence, print in one line "YES" if it is indeed a possible pop sequence of the stack, or "NO" if not.

Sample Input:
5 7 5
1 2 3 4 5 6 7
3 2 1 7 5 6 4
7 6 5 4 3 2 1
5 6 4 3 7 2 1
1 7 6 5 4 3 2
Sample Output:
YES
NO
NO
YES
NO
*/

#include <cstdio>
#include <stack>

using namespace std;

bool IsPopSequence(int *seq, int length, int max_stack_length) {
	if (seq == nullptr || length <= 0 || max_stack_length <= 0)
		return false;

	stack<int> s;
	bool result = true;
	int i = 0;
	int val_to_push = 1;
	while (i<length) {
		while ((s.empty() || s.top() < seq[i]) && s.size()<max_stack_length) {
			s.push(val_to_push++);
		}

		int val_pop = s.top();
		s.pop();
		if (val_pop != seq[i++]) {
			result = false;
			break;
		}
	}

	return result;
}

int main() {
	int M, N, K;
	scanf("%d %d %d", &M, &N, &K);

	int *seq = new int[N];
	for (int i = 0; i<K; ++i) {
		for (int j = 0; j<N; ++j) {
			scanf("%d", seq + j);
		}

		bool result = IsPopSequence(seq, N, M);
		if (result)
			printf("YES\n");
		else
			printf("NO\n");
	}
	delete[] seq;

	return 0;
}
