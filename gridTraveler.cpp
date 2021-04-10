#include<bits/stdc++.h>
using namespace std;

#define ll long long int

/*--------------------------Main Logic functions-------------------------*/
/* We have a m x n matrix grid. Find out the number of ways 
to go from top left corner to bottom right corner.
We can move only right and down. */

//without dynamic programming
ll gridTraveler(int m, int n) {
	if(m == 1 && n == 1) return 1; //single grid cell
   if(m == 0 || n == 0) return 0; // 0 dimension grid not possible
   // either go down or go right. either way the dimension will reduce by 1.
   // And we need to add the possible steps. 
	return gridTraveler(m-1, n) + gridTraveler(m, n-1);
} //time - O(2^(n+m))

//---------------------------------------------------------------------------------

//with dynamic programming - memoization
//storing the overlapping subproblems
unordered_map<string, ll> memo;
ll gridTravelerdm(ll m, ll n) {
   //here to check if value already stored we can concatenate m and n 
   //to make them into a single key string
   string key = to_string(m) + ',' + to_string(n);
   if(memo.find(key) != memo.end()) return memo[key];

   if(m == 1 && n == 1) return 1; //single grid cell
   if(m == 0 || n == 0) return 0; // 0 dimension grid not possible

   // either go down or go right. either way the dimension will reduce by 1.
   // And we need to add the possible steps. 
   //save the value so that we can just re-use it and avoid calculating again.
   memo[key] =  gridTravelerdm(m-1, n) + gridTravelerdm(m, n-1);
   return memo[key];
} //time - O(n * m)

//---------------------------------------------------------------------------
//with dynamic programming - tabulation
ll gridTravelerdt(ll m, ll n) {
   ll table[m+1][n+1] = {};

   table[1][1] = 1;
   for(int i=0;i<=n;i++) {
      for(int j=0;j<=n;j++) {
         ll current = table[i][j];
         // add this current value to right and down cells.
         if(j+1 <= m) table[i][j+1] += current;
         if(i+1 <= m) table[i+1][j] += current;
      }
   }

   return table[m][n];
}


/*----------------------------Main Logic functions end------------------------*/


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
    cout<<gridTravelerdt(18, 18)<<"\n";
}
