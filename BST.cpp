#include <iostream>
#include <ctime>

using namespace std;

template <class T>
class BST;

template <class T>
class BSTNode{
	BSTNode<T>* parent, *left, *right;
	T data;
public:
	friend class BST < T > ;
	BSTNode(const T& newdata = T(), BSTNode<T>* newparent = nullptr, BSTNode<T>* newleft = nullptr, BSTNode<T>* newright = nullptr):
		data(newdata), parent(newparent), left(newleft), right(newright){}
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
	int height()const{
		int leftSize = -1;
		int rightSize = -1;
		if (left != nullptr)
			leftSize = left->height();
		if (right != nullptr)
			rightSize = right->height();
		return 1 +max(leftSize,rightSize);
	}
	int depth() const{
		int parentDepth = -1;
		if (parent != nullptr)
			parentDepth = parent->depth();
		return 1 + parentDepth;
	}
};

template <class T>
class BST{
	BSTNode<T>* root;
	int size;
	BSTNode<T>* recursiveCopy(BSTNode<T>* toCopy);
public:
	BST():size(0){ root = nullptr; }
	
	//memory on the heap so.... here comes the big 3!
	BST(const BST<T>& rhs) :root(nullptr){ *this = rhs; }
	virtual ~BST(){ clear(); }
	BST& operator=(const BST<T>& rhs);

	bool isInTree(const T& toFind) const{ return find(toFind) != nullptr; }
	bool isEmpty()const{ return root == nullptr; }
	int getSize()const { return size; }
	void remove(const T& toRemove){
		BSTNode<T>* item = find(toRemove);
		if (item != nullptr)
			remove(item);
	}
	void insert(const T&);
	void remove(BSTNode<T>*);
	BSTNode<T>* find(const T& toFind) const;
	void clear(){ while (!isEmpty()) remove(root); }
	void printInOrder()const{ root->printInOrder(); }
};

template <class T>
BSTNode<T>* BST<T>::recursiveCopy(BSTNode<T>* toCopy){
	if (toCopy == nullptr)
		return nullptr;
	BSTNode<T>* temp = new BSTNode<T>(toCopy->data, nullptr, recursiveCopy(toCopy->left), recursiveCopy(toCopy->right));
	if (temp->left != nullptr)
		temp->left->parent = temp;
	if (temp->right != nullptr)
		temp->right->parent = temp;
	return temp;
}

template <class T>
BST<T>& BST<T>::operator=(const BST<T>& rhs){
	if (this == &rhs)
		return *this;
	clear();
	root = recursiveCopy(rhs.root);
	size = rhs.size;
	return *this;
}

template <class T>
void BST<T>::remove(BSTNode<T>* toRemove){
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
		BSTNode<T>* temp = toRemove->right;
		while (temp->left != nullptr)
			temp = temp->left;
		toRemove->data = temp->data;
		remove(temp);
	}

}

template <class T>
BSTNode<T>* BST<T>::find(const T& toFind) const{
	BSTNode<T>* temp = root;
	while (temp != nullptr && temp->data != toFind){
		if (toFind < temp->data)
			temp = temp->left;
		else
			temp = temp->right;
	}
	return temp;
}

template <class T>
void BST<T>::insert(const T& toInsert){
	size++;
	if (root == nullptr){
		root = new BSTNode<T>(toInsert);
	}
	else{
		BSTNode<T>* temp = root;
		BSTNode<T>* prev = temp;
		while (temp != nullptr){
			prev = temp;
			if (toInsert < temp->data)
				temp = temp->left;
			else
				temp = temp->right;
		}
		//now temp points to null and prev points to the node we want to insert onto
		if (toInsert < prev->data){ //insert onto the left of Prev
			prev->left = new BSTNode<T>(toInsert, prev);
		}
		else
			prev->right = new BSTNode<T>(toInsert, prev);
	}
}


int main(){
	{BST<int> b;
	srand(time(NULL));
	for (int i = 0; i < 100; i++)
		b.insert(rand() % 1000);

	b.printInOrder();
	cout << "Got here!" << endl;
	}
	cout << "Got here #2" << endl;
}