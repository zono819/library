#include<bits/stdc++.h>
using namespace std;
using Int = long long;
struct SuffixArray{ 
  string s;
  vector<int> sa,rev;
  
  SuffixArray(){}
  SuffixArray(const string &S):s(S){
    int n=s.size();
    s.push_back('$');
    sa.resize(n+1);
    iota(sa.begin(),sa.end(),0);
    sort(sa.begin(),sa.end(),
         [&](int a,int b){
           if(s[a]==s[b]) return a>b;
           return s[a]<s[b];
         });
    vector<int> c(n+1,0),r(n+1),cnt(n+1);
    for(int i=0;i<=n;i++) r[i]=s[i];
    for(int len=1;len<=n;len*=2){
      for(int i=0;i<=n;i++){       
        c[sa[i]]=i;
        if(i>0 &&
           r[sa[i-1]]==r[sa[i]] &&
           sa[i-1]+len<=n &&
           r[sa[i-1]+len/2]==r[sa[i]+len/2]) c[sa[i]]=c[sa[i-1]];
      }
      iota(cnt.begin(),cnt.end(),0);
      copy(sa.begin(),sa.end(),r.begin());
      for(int i=0;i<=n;i++){
        int s1=r[i]-len;
        if(s1>=0) sa[cnt[c[s1]]++]=s1;
      }
      c.swap(r);
    }
    rev.resize(n+1);
    for(int i=0;i<=n;i++) rev[sa[i]]=i;    
  }
  int operator[](int i) const{return sa[i];}
  
  bool lt_substr(string &t,int si,int ti){
    int sn=s.size(),tn=t.size();
    while(si<sn&&ti<tn){
      if(s[si]<t[ti]) return 1;
      if(s[si]>t[ti]) return 0;
      si++;ti++;
    }    
    return si==sn&&ti<tn;
  }

  int lower_bound(string& t){
    int l=0,r=s.size();
    while(l+1<r){
      int m=(l+r)>>1;
      if(lt_substr(t,sa[m],0)) l=m;
      else r=m;
    }
    return r;
  }
  
  int upper_bound(string& t){
    t.back()++;
    int res=lower_bound(t);
    t.back()--;
    return res;
  }
  
  // O(|T|*log|S|)
  int count(string& T){
    return upper_bound(T)-lower_bound(T);
  }  
};
//BEGIN CUT HERE
struct LongestCommonPrefix{
  SuffixArray sa;
  
  vector<int> lcp,ht;
  vector<vector<int> > dat;
  LongestCommonPrefix(string &s):sa(s){
    int n=s.size();
    lcp.assign(n,0);
    
    int t=0;
    lcp[0]=0;
    for(int i=0;i<n;i++){
      int j=sa[sa.rev[i]-1];
      if(t>0) t--;
      for(;j+t<n&&i+t<n;t++){
        if(sa.s[j+t]!=sa.s[i+t]) break;
      }
      lcp[sa.rev[i]-1]=t;
    }
    
    int h=1;
    while((1<<h)<n) h++;
    dat.assign(h,vector<int>(n));
    ht.assign(n+1,0);
    for(int j=2;j<=n;j++) ht[j]=ht[j>>1]+1;
    
    for(int j=0;j<n;j++) dat[0][j]=lcp[j];
    for(int i=1,p=1;i<h;i++,p<<=1)
      for(int j=0;j<n;j++)
        dat[i][j]=min(dat[i-1][j],dat[i-1][min(j+p,n-1)]);
  }
  
  int query(int a,int b){
    if(a>b) swap(a,b);
    int l=b-a;
    return min(dat[ht[l]][a],dat[ht[l]][b-(1<<ht[l])]);
  }  
};

//END CUT HERE
//INSERT ABOVE HERE
signed ARC060_F(){
  cin.tie(0);
  ios::sync_with_stdio(0);
  
  string s;
  cin>>s;
  int n=s.size();
  {
    string t(s);
    t.erase(unique(t.begin(),t.end()),t.end());
    if(t.size()==1u){
      cout<<n<<endl<<1<<endl;
      return 0;
    }
  }
  
  vector<vector<int> > v(n+1);
  for(int i=1;i<=n;i++)
    for(int j=i+i;j<=n;j+=i)
      v[j].emplace_back(i);

  LongestCommonPrefix lcp(s);  
  auto check=
    [&](int l,int r)->int{    
      for(int x:v[r-l])
        if(lcp.query(lcp.sa.rev[l],lcp.sa.rev[l+x])>=r-l-x) return 0;
      return 1;
    };
  
  if(check(0,n)){
    cout<<1<<endl<<1<<endl;
    return 0;
  }
  
  int ans=0;
  for(int i=1;i<n;i++)
    ans+=check(0,i)&&check(i,n);
  
  cout<<2<<endl<<ans<<endl;
  return 0;
}
/*
  verified on 2019/05/23
  https://beta.atcoder.jp/contests/arc060/tasks/arc060_d
*/


signed main(){
  ARC060_F();
  return 0;
};
