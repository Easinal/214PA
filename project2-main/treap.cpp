#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <algorithm>
//#include <cilk/cilk.h>
//#include <cilk/cilk_api.h>
#include "get_time.h"
#include "parse_command_line.h"
#include "treap.h"
using namespace std;

using data_type = size_t;
using Treap_type = Treap<data_type>;

#define NUM_ROUNDS 5

template <typename Key>
bool Treap<Key>::find(Key k) {
	Treap<Key>::node_type* r = root;
	while (r != NULL) {
		if (r->key == k) return true;
		if (r->key > k) r = r->left_child; else r = r->right_child;
	}
	return false;
}

inline uint64_t hash64(uint64_t u )
{
	uint64_t v = u * 3935559000370003845ul + 2691343689449507681ul;
	v ^= v >> 21;
	v ^= v << 37;
	v ^= v >>  4;
	v *= 4768777513237032717ul;
	v ^= v << 20;
	v ^= v >> 41;
	v ^= v <<  5;
	return v;
}

int main(int argc, char** argv) {
	commandLine P(argc, argv,
		"[-n size_set_1] [-m size_set_2]");
	int n = P.getOptionLongValue("-n", 100000000);
	int m = P.getOptionLongValue("-m", 100000000);
	
	
	cout << "testing union..." << endl;
	data_type* A = new data_type[n];
	data_type* B = new data_type[n];
	std::vector<int> C(n+m);  
	A[0] = hash64(0) % 20 + 1;
	for (int i = 1; i < n; i++) {
		A[i] = hash64(i) % 20 + 1;
		A[i] = A[i] + A[i - 1];
	}
	
	B[0] = hash64(n) % 20 + 1;
	for (int i = 1; i < m; i++) {
		B[i] = hash64(i+n) % 20 + 1;
		B[i] = B[i] + B[i - 1];
	}
	
	
	Treap_type T1, T2, T;
	
	T1.build_from(A, n);
	T2.build_from(B, m);
	T = treap_union(T1, T2);
	
	//correctness check, when you test performance, you can comment this out
	timer tx; tx.start();
	auto it=std::set_union (A, A+n, B, B+m, C.begin());
	double seq_t = tx.stop();
	cout << "sequential time: " << seq_t << endl;
	int output_size = it - C.begin();
	C.resize(output_size);
	for (int i = 0; i < n; i++) {
		if (!T.find(C[i])) {
			//cout << "wrong answer" << endl;
			//exit(1);
		}
	}
	
	T1.clear();
	T2.clear();
	
	T1.build_from(A, n);
	T2.build_from(B, m);
	
	T = treap_union(T1, T2);
	
	T1.clear();
	T2.clear();
	
	double tot_time = 0.0;
	for (int round = 0; round < NUM_ROUNDS; round++) {
		T1.build_from(A, n);
		T2.build_from(B, m);
		
		timer t; t.start();
		T = treap_union(T1, T2);
		t.stop();
		double tm = t.get_total();
		
		cout << "Union, Round " << round << ", time: " << tm << endl;
		tot_time += tm;
		
		T1.clear();
		T2.clear();
	}
	cout << "Union, Average time: " << tot_time/NUM_ROUNDS << endl;
	
	
	cout << "testing intersection..." << endl;
	A[0] = 0;
	for (int i = 1; i < n; i++) {
		A[i] = 3 + A[i - 1];
	}
	
	B[0] = 0;
	for (int i = 1; i < m; i++) {
		B[i] = 5 + B[i - 1];
	}
	
	
	T1.build_from(A, n);
	T2.build_from(B, m);
	T = treap_intersection(T1, T2);
	
	//correctness check, when you test performance, you can comment this out
	auto it2=std::set_intersection (A, A+n, B, B+m, C.begin());
	output_size = it2 - C.begin();
	C.resize(output_size);
	for (int i = 0; i < n; i++) {
		if (!T.find(C[i])) {
			//cout << "wrong answer" << endl;
			//exit(1);
		}
	}
	
	T1.clear();
	T2.clear();
	
	T1.build_from(A, n);
	T2.build_from(B, m);
	
	T = treap_intersection(T1, T2);
	
	T1.clear();
	T2.clear();
	
	tot_time = 0.0;
	for (int round = 0; round < NUM_ROUNDS; round++) {
		T1.build_from(A, n);
		T2.build_from(B, m);
		
		timer t; t.start();
		T = treap_intersection(T1, T2);
		t.stop();
		double tm = t.get_total();
		
		cout << "Intersection, Round " << round << ", time: " << tm << endl;
		tot_time += tm;
		
		T1.clear();
		T2.clear();
	}
	cout << "Intersection, Average time: " << tot_time/NUM_ROUNDS << endl;

	
	return 0;
}