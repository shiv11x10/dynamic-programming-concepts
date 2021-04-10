#include<bits/stdc++.h>
using namespace std;

#define ll long long int

/*------------------------------Main Logic functions---------------------*/
/* the function should return a boolean indicating whether or not it is possible
to generate the targetSum using numbers from array. We can use a number multiple times.  */

//without dynamic programming
bool canSum(ll targetSum, ll array[], int n) {
   // if we get 0 then sum is possible.
	if(targetSum == 0) return true;
   //if we get a negative value then we cannot go any further in recursion tree.
   if(targetSum < 0) return false;

   // here, we subtract each element of array from target sum 
   //and generate recursion cases.
   for(int i=0; i < n; i++) {
      ll remainder = targetSum - array[i];
      // if for remaining value after subtracting a number from taget sum
      // we get a true value then return true.
      // NOTE that we get a true value only when target sum becomes 0 in base case.
      if(canSum(remainder, array, n) == true) {
         return true;
      }
   }

   //we will return a false when each of possible cases have been completed.
   //we get here when none of the cases returns true.

	return false;
} //time - O(n^m)

//-----------------------------------------------------------------------------------

//with dynamic programming - memoization
//storing the overlapping subproblems
unordered_map<ll, ll> memo;
bool canSumdm(ll targetSum, ll array[], int n) {
   // if already have the value stored then return it.
   if(memo.find(targetSum) != memo.end()) return memo[targetSum];

   // if we get 0 then sum is possible.
   if(targetSum == 0) return true;
   //if we get a negative value then we cannot go any further in recursion tree.
   if(targetSum < 0) return false;

   // here, we subtract each element of array from target sum 
   //and generate recursion cases.
   for(int i=0; i < n; i++) {
      ll remainder = targetSum - array[i];
      // if for remaining value after subtracting a number from taget sum
      // we get a true value then return true.
      // NOTE that we get a true value only when target sum becomes 0 in base case.
      if(canSumdm(remainder, array, n) == true) {
         // save then value in hash before returning. so that it can be used
         // later for optimization 
         memo[targetSum] = true;
         return true;
      }
   }

   //we will return a false when each of possible cases have been completed.
   //we get here when none of the cases returns true.
   memo[targetSum] = false;
   return false;
} // time - O(m * n)

//------------------------------------------------------------------------------

//with dynamic programming - tabulation
// assign 1 at index 0 as we cam get 0 sum by taking no elements from array.
// iterate through table aray and if it possible to reach current element i.e. if
// current element is true then for each element in array 
// assign true to (table[i] + array[i]). This means that we reach every elemnt from 
// current element by adding any value from array..
bool canSumdt(ll targetSum, ll array[], int n) {
   bool table[targetSum+1];
   memset(table, false, sizeof(table));
   table[0] = true;

   for(ll i=0; i<=targetSum; i++) { // iterating table 
      if(table[i] == true) { // here, true means we can reach here by adding values from array
         for(ll j=0;j<n;j++) { // iterating array vales.
            if(i+array[j] <= targetSum)
               table[i+array[j]] = true;
         }
      }
   }

   return table[targetSum];
}


/*--------------------------Main Logic functions end---------------------------*/


/*-----------driver code-------------*/

void solve();
int main()
{
   ios_base::sync_with_stdio(false);cin.tie(NULL);
   
   #ifndef ONLINE_JUDGE
   freopen("input.txt", "r", stdin);
   //freopen("error.txt", "w", stderr);
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
   ll arr[2] = {7, 14};  
   //cout<<canSum(7, arr, 2)<<"\n";
   if(canSumdt(300, arr, 2))
      cout<<"true";
   else
      cout<<"false";
}
