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

template<typename T>//���������ʱ���ڵ㸳��ֵ
RB_Tree<T>::RB_Tree() :Root(nullptr),num(0) {}

template<typename T>//���뺯����ʵ�ֲ���һ���½�㲢�����Ƿ�ɹ�
bool RB_Tree<T>::Insert(T data){
	if (Root == nullptr) {//�������ʱ��Ϊ��������ֱ�Ӳ�����ڵ�λ��
		Root = new RB_Tree_Node<T>(data);
		Root->color = 'b';
		num++;
		return true;
	}
	RB_Tree_Node<T>* p = Root;
	while (true) {//�ҵ�Ӧ�ò����λ�ò�����һ����ɫ���p
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

template<typename T>//ɾ��������ʵ��ɾ��һ����㲢�����Ƿ�ɹ�
bool RB_Tree<T>::Delete(T data){
	if (Root == nullptr) return false;//���շ���ɾ��ʧ��
	RB_Tree_Node<T>* N = Root;
	while (true) {//�ҵ�Ҫɾ���Ľ��λ��
		if (N == nullptr) return false;//�Ҳ���Ҫɾ����ֵ������ɾ��ʧ��
		if (data > N->val) N = N->right;
		else if (data < N->val) N = N->left;
		else break;
	}
	if (N == Root) {//ɾ�����ڵ�
		if (N->left == nullptr && N->right == nullptr) {//��ֻ��һ�����
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
	char flag = 'r';//flag��ǵ�ǰ��������ӻ����Һ���
	if (N == N->father->left) flag = 'l';
	if (N->left == nullptr && N->right == nullptr) {//ɾ������޺���
		if (N->color == 'r') {//ɾ�����Ϊ�죬ֱ��ɾ��
			if (flag == 'l') N->father->left = nullptr;
			else N->father->right = nullptr;
			delete(N);
			num--;
			return true;
		}
		else {//ɾ�����Ϊ�ڣ���Ҫƽ�����
			if (flag == 'l')N->father->left = nullptr;
			else N->father->right = nullptr;
			RB_Tree_Node<T>* P = N->father;
			delete(N);
			num--;
			Delete_balance(P,flag);
			return true;
		}
	}
	else if (N->left && N->right) {//ɾ��������������ӣ���Ҫ�滻Ϊǰ�����̽�㣬Ȼ��ɾ��ǰ�����̽��
		RB_Tree_Node<T>* p = N->left;
		while (p->right) p = p->right;
		int tmp = p->val;
		Delete(p->val);
		N->val = tmp;
		return true;
	}
	else {//ɾ�������һ�����ӣ�ֱ��ɾ�����Ѻ����Ⱦ�ڲ��������ڵ���
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

template<typename T>//���Һ������ҵ����سɹ������򷵻�ʧ��
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

template<typename T>//size()�������غ�����зǿս����
int RB_Tree<T>::size() {
	return num;
}

template<typename T>//����뵼�º������ƽ��ʱ�ô˺���ƽ������
RB_Tree_Node<T>* RB_Tree<T>::Insert_balance(RB_Tree_Node<T>* node) {
	RB_Tree_Node<T>* N = node;
	if (N == Root) {//�����Ҫ�������Ǹ��ڵ㣬ֻ��Ѹ��ڵ�Ⱦ��
		N->color = 'b';
		return nullptr;
	}
	RB_Tree_Node<T>* P = N->father;//���Ǹ��ڵ���и��ڵ�
	if (P->color == 'b')//���ڵ�Ϊ�ڣ�˵���Ѿ������������
		return nullptr;
	RB_Tree_Node<T>* GP = N->father->father;//���ڵ�Ϊ��˵�����ڵ㲻�Ǹ��ڵ㣬�����游���
	char flag = 'l';//flag��Ǹ��ڵ������ӻ����Һ���
	RB_Tree_Node<T>* U = GP->right;
	if(P == GP->right) {
		flag = 'r';
		U = GP->left;
	}
	if (U&&U->color=='r'){//������� 
		GP->color = 'r';
		P->color = 'b';
		U->color = 'b';
		return Insert_balance(GP);
	}
	if (flag=='l'&&N==P->left) {//��Nͬ��
		GP->color = 'r';
		P->color = 'b';
		right_rotation(GP);
		return nullptr;
	}
	if(flag=='l'&&N == P->right) {//����N��
		left_rotation(P);
		return Insert_balance(P);
	}
	if (flag=='r'&&N==P->right) {//��Nͬ��
		GP->color = 'r';
		P->color = 'b';
		left_rotation(GP);
		return nullptr;
	}
	if (flag == 'r' && N == P->left) {//����N��
		right_rotation(P);
		return Insert_balance(P);
	}
}

template<typename T>//��ɾ�����º������ƽ��ʱ�ô˺���ƽ������
RB_Tree_Node<T>* RB_Tree<T>::Delete_balance(RB_Tree_Node<T>* node,char flag) {
	RB_Tree_Node<T>* P = node;//������Ǹ��ڵ�
	RB_Tree_Node<T>* N = P->left;//�ҵ���ǰ���
	RB_Tree_Node<T>* S = P->right;//��Ϊ��ǰ���Ϊ�ڣ����Ա����ֵܽ��
	if (flag == 'r') {
		N = P->right;
		S = P->left;
	}
	if (S->color == 'b') {//�ֵܽ��Ϊ��ɫ
		if ((S->left == nullptr || S->left->color == 'b') && (S->right == nullptr || S->right->color == 'b')) {//�ֵܽ���ӽڵ�ȫ��
			if (P->color == 'r') {//���ڵ�Ϊ�죬��ֻ�踸�ڵ�Ⱦ�ڣ��ֵܽ��Ⱦ��
				S->color = 'r';
				P->color = 'b';
				return P;
			}
			if (P->color == 'b') {//���ڵ�Ϊ�ڣ�����ֵܽ��Ⱦ�죬�ݹ鵽��һ��
				S->color = 'r';
				flag = 'r';
				if (P == Root) return P;//���ڵ��Ǹ��ڵ㣬���Ѿ�ƽ��ɹ�������Ҫ�ݹ�
				if (P == P->father->left) flag = 'l';
				Delete_balance(P->father, flag);
			}
		}
		else if (flag == 'r') {//�ֵܽ���ӽڵ㲻ȫ�ڣ���SΪ����
			if (S->left && S->left->color == 'r') {//SL��
				S->left->color = 'b';
				S->color = P->color;
				P->color = 'b';
				right_rotation(P);
				return P;
			}
			else {//SL��
				S->right->color = 'b';
				S->color = 'r';
				left_rotation(S);
				Delete_balance(P, flag);
			}
		}
		else if (flag == 'l') {//�ֵܽ���ӽڵ㲻ȫ�ڣ���SΪ�Һ���
			if (S->right && S->right->color == 'r') {//SR��
				S->right->color = 'b';
				S->color = P->color;
				P->color = 'b';
				left_rotation(P);
				return P;
			}
			else {//SR��
				S->left->color = 'b';
				S->color = 'r';
				right_rotation(S);
				Delete_balance(P, flag);
			}
		}
	}
	else {//�ֵܽ��Ϊ��ɫ
		if (flag == 'r') {//�ֵܽ��Ϊ����
			S->color = 'b';
			P->color = 'r';
			right_rotation(P);
			Delete_balance(P, flag);
		}
		else {//�ֵܽ��Ϊ�Һ���
			S->color = 'b';
			P->color = 'r';
			left_rotation(P);
			Delete_balance(P, flag);
		}
	}
}

template<typename T>//�Դ�����Ϊ֧������
void RB_Tree<T>::left_rotation(RB_Tree_Node<T>* node) {
	RB_Tree_Node<T>* GP = node;
	RB_Tree_Node<T>* P = GP->right;
	RB_Tree_Node<T>* N = P->left;
	if (GP->father) {//����游��㲻�Ǹ��ڵ㣬��Ҫ�Ѹ��ڵ������游�ڵ�ĸ��ڵ���
		GP->father->right = P;
		P->father = GP->father;
	}
	else {//����游�ڵ��Ǹ��ڵ㣬��Ѹ��ڵ���Ϊ�����
		Root = P;
		P->father = nullptr;
	}
	GP->father = P;
	P->left = GP;
	GP->right = N;
	if(N) N->father = GP;
}

template<typename T>//�Դ�����Ϊ֧������
void RB_Tree<T>::right_rotation(RB_Tree_Node<T>* node) {
	RB_Tree_Node<T>* GP = node;
	RB_Tree_Node<T>* P = GP->left;
	RB_Tree_Node<T>* N = P->right;
	if (GP->father) {//����游��㲻�Ǹ��ڵ㣬��Ҫ�Ѹ��ڵ������游�ڵ�ĸ��ڵ���
		GP->father->left = P;
		P->father = GP->father;
	}
	else {//����游�ڵ��Ǹ��ڵ㣬��Ѹ��ڵ���Ϊ�����
		Root = P;
		P->father = nullptr;
	}
	GP->father = P;
	P->right = GP;
	GP->left = N;
	if(N) N->father = GP;
}


#endif