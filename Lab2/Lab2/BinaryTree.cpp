#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <cstring>
#include <queue>
/*
Калитин А.В.
Ктбо1-6
Лабараторная 2 (3 вариант)
Дано бинарное дерево, содержащее числовые значения. Требуется заменить значение
каждой внутренней вершины суммой значений всех ее потомков.
*/
using namespace std;
struct Tree
{
	Tree* left, * right;
	int num;
	char pos[30];
};

Tree* initialization(Tree* root)
{
	FILE* inp = fopen("tree.txt", "r");
	char position[30];
	int numb;
	Tree* temp;
	root->left = NULL;
	root->right = NULL;
	fscanf(inp, "%s %d\n", root->pos, &root->num);
	while (!feof(inp))
	{
		Tree* newnode = new Tree;
		fscanf(inp, "%s %d\n", position, &numb);
		newnode->num = numb;
		newnode->left = NULL;
		newnode->right = NULL;
		strcpy(newnode->pos, position);
		temp = root;
		for (int i = 1; i < strlen(newnode->pos); i++)
		{
			if (newnode->pos[i] == 48)
			{
				if (temp->left)
					temp = temp->left;
				else {
					temp->left = newnode;
				}
			}
			else if (newnode->pos[i] == 49)
			{
				if (temp->right)
					temp = temp->right;
				else {
					temp->right = newnode;
				}
			}
		}
	}
	fclose(inp);
	cout << "Suссess\n";
	return root;
}

void show_tree(Tree* node)
{
	if (node)
	{
		show_tree(node->left);
		for (int i = 1; i < strlen(node->pos); i++)
			cout << " ";
		cout << node->pos << " " << node->num << endl;
		show_tree(node->right);
	}
}

int sum = 0;

int summ(Tree* node)
{
	if (node)
	{
		sum += node->num;
		summ(node->left);
		summ(node->right);
	}
	return sum;
}

void make_tree_correct(Tree* root)
{
	if (root)
	{
		root->num = summ(root) - root->num;
		sum = 0;
		make_tree_correct(root->left);
		make_tree_correct(root->right);
	}
}

int sum_without_recur(Tree* root)
{
	queue  <Tree*> steck1;
	steck1.push(root);
	int sum = 0;
	while (!steck1.empty())
	{
		Tree* node = steck1.front();
		steck1.pop();
		sum += node->num;
		if (node->left != NULL)
			steck1.push(node->left);
		if (node->right != NULL)
			steck1.push(node->right);
	}
	return sum - root->num;
}

void make_tree_correct_without_recur(Tree* root)
{
	queue  <Tree*> steck;
	steck.push(root);
	int sum = 0;
	while (!steck.empty())
	{
		Tree* node = steck.front();
		steck.pop();
		cout << node->pos << endl;
		node->num = sum_without_recur(node);
		if (node->left != NULL)
			steck.push(node->left);
		if (node->right != NULL)
			steck.push(node->right);
	}
}


int main()
{
	setlocale(LC_ALL, "Russian");
	Tree* root = new Tree;
	bool flag = 0, endl = 0;
	string command;
	cout << "1 - Initiolization\n2 - Print tree\n3 - Sum with recursion\n4 - Iterative sum\n";
	while (command != "6")
	{
		cin >> command;
		if (command == "1")
		{
			root = initialization(root);
			flag = 1;
		}
		if (command == "2")
		{
			show_tree(root);
			flag = 1;
		}
		if (command == "3")
		{
			make_tree_correct(root);
			cout << "Suссess\n";
			flag = 1;
		}
		if (command == "4")
		{
			make_tree_correct_without_recur(root);
			cout << "Suссess\n";
			flag = 1;
		}
		if (flag == 0)
		{
			cout << "Некорректная команда\n";
		}
		flag = 0;
	}
	return 0;
}
