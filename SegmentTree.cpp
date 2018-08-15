#include<bits/stdc++.h>
using namespace std;

template<class mtype>
struct SegmentTree{
    SegmentTree(int n):n(n), tree(n<<2), arr(0){}
    SegmentTree(int n, vector<mtype>arr):n(n), arr(arr), tree(n<<2){build(1, 0, n-1);}

    void update(int i, mtype x){update(1, 0, n-1, i, x);}
    mtype query(int i, int j){return query(1, 0, n-1, i, j);}
    void display(){display(1, 0, n-1);}

    private:
        int n;
        vector<mtype>arr;
        vector<mtype>tree;

        inline mtype combine(mtype a, mtype b){
            return a+b;
        }
        inline mtype null(){
            return 0;
        }
        void display(mtype x){
            cout<<x<<" ";
        }


        void build(int node, int a, int b){
            if(a>b)return;
            if(a==b)tree[node]=arr[a];
            else{
                build(node<<1, a, (a+b)>>1);
                build((node<<1)|1, 1+((a+b)>>1), b);
                tree[node] = combine(tree[node<<1], tree[(node<<1)|1]);
            }
        }

        void update(int node, int a, int b, int i, mtype x){
            if(a>b || i<a || i>b)return;
            if(a == b)tree[node] = x;
            else{
                update(node<<1, a, (a+b)>>1, i, x);
                update((node<<1)|1, 1+((a+b)>>1), b, i, x);
                tree[node] = combine(tree[node<<1], tree[(node<<1)|1]);
            }
        }

        mtype query(int node, int a, int b, int i, int j){
            if(a>b || i>b || j<a)return null();
            if(a>=i && b<=j)return tree[node];
            return combine( query(node<<1, a, (a+b)>>1, i, j)   ,   query((node<<1)|1, 1+((a+b)>>1), b, i, j)   );
        }

        void display(int node, int a, int b){
            if(a>b)return;
            if(a == b)display(tree[node]);
            else{
                display(node<<1, a, (a+b)>>1);
                display((node<<1)|1, 1+((a+b)>>1), b);
            }
        }
};



int main(){
    int i,j;
	int x;
    SegmentTree<int> *s = new SegmentTree<int>(5, {1, 2, 3, 4, 5});
    while(true){
        cout<<"update i,x : ";
        cin>>i>>x;
        s->update(i, x);
        s->display();

        cout<<"query i,j : ";
        cin>>i>>j;
        cout<<s->query(i, j)<<"\n";
    }
}
