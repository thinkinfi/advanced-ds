#include "Snippet.h"
using namespace std;

class Trie{
public:
    Trie* links[26];
    bool flag = false;

    bool containsKey(char ch){
        return links[ch-'a']!=NULL;
    }
    void put(char ch, Trie* node){
        links[ch-'a'] = node;
    }
    Trie* get(char ch){
        return links[ch-'a'];
    }
    void setEnd(){
        flag = true;
    }
    bool isEnd(){
        return flag;
    }
};

class DSU{
	vector<int> size, par;
public:
	DSU(int n){
		size.resize(n+1,1);
		par.resize(n+1);
		for(int i=1;i<=n;i++) par[i] = i;
	}
	int findPar(int u){
		if(u==par[u]) return u;
		return par[u] = findPar(par[u]);
	}
	void unionBySize(int u,int v){
		int uPar = findPar(u), vPar = findPar(v);
		if(uPar==vPar) return;
		if(size[uPar]>size[vPar]){
			par[vPar] = uPar;
			size[uPar] += size[vPar];
		}
		else{
			par[uPar] = vPar;
			size[vPar] += size[uPar];
		}
	}
};

class fenwickTree{
	const int N = 1e5+10;
	int bit[N];

	void update(int i, int x){
		for(;i<N;i+=(i&-i)){
			bit[i] += x;
		}
	}

	int sum(int i){
		int ans = 0;
		for(; i > 0; i -= (i&-i))
			ans += bit[i];
		return ans;
	}
};


// Segment Tree
class segtree{
    int size, n;
    vector<long long> rangeValues;
public:
    segtree(int n){
        this->n = n;
        size = 1;
        while(size<n) size *= 2;
        rangeValues.assign(2*size, 0);
    }

    long long Ops(long long& a, long long& b){
        return min(a,b);
    }

    void set(int i,int v,int node,int start,int end){
        if(start==end) {
            rangeValues[node] = v;
        }
        else {
            int mid = start + (end-start)/2;
            if(i<=mid){
                set(i,v,2*node+1,start,mid);
            }
            else{
                set(i,v,2*node+2,mid+1,end);
            }
            rangeValues[node] = Ops(rangeValues[2*node+1],rangeValues[2*node+2]);
        }
    }

    void set(int i,int v){
        set(i,v,0,0,n-1);
    }

    long long query(int i,int j,int node,int start,int end){
        if(i>end || j<start) return INT_MAX;
        if(i<=start && j>=end) return rangeValues[node];
        int mid = start + (end-start)/2;
        long long left = query(i,j,2*node+1,start,mid);
        long long right = query(i,j,2*node+2,mid+1,end);
        return Ops(left,right);
    }

    long long query(int i,int j){
        return query(i,j,0,0,n-1);
    }
};
