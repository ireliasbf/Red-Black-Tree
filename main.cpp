#include<iostream>
#include<queue>
#include"RB_Tree.h"
#define T int
using namespace std;
void search(RB_Tree<T> tree);
int main() {
	RB_Tree<T> tree;
	vector<T> nums(10);
	for (int i = 0; i < nums.size(); ++i) nums[i] = i+1;
	for (int i = 0; i < nums.size(); i++) {
		tree.Insert(nums[i]);
	}
	vector<T> delnums={1,3,6,7,10};
	for (int i = 0; i < delnums.size(); ++i) {
		tree.Delete(delnums[i]);
	}
	search(tree);
	cout << tree.size();
}

void search(RB_Tree<T> tree) {
	if (tree.Root == nullptr) return;
	queue<RB_Tree_Node<T>*> qu;
	RB_Tree_Node<T>* p = tree.Root;
	qu.push(p);
	while (!qu.empty()) {
		int len = qu.size();
		for (int i = 0; i < len; i++) {
			p = qu.front();
			qu.pop();
			cout <<p->color<< p->val<<" ";
			if (p->left) qu.push(p->left);
			if (p->right) qu.push(p->right);
		}
		cout << endl;
	}
}