template<typename Key>
struct Treap_node {
	Treap_node<Key>* left_child;
	Treap_node<Key>* right_child;
	Key key;
	int priority;
};

template<typename Key>
class Treap {
public:
	using node_type = Treap_node<Key>;
	Treap() { root = NULL;}
	Treap(node_type* r) { root = r;}
	
	//build Treap from the array A of entries of size n
	//You can assume array A is sorted, with no duplicates
	void build_from(Key* A, int n) {
		//allocate memory for all tree nodes
		nodes = new node_type[n];
		
	}
	
	
	//return true if k is in this set, return false otherwise
	bool find(Key k);
	
	void clear() {
		delete[] nodes;
	}
	
private:
	node_type* nodes;
	node_type* root;	
};

template <typename K>
Treap<K> treap_union(Treap<K> T1, Treap<K> T2) {
	return Treap<K>();
}

template <typename K>
Treap<K> treap_intersection(Treap<K> T1, Treap<K> T2) {
	// If you don't want to work on the bonus question, just output the sentence below
	std::cout << "no implementation for intersection" << std::endl;
	return Treap<K>();
}