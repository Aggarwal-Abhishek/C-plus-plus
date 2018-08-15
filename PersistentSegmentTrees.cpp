#include<bits/stdc++.h>
using namespace std;

struct SegmentTree{

    struct Node{
        int val;
        Node *left;
        Node *right;

        Node(int val=0, Node *left=NULL, Node *right = NULL):val(val), left(left), right(right){}
    };

    SegmentTree(int n):n(n), arr(0), version(){build();}
    SegmentTree(int n, vector<int>arr):n(n), arr(arr), version(){build();}

    void build(){
        version.push_back(new Node());
        if(arr.size() == 0){
        	make(version[0], 0, n-1);
		}
        else build(version[0], 0, n-1);
    }
    void update(int i, int x){
        update(version[current_version], 0, n-1, i, x);
    }
    void upgrade(int i, int x){
        version.push_back(new Node());
        upgrade(version[current_version], version[current_version+1], 0, n-1, i, x);
        ++current_version;
	}
    int query(int ver, int i, int j){
        return query(version[ver], 0, n-1, i, j);
    }
    int query(int i, int j){
        return query(version[current_version], 0, n-1, i, j);
    }
    void display(int ver){
        return display(version[ver], 0, n-1);
    }
    void display(){
        return display(version[current_version], 0, n-1);
    }

    private:
        int n;
        vector<Node*>version;
        vector<int>arr;
        int current_version = 0;

        inline int combine(int a, int b){
            return a+b;
        }
        inline int null(){
            return 0;
        }

        void make(Node *cur, int a, int b){
            if(a>b || a==b)return;
            cur->left = new Node();
            cur->right = new Node();

            make(cur->left, a, (a+b)>>1);
        	make(cur->right, 1+((a+b)>>1), b);
        }

        void build(Node *cur, int a, int b){
            if(a>b)return;
            if(a == b)cur->val = arr[a];
            else{
                cur->left = new Node();
                cur->right = new Node();

                build(cur->left, a, (a+b)>>1);
                build(cur->right, 1+((a+b)>>1), b);
                cur->val = combine(cur->left->val, cur->right->val);
            }
        }

        void update(Node *cur, int a, int b, int i, int x){
            if(a>b || i<a || i>b)return;
            if(a==b)cur->val = x;
            else{
                update(cur->left, a, (a+b)>>1, i, x);
                update(cur->right, 1+((a+b)>>1), b, i, x);
                cur->val = combine(cur->left->val, cur->right->val);
            }
        }

        void upgrade(Node *prev, Node *cur, int a, int b, int i, int x){
            if(a>b || i<a || i>b)return;
            if(a == b){
            	cur->val = x;
			}
            else{
                int mid = (a+b)>>1;
                if(i<=mid){
                    cur->left = new Node();
                    cur->right = prev->right;
                    upgrade(prev->left, cur->left, a, mid, i, x);
//                    cur->val = combine(cur->left->val , prev->right->val);
                }else{
                    cur->right = new Node();
                    cur->left = prev->left;
                    upgrade(prev->right, cur->right, mid+1, b, i, x);
//                    cur->val = combine(prev->left->val , cur->right->val);
                }
                cur->val = combine(cur->left->val , cur->right->val);
            }
        }

        int query(Node *cur, int a, int b, int i, int j){
            if(a>b || i>b || j<a)return null();
            if(a>=i && b<=j)return cur->val;
            return combine( query(cur->left, a, (a+b)>>1, i, j)     ,    query(cur->right, 1+((a+b)>>1), b, i, j)   );
        }

        void display(Node *cur, int a, int b){
            if(a>b)return;
            if(a==b)cout<<cur->val<<" ";
            else{
                display(cur->left, a, (a+b)>>1);
                display(cur->right, 1+((a+b)>>1), b);
            }
        }
};


int main(){
	int i, j;
	int x;
	
    SegmentTree *s = new SegmentTree(5, {1, 2, 3, 4, 5});
    
    while(true){
        cout<<"update i,x : ";
        cin>>i>>x;
        s->upgrade(i, x);
        s->display();


        cout<<"query i,j : ";
        cin>>i>>j;
        cout<<s->query(i, j)<<"\n";
    }
}
