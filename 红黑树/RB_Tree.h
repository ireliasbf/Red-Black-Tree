//created by WJN,2022/04/09
//
#ifndef RB_TREE_H
#define RB_TREE_H
#include "RB_Tree_Node.h"
template<typename T> class RB_Tree {
public:
	RB_Tree_Node<T>* Root;
	bool Insert(T data);
	bool Delete(T data);
	bool find(T data);
	int size();
	RB_Tree();
private:
	int num;
	RB_Tree_Node<T>* Insert_balance(RB_Tree_Node<T>* node);
	RB_Tree_Node<T>* Delete_balance(RB_Tree_Node<T>* node,char flag);
	void left_rotation(RB_Tree_Node<T>* node);
	void right_rotation(RB_Tree_Node<T>* node);	
};

template<typename T>//创建红黑树时根节点赋空值
RB_Tree<T>::RB_Tree() :Root(nullptr),num(0) {}

template<typename T>//插入函数，实现插入一个新结点并返回是否成功
bool RB_Tree<T>::Insert(T data){
	if (Root == nullptr) {//如果插入时树为空树，则直接插入根节点位置
		Root = new RB_Tree_Node<T>(data);
		Root->color = 'b';
		num++;
		return true;
	}
	RB_Tree_Node<T>* p = Root;
	while (true) {//找到应该插入的位置并插入一个红色结点p
		if (data == p->val) return false;
		else if(data < p->val) {
			if (p->left) p = p->left;
			else {
				RB_Tree_Node<T>* child = new RB_Tree_Node<T>(data);
				p->left = child;
				child->father = p;
				p = child;
				num++;
				break;
			}
		}
		else if (data > p->val) {
			if (p->right) p = p->right;
			else {
				RB_Tree_Node<T>* child = new RB_Tree_Node<T>(data);
				p->right = child;
				child->father = p;
				p = child;
				num++;
				break;
			}
		}
	}
	Insert_balance(p);
	return true;
}

template<typename T>//删除函数，实现删除一个结点并返回是否成功
bool RB_Tree<T>::Delete(T data){
	if (Root == nullptr) return false;//树空返回删除失败
	RB_Tree_Node<T>* N = Root;
	while (true) {//找到要删除的结点位置
		if (N == nullptr) return false;//找不到要删除的值，返回删除失败
		if (data > N->val) N = N->right;
		else if (data < N->val) N = N->left;
		else break;
	}
	if (N == Root) {//删除根节点
		if (N->left == nullptr && N->right == nullptr) {//树只有一个结点
			Root = nullptr;
			delete(N);
			num--;
			return true;
		}
		if (N->left) {
			RB_Tree_Node<T>* p = N->left;
			while (p->right) p = p->right;
			int tmp = p->val;
			Delete(p->val);
			N->val = tmp;
			return true;
		}
		else if (N->right) {
			RB_Tree_Node<T>* p = N->right;
			while (p->left) p = p->left;
			int tmp = p->val;
			Delete(p->val);
			N->val = tmp;
			return true;
		}
	}
	char flag = 'r';//flag标记当前结点是左孩子还是右孩子
	if (N == N->father->left) flag = 'l';
	if (N->left == nullptr && N->right == nullptr) {//删除结点无孩子
		if (N->color == 'r') {//删除结点为红，直接删除
			if (flag == 'l') N->father->left = nullptr;
			else N->father->right = nullptr;
			delete(N);
			num--;
			return true;
		}
		else {//删除结点为黑，需要平衡操作
			if (flag == 'l')N->father->left = nullptr;
			else N->father->right = nullptr;
			RB_Tree_Node<T>* P = N->father;
			delete(N);
			num--;
			Delete_balance(P,flag);
			return true;
		}
	}
	else if (N->left && N->right) {//删除结点有两个孩子，需要替换为前驱或后继结点，然后删除前驱或后继结点
		RB_Tree_Node<T>* p = N->left;
		while (p->right) p = p->right;
		int tmp = p->val;
		Delete(p->val);
		N->val = tmp;
		return true;
	}
	else {//删除结点有一个孩子，直接删除并把孩结点染黑并连到父节点上
		RB_Tree_Node<T>* child;
		if (N->left) child = N->left;
		else child = N->right;
		if (flag == 'r') N->father->right = child;
		else N->father->left = child;
		child->father = N->father;
		child->color = 'b';
		num--;
		delete(N);
		return true;
	}
}

template<typename T>//查找函数，找到返回成功，否则返回失败
bool RB_Tree<T>::find(T data) {
	if (Root == nullptr) return false;
	RB_Tree_Node<T>* p = Root;
	while (true) {
		if (p == nullptr) return false;
		if (p->val == data) return true;
		if (data > p->val) p = p->right;
		else if (data < p->val) p = p->left;
	}
}

template<typename T>//size()函数返回红黑树中非空结点数
int RB_Tree<T>::size() {
	return num;
}

template<typename T>//因插入导致红黑树不平衡时用此函数平衡红黑树
RB_Tree_Node<T>* RB_Tree<T>::Insert_balance(RB_Tree_Node<T>* node) {
	RB_Tree_Node<T>* N = node;
	if (N == Root) {//如果需要调整的是根节点，只需把根节点染黑
		N->color = 'b';
		return nullptr;
	}
	RB_Tree_Node<T>* P = N->father;//不是根节点必有父节点
	if (P->color == 'b')//父节点为黑，说明已经有序无需调整
		return nullptr;
	RB_Tree_Node<T>* GP = N->father->father;//父节点为红说明父节点不是根节点，必有祖父结点
	char flag = 'l';//flag标记父节点是左孩子还是右孩子
	RB_Tree_Node<T>* U = GP->right;
	if(P == GP->right) {
		flag = 'r';
		U = GP->left;
	}
	if (U&&U->color=='r'){//父红叔红 
		GP->color = 'r';
		P->color = 'b';
		U->color = 'b';
		return Insert_balance(GP);
	}
	if (flag=='l'&&N==P->left) {//父N同左
		GP->color = 'r';
		P->color = 'b';
		right_rotation(GP);
		return nullptr;
	}
	if(flag=='l'&&N == P->right) {//父左N右
		left_rotation(P);
		return Insert_balance(P);
	}
	if (flag=='r'&&N==P->right) {//父N同右
		GP->color = 'r';
		P->color = 'b';
		left_rotation(GP);
		return nullptr;
	}
	if (flag == 'r' && N == P->left) {//父右N左
		right_rotation(P);
		return Insert_balance(P);
	}
}

template<typename T>//因删除导致红黑树不平衡时用此函数平衡红黑树
RB_Tree_Node<T>* RB_Tree<T>::Delete_balance(RB_Tree_Node<T>* node,char flag) {
	RB_Tree_Node<T>* P = node;//传入的是父节点
	RB_Tree_Node<T>* N = P->left;//找到当前结点
	RB_Tree_Node<T>* S = P->right;//因为当前结点为黑，所以必有兄弟结点
	if (flag == 'r') {
		N = P->right;
		S = P->left;
	}
	if (S->color == 'b') {//兄弟结点为黑色
		if ((S->left == nullptr || S->left->color == 'b') && (S->right == nullptr || S->right->color == 'b')) {//兄弟结点子节点全黑
			if (P->color == 'r') {//父节点为红，则只需父节点染黑，兄弟结点染红
				S->color = 'r';
				P->color = 'b';
				return P;
			}
			if (P->color == 'b') {//父节点为黑，则把兄弟结点染红，递归到上一层
				S->color = 'r';
				flag = 'r';
				if (P == Root) return P;//父节点是根节点，则已经平衡成功，不需要递归
				if (P == P->father->left) flag = 'l';
				Delete_balance(P->father, flag);
			}
		}
		else if (flag == 'r') {//兄弟结点子节点不全黑，且S为左孩子
			if (S->left && S->left->color == 'r') {//SL红
				S->left->color = 'b';
				S->color = P->color;
				P->color = 'b';
				right_rotation(P);
				return P;
			}
			else {//SL黑
				S->right->color = 'b';
				S->color = 'r';
				left_rotation(S);
				Delete_balance(P, flag);
			}
		}
		else if (flag == 'l') {//兄弟结点子节点不全黑，且S为右孩子
			if (S->right && S->right->color == 'r') {//SR红
				S->right->color = 'b';
				S->color = P->color;
				P->color = 'b';
				left_rotation(P);
				return P;
			}
			else {//SR黑
				S->left->color = 'b';
				S->color = 'r';
				right_rotation(S);
				Delete_balance(P, flag);
			}
		}
	}
	else {//兄弟结点为红色
		if (flag == 'r') {//兄弟结点为左孩子
			S->color = 'b';
			P->color = 'r';
			right_rotation(P);
			Delete_balance(P, flag);
		}
		else {//兄弟结点为右孩子
			S->color = 'b';
			P->color = 'r';
			left_rotation(P);
			Delete_balance(P, flag);
		}
	}
}

template<typename T>//以传入结点为支点左旋
void RB_Tree<T>::left_rotation(RB_Tree_Node<T>* node) {
	RB_Tree_Node<T>* GP = node;
	RB_Tree_Node<T>* P = GP->right;
	RB_Tree_Node<T>* N = P->left;
	if (GP->father) {//如果祖父结点不是根节点，需要把父节点连到祖父节点的父节点上
		GP->father->right = P;
		P->father = GP->father;
	}
	else {//如果祖父节点是根节点，则把父节点设为根结点
		Root = P;
		P->father = nullptr;
	}
	GP->father = P;
	P->left = GP;
	GP->right = N;
	if(N) N->father = GP;
}

template<typename T>//以传入结点为支点右旋
void RB_Tree<T>::right_rotation(RB_Tree_Node<T>* node) {
	RB_Tree_Node<T>* GP = node;
	RB_Tree_Node<T>* P = GP->left;
	RB_Tree_Node<T>* N = P->right;
	if (GP->father) {//如果祖父结点不是根节点，需要把父节点连到祖父节点的父节点上
		GP->father->left = P;
		P->father = GP->father;
	}
	else {//如果祖父节点是根节点，则把父节点设为根结点
		Root = P;
		P->father = nullptr;
	}
	GP->father = P;
	P->right = GP;
	GP->left = N;
	if(N) N->father = GP;
}


#endif