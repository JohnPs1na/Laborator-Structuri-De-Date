#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("abce.in");
ofstream fout("abce.out");
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

int getHeight(Node* root) {
	if (root == nullptr) {
		return 0;
	}
	return root->height;
}

int balanceFactor(Node* root) {
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
			root->left = leftRotation(root->left);
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
	Node* curr = root;
	while (curr->left) {
		curr = curr->left;
	}
	return curr;
}


void remove(Node*& root, int val) {
	if (root == NULL) {
		return;
	}

	if (val < root->val) remove(root->left, val);
	else if (val > root->val) remove(root->right, val);

	//am gasit nodul pe care trebuie sa il stergem
	else {
		if (root->left == NULL || root->right == NULL)
		{
			Node* aux = NULL;
			if (root->left != NULL) {
				aux = root->left;
			}
			else if (root->right != NULL) {
				aux = root->right;
			}
			if (aux == NULL) {
				aux = root;
				root = NULL;
			}
			else {
				*root = *aux;
			}

			delete aux;
		}
		else {
			Node* aux = getMin(root->right);
			root->val = aux->val;
			remove(root->right, aux->val);
		}
	}
	if (root == NULL) {
		return;
	}

	root->height = 1 + max(getHeight(root->left), getHeight(root->right));
	int balance = balanceFactor(root);
	int bfl = balanceFactor(root->left);
	int bfr = balanceFactor(root->right);

	if (balance > 1 && bfl >= 0)
		root = rightRotation(root);
	else if (balance > 1 && bfl < 0) {
		root->left = leftRotation(root->left);
		root = rightRotation(root);
	}
	else if (balance < -1 && bfr <= 0)
		root = leftRotation(root);
	else if (balance < -1 && bfr>0) {
		root->right = rightRotation(root->right);
		root = leftRotation(root);
	}
}

void seeIfIn(Node* root, int val) {
	if (root != nullptr) {
		if (root->val > val)
			seeIfIn(root->left, val);
		else if (root->val < val)
			seeIfIn(root->right, val);
		else
			fout << "1\n";
	}
	else fout << "0\n";
}
void inorderBest(Node* root,int x,int y) {
	if (root != nullptr) {
		inorderBest(root->left, x, y);
		if (root->val >= x && root->val<=y) fout << root->val<<' ';
		inorderBest(root->right, x, y);
	}
}

int succesor(Node* root, int val) {
	if (root == NULL)
		return 2147483647;
	if (root->val == val)
		return val;
	if (val < root->val) {
		return min(root->val, succesor(root->left, val));
	}
	else
		return succesor(root->right, val);
}

int predecesor(Node* root, int val) {

	if (root == NULL) {
		return -2147483648;
	}
	if (root->val == val) {
		return val;
	}
	if (val < root->val) {
		return predecesor(root->left, val);
	}
	else
		return max(root->val, predecesor(root->right, val));
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
	int n;
	fin >> n;

	int operatie;
	int x, y;
	Node* root = NULL;
	for (int i = 0; i < n; i++) {
		fin >> operatie;
		if (operatie == 1) {
			fin >> x;
			insert(root, x);
		}
		else if (operatie == 2) {
			fin >> x;
			remove(root, x);
		}
		else if (operatie == 3) {
			fin >> x;
			seeIfIn(root, x);
		}
		else if (operatie == 4) {
			fin >> x;
			fout << predecesor(root, x) << '\n';
		}
		else if (operatie == 5) {
			fin >> x;
			fout << succesor(root, x) << '\n';
		}
		else {
			fin >> x >> y;
			inorderBest(root, x, y);
			fout << '\n';
		}

	}
}
