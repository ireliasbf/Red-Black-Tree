//created by WJN,2022/04/09
//
#ifndef RB_TREE_NODE_H
#define RB_TREE_NODE_H
template<typename T> class RB_Tree_Node{//定义红黑树类
public:
	RB_Tree_Node* left;
	RB_Tree_Node* right;
	RB_Tree_Node* father;
	T val;
	char color;
	RB_Tree_Node(T data);
	~RB_Tree_Node();
};
template<typename T>
RB_Tree_Node<T>::RB_Tree_Node(T data):left(nullptr), right(nullptr), father(nullptr), val(data), color('r'){}//插入节点默认为红色
template<typename T>
RB_Tree_Node<T>::~RB_Tree_Node<T>(){}
#endif
