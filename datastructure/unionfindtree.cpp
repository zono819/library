#ifndef call_from_test
#include<bits/stdc++.h>
using namespace std;
using Int = long long;
#endif
//BEGIN CUT HERE
struct UnionFind{
  int num;
  vector<int> r,p;
  UnionFind(){}
  UnionFind(int n):num(n),r(n,1),p(n,0){iota(p.begin(),p.end(),0);}
  int find(int x){
    return (x==p[x]?x:p[x]=find(p[x]));
  }
  bool same(int x,int y){
    return find(x)==find(y);
  }
  void unite(int x,int y){
    x=find(x);y=find(y);
    if(x==y) return;
    if(r[x]<r[y]) swap(x,y);
    r[x]+=r[y];
    p[y]=x;
    num--;
  }
  int size(int x){
    return r[find(x)];
  }
  int count() const{
    return num;
  }
};
//END CUT HERE
#ifndef call_from_test
struct FastIO{
  FastIO(){
    cin.tie(0);
    ios::sync_with_stdio(0);
  }
}fastio_beet;

//INSERT ABOVE HERE
signed ABC120_D(){
  int n,m;
  cin>>n>>m;
  vector<int> a(m),b(m);
  for(int i=0;i<m;i++) cin>>a[i]>>b[i];

  UnionFind uf(n);
  vector<Int> ans(m+1,0);
  ans[m]=(Int)n*(n-1)/2;
  for(int i=m-1;i>=0;i--){
    a[i]--;b[i]--;
    ans[i]=ans[i+1];
    if(uf.same(a[i],b[i])) continue;

    Int x=uf.size(a[i]),y=uf.size(b[i]);
    ans[i]-=x*y;

    uf.unite(a[i],b[i]);
  }
  ans.erase(ans.begin());
  for(Int x:ans) cout<<x<<"\n";
  cout<<flush;
  return 0;
}

/*
  verified on 2019/03/03
  https://atcoder.jp/contests/abc120/tasks/abc120_d
*/

signed ABC126_E(){
  Int n,m;
  cin>>n>>m;
  UnionFind uf(n);
  for(Int i=0;i<m;i++){
    Int x,y,z;
    cin>>x>>y>>z;
    x--;y--;
    z%=2;
    uf.unite(x,y);
  }
  cout<<uf.count()<<endl;
  return 0;
}
/*
  verified on 2019/05/19
  https://atcoder.jp/contests/abc126/tasks/abc126_e
*/


signed main(){
  //ABC120_D();
  //ABC126_E();
  return 0;
}
#endif
