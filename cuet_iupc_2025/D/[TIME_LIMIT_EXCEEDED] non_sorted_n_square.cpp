#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <bitset>
#include <array>
#include <stack>
#include <algorithm>
using namespace std;
 
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef double db;
 
#define mp make_pair
#define pb push_back
#define pt(i) printf("%lld\n",(ll)i)
#define mp make_pair
#define ff first
#define ss second
#define pi acos(-1.0)
#define CLR(a)          memset(a,0,sizeof(a))
#define SET(a)          memset(a,-1,sizeof(a))
 
ll in() { ll a;scanf("%lld",&a); return a;}
db din(){ db a;scanf("%lf",&a); return a; }
ll bigmod(ll b, ll p,ll md){if(p==0) return 1;if(p%2==1){ return ((b%md)*bigmod(b,p-1,md))%md;} else {ll y=bigmod(b,p/2,md);return (y*y)%md;}}
ll gcd(ll a,ll b){ if(b==0) return a; else return gcd(b,a%b);}
 
long long getRandom(long long a,long long b){
    long long ret = (long long)rand()*(long long)rand();
    ret %= (b - a + 1);
    ret += a;
    return ret;
}

int main()
{
    //freopen("in.c","r",stdin);
    //freopen("out.c","w",stdout);
    int t=in();
    while(t--)
    {
        int n=in();
        int ar[n+5];
        for(int i=0;i<n;i++)
        {
            ar[i]=in();
        }
        int ans=INT_MAX;
        for(int i=0;i<n;i++)
        {
            for(int j=i+1;j<n;j++)
            {
                ans=min(ans,ar[i]^ar[j]);
            }
        }
        pt(ans);
    }
}