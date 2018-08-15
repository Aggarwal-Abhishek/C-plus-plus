#include<algorithm>
#include<iostream>
#include<vector>
#include<stack>
using namespace std ;

struct Point{
	int x , y ;
};

Point getPoint(int x , int y){
	Point ret ;
	ret.x = x ;
	ret.y = y ;
	return ret ;
}

struct Intersect{

	//Given p,q,r are collinear
	//checks q lies on pr
	bool onSegment(Point p , Point q , Point r){
		return (
				(q.x <= max(p.x , r.x)) and (q.x >= min(p.x , r.x))
				and (q.y <= max(p.y , r.y)) and (q.y >= min(p.y , r.y))
		) ;
	}

	//0 -> collinear
	//1 -> CW
	//2 -> CCW
	int orientation(Point p , Point q , Point r){

		int val = (q.y - p.y)*(r.x - q.x) - (q.x - p.x)*(r.y - q.y) ;

		if(val == 0)return 0 ;
		return (val > 0) ? 1 : 2 ;
	}

	bool doIntersect(Point p1 , Point q1 , Point p2 , Point q2){

		int o1 = orientation(p1 , q1 , p2) ;
		int o2 = orientation(p1 , q1 , q2) ;
		int o3 = orientation(p2 , q2 , p1) ;
		int o4 = orientation(p2 , q2 , q1) ;

		if(o1 != o2 and o3 != o4)return true ;

		if(o1 == 0 and onSegment(p1 , p2 , q1) )return true ;
		if(o2 == 0 and onSegment(p1 , q2 , q1) )return true ;
		if(o3 ==0 and onSegment(p2 , p1 , q2) )return true ;
		if(o4 ==0 and onSegment(p2 , q1 , q2) )return true ;

		return false ;
	}

};

//Jarvis Algorithm
struct JConvexHull{

	vector<Point>points ;

	void addPoint(Point x){
		points.push_back(x) ;
	}

	//0 -> collinear
	//1 -> CW
	//2 -> CCW
	int orientation(Point p , Point q , Point r){

		int val = (q.y - p.y)*(r.x - q.x) - (q.x - p.x)*(r.y - q.y) ;

		if(val == 0)return 0 ;
		return (val > 0) ? 1 : 2 ;
	}


	vector<Point>getHull(){

		vector<Point>hull ;
		int n = points.size() ;

		if(n < 3)return hull ;

		//Leftmost Point
		int L = 0 ;
		for(int i=1 ; i<n ; i++){
			if(points[i].x < points[L].x){
				L = i ;
			}
		}

		int p = L , q ;
		do{
			hull.push_back(points[p]) ;

			//find point with most ccw angle
			p = (p+1)%n ;
			for(int i = 0 ; i<n ; i++){
				if( orientation(points[p] , points[i] , points[q]) == 2){
					q = i ;
				}
			}
			p = q ;

		}while(p != L) ;

		return hull ;
	}
};

//Graham Scan
struct GConvexHull{


	//Reference Point need to Sort other points
	Point p0 ;
	vector<Point>point ;

	void addPoint(Point x){
		point.push_back(x) ;
	}

	Point nextToTop(stack<Point>s){
		Point p = s.top() ;
		s.pop() ;
		Point ret = s.top() ;
		s.push(p) ;

		return ret ;
	}

	void swap(Point &x , Point &y){
		Point tmp = x ;
		x = y ;
		y = tmp ;
	}

	int distSq(Point p1 , Point p2){
		return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y) ;
	}

	//0 -> collinear
	//1 -> CW
	//2 -> CCW
	int orientation(Point p , Point q , Point r){

		int val = (q.y - p.y)*(r.x - q.x) - (q.x - p.x)*(r.y - q.y) ;

		if(val == 0)return 0 ;
		return (val > 0) ? 1 : 2 ;
	}

	//To sort Points
	bool compare(Point x , Point y){

		int o = orientation(p0 , x , y) ;

		if(o == 0){
			return (distSq(p0 , y) >= distSq(p0 , x) ) ;
		}
		return (o != 1 ) ;
	}

	stack<Point>getHull(){
		stack<Point>hull ;
		int n = point.size() ;

		//Bottom most Point
		int ymin = point[0].y , min = 0 ;
		for(int i=1 , y ; i<n ; i++){
			y = point[i].y ;

			if( (y < ymin) or ( y==ymin  and point[i].x < point[min].x  )   ){
				ymin = y ;
				min = i ;
			}
		}
		swap(point[0] , point[min]) ;
		p0 = point[0] ;
		sort(point.begin() , point.end() , compare) ;

		//Remove useless Points
		int m=1 ;
		for(int i=1 ; i<n ; i++){
			while(i<n-1 and orientation(p0 , point[i] , point[i+1]) == 0 ){
				++i ;
			}
			point[m++] = point[i] ;
		}

		if(m < 3)return hull ;

		hull.push(point[0]) ;
		hull.push(point[1]) ;
		hull.push(point[2]) ;

		for(int i=3 ; i<m ; i++){
			while(orientation(nextToTop(hull) , hull.top() , point[i]  ) !=2  ){
				hull.pop() ;
			}
			hull.push(point[i]) ;
		}

		return hull ;
	}




};


int main(){

	pair<int,int> points[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4},{0, 0}, {1, 2}, {3, 1}, {3, 3}};

	//cout<<"Hello" ;

	for(auto p : points){
		addPoint(getPoint(p.first , p.second)) ;
	}

	auto res = getHull() ;

	cout<<res.size()<<"\n" ;

	while(not res.empty()){
		cout << "(" << res.top().x << ", " << res.top().y <<")" << "\n";
		res.pop() ;
	}

	system("pause");
}

