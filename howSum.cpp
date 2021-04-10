#include<bits/stdc++.h>
using namespace std;

#define ll long long int

/*------------------------------Main Logic functions----------------------------*/
/* the function should return an array containing any combination of elements
that add up to exactly the targetSum. If there is no combination return null.
If there are multiple combinations, you may return any single one. */


//without dynamic programming
vector<ll> howSum(ll targetSum, ll array[], int n) {
   // if we get 0 then sum is possible with empty list.
	if(targetSum == 0) return vector<ll> ();
   //if we get a negative value then we cannot go any further in recursion tree.
   //checking null value by returning -1 as vector
   if(targetSum < 0) {return vector<ll> ({-1});}

   // here, we subtract each element of array from target sum 
   //and generate recursion cases.
   for(int i=0; i < n; i++) {
      ll remainder = targetSum - array[i];
      //get the list of elements into the vector.
      // If the vector is not -1 vector(NULL concept) 
      //then add current element to it and return 
      vector<ll> remainderResult = howSum(remainder, array, n);
      if(remainderResult.empty() || (remainderResult.size() > 0 && remainderResult[0] != -1)) {
         remainderResult.push_back(array[i]);
         return remainderResult;
      }
   }

   //we will return a null when each of possible cases have been completed.
   //we get here when none of the cases returns a value.

	return vector<ll> ({-1});
} //time - O(n^m + m)

//--------------------------------------------------------------------------------

//with dynamic programming - memoization
//storing the overlapping subproblems
unordered_map<ll, vector<ll>> memo;
vector<ll> howSumdm(ll targetSum, ll array[], int n) {
   // If value is already calculated return the value
   if(memo.find(targetSum) != memo.end()) return memo[targetSum];

   // if we get 0 then sum is possible with empty list.
   if(targetSum == 0) return vector<ll> ();
   //if we get a negative value then we cannot go any further in recursion tree.
   //checking null value by returning -1 as vector
   if(targetSum < 0) {return vector<ll> ({-1});}

   // here, we subtract each element of array from target sum 
   //and generate recursion cases.
   for(int i=0; i < n; i++) {
      ll remainder = targetSum - array[i];
      //get the list of elements into the vector.
      // If the vector is not -1 vector(NULL concept) 
      //then add current element to it and return 
      vector<ll> remainderResult = howSumdm(remainder, array, n);
      if(remainderResult.empty() || (remainderResult.size() > 0 && remainderResult[0] != -1)) {
         remainderResult.push_back(array[i]);
         // save the value of vector for future use in optimization.
         memo[targetSum] = remainderResult;
         return memo[targetSum];
      }
   }

   //we will return a null when each of possible cases have been completed.
   //we get here when none of the cases returns a value.
   vector<ll> r({-1});
   memo[targetSum] = r;
   return r;
} //time - O(n * m * m)

//---------------------------------------------------------------------------------

//with dynamic programming - tabulation
// assign empty vector at index 0 as we cam get 0 sum by taking no elements from array.
// iterate through table aray and if it possible to reach current element i.e. if
// current element is not null(-1 vector) then for each element in array 
// assign vector table[i] to (table[i] + array[i]) after appending array[j]. 
// This means that we reach every elemnt from 
// current element by adding any value from array..
vector<ll> howSumdt(ll targetSum, ll array[], int n) {
   // list with size targetSum and each value assign as -1 vector(assumes null)
   vector<vector<ll>> table(targetSum+1, vector<ll> ({-1}));
   
   table[0] = vector<ll> (); // emoty vector at 0
   for(int i=0;i<=targetSum; i++) {
      // here, table[i].empty() is to check for 0 index
      if(table[i].empty() || (table[i].size() >= 1 && table[i][0] != -1)){
         for(int j=0;j<n;j++) {
            if(i+array[j] <= targetSum) {
               table[i+array[j]] = table[i];
               table[i+array[j]].push_back(array[j]); 
            }
         }
      }
   }
   // for(auto x:table) {
   //    for(auto y: x)
   //       cout<<y<<" ";
   //    cout<<"\n";
   // }

   return table[targetSum];
}


/*-----------------------------Main Logic functions end--------------------------*/


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
   ll arr[2] = {2, 3};  
   //cout<<canSum(7, arr, 2)<<"\n";
   //vector<ll> res = howSum(7, arr, 2);
   vector<ll> res = howSumdt(7, arr, 2);
   //if we get null back(-1 vector) then print null or print vector elements
   if(res.size() == 1 && res[0] == -1)
      cout<<"null";
   else {
      for(int i=0;i<res.size();i++)
         cout<<res[i]<<" ";
   }
}
