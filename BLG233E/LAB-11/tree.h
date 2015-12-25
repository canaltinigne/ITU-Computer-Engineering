#ifndef tree_H
#define tree_H

struct node {
	int number;
	node* left;
	node* right;
    node *next;
};

struct tree {
	node *root;
	void add(int);
	void createTree();
	void removeTree(node *);
	void printPostorder(node*);
	void printInorder(node*);
	void printPreorder(node*);
	int findNumNode(node *);
	int findNumLeaf(node*);
	int findMax(node *);
	int findMin(node*);
	int calculateDepth(node *);
	int calculateSum(node*);
	double calculateAverage(node *);

	int temp_recursive;
};
#endif // !tree


