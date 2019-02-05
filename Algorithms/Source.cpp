#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>

/**	
	Algorithms from the book Introduction to the Designs and Analysis of Algorithms by Anany Levitin
**/
struct Point2D;
struct Node;

void PrintArray(const std::vector<int>& array);
void SelectionSort(std::vector<int> &array);
void BubbleSort(std::vector<int> &array);
int SequentialSearch2(std::vector<int> &array, int key);
int BruteForceStringMatch(const std::string &text, const std::string &pattern);
int Min(float a, float b);
float BruteForceClosestPair(const std::vector<Point2D>& points);
void  DepthFirstSearch(std::stack<Node*> &stack);
void CreateDFSTree(std::vector<Node*> &graph);
Node *CreateBFSTree(Node *start, Node *end);
void PrintShortestPath(Node *start, Node *end);

int main()
{
	Node a('a'), b('b'), c('c'), d('d'), e('e'), f('f'), g('g');
	a.AddAdjacencies({ &b, &c, &d });
	b.AddAdjacencies({ &a, &f, &g });
	c.AddAdjacencies({ &a, &e });
	d.AddAdjacencies({ &a, &e });
	e.AddAdjacencies({ &d, &c });
	f.AddAdjacencies({ &b, &g });
	g.AddAdjacencies({ &b, &f });

	std::vector<Node*> graph = { &a, &b, &c, &d, &e, &f, &g };
	CreateDFSTree(graph);

	std::cin.get();
	return 0;
}

void PrintArray(const std::vector<int>& array)
{
	for(const int element : array)
	{
		std::cout << element << " ";
	}
	std::cout << std::endl;
}

//Sorts in nondecreasing order
void SelectionSort(std::vector<int> &array)
{
	int min = 0;
	for (int i = 0; i < array.size() - 1; ++i)
	{
		min = i;
		for (int j = i + 1; j < array.size(); ++j)
		{	
			if (array[j] < array[min])
			{
				min = j;
			}
		}
		int temp = array[i];
		array[i] = array[min];
		array[min] = temp;
	}
}

//Sorts in nondecreasing order
void BubbleSort(std::vector<int> &array)
{
	for (int i = 0; i < array.size() - 1; ++i)
	{
		for (int j = 0; j < array.size() - 1 - i; ++j)
		{
			if (array[j + 1] < array[j])
			{
				int temp = array[j];
				array[j] = array[j+1];
				array[j + 1] = temp;
			}
		}
	}
}

int SequentialSearch2(std::vector<int> &array, int key)
{
	int length = array.size();
	array.push_back(key);
	int i = 0;

	while (array[i] != key)
	{
		++i;
	}

	array.erase(array.end() - 1);

	if (i < length)
		return i;
	else
		return -1;
}

int BruteForceStringMatch(const std::string &text, const std::string &pattern)
{
	int iMax = text.size() - pattern.size();

	for (int i = 0; i < iMax; ++i)
	{
		int j = 0;
		while (j < pattern.size() && pattern[j] == text[i + j])
		{
			++j;
		}

		if (j == pattern.size())
			return i;
	}
	return -1;
}

struct Point2D
{
	float x, y;
	Point2D(float x, float y) : x(x), y(y) {}
};

int Min(float a, float b)
{
	if (a < b)
		return a;
	else
		return b;
}


float BruteForceClosestPair(const std::vector<Point2D>& points)
{
	float d = 100;
	int size = points.size();
	for (int i = 0; i < size-2; ++i)
	{
		for (int j = i + 1; j <= size-1; ++j)
		{
			float x2 = (points[i].x - points[j].x) * (points[i].x - points[j].x);
			float y2 = (points[i].y - points[j].y) * (points[i].y - points[j].y);
			d = Min(d, x2 + y2);
		}
	}
	return d;
}

struct Node
{
	char mName;
	int mCount = 0;
	std::vector<Node*> mAdjacencies;
	Node *mParent = nullptr;

	Node(char name) : mName(name){}

	void AddAdjacencies(const std::initializer_list<Node*> &adj)
	{
		mAdjacencies = adj;
	}
};

void  DepthFirstSearch(std::stack<Node*> &stack)
{
	static int count = 0;

	Node *node = stack.top();
	if (node->mCount == 0)
	{
		node->mCount = ++count;
		std::cout << node->mName << " ";

		for (Node *node : node->mAdjacencies)
		{
			if (node->mCount == 0)
			{
				stack.push(node);
				DepthFirstSearch(stack);
			}
		}
		stack.pop();
	}
	
}

void CreateDFSTree(std::vector<Node*> &graph)
{
	std::stack<Node*> stack;
	stack.push(graph[0]);

	for (Node* node : graph)
	{
		if (node->mCount == 0)
		{
			DepthFirstSearch(stack);
		}
	}
}

Node *CreateBFSTree(Node *start, Node *end)
{
	static int count = 1;
	std::queue<Node*> nodes;

	start->mCount = count;
	nodes.push(start);

	while (!nodes.empty())
	{
		Node *front = nodes.front();
		for (Node *adj : front->mAdjacencies)
		{
			if (adj->mCount == 0)
			{
				adj->mCount = ++count;
				adj->mParent = front;
				if (adj->mName == end->mName)
				{
					return adj;
				}
				nodes.push(adj);
			}
		}
		nodes.pop();
	}
}

void PrintShortestPath(Node *start, Node *end)
{
	Node *currentNode = end;
	while (currentNode->mParent != nullptr)
	{
		std::cout << currentNode->mName << " <- ";
		currentNode = currentNode->mParent;
	}
	std::cout << start->mName << std::endl;
}

