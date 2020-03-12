/*
原题链接: https://pintia.cn/problem-sets/1010070491934568448/problems/1040435498128044033

03-树2 List Leaves （25 分）
Given a tree, you are supposed to list all the leaves in the order of top down, and left to right.

Input Specification:
Each input file contains one test case. For each case, the first line gives a positive integer N (≤10) which is the total number of nodes in the tree
-- and hence the nodes are numbered from 0 to N−1. Then N lines follow, each corresponds to a node, and gives the indices of the left and right children of the node.
If the child does not exist, a "-" will be put at the position. Any pair of children are separated by a space.

Output Specification:
For each test case, print in one line all the leaves' indices in the order of top down, and left to right. There must be exactly one space between any adjacent numbers,
and no extra space at the end of the line.

Sample Input:
8
1 -
- -
0 -
2 7
- -
- -
5 -
4 6
Sample Output:
4 1 5
*/

/*
与上一题类似，用静态链表构建出树，然后按顺序找到叶子结点，顺序是从上到下，从左到右，即不同层的叶子结点，先输出上面的，同一层的叶子结点，从左到右。
方法1：可以考虑选择层序遍历方式，层序遍历需要用到队列。
方法2：也可以考虑先用前序遍历，记录下每个叶结点以及对应的层数。
考虑用方法1，顺便练一下队列,队列考虑用动态数组来表示。
*/

#include <cstdio>
#include <vector>
#include <stack>
#include <queue>
#include <exception>

using namespace std;


struct TreeNode
{
	TreeNode() : element(0), left(0), right(0) {};
	TreeNode(char element, char left, char right) {
		this->element = element;
		this->left = (left == '-') ? -1 : left - '0';
		this->right = (right == '-') ? -1 : right - '0';
	};
	~TreeNode() {};

	char element;
	char left;
	char right;
};

class BinTree
{
public:
	BinTree() : start_idx(-1), size(0) {};
	~BinTree() {};

	void ReadInput();
	bool SecurityCheck();
	void ShowPreorder(int idx = -2);
	void ShowInorder(int idx = -2);
	void PrintLeaves();

public:
	vector<TreeNode> data;
	int start_idx;
	int size;
};



int main(int narg, const char ** args) {
	BinTree bt;

	bt.ReadInput();

	bt.PrintLeaves();
	
	return 0;
}

void BinTree::ReadInput() {
	data.clear();

	scanf("%d\n", &size);

	char element = 0, left = -1, right = -1;
	for (int i = 0; i<size; ++i) {
		element = i;
		scanf("%c %c\n", &left, &right);
		data.push_back(TreeNode(element, left, right));
	}

	if (!SecurityCheck())
		throw new exception();
}

bool BinTree::SecurityCheck() {
	if (data.size() != size)
		return false;

	if (size == 0)
		return true;

	// 检查输入是否一个正确的二叉树
	// 可能出现错误的情况
	// 1. left right越界
	// 2. 找不到根节点或者找不到头节点
	// 3. 多个头节点或者超过三个子节点
	// 4. 指向自己
	bool ret = true;
	vector<int> count(size, 0);

	for (int i = 0; i<size; ++i) {
		TreeNode tmp = data[i];
		if (tmp.left<-1 || tmp.left >= size || tmp.left == i \
			|| tmp.right<-1 || tmp.right >= size || tmp.right == i) {
			ret = false;
			break;
		}
		if (tmp.left != -1)
			++count[tmp.left];
		if (tmp.right != -1)
			++count[tmp.right];
	}

	for (int i = 0; i<size; ++i) {
		if (count[i] == 0) {
			if (start_idx == -1)
				start_idx = i;
			else {
				ret = false;
				break;
			}
		}
		else if (count[i]>2) {
			ret = false;
			break;
		}
	}

	int i = 0;
	stack<int> s;
	s.push(start_idx);
	while (!s.empty() & i<size) {
		int idx = s.top();
		s.pop();

		TreeNode tmp = data[idx];
		if (tmp.right != -1)
			s.push(tmp.right);
		if (tmp.left != -1)
			s.push(tmp.left);
		++i;
	}
	if (!s.empty()) {
		ret = false;
	}

	return ret;
}

void BinTree::ShowPreorder(int idx) {
	if (idx == -1)
		return;

	if (idx == -2)
		idx = start_idx;

	printf("%c ", data[idx].element);
	ShowPreorder(data[idx].left);
	ShowPreorder(data[idx].right);

	if (idx == -2)
		printf("\n");
}
void BinTree::ShowInorder(int idx) {
	if (idx == -1)
		return;

	if (idx == -2)
		idx = start_idx;

	ShowInorder(data[idx].left);
	printf("%c ", data[idx].element);
	ShowInorder(data[idx].right);

	if (idx == -2)
		printf("\n");
}

void BinTree::PrintLeaves() {
	if (size <= 0)
		return;

	queue<int> q;
	vector<int> leaves_list;
	q.push(start_idx);
	while (!q.empty()) {
		int idx = q.front();
		q.pop();
		TreeNode tmp = data[idx];
		if (tmp.left == -1 && tmp.right == -1)
			leaves_list.push_back(tmp.element);
		
		if (tmp.left != -1)
			q.push(tmp.left);
		if (tmp.right != -1)
			q.push(tmp.right);
	}
	
	for (vector<int>::iterator it = leaves_list.begin(); it != leaves_list.end(); ++it) {
		if (it == leaves_list.begin())
			printf("%d", *it);
		else
			printf(" %d", *it);
	}
}