#include<bits/stdc++.h>
using namespace std;
using Int = long long;
template<typename T1,typename T2> inline void chmin(T1 &a,T2 b){if(a>b) a=b;}
template<typename T1,typename T2> inline void chmax(T1 &a,T2 b){if(a<b) a=b;}
//BEGIN CUT HERE
template<typename T>
struct DiameterForVertex{
  vector<T> vs,dp;
  vector<vector<int> > G;
  DiameterForVertex(int n):dp(n),G(n){}
  DiameterForVertex(vector<T> vs):vs(vs),dp(vs.size()),G(vs.size()){}
  void add_edge(int u,int v){
    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }
  void dfs(int v,int p,int &s){
    if(p<0) dp[v]=T(0);
    dp[v]+=vs[v];
    if(dp[s]<dp[v]) s=v; 
    for(int u:G[v]){
      if(u==p) continue;
      dp[u]=dp[v];
      dfs(u,v,s);
    }    
  }  
  T build(){
    assert(!vs.empty());
    int s=0;
    dfs(s,-1,s);
    dfs(s,-1,s);
    return dp[s];    
  }
  T build(vector<T> us){
    assert(us.size()==dp.size());
    vs=us;
    return build();
  }
};
//END CUT HERE

struct FastIO{
  FastIO(){
    cin.tie(0);
    ios::sync_with_stdio(0);
  }
}fastio_beet;

//INSERT ABOVE HERE

signed AGC033_C(){
  int n;
  cin>>n;
  vector<int> vs(n,1);
  DiameterForVertex<int> G(vs);
  for(int i=1;i<n;i++){
    int x,y;
    cin>>x>>y;
    x--;y--;
    G.add_edge(x,y);
  }  
  int ans=G.build();
  cout<<((ans%3!=2)?"First":"Second")<<endl;
  return 0;
}
/*
  verified on 2019/05/07
  https://atcoder.jp/contests/agc033/tasks/agc033_c
*/

signed ARC097_F(){
  int n;
  cin>>n;
  DiameterForVertex<int> G(n);
  vector<int> deg(n,0);
  for(int i=1;i<n;i++){
    int x,y;
    cin>>x>>y;
    x--;y--;
    G.add_edge(x,y);
    deg[x]++;
    deg[y]++;
  }
  
  string s;
  cin>>s;
  
  int cnt=(n-1)*2,num=0;
  queue<int> que;
  vector<int> dead(n,0);
  for(int i=0;i<n;i++){
    num+=(s[i]=='W');
    if((deg[i]==1)&&(s[i]=='B')){
      dead[i]=1;
      que.emplace(i);
    }
  }
  
  while(!que.empty()){
    int v=que.front();que.pop();
    cnt-=2;
    for(int u:G.G[v]){
      if(dead[u]) continue;
      deg[u]--;
      if(deg[u]==1&&(s[u]=='B')){
        dead[u]=1;
        que.emplace(u);
      }
    }
  }
  
  if(num<=1){
    cout<<num<<endl;
    return 0;
  }
  
  vector<int> vs(n,0);  
  for(int i=0;i<n;i++){
    if(dead[i]) continue;
    vs[i]=deg[i]+(s[i]=='W');
    vs[i]%=2;
    cnt+=vs[i];
  }
  
  cout<<cnt-G.build(vs)*2<<endl;
  return 0;            
}
/*
  verified on 2019/05/07
  https://atcoder.jp/contests/arc097/tasks/arc097_d
*/

signed main(){
  //AGC033_C();
  //ARC097_F();
  return 0;
}
