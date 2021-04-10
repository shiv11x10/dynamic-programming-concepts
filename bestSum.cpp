#include<bits/stdc++.h>
using namespace std;

#define ll long long int

/*------------------------------Main Logic functions----------------------------*/
/* The function should return an array containing the shortest combination of numbers 
that add up to excatly the targetSum. If there is a tie for shortest then return
any one of the shortest.*/


//without dynamic programming
vector<ll> bestSum(ll targetSum, ll array[], int n) {
   // if we get 0 then sum is possible with empty list.
	if(targetSum == 0) return vector<ll> ();
   //if we get a negative value then we cannot go any further in recursion tree.
   //checking null value by returning -1 as vector
   if(targetSum < 0) {return vector<ll> ({-1});}

   // assign a vector for string shortest list from multiple possible results.
   vector<ll> shortestCombination({-1});

   // here, we subtract each element of array from target sum 
   //and generate recursion cases.
   for(int i=0; i < n; i++) {
      ll remainder = targetSum - array[i];
      //get the list of sub-problem elements into the vector.
      // we can get either -1 vector(null) or a vector list.
      vector<ll> remainderCombination = bestSum(remainder, array, n);

      if(remainderCombination.empty() || (remainderCombination.size() > 0 && remainderCombination[0] != -1)) {
         // add the value to vector
         remainderCombination.push_back(array[i]);
         //if shortest combination so far for that tree level is bigger than
         // current combination then update shortest combination.
         if(shortestCombination[0] == -1 || remainderCombination.size() < shortestCombination.size()) {
            shortestCombination = remainderCombination;
         }

         //we do not return here as we have to generate all possible cases
         //return remainderResult;
      }
   }

   //we will return a null when each of possible cases have been completed.
   // if no value is possible -1 vector will be returned
	return shortestCombination;
} //time - O(n^m + m)

//--------------------------------------------------------------------------------

//with dynamic programming - memoization
//storing the overlapping subproblems
unordered_map<ll, vector<ll>> memo;
vector<ll> bestSumdm(ll targetSum, ll array[], int n) {
   // If value is already calculated return the value
   if(memo.find(targetSum) != memo.end()) return memo[targetSum];

   // if we get 0 then sum is possible with empty list.
   if(targetSum == 0) return vector<ll> ();
   //if we get a negative value then we cannot go any further in recursion tree.
   //checking null value by returning -1 as vector
   if(targetSum < 0) {return vector<ll> ({-1});}

   // assign a vector for string shortest list from multiple possible results.
   vector<ll> shortestCombination({-1});

   // here, we subtract each element of array from target sum 
   //and generate recursion cases.
   for(int i=0; i < n; i++) {
      ll remainder = targetSum - array[i];
      //get the list of sub-problem elements into the vector.
      // we can get either -1 vector(null) or a vector list.
      vector<ll> remainderCombination = bestSumdm(remainder, array, n);

      if(remainderCombination.empty() || (remainderCombination.size() > 0 && remainderCombination[0] != -1)) {
         // add the value to vector
         remainderCombination.push_back(array[i]);
         //if shortest combination so far for that tree level is bigger than
         // current combination then update shortest combination.
         if(shortestCombination[0] == -1 || remainderCombination.size() < shortestCombination.size()) {
            shortestCombination = remainderCombination;
         }

         //we do not return here as we have to generate all possible cases
         //return remainderResult;
      }
   }

   //we will return a null when each of possible cases have been completed.
   // if no value is possible -1 vector will be returned
   memo[targetSum] = shortestCombination;
   return shortestCombination;
} //time - O(m * n * m)

//- ------------------------------------------------------------------------

// with dynamic programming - tabulation
// assign empty vector at index 0 as we cam get 0 sum by taking no elements from array.
// iterate through table aray and if it possible to reach current element i.e. if
// current element is not null(-1 vector) then for each element in array 
// assign vector table[i] to (table[i] + array[i]) after appending array[j] if the value
// already present at (table[i] + array[i]) is greater in size.
// This means that we reach every elemnt from current element by adding any value from array..
vector<ll> bestSumdt(ll targetSum, ll array[], int n) {
   // list with size targetSum and each value assign as -1 vector(assumes null)
   vector<vector<ll>> table(targetSum+1, vector<ll> ({-1}));
   
   table[0] = vector<ll> (); // emoty vector at 0
   for(int i=0;i<=targetSum; i++) {
      // here, table[i].empty() is to check for 0 index
      if(table[i].empty() || (table[i].size() >= 1 && table[i][0] != -1)){
         for(int j=0;j<n;j++) {
            if(i+array[j] <= targetSum) { // to not go out of bounds
               // save the list at current index
               vector<ll> combination = table[i];
               // append current value to it
               combination.push_back(array[j]);
               // check if list at i+arr[j] is null(-1 vector) or is greater in size than current list
               // note that if list at i+array[j] is already smaller we do not change it
               if(table[i+array[j]][0] == -1 || table[i+array[j]].size() > combination.size())
                  //store the smaller current list in i+array[j]
                  table[i+array[j]] = combination; 
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
   ll arr[] = {1, 2, 5, 25};  
   //cout<<canSum(7, arr, 2)<<"\n";
   vector<ll> res = bestSumdt(100, arr, sizeof(arr)/sizeof(arr[0]));
   //vector<ll> res = howSumdm(300, arr, 2);
   //if we get null back(-1 vector) then print null or print vector elements
   if((res.size() == 1 && res[0] == -1))
      cout<<"null";
   else {
      for(int i=0;i<res.size();i++)
         cout<<res[i]<<" ";
   }
}
