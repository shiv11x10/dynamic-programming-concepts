#include<bits/stdc++.h>
using namespace std;

#define ll long long

/*---------------------Main Logic functions---------------------*/

//without dynamic programming
ll fib(int n) {
	if(n<=2) return 1;
	return fib(n-1) + fib(n-2);
} //time - O(2^n)

//---------------------------------------------------------------------

//with dynamic programming - memoization
//storing the overlapping subproblems
unordered_map<ll, ll> memo;
ll fibdm(ll n) {
   //if we already have the value stored then just return it.
	if(memo.find(n)!=memo.end()) return memo[n];

	if(n<=2) return 1;
   //save the value so that we can just re-use it and avoid calculating again.
	memo[n] = fibdm(n-1) + fibdm(n-2);
	return memo[n];
} //time - O(n)

//--------------------------------------------------------------------

// with dynamic programming - tabulation
ll fibdt(ll n) {
   ll table[n+1];
   table[0] = 0; table[1] = 1;
   for(int i=2; i<=n; i++)
      table[i] = table[i-1] + table[i-2];

   return table[n];
}

/*------------------Main Logic functions end---------------------*/


/*-----------driver code-------------*/

void solve();
int main()
{
   ios_base::sync_with_stdio(false);cin.tie(NULL);
   
   #ifndef ONLINE_JUDGE
   freopen("input.txt", "r", stdin);
   // freopen("error.txt", "w", stderr);
   freopen("output.txt", "w", stdout);
   #endif
   
   int t=1;
   cin>>t;
   while(t--)
   {
      solve();
      cout<<"\n";
   }
   
   cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<endl;
   return 0;
}

void solve()
{
    //cout<<fib(6)<<"\n";
   	// cout<<fib(50);

   	cout<<fibdm(100)<<"\n";
      cout<<fibdt(6)<<"\n";
   	//cout<<fibdm(50);
   //cout<<"hello";

}
