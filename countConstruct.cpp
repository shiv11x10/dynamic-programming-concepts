#include<bits/stdc++.h>
using namespace std;

#define ll long long int

/*------------------------------Main Logic functions----------------------------*/
/* Function accepts target string and array of strings. 
The function should return the number of ways that the target can be
constructed by concatenating elements of the wordBank array*/


//without dynamic programming
ll countConstruct(string target, vector<string> wordBank) {
   // if target is empty then we select zero words and it is considered in our answer
   // so we return 1. (base case)
   if(target.length() == 0) return 1;
   
   // variable to store total count
   ll totalCount = 0;

   //iterate our each word from word bank and remove the suffix from target
   // them, again call the subproblem on new reduced target.
   for(int i=0; i < wordBank.size(); i++) {
      // if word is suffix of target
      if(target.find(wordBank[i]) == 0) {
         // get the reduced target
         string suffix = target.substr(wordBank[i].length());

         // here, we are only removing the suffix as if we remove any substring
         // from middle then it might create a new sequence.
         ll numWaysForRest = countConstruct(suffix, wordBank);
         totalCount += numWaysForRest;
      }
   } 

   // we get here if none of the combinations generate result.
   // in that case totalConut will return 0.
   return totalCount;
} // time - O((n ^ m) * m)

//--------------------------------------------------------------------------------

//with dynamic programming - memoization
//storing the overlapping subproblems
unordered_map<string, ll> memo;
ll countConstructdm(string target, vector<string> wordBank) {
   // if target key is already stored return the value
   if(memo.find(target) != memo.end()) return memo[target];

   // if target is empty then we select zero words and it is considered in our answer
   // so we return 1. (base case)
   if(target.length() == 0) return 1;
   
   // variable to store total count
   ll totalCount = 0;

   //iterate our each word from word bank and remove the suffix from target
   // them, again call the subproblem on new reduced target.
   for(int i=0; i < wordBank.size(); i++) {
      // if word is suffix of target
      if(target.find(wordBank[i]) == 0) {
         // get the reduced target
         string suffix = target.substr(wordBank[i].length());

         // here, we are only removing the suffix as if we remove any substring
         // from middle then it might create a new sequence.
         ll numWaysForRest = countConstructdm(suffix, wordBank);
         totalCount += numWaysForRest;
      }
   } 

   // if none of the combinations generate result.
   // in that case totalConut will return 0.
   memo[target] = totalCount;
   return totalCount;
} // time - O(n * m * m)

// ----------------------------------------------------------------------------------

// with dynamic programming - tabulation
ll countConstructdt(string target, vector<string> wordBank) {
   // declare array of size target length + 1.
   // here, index i will mean the substing from target[0] to target[i-1].
   // index 0 will mean an empty substring
   ll table[target.length()+1];
   memset(table, 0, sizeof(table));

   // empty substring is valid
   table[0] = 1;

   //iterate for each index of target array.
   for(int i=0; i<= target.length(); i++) {
      // if current index is more than 0 that means substring from target[0] to target[i-1]
      // is already matched and is valid.
      if(table[i] > 0) {
         // iterate for each word in wordbank
         for(int j=0;j<wordBank.size();j++) {
            // cout<<target.substr(i, i + wordBank[j].length())<<"\n";

            // if substring of target string from current index upto length of 
            // current word is equal to current word that means it is a valid substring. 
            if((target.compare(i, wordBank[j].length(), wordBank[j]))==0){
               // add value at index i to i + (current word length) to represnt the
               // number of ways generating substrings from target[0] to target[i-1] 
               // from wordbank
               table[i + wordBank[j].length()] += table[i];
            }
         }
         // for(int k=0;k<=target.length();k++)
         //    cout<<table[k]<<" ";
         // cout<<"\n";
      }
   }

   // return the last index value.(last index will have value for complete target string)
   return table[target.length()];
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
   vector<string> wordBank({"purp", "p", "ur", "le", "purpl"});
   cout<<countConstructdt("purple", wordBank)<<"\n";

   vector<string> wordBank2({"ab", "abc", "cd", "def", "abcd"});
   cout<<countConstructdt("abcdef", wordBank2)<<"\n";

   vector<string> wordBank3({"bo", "rd", "ate", "t", "ska", "sk", "boar"});
   cout<<countConstructdt("skateboard", wordBank3)<<"\n";

   vector<string> wordBank4({"a", "p", "ent", "enter", "ot", "o", "t"});
   cout<<countConstructdt("enterapotentpot", wordBank4)<<"\n";

   vector<string> wordBank5({"e", "ee", "eee", "eeee", "eeeee", "eeeeee"});
   cout<<countConstructdt("eeeeeeeeeeeeeeeeeeeeeeeef", wordBank5)<<"\n";

}
