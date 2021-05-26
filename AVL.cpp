#include <iostream>
#include <fstream>
using namespace std;

struct Node {
	int val;
	Node* left;
	Node* right;
	int height;

	Node(int x = 0) {
		val = x;
		left = nullptr;
		right = nullptr;
		height = 1;

	}
};

int getHeight(Node*& root) {
	if (root == nullptr) {
		return 0;
	}
	return root->height;
}

int balanceFactor(Node*& root) {
	if (root == nullptr) {
		return 0;
	}
	return getHeight(root->left) - getHeight(root->right);
}

Node* rightRotation(Node*& a) {
	Node* b = a->left;
	a->left = b->right;
	b->right = a;
	a->height = 1 + max(getHeight(a->right), getHeight(a->left));
	b->height = 1 + max(getHeight(b->right), getHeight(b->left));
	return b;
}

Node* leftRotation(Node*& a) {
	Node* b = a->right;
	a->right = b->left;
	b->left = a;
	a->height = 1 + max(getHeight(a->right), getHeight(a->left));
	b->height = 1 + max(getHeight(b->right), getHeight(b->left));
	return b;
}

void insert(Node*& root, int x) {
	if (root == nullptr) {
		root = new Node(x);
		return;
	}
	if (x < root->val) 
		insert(root->left, x);
	else if (x > root->val)
		insert(root->right, x);
	
	root->height = 1 + max(getHeight(root->left), getHeight(root->right));
	int bf = balanceFactor(root);

	if (bf > 1) {
		if (root->left->val > x)
			root = rightRotation(root);
		else {
			root->left	= leftRotation(root->left);
			root = rightRotation(root);
		}
	}
	else if (bf < -1) {
		if (root->right->val < x) {
			root = leftRotation(root);
		}
		else {
			root->right = rightRotation(root->right);
			root = leftRotation(root);
		}
	}
}

Node* getMin(Node* root) {
	if (root->left == nullptr)
		return root;
	return getMin(root->left);
}

Node* remove(Node* &root, int x) {
	if (root == nullptr) {
		return root;
	}
	else if (x < root->val) {
		root->left = remove(root->left, x);
	}
	else if (x > root->val)
		root->right = remove(root->right, x);
	else {
		if (root->left == nullptr) {
			Node* aux = root->right;
			root = nullptr;
			return aux;
		}
		else if (root->right == nullptr) {
			Node* aux = root->left;
			root = nullptr;
			return aux;
		}
		Node* aux = getMin(root->right);
		root->val = aux->val;
		root->right = remove(root->right, aux->val);
	}
	if (root == nullptr) {
		return root;
	}

	root->height = 1 + max(getHeight(root->left), getHeight(root->right));
	int bf = balanceFactor(root);

	if (bf > 1) {
		if (root->left->val > x) {
			root = rightRotation(root);
			return root;
		}
		else {
			root->left = leftRotation(root->left);
			root = rightRotation(root);
			return root;
		}
	}
	else if (bf < -1) {
		if (root->right->val < x) {
			root = leftRotation(root);
			return root;
		}
		else {
			root->right = rightRotation(root->right);
			root = leftRotation(root);
			return root;
		}
	}

}

void inorderBest(Node* root,int x,int y) {
	if (root != nullptr) {
		inorderBest(root->left, x, y);
		if (root->val >= x && root->val<=y) cout << root->val;
		inorderBest(root->right, x, y);
	}
}

void preorder(Node* root) {
	if (root == NULL) {
		return;
	}
	cout << root->val << ' ';
	preorder(root->left);
	preorder(root->right);
}

int main()
{
	Node* root = new Node(5);
	insert(root, 3);
	insert(root, 6);
	insert(root, 2);
	insert(root, 1);

	preorder(root);
	return 0;
}