/* \author Aaron Brown */
// Quiz on implementing kd tree

#include "../../render/render.h"


// Structure to represent node of kd tree
struct Node
{
	std::vector<float> point;
	int id;
	Node* left;
	Node* right;

	Node(std::vector<float> arr, int setId)
	:	point(arr), id(setId), left(NULL), right(NULL)
	{}

	~Node()
	{
		delete left;
		delete right;
	}
};

struct KdTree
{
	Node* root;

	KdTree()
	: root(NULL)
	{}

	~KdTree()
	{
		delete root;
	}

	void insert(std::vector<float> point, int id)
	{

		// TODO: Fill in this function to insert a new point into the tree
		// the function should create a new node and place correctly with in the root 

		insert_recursive(&root, 0, point, id);

	}

	void insert_recursive(Node** node, int depth, std::vector<float> point, int id) {

		// At a null, insert the node.
		if (*node==NULL)
			*node= new Node(point, id);
		else {
			
			int current_dimension = depth % 2; //get the current dimension to check. 

			if(point[current_dimension] < ((*node) -> point[current_dimension]))
				insert_recursive( &((*node) -> left), depth + 1, point, id);
			else
				insert_recursive( &((*node)->right), depth + 1, point, id);
		}

	}

	// return a list of point ids in the tree that are within distance of target
	std::vector<int> search(std::vector<float> target, float distanceTol)
	{
		std::vector<int> ids;
		return ids;
	}
	

};




