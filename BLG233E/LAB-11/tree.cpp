#include <iostream>
#include "tree.h"

using namespace std;

bool a = false;

void tree::createTree() {
	root = NULL;
	temp_recursive = 0;
	cout << "Enter the node number in Tree: ";
	int N;
	cin >> N;
	int *RandomArray = new int[N];
	int *check = new int[N];
	for (int i = 0;i < N;i++) {
		check[i] = 0;
	}
	for (int i = 0; i < N;) {
		int a = rand() % N;
		if (check[a] == 0) {
			check[a] = 1;
			RandomArray[i] = a;
			cout << a+1 << endl;
			i++;
		}
	}
	for (int i = 0;i < N;i++) {
		add(RandomArray[i] + 1);
	}
}

void tree::removeTree(node *p) {
	if (p) {
		if (p->left != NULL) {
			removeTree(p->left);
			p->left = NULL;
		}
		if (p->right != NULL) {
			removeTree(p->right);
			p->right = NULL;
		}
		delete p;
	}
}

void tree::add(int toadd) {  //Binary tree, Binary search tree de?il!!!!  (d-1) bo?ken (d)'ye eleman eklemez
	node *traverse, *newnode;
	traverse = root;
	int comparison;
	bool added = false;
	newnode = new node;
	newnode->number = toadd;
	newnode->left = NULL;
	newnode->right = NULL;
	if (root == NULL) {//first node being added
		root = newnode;
		return;
	}
	if (root->left == NULL) {
		root->left = newnode;
		return;
	}
	if (root->right == NULL) {
		root->right = newnode;
		return;
	}
    

	int l, r;
    
    while (findNumNode(traverse)>2) {
		temp_recursive = 0;
		l = findNumNode(traverse->left);
		temp_recursive = 0;
		r = findNumNode(traverse->right);
		temp_recursive = 0;
		if (l == r)
			traverse = traverse->left;
        else if (l == r + 1 && !traverse->right->left && !traverse->right->right) {
            traverse = traverse->left;
        } else
            traverse = traverse->right;
	}

	if (traverse->left == NULL) {
		traverse->left = newnode;
		return;
	}

	if (traverse->right == NULL) {
		traverse->right = newnode;
		return;
	}
}

void tree::printPostorder(node *nptr) {
	if (nptr) {
		printPostorder(nptr->left);
		printPostorder(nptr->right);
		cout << nptr->number << " ";
	}
}

void tree::printInorder(node *nptr) {
	if (nptr) {
		printInorder(nptr->left);
		cout << nptr->number << " ";
		printInorder(nptr->right);
	}
}

void tree::printPreorder(node *nptr) {
	if (nptr) {
		cout << nptr->number << " ";
		printPreorder(nptr->left);
		printPreorder(nptr->right);
	}
}

int tree::findNumNode(node* ptr) {
	if (ptr) {
		temp_recursive++;
		findNumNode(ptr->left);
		findNumNode(ptr->right);
	}
	return temp_recursive;
}

int tree::findNumLeaf(node* ptr) {
	if (ptr) {
		if (NULL == ptr->left && ! ptr->right) {
			temp_recursive++;
		}
		findNumLeaf(ptr->left);
		findNumLeaf(ptr->right);
	}
	return temp_recursive;
}

int tree::calculateSum(node *ptr) {
	if (ptr) {
		temp_recursive += ptr->number ;
		calculateSum(ptr->left);
		calculateSum(ptr->right);
	}
	return temp_recursive;
}

double tree::calculateAverage(node *ptr) {
	double sum = (double) calculateSum(ptr);
	temp_recursive = 0;
	double node_num = (double) findNumNode(ptr);
	temp_recursive = 0;
	return sum / node_num;
}

int tree::findMax(node* ptr) {
	if (ptr) {
		if (temp_recursive < ptr->number) {
			temp_recursive = ptr->number;
		}
		findMax(ptr->left);
		findMax(ptr->right);
	}
	return temp_recursive;
}

int tree::findMin(node* ptr) {
	if (ptr) {
		if (temp_recursive > ptr->number) {
			temp_recursive = ptr->number;
		}
		findMin(ptr->left);
		findMin(ptr->right);
	}
	return temp_recursive;
}

int tree::calculateDepth(node *ptr) {
	if (ptr) {
		if (ptr->left != NULL) {
			temp_recursive++;	
			calculateDepth(ptr->left);
		}
	}
	return temp_recursive;
}