#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;
struct BST {
	int key;
	int weight;
	BST* left;
	BST* right;
};
void search(BST* root, int key) {
	if (root->key != key) {
		if (root->key > key) {
			search(root->left, key);
		} else {
			search(root->right, key);
		}
	}
}
BST *standard(int**elm, int left, int right) {
	BST* root = new BST;
	if (left == right) {
		root->key = elm[left][0];
		root->weight = elm[left][1];
		root->left = NULL;
		root->right = NULL;
		return root;
	} else if (left > right) {
		root = NULL;
		return root;
	} else {
		int mid = (left + right) / 2;
		root->key = elm[mid][0];
		root->weight = elm[mid][1];
		root->left = standard(elm, left, mid - 1);
		root->right = standard(elm, mid + 1, right);
		return root;
	}
}
BST *dynamic_construct(int **root, int **input, int i, int j) {
	if (i > j) {
		return NULL;
	}
	BST *z = new BST;
	z->key = input[root[i][j] - 1][0];
	z->weight = input[root[i][j] - 1][1];
	z->left = dynamic_construct(root, input, i, root[i][j] - 1);
	z->right = dynamic_construct(root, input, root[i][j] + 1, j);
	return z;
}
BST *dynamic(int**input) {
	int **e, **w, **root;
	e = new int *[102];
	w = new int *[102];
	root = new int *[102];
	for (int i = 0; i < 102; i++) {
		e[i] = new int[102];
		w[i] = new int[102];
		root[i] = new int[102];
	}
	for (int i = 0; i <= 101; i++) {
		for (int j = 0; j <= 101; j++) {
			e[i][j] = 0;
			w[i][j] = 0;
			root[i][j] = 0;
		}
	}
	for (int i = 1; i <= 100; i++) {
		w[i][i] = input[i - 1][1];
		for (int j = i + 1; j <= 100; j++) {
			w[i][j] = w[i][j - 1] + input[j - 1][1];
		}
	}
	for (int l = 1; l <= 100; l++) {
		for (int i = 1; i <= 101 - l; i++) {
			int j = i + l - 1;
			e[i][j] = 999999999;
			for (int k = i; k <= j; k++) {
				int t = e[i][k - 1] + e[k + 1][j] + w[i][j];
				if (t < e[i][j]) {
					e[i][j] = t;
					root[i][j] = k;
				}
			}
		}
	}
	return dynamic_construct(root, input, 1, 100);
}
int main() {
	srand(time(0));
	clock_t begin, end;
	double time_spent;
	string line_a, line_b;
	ifstream infile_a, infile_b;
	infile_a.open("pa3a.txt");
	infile_b.open("pa3b.txt");
	if (infile_a.good()) {
		cout << "There's no problem opening the file pa3a.txt" << endl;
	} else {
		cerr << "There's problem opening the file pa3a.txt" << endl;
	}
	if (infile_b.good()) {
		cout << "There's no problem opening the file pa3b.txt" << endl;
	} else {
		cerr << "There's problem opening the file pa3b.txt" << endl;
	}
	int **a, **b;
	a = new int *[100];
	b = new int *[100];
	for (int i = 0; i < 100; i++) {
		a[i] = new int[2];
		b[i] = new int[2];
	}

	for (int line = 0; line < 100; line++) {
		getline(infile_a, line_a);
		getline(infile_b, line_b);
		stringstream s1(line_a), s2(line_b);
		int i1, i2, j1 = 0, j2 = 0;
		while (s1 >> i1) {
			a[line][j1] = i1;
			if (s1.peek() == ',') {
				s1.ignore();
			}
			j1++;
		}
		while (s2 >> i2) {
			b[line][j2] = i2;
			if (s2.peek() == ',') {
				s2.ignore();
			}
			j2++;
		}
	}
	//standard way: perfect balanced BST for pa3a.txt
	BST *root_a1 = standard(a, 0, 99);
	//standard way: perfect balanced BST for pa3b.txt
	BST *root_b1 = standard(b, 0, 99);
	//dynamic programming: optimal BST for pa3a.txt
	BST *root_a2 = dynamic(a);
	//dynamic programming: optimal BST for pa3b.txt
	BST *root_b2 = dynamic(b);
	// search the number
	begin = clock();
	for (int k=0; k<1000; k++){
	for (int i = 1; i <= 100; i++) {
		for (int j = 0; j < a[i - 1][1]; j++) {
			search(root_a1, i);

		}
	}
	}
	end = clock();
	time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
	cout << "standard for a:" << time_spent << endl;
	begin = clock();
	for (int k=0; k<1000; k++){
	for (int i = 1; i <= 100; i++) {
		for (int j = 0; j < a[i - 1][1]; j++) {
			search(root_a2, i);
		}
	}
	}
	end = clock();
	time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
	cout << "optimal for a:" << time_spent << endl;
	begin = clock();
	for (int k=0; k<1000; k++){
	for (int i = 1; i <= 100; i++) {
		for (int j = 0; j < b[i - 1][1]; j++) {
			search(root_b1, i);
		}
	}
	}
	end = clock();
	time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
	cout << "standard for b:" << time_spent << endl;
	begin = clock();
	for (int k=0; k<1000; k++){
	for (int i = 1; i <= 100; i++) {
		for (int j = 0; j < b[i - 1][1]; j++) {
			search(root_b2, i);
		}
	}
	}
	end = clock();
	time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
	cout << "optimal for b:"<< time_spent << endl;
	return 0;
}

