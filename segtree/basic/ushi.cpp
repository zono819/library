#ifndef call_from_test
#include<bits/stdc++.h>
using namespace std;
using Int = long long;
#endif
//BEGIN CUT HERE
template <typename T>
struct SegmentTree{
  using F = function<T(T,T)>;
  int n;
  F f;
  T ti;
  vector<T> dat;
  SegmentTree(){};
  SegmentTree(F f,T ti):f(f),ti(ti){}
  void init(int n_){
    n=1;
    while(n<n_) n<<=1;
    dat.assign(n<<1,ti);
  }
  void build(const vector<T> &v){
    int n_=v.size();
    init(n_);
    for(int i=0;i<n_;i++) dat[n+i]=v[i];
    for(int i=n-1;i;i--)
      dat[i]=f(dat[(i<<1)|0],dat[(i<<1)|1]);
  }
  void set_val(int k,T x){
    dat[k+=n]=x;
    while(k>>=1)
      dat[k]=f(dat[(k<<1)|0],dat[(k<<1)|1]);
  }
  T query(int a,int b){
    T vl=ti,vr=ti;
    for(int l=a+n,r=b+n;l<r;l>>=1,r>>=1) {
      if(l&1) vl=f(vl,dat[l++]);
      if(r&1) vr=f(dat[--r],vr);
    }
    return f(vl,vr);
  }
  template<typename C>
  int find(int st,C &check,T &acc,int k,int l,int r){
    if(l+1==r){
      acc=f(acc,dat[k]);
      return check(acc)?k-n:-1;
    }
    int m=(l+r)>>1;
    if(m<=st) return find(st,check,acc,(k<<1)|1,m,r);
    if(st<=l&&!check(f(acc,dat[k]))){
      acc=f(acc,dat[k]);
      return -1;
    }
    int vl=find(st,check,acc,(k<<1)|0,l,m);
    if(~vl) return vl;
    return find(st,check,acc,(k<<1)|1,m,r);
  }
  template<typename C>
  int find(int st,C &check){
    T acc=ti;
    return find(st,check,acc,1,0,n);
  }
};
//END CUT HERE
#ifndef call_from_test

signed ARC038_C(){
  int n;
  scanf("%d",&n);
  vector<int> cs(n),as(n);
  for(int i=1;i<n;i++) scanf("%d %d",&cs[i],&as[i]);

  const int INF = 1e9;
  auto f=[](int a,int b){return min(a,b);};
  SegmentTree<int> seg(f,INF);
  seg.build(vector<int>(n,-1));

  vector<int> dp(n);
  dp[0]=0;
  seg.set_val(0,0);
  for(int i=1;i<n;i++){
    auto check=[&](int x){return x<i-cs[i];};
    dp[i]=seg.find(0,check);
    seg.set_val(dp[i],max(seg.query(dp[i],dp[i]+1),i));
  }

  int ans=0;
  for(int i=1;i<n;i++)
    if(as[i]&1) ans^=dp[i];

  puts(ans?"First":"Second");
  return 0;
}
/*
  verified on 2019/06/26
  https://atcoder.jp/contests/arc038/tasks/arc038_c
*/

signed KUPC2013_D(){
  int n;
  scanf("%d",&n);
  vector<int> as(n+2,0);
  for(int i=1;i<=n;i++) scanf("%d",&as[i]);

  const int INF = 1.1e9;
  auto f=[](int a,int b){return min(a,b);};
  SegmentTree<int> seg(f,INF);
  seg.build(as);

  using P = pair<int, int>;
  set<P> sp;
  for(int k=0;k<2;k++){
    for(int i=1;i<=n;i++){
      auto check=[&](int x){return x<as[i];};
      int l=seg.find(i,check);
      sp.emplace(k?n+2-l:l,as[i]);
    }
    reverse(as.begin(),as.end());
    seg.build(as);
  }

  printf("%d\n",(int)sp.size()/2);
  return 0;
}
/*
  verified on 2019/06/26
  https://atcoder.jp/contests/kupc2013/tasks/kupc2013_d
*/

signed ABC130_D(){
  using ll = long long;
  ll n,k;
  cin>>n>>k;
  vector<ll> as(n);
  for(int i=0;i<n;i++) cin>>as[i];

  auto f=[](ll a,ll b){return a+b;};
  SegmentTree<ll> seg(f,0);
  seg.build(as);

  ll ans=0;
  auto check=[&](ll d){return d>=k;};
  for(int i=0;i<n;i++){
    int idx=seg.find(i,check);
    if(~idx) ans+=n-idx;
  }

  cout<<ans<<endl;
  return 0;
}
/*
  verified on 2019/06/26
  https://atcoder.jp/contests/abc130/tasks/abc130_d
*/

signed main(){
  //ARC038_C();
  //KUPC2013_D();
  //ABC130_D();
  return 0;
}
#endif
