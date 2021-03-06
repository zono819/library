#ifndef call_from_test
#include<bits/stdc++.h>
using namespace std;
using Int = long long;
#endif
//BEGIN CUT HERE
template<typename V>
V compress(V v){
  sort(v.begin(),v.end());
  v.erase(unique(v.begin(),v.end()),v.end());
  return v;
}
template<typename T>
map<T, int> dict(const vector<T> &v){
  map<T, int> res;
  for(int i=0;i<(int)v.size();i++)
    res[v[i]]=i;
  return res;
}
map<char, int> dict(const string &v){
  return dict(vector<char>(v.begin(),v.end()));
}
//END CUT HERE
#ifndef call_from_test
//INSERT ABOVE HERE
signed ABC036_C(){
  int n;
  cin>>n;
  vector<int> a(n);
  for(int i=0;i<n;i++) cin>>a[i];
  auto v=compress(a);
  auto m=dict(v);
  for(int i=0;i<n;i++) cout<<m[a[i]]<<endl;
  return 0;
}
/*
  verified on 2018/08/26
  https://abc036.contest.atcoder.jp/tasks/abc036_c
*/

signed main(){
  ABC036_C();
  return 0;
}
#endif
