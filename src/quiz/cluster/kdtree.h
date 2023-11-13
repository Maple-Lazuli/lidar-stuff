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

		uint startingDepth = 0;

		insert_recursive(&root, startingDepth, point, id);

	}

	void insert_recursive(Node** node, uint depth, std::vector<float> point, int id) {

		// At a null, insert the node.
		if (*node==NULL)
			*node = new Node(point, id);
		else {
			
			if(point[depth%2] < ((*node)->point[depth%2]))
				insert_recursive( &((*node)->left), depth + 1, point, id);
			else
				insert_recursive( &((*node)->right), depth + 1, point, id);
		}

	}


	void recursive_search(std::vector<float> target, Node* node, uint depth, float distanceTol, std::vector<int>& ids){

		if(node != NULL) {
			bool checkDim0 = (node->point[0]>=(target[0]-distanceTol)) && (node->point[0]<=(target[0]+distanceTol));
			bool checkDim1 = (node->point[1]>=(target[1]-distanceTol)) && (node->point[1]<=(target[1]+distanceTol));

			if (checkDim0 && checkDim1) {
				float difference0 = node->point[0] - target[0];
				float difference1 = node->point[1] - target[1];
				float distance = sqrt((difference0 * difference0) + (difference1 * difference1));

				if(distance <= distanceTol)
					ids.push_back(node->id);
			}

			if((target[depth%2] - distanceTol) < node->point[depth%2])
				recursive_search(target, node->left, depth+1, distanceTol, ids);
			if((target[depth%2] + distanceTol) > node->point[depth%2])
				recursive_search(target, node->right, depth+1, distanceTol, ids);

		}
	}

	// return a list of point ids in the tree that are within distance of target
	std::vector<int> search(std::vector<float> target, float distanceTol)
	{
		std::vector<int> ids;

		uint startingDepth = 0;

		recursive_search(target, root, startingDepth, distanceTol, ids);

		return ids;
	}
	

};




