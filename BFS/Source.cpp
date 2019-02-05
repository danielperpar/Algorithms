#include <iostream>
#include <vector>
#include <queue>

struct Node;
class Graph;
struct BFSTreeNode;
class BFSTree;
void BFS(Graph *graph, char targetNodeId, BFSTree *bfsTree);

int main(int argc, char **argv)
{
	Node *A = new Node('A');
	Node *B = new Node('B');
	Node *C = new Node('C');
	Node *D = new Node('D');
	Node *E = new Node('E');
	Node *F = new Node('F');
	Node *G = new Node('G');
	Node *H = new Node('H');

	Graph graph;

	graph.AddNode(A);
	graph.AddNode(B);
	graph.AddNode(C);
	graph.AddNode(D);
	graph.AddNode(E);
	graph.AddNode(F);
	graph.AddNode(G);
	graph.AddNode(H);

	graph.AddEdge(A, B);
	graph.AddEdge(A, E);
	graph.AddEdge(B, C);
	graph.AddEdge(B, F);
	graph.AddEdge(C, D);
	graph.AddEdge(C, G);
	graph.AddEdge(D, H);


	BFSTree bfsTree;
	BFS(&graph, 'D', &bfsTree);
	bfsTree.PrintBSFTreePath();

	getchar();
	return 0;
}

struct Node
{
	Node(char id) : mId(id) {}

	char mId;
	bool mVisited = false;
	int mIndex = 0;
};


class Graph
{
public:
	Graph() 
	{
		ResetAdjacencies(); 
	}

	~Graph() 
	{
		for (auto it = mGraphNodes.begin(); it != mGraphNodes.end(); ++it)
		{
			if (*it != nullptr)
			{
				delete(*it);
				*it = nullptr;
			}
		}
		mGraphNodes.clear();
	}

	void AddNode(Node *node)
	{
		if (mNumNodes == MAX_NODES)
		{
			std::cout << "max nodes number reached" << std::endl;
			return;
		}
		node->mIndex = mNumNodes;
		mGraphNodes.push_back(node);
		++mNumNodes;
	}

	void AddEdge(const Node *node1, const Node *node2)
	{
		mAdjacencies[node1->mIndex][node2->mIndex] = 1;
		mAdjacencies[node2->mIndex][node1->mIndex] = 1;
	}

	void ResetAdjacencies()
	{
		for (int i = 0; i < MAX_NODES; ++i)
		{
			for (int j = 0; j < MAX_NODES; ++j)
			{
				mAdjacencies[i][j] = 0;
			}
		}
	}

	bool IsAdjacent(const Node *node1, const Node *node2) const
	{
		if (mAdjacencies[node1->mIndex][node2->mIndex] == 1)
			return true;
		else
			return false;
	}

public:
	const static int MAX_NODES = 8;
	std::vector<Node*> mGraphNodes;
	int mAdjacencies[MAX_NODES][MAX_NODES];

private:
	int mNumNodes = 0;

};

struct BFSTreeNode
{
	
	BFSTreeNode(BFSTreeNode *parent, char id) : mParent(parent), mId(id){}
	BFSTreeNode *mParent = nullptr;
	char mId;
};

class BFSTree
{
public:
	BFSTree() {}
	~BFSTree() 
	{
		for (auto it = mBFSTree.begin(); it != mBFSTree.end(); ++it)
		{
			if (*it != nullptr)
			{
				delete *it;
				*it = nullptr;
			}
		}
		mBFSTree.clear();
	}

	BFSTreeNode *FindNode(char nodeId)
	{
		for (auto it = mBFSTree.begin(); it != mBFSTree.end(); ++it)
		{
			if ((*it)->mId == nodeId)
				return *it;
		}
		return nullptr;
	}

	void PrintBSFTreePath()
	{
		std::vector<char> output;

		BFSTreeNode *currentNode = mTargetNode;

		while (currentNode != nullptr)
		{
			output.push_back(currentNode->mId);
			currentNode = currentNode->mParent;
		}

		for (auto rit = output.rbegin(); rit != output.rend(); ++rit)
		{
			std::cout << *rit;
			std::cout << std::endl;
		}
	}

public:
	std::vector<BFSTreeNode*> mBFSTree;
	BFSTreeNode *mTargetNode = nullptr;
};

/**
* brief Breadth First Search algorithm with creation of the BFS tree for a target node
* param graph Graph to be traversed
* param targetNodeId Node to be searched
* param bfsTree BFSTree created using BFS
**/
void BFS(Graph *graph, char targetNodeId, BFSTree *bfsTree)
{
	std::queue<Node*> visitedNodes;

	for (auto it = graph->mGraphNodes.begin(); it != graph->mGraphNodes.end(); ++it)
	{
		if ((*it)->mVisited == false)
		{
			(*it)->mVisited = true;
			visitedNodes.push(*it);

			//add a copy of this node to the BFSTree
			BFSTreeNode *treeNode = new BFSTreeNode(nullptr, (*it)->mId);
			bfsTree->mBFSTree.push_back(treeNode);

			while (!visitedNodes.empty())
			{
				Node *frontNode = visitedNodes.front();

				//Found the target node
				if (frontNode->mId == targetNodeId)
				{
					bfsTree->mTargetNode =  bfsTree->FindNode(frontNode->mId);
					return;
				}

				BFSTreeNode *parent = bfsTree->FindNode(frontNode->mId);

				for (auto it = graph->mGraphNodes.begin(); it != graph->mGraphNodes.end(); ++it)
				{
					if (graph->IsAdjacent(frontNode, *it) && (*it)->mVisited == false)
					{
						(*it)->mVisited = true;
						visitedNodes.push(*it);

						//add new nodes to the BFSTree
						if (parent)
						{
							BFSTreeNode *node = new BFSTreeNode(parent, (*it)->mId);
							bfsTree->mBFSTree.push_back(node);
						}
					}
				}
				visitedNodes.pop();
			}
		}
	}
}
