/*
原题链接：https://pintia.cn/problem-sets/1010070491934568448/problems/1040435498128044032

03-树1 树的同构 （25 分）
给定两棵树T1和T2。如果T1可以通过若干次左右孩子互换就变成T2，则我们称两棵树是“同构”的。例如图1给出的两棵树就是同构的，因为我们把其中一棵树的结点A、B、G的左右孩子互换后，就得到另外一棵树。
而图2就不是同构的。

现给定两棵树，请你判断它们是否是同构的。
输入格式:
输入给出2棵二叉树树的信息。对于每棵树，首先在一行中给出一个非负整数N (≤10)，即该树的结点数（此时假设结点从0到N−1编号）；随后N行，第i行对应编号第i个结点，
给出该结点中存储的1个英文大写字母、其左孩子结点的编号、右孩子结点的编号。如果孩子结点为空，则在相应位置上给出“-”。给出的数据间用一个空格分隔。
注意：题目保证每个结点中存储的字母是不同的。

输出格式:
如果两棵树是同构的，输出“Yes”，否则输出“No”。

输入样例1（对应图1）：
8
A 1 2
B 3 4
C 5 -
D - -
E 6 -
G 7 -
F - -
H - -
8
G - 4
B 7 6
F - -
A 5 1
H - -
C 0 -
D - -
E 2 -
输出样例1:
Yes
输入样例2（对应图2）：
8
B 5 7
F - -
A 0 3
C 6 -
H - -
D - -
G 4 -
E 1 -
8
D 6 -
B 5 -
E - -
H - -
C 0 2
G - 3
F - -
A 1 4
输出样例2:
No
*/

/*
二叉树的静态链表的实现
选择前序遍历
*/

#include <cstdio>
#include <vector>
#include <stack>
#include <exception>

using namespace std;


struct TreeNode
{
	TreeNode() : element(0), left(0), right(0) {};
	TreeNode(char element, char left, char right) {
		this->element = element;
		this->left = (left == '-') ? -1 : left-'0';
		this->right = (right == '-') ? -1 : right-'0';
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

public:
	vector<TreeNode> data;
	int start_idx;
	int size;
};

bool Isomerism(BinTree bt1, BinTree bt2);
bool Isomerism(BinTree bt1, int idx1, BinTree bt2, int idx2);

int main(int narg, const char ** args) {
	BinTree bt1, bt2;
	bt1.ReadInput();
	bt2.ReadInput();

	//bt1.ShowPreorder();
	//bt2.ShowPreorder();

	bool result = Isomerism(bt1, bt2);

	printf(result ? "Yes" : "No");

	return 0;
}

void BinTree::ReadInput() {
	data.clear();

	scanf("%d\n", &size);

	char element = 0, left = -1, right = -1;
	for (int i = 0; i<size; ++i) {
		scanf("%c %c %c\n", &element, &left, &right);
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
	vector<int> count(size,0);

	for (int i = 0; i<size; ++i) {
		TreeNode tmp = data[i];
		if (tmp.left<-1 || tmp.left >= size || tmp.left == i \
			|| tmp.right<-1 || tmp.right >= size || tmp.right == i) {
			ret = false;
			break;
		}
		if(tmp.left != -1)
			++count[tmp.left];
		if(tmp.right != -1)
			++count[tmp.right];
	}

	for (int i = 0; i<size; ++i) {
		if (count[i] == 0) {
			if(start_idx == -1)
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

bool Isomerism(BinTree bt1, BinTree bt2) {
	if (bt1.size != bt2.size)
		return false;
	if (bt1.size == 0)
		return true;

	return Isomerism(bt1, bt1.start_idx, bt2, bt2.start_idx);
}
bool Isomerism(BinTree bt1, int idx1, BinTree bt2, int idx2) {
	if (idx1 == -1 && idx2 == -1)
		return true;
	if (idx1 == -1 || idx2 == -1)
		return false;
	if (bt1.data[idx1].element != bt2.data[idx2].element)
		return false;

	int left1 = bt1.data[idx1].left;
	int right1 = bt1.data[idx1].right;
	int left2 = bt2.data[idx2].left;
	int right2 = bt2.data[idx2].right;
	return (Isomerism(bt1, left1, bt2, left2) && Isomerism(bt1, right1, bt2, right2))
		|| (Isomerism(bt1, left1, bt2, right2) && Isomerism(bt1, right1, bt2, left2));
}