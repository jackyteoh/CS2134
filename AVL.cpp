#include <iostream>
#include <ctime>

using namespace std;

template <class T>
class AVL;

template <class T>
class AVLNode{
	AVLNode<T>* parent, *left, *right;
	int height;
	T data;
public:
	friend class AVL < T >;
	AVLNode(const T& newdata = T(), AVLNode<T>* newparent = nullptr, AVLNode<T>* newleft = nullptr, AVLNode<T>* newright = nullptr) :
		data(newdata), parent(newparent), left(newleft), right(newright), { height(calcHeight()); }
	void calcHeight(){
		int leftHeight = -1;
		int rightHeight = -1;
		if (left != nullptr)
			leftHeight = left->height + 1;
		if (right != nullptr)
			rightHeight = right->height + 1;
		height = max(leftHeight, rightHeight) + 1;
	}
		void printInOrder()const{
		if (left != nullptr)
			left->printInOrder();
		cout << data << endl;
		if (right != nullptr)
			right->printInOrder();
	}
	int size()const{
		int leftSize = 0;
		int rightSize = 0;
		if (left != nullptr)
			leftSize = left->size();
		if (right != nullptr)
			rightSize = right->size();
		return 1 + leftSize + rightSize;
	}
/*	int height()const{
		int leftSize = -1;
		int rightSize = -1;
		if (left != nullptr)
			leftSize = left->height();
		if (right != nullptr)
			rightSize = right->height();
		return 1 + max(leftSize, rightSize);
	}*/
	int depth() const{
		int parentDepth = -1;
		if (parent != nullptr)
			parentDepth = parent->depth();
		return 1 + parentDepth;
	}
};

template <class T>
class AVL{
	AVLNode<T>* root;
	int size;
	AVLNode<T>* recursiveCopy(AVLNode<T>* toCopy);
	void singleCCR(AVLNode<T>*& point);
	void doubleCR(AVLNode<T>*& point);
	void singleCR(AVLNode<T>*& point);
	void doubleCCR(AVLNode<T>*& point);
	int heightDiff(AVLNode<T>* point);
	void doRotation(AVLNode<T>* point);
public:
	AVL() :size(0){ root = nullptr; }

	//memory on the heap so.... here comes the big 3!
	AVL(const AVL<T>& rhs) :root(nullptr){ *this = rhs; }
	virtual ~AVL(){ clear(); }
	AVL& operator=(const AVL<T>& rhs);

	bool isInTree(const T& toFind) const{ return find(toFind) != nullptr; }
	bool isEmpty()const{ return root == nullptr; }
	int getSize()const { return size; }
	void remove(const T& toRemove){
		AVLNode<T>* item = find(toRemove);
		if (item != nullptr)
			remove(item);
	}
	void insert(const T&);
	void remove(AVLNode<T>*);
	AVLNode<T>* find(const T& toFind) const;
	void clear(){ while (!isEmpty()) remove(root); }
	void printInOrder()const{ root->printInOrder(); }
};
template <class T>
void AVL<T>::doubleCCR(AVLNode<T>*& point){
	singleCR(point->right);
	singleCCR(point);
}

template <class T>
void AVL<T>::doubleCR(AVLNode<T>*& point){
	singleCCR(point->left);
	singleCR(point);
}

template <class T>
void AVL<T>::singleCR(AVLNode<T>*& point){
	AVLNode<T>* grandparent = point;
	AVLNode<T>* parent = point->left;
	parent->parent = grandparent->parent;
	grandparent->parent = parent; 
	grandparent->left = parent->right;
	parent->right = grandparent;
	if (grandparent->left != nullptr) //if we now have a left child, update its parent pointer
		grandparent->left->parent = grandparent;
	if (parent->parent == nullptr)//if we were the root, update the root!
		root = parent;
	else if (parent->parent->left == grandparent)
		parent->parent->left = parent;
	else
		parent->parent->right = parent;
	grandparent->calcHeight();
	parent->calcHeight();
}

template <class T>
void AVL<T>::singleCCR(AVLNode<T>*& point){
	AVLNode<T>* grandparent = point;
	AVLNode<T>* parent = point->right;
	parent->parent = grandparent->parent;
	grandparent->parent = parent;
	grandparent->right = parent->left;
	parent->left = grandparent;
	if (grandparent->right != nullptr) //if we now have a right child, update its parent pointer
		grandparent->right->parent = grandparent;
	if (parent->parent == nullptr)//if we were the root, update the root!
		root = parent;
	else if (parent->parent->right == grandparent)
		parent->parent->right = parent;
	else
		parent->parent->left = parent;
	grandparent->calcHeight();
	parent->calcHeight();
}


template <class T>
AVLNode<T>* AVL<T>::recursiveCopy(AVLNode<T>* toCopy){
	if (toCopy == nullptr)
		return nullptr;
	AVLNode<T>* temp = new AVLNode<T>(toCopy->data, nullptr, recursiveCopy(toCopy->left), recursiveCopy(toCopy->right));
	if (temp->left != nullptr)
		temp->left->parent = temp;
	if (temp->right != nullptr)
		temp->right->parent = temp;
	return temp;
}

template <class T>
AVL<T>& AVL<T>::operator=(const AVL<T>& rhs){
	if (this == &rhs)
		return *this;
	clear();
	root = recursiveCopy(rhs.root);
	size = rhs.size;
	return *this;
}

template <class T>
void AVL<T>::remove(AVLNode<T>* toRemove){
	if (root == nullptr)
		return; //Remove from an empty tree????
	if (toRemove->left == nullptr && toRemove->right == nullptr){ //leaf node case
		if (toRemove->parent == nullptr){
			root = nullptr;
		}
		else if (toRemove == toRemove->parent->left) //left child!
			toRemove->parent->left = nullptr; //fix the parent's pointer!
		else
			toRemove->parent->right = nullptr;
		delete toRemove;
		size--;
	}
	else if (toRemove->right == nullptr){ //has one (left) child
		if (toRemove->parent == nullptr){
			root = toRemove->left;
			root->parent = nullptr;
		}
		else if (toRemove == toRemove->parent->left){ //we're the left child of our parent
			toRemove->parent->left = toRemove->left;
			toRemove->left->parent = toRemove->parent;
		}
		else{
			toRemove->parent->right = toRemove->left;
			toRemove->left->parent = toRemove->parent;
		}
		delete toRemove;
		size--;
	}
	else if (toRemove->left == nullptr){ //has one right child, almost same solution as left child only
		if (toRemove->parent == nullptr){
			root = toRemove->right;
			root->parent = nullptr;
		}
		else if (toRemove == toRemove->parent->left){ //we're the left child of our parent
			toRemove->parent->left = toRemove->right;
			toRemove->right->parent = toRemove->parent;
		}
		else{
			toRemove->parent->right = toRemove->right;
			toRemove->right->parent = toRemove->parent;
		}
		delete toRemove;
		size--;
	}
	else{ //sigh... two children!
		AVLNode<T>* temp = toRemove->right;
		while (temp->left != nullptr)
			temp = temp->left;
		toRemove->data = temp->data;
		remove(temp);
	}

}

template <class T>
AVLNode<T>* AVL<T>::find(const T& toFind) const{
	AVLNode<T>* temp = root;
	while (temp != nullptr && temp->data != toFind){
		if (toFind < temp->data)
			temp = temp->left;
		else
			temp = temp->right;
	}
	return temp;
}

template <class T>
void AVL<T>::insert(const T& toInsert){
	size++;
	if (root == nullptr){
		root = new AVLNode<T>(toInsert);
	}
	else{
		AVLNode<T>* temp = root;
		AVLNode<T>* prev = temp;
		while (temp != nullptr){
			prev = temp;
			if (toInsert < temp->data)
				temp = temp->left;
			else
				temp = temp->right;
		}
		//now temp points to null and prev points to the node we want to insert onto
		if (toInsert < prev->data){ //insert onto the left of Prev
			prev->left = new AVLNode<T>(toInsert, prev);
		}
		else
			prev->right = new AVLNode<T>(toInsert, prev);

		while (prev != nullptr){
			prev->calcHeight();
			if (heightDiff(prev)>1)
				doRotation(prev);
		}
	}
}
template <class T>
void AVL<T>::doRotation(AVLNode<T>* point){
	int leftChild = -1;
	int rightChild = -1;
	if (point->left != nullptr)
		leftChild = point->left->height;
	if (point->right != nullptr)
		rightChild = point->right->height;

	if (leftChild > rightChild){//CR, but is it single or double?
		int leftGC = -1;
		int rightGC = -1;
		if (point->left->left != nullptr)
			leftGC = point->left->left->height();
		if (point->left->right != nullptr)
			rightGC = point->left->right->height();
		if (leftGC > rightGC) // single rotation
			singleCR(point);
		else
			doubleCR(point);
	}
	else{//definitely a CCR, but which one?
		int leftGC = -1;
		int rightGC = -1;
		if (point->right->left != nullptr)
			leftGC = point->right->left->height();
		if (point->right->right != nullptr)
			rightGC = point->right->right->height();
		if (leftGC > rightGC) // double rotation
			doubleCCR(point);
		else
			singleCR(point);
	}
}


template<class T>
int AVL<T>::heightDiff(AVLNode<T>* point){
	int leftHeight = -1;
	int rightHeight = -1;
	if (point->left != nullptr)
		leftHeight = point->left->height;
	if (point->right != nullptr)
		rightHeight = point->right->height;
	return (abs(leftHeight - rightHeight));
}


int main(){
	{AVL<int> b;
	srand(time(NULL));
	for (int i = 0; i < 100; i++)
		b.insert(rand() % 1000);

	b.printInOrder();
	cout << "Got here!" << endl;
	}
	cout << "Got here #2" << endl;
}