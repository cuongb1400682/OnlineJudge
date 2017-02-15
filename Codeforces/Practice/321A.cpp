#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<vector>
#include<iostream>
using namespace std;

#define N 150

typedef long long ll;

struct Point{
    ll x,y;
    Point(ll _x=0,ll _y=0):x(_x),y(_y){}
};

const Point d[]={Point(0,1),Point(1,0),Point(0,-1),Point(-1,0)};

Point A,O;
char inst[N];
vector<Point> points;

Point operator+(Point a,Point b){
    return Point(a.x+b.x,a.y+b.y);
}

Point operator*(ll b,Point a){
    return Point(a.x*b,a.y*b);
}

bool operator==(Point a,Point b){
    return (a.x==b.x)&&(a.y==b.y);
}

int main(){
    ll a,b;
    cin>>a>>b;
    A=Point(a,b);
    scanf("%s",inst);
    O=Point(0,0);
    points.push_back(O);
    for(ll i=0;inst[i];i++){
        if(inst[i]=='U'){
            O=O+d[0];
        }else if(inst[i]=='R'){
            O=O+d[1];
        }else if(inst[i]=='D'){
            O=O+d[2];
        }else{
            O=O+d[3];
        }
        points.push_back(O);        
    }
    Point v=O;
    for(int i=0;i<(int)points.size();i++){
        if(v==Point(0,0)){
            if(points[i]==A){
                puts("Yes");
                return 0;
            }
        }else{
            Point u=A+(-1)*points[i];
            if(u==Point(0,0)){
                puts("Yes");
                return 0;
            }
            int k=0;
            if(v.x!=0&&u.x!=0)
                k=u.x/v.x;
            else if(v.y!=0)
                k=u.y/v.y;
            if(u==k*v&&k>0){
                puts("Yes");
                return 0;
            }
        }
    }
    puts("No");
    return 0;
}
