
#include "render/render.h"

template<typename PointT>
struct Node
{
	PointT point;
	int id;
	Node<PointT>* left;
	Node<PointT>* right;

	Node(PointT point, int setId)
	:	point(point), id(setId), left(NULL), right(NULL)
	{}

	~Node()
	{
		delete left;
		delete right;
	}
};

template<typename PointT>
struct KdTree
{
	Node<PointT>* root;

	KdTree()
	: root(NULL)
	{}

	~KdTree()
	{
		delete root;
	}

	void insert(PointT point, int id)
	{

		// TODO: Fill in this function to insert a new point into the tree
		// the function should create a new node and place correctly with in the root 

		insert_recursive(&root, 0, point, id);

	}

	void insert_recursive(Node<PointT>** node, uint depth, PointT point, int id) {

		// At a null, insert the node.
		if (!*node)
			*node = new Node<PointT>(point, id);
		else {
			
            float point_value;
            float node_value;

            switch(depth%3){
                case 0:
                    point_value = point.x;
                    node_value  = (*node)->point.x;
                    break;
                case 1:
                    point_value = point.y;
                    node_value  = (*node)->point.y;
                    break;
                case 2:
                    point_value = point.z;
                    node_value  = (*node)->point.z;
                    break;       
            }


			if(point_value < node_value)
				insert_recursive( &((*node)->left), depth + 1, point, id);
			else
				insert_recursive( &((*node)->right), depth + 1, point, id);
		}

	}


	void recursive_search(PointT target, Node<PointT>* node, uint depth, float distanceTol, std::vector<int>& ids){

		if(node) {
			bool checkDim0 = (node->point.x>=(target.x-distanceTol)) && (node->point.x<=(target.x+distanceTol));
			bool checkDim1 = (node->point.y>=(target.y-distanceTol)) && (node->point.y<=(target.y+distanceTol));
            bool checkDim2 = (node->point.z>=(target.z-distanceTol)) && (node->point.z<=(target.z+distanceTol));
            

			if (checkDim0 && checkDim1 && checkDim2) {
				float difference0 = node->point.x - target.x;
				float difference1 = node->point.y - target.y;
                float difference2 = node->point.z - target.z;
				float distance = sqrt((difference0 * difference0) + (difference1 * difference1) + (difference2 * difference2));

				if(distance <= distanceTol)
					ids.push_back(node->id);
			}

            float dim_target_value;
            float dim_point_value;
            

            switch(depth%3){
                case 0:
                    dim_target_value = target.x;
                    dim_point_value = node->point.x;
                    break;
                case 1:
                    dim_target_value = target.y;
                    dim_point_value = node->point.x;
                    break;
                case 2:
                    dim_target_value = target.z;
                    dim_point_value = node->point.x;
                    break;       
            }

			if((dim_target_value - distanceTol) < dim_point_value)
				recursive_search(target, node->left, depth+1, distanceTol, ids);
			if((dim_target_value + distanceTol) > dim_point_value)
				recursive_search(target, node->right, depth+1, distanceTol, ids);
		}
	}

	// return a list of point ids in the tree that are within distance of target
	std::vector<int> search(PointT target, float distanceTol)
	{
		std::vector<int> ids;

		recursive_search(target, root, 0, distanceTol, ids);

		return ids;
	}
	

};




