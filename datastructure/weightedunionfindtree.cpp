#ifndef call_from_test
#include<bits/stdc++.h>
using namespace std;
using Int = long long;
#endif
//BEGIN CUT HERE
template <typename T>
struct WeightedUnionFind{
  T d;
  vector<int> r,p;
  vector<T> ws;

  WeightedUnionFind(){}
  WeightedUnionFind(int n,T d):
    d(d),r(n,1),p(n),ws(n,d){iota(p.begin(),p.end(),0);}

  int find(int x){
    if(x==p[x]) return x;
    int t=find(p[x]);
    ws[x]+=ws[p[x]];
    return p[x]=t;
  }

  T weight(int x){
    find(x);
    return ws[x];
  }

  bool same(int x,int y){
    return find(x)==find(y);
  }

  void unite(int x,int y,T w){
    w+=weight(x);
    w-=weight(y);
    x=find(x);y=find(y);
    if(x==y) return;
    if(r[x]<r[y]) swap(x,y),w=-w;
    r[x]+=r[y];
    p[y]=x;
    ws[y]=w;
  }

  T diff(int x,int y){
    return weight(y)-weight(x);
  }
};
//END CUT HERE
#ifndef call_from_test
signed main(){
  return 0;
}
#endif
