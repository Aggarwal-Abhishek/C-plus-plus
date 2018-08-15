/*
	Name: Spoj MKTHNUM
	Date: 21-07-17 18:35
	Description: finds the k'th number in sorted range a[i..j]
*/



#include<algorithm>
#include<iostream>
#include<vector>
#include<mem.h>
using namespace std;
#define N 100001
#define Null new node(0,NULL,NULL)
#define Left cur->left,a,(a+b)>>1
#define Right cur->right,((a+b)>>1)+1,b

inline bool operator <(const pair<int,int>x,const pair<int,int>y){
	return x.first<y.first;
}

struct node{
	int val;
	node *left,*right;
	node(int val,node *left,node *right):
		val(val),left(left),right(right){}
};

int arr[N],posOf[N],n,m;
node *version[N];
vector<pair<int,int> >v;

void build(node *cur,int a,int b){
	if(a>b)return;
	if(a==b)cur->val=arr[a];
	else{
		cur->left=Null;
		cur->right=Null;
		build(Left);
		build(Right);
		
		cur->val=cur->left->val+cur->right->val;
	}
}

void upgrade(node *prev,node *cur,int a,int b,int i,int val){
	if(a>b or i<a or i>b)return ;
	
	if(a==b){
		cur->val=val;
		return ;
	}
	
	int mid=(a+b)>>1;
	if(i<=mid){
		cur->right=prev->right;
		cur->left=Null;
		upgrade(prev->left,Left,i,val);
	}
	else{
		cur->left=prev->left;
		cur->right=Null;
		upgrade(prev->right,Right,i,val);
	}
	cur->val=cur->left->val+cur->right->val;
}


int query(node *cur,int a,int b,int i,int j){
	if(a>b or j<a or i>b)return 0;
	if(a>=i and b<=j)return cur->val;
	return query(Left,i,j)+query(Right,i,j);
}

int query(node *i,node *j,int a,int b,int k){
	if(a==b)return v[a].first;
	int L=j->left->val-i->left->val;

	if(k<=L)return query(i->left,j->left,a,(a+b)>>1,k);
	else return query(i->right,j->right,((a+b)>>1)+1,b,k-L);
}

void display(node *cur,int a=0,int b=n-1){
	if(a==b)cout<<cur->val<<" ";
	else{
		display(Left);
		display(Right);
	}
}

void fuck(){
	cin>>n>>m;
	
	memset(arr,0,n);
	version[0]=Null;
	build(version[0],0,n-1);

	for(int i=0;i<n;i++){
		cin>>arr[i];

		v.push_back(make_pair(arr[i],i));
		version[i+1]=Null;
	}
	sort(v.begin(),v.end());
	for(int i=0;i<n;i++){
		posOf[v[i].second]=i;
	}

	for(int i=0;i<n;i++){
		upgrade(version[i],version[i+1],0,n-1,posOf[i],1);
	}

	int i,j,k,offset;
	while(m--){
		cin>>i>>j>>k;
		
//		cout<<"Tree 1:\n";
//		display(version[i-1]);
//		cout<<"\nTree 2:\n";
//		display(version[j]);
		
		cout<<query(version[i-1],version[j],0,n-1,k)<<"\n";
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	fuck();
}
