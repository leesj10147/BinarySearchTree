#include <cstdio>
#include <vector>
#include <tuple>
#include <climits>
using namespace std;

class node 
{
public:
	int value;
	node* right;
	node* left;
	node* parent;
	node(int value, node* right, node* left, node* parent) : 
		value(value), right(right), left(left), parent(parent) {}
	~node()
	{
		if (right != 0)
			delete right;
		if (left != 0)
			delete left;
	}
};
void push(int a, node* root)
{
	if (root->value > a)
		if (root->left == 0)
			root->left = new node(a, 0, 0, root);
		else
			push(a, root->left);
	else
		if (root->right == 0)
			root->right = new node(a, 0, 0, root);
		else
			push(a, root->right);
}

//target의 value가 어느 노드로 이동했는지를 리턴한다.
node* binaryfi(node* target)
{
	if (target->right != 0 && target->left != 0 && target->right->value < target->left->value)
		swap(target->right, target->left);
	if (target->right != 0 && target->value > target->right->value)
	{
		swap(target->value, target->right->value);
		return binaryfi(target->right);
	}
	else if (target->left != 0 && target->value < target->left->value)
	{
		swap(target->value, target->left->value);
		return binaryfi(target->left);
	}
	return target;
}
void remove(node* target)
{
	target->value = INT_MIN;
	target = binaryfi(target);
	if (target->parent->left == target)
		target->parent->left = 0;
	else
		target->parent->right = 0;
	delete target;
}
void printAll(node* root)
{
	if (root == 0)
		return;
	printf("%d\n", root->value);
	printAll(root->left);
	printAll(root->right);
}
void BuildBinaryTree(node* root)
{
	if (root == 0)
		return;
	BuildBinaryTree(root->left);
	BuildBinaryTree(root->right);
	binaryfi(root);
}
node* find(int v, node* root)
{
	if (root == 0)
		return 0;
	if (root->value == v)
		return root;
	if (v > root->value)
		return find(v, root->right);
	return find(v, root->left);
}
void removeByNumber(int v, node* root)
{
	node* t = find(v, root);
	if (t == 0)
		return;
	remove(t);
}
bool isBinaryTree(node* root)
{
	if (root == 0)
		return true;
	int min, mid, max;

	if (root->left == 0)
		min = INT_MIN;
	else
		min = root->left->value;

	if (root->right == 0)
		max = INT_MAX;
	else
		max = root->right->value;

	mid = root->value;
	if (min <= mid && mid <= max && isBinaryTree(root->left) && isBinaryTree(root->right))
		return true;
	return false;
}

int main(void)
{
	node* root = new node(10, 0, 0, 0);
	int v;
	node* cur = root;
	while (~scanf("%d", &v))
	{
		cur->left = new node(v, 0, 0, cur);
		cur = cur->left;
	}
	BuildBinaryTree(root);
	if (isBinaryTree(root))
		printf("safe");
	delete root;
	return 0;
}