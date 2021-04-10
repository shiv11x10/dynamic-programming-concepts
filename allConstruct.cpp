#include<bits/stdc++.h>
using namespace std;

#define ll long long int

/*------------------------------Main Logic functions----------------------------*/
/* Function accepts target string and array of strings. 
The function should return 2D array containing all of the ways the 'target' can
be constructed by concatenating elements of the 'wordBank' array.
Each element of the 2D array should represent one combination that construxts the 'target' */


//without dynamic programming
vector<vector<string>> allConstruct(string target, vector<string> wordBank) {
   // if target is empty then we return empty 2D list. (base case)
   if(target.length() == 0) return vector<vector<string>> {{}};
   
   // variable to store merged result 
   vector<vector<string>> result;

   //iterate our each word from word bank and remove the suffix from target
   // them, again call the subproblem on new reduced target.
   for(int i=0; i < wordBank.size(); i++) {
      // if word is suffix of target
      if(target.find(wordBank[i]) == 0) {
         // get the reduced target
         string suffix = target.substr(wordBank[i].length());

         // here, we are only removing the suffix as if we remove any substring
         // from middle then it might create a new sequence.

         // get the vector of string from children
         vector<vector<string>> suffixWays = allConstruct(suffix, wordBank);

         // we will insert the current word at the beginning 
         //into each list of suffix array and store it in targetWays
         vector<vector<string>> targetWays;
         for(auto ele: suffixWays) {
            ele.insert(ele.begin(), wordBank[i]);
            targetWays.push_back(ele);
         }

         // add all the lists in targetWays to result.
         for(auto ele: targetWays) {
            result.push_back(ele);
         }

      }
   } 

   // we get here if none of the combinations generate result.
   // in that case totalConut will return 0.
   return result;
} // time - O((n ^ m))

//--------------------------------------------------------------------------------

//with dynamic programming - memoization
//storing the overlapping subproblems
unordered_map<string, vector<vector<string>>> memo;
vector<vector<string>> allConstructdm(string target, vector<string> wordBank) {
   // if target key is already stored return the value
   if(memo.find(target) != memo.end()) return memo[target];

   // if target is empty then we return empty 2D list. (base case)
   if(target.length() == 0) return vector<vector<string>> {{}};
   
   // variable to store merged result 
   vector<vector<string>> result;

   //iterate our each word from word bank and remove the suffix from target
   // them, again call the subproblem on new reduced target.
   for(int i=0; i < wordBank.size(); i++) {
      // if word is suffix of target
      if(target.find(wordBank[i]) == 0) {
         // get the reduced target
         string suffix = target.substr(wordBank[i].length());

         // here, we are only removing the suffix as if we remove any substring
         // from middle then it might create a new sequence.

         // get the vector of string from children
         vector<vector<string>> suffixWays = allConstructdm(suffix, wordBank);

         // we will insert the current word at the beginning 
         //into each list of suffix array and store it in targetWays
         vector<vector<string>> targetWays;
         for(auto ele: suffixWays) {
            ele.insert(ele.begin(), wordBank[i]);
            targetWays.push_back(ele);
         }

         // add all the lists in targetWays to result.
         for(auto ele: targetWays) {
            result.push_back(ele);
         }

      }
   } 

   // we get here if none of the combinations generate result.
   // in that case totalConut will return 0.
   memo[target] = result;
   return result;
} // // time - O((n ^ m))

// -------------------------------------------------------------------------------

// with dynamic programming - tabulation
vector<vector<string>> allConstructdt(string target, vector<string> wordBank) {
   // define a vector which contains a 2D vector to store all combaintion results
   // initiazlize the vector with empty list
   // here, index i will mean the substing from target[0] to target[i-1].
   // index 0 will mean an empty substring
   vector<vector<vector<string>>> table(target.length()+1, vector<vector<string>> ());
   
   // empty string is valid therefore, initialize it with empty 2D vector
   table[0] = vector<vector<string>> {{}};

   //iterate for each index of target array.
   for(int i=0;i<=target.length();i++) {
      // iterate for each word in wordbank
      for(int j=0;j<wordBank.size();j++) {
         // if substring of target string from current index upto length of 
         // current word is equal to current word that means it is a valid substring.
         if((target.compare(i, wordBank[j].length(), wordBank[j]))==0) {
            // now, we store the 2D list at index i to index i+(current word length)
            // after appending current word to each list

            // newCombinations will store appended result of table[i] 
            vector<vector<string>> newCombinations;
            for(auto x: table[i]) {
                  x.push_back(wordBank[j]);
                  newCombinations.push_back(x);
            }

            // add the newCombinations 2D list to index i+(current word length)
            for(auto ele: newCombinations)
               table[i + wordBank[j].length()].push_back(ele);
         }
      }
   }

   // for(auto x:table){
   //    for(auto y:x){
   //       for(auto z:y)
   //          cout<<z<<"  ||";
   //       cout<<"\n";
   //    }
   //    cout<<"\n";
   // }

   // return the last index value.
   // (last index will have all combinations for complete target string that can be 
   // generated from wordBank)
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
   vector<vector<string>> res = allConstructdt("purple", wordBank);
   if(res.size() == 0)
         cout<<"empty\n";
   else 
      for(auto ele: res) {
         for(auto elem: ele)
            cout<<elem<<" ";
         cout<<"\n";
      }
   cout<<"\n -----------------\n";

   vector<string> wordBank2({"ab", "abc", "cd", "def", "abcd", "ef", "c"});
   vector<vector<string>> res2 = allConstructdt("abcdef", wordBank2);
   if(res2.size() == 0)
         cout<<"empty\n";
   else 
      for(auto ele: res2) {
         for(auto elem: ele)
            cout<<elem<<" ";
         cout<<"\n";
      }
   cout<<"\n -----------------\n";

   vector<string> wordBank3({"bo", "rd", "ate", "t", "ska", "sk", "boar"});
   vector<vector<string>> res3 = allConstructdt("skateboard", wordBank3);
   if(res3.size() == 0)
         cout<<"empty\n";
   else 
      for(auto ele: res3) {
         for(auto elem: ele)
            cout<<elem<<" ";
         cout<<"\n";
      }
   cout<<"\n -----------------\n";

   vector<string> wordBank4({"a", "p", "ent", "enter", "ot", "o", "t"});
   vector<vector<string>> res4 = allConstructdt("enterapotentpot", wordBank4);
   if(res4.size() == 0)
         cout<<"empty\n";
   else 
      for(auto ele: res4) {
         for(auto elem: ele)
            cout<<elem<<" ";
         cout<<"\n";
      }
   cout<<"\n -----------------\n";

   vector<string> wordBank5({"e", "ee", "eee", "eeee", "eeeee", "eeeeee"});
   vector<vector<string>> res5 = allConstructdt("eeeeeeeef", wordBank5);
   if(res5.size() == 0)
         cout<<"empty\n";
   else 
      for(auto ele: res5) {
         for(auto elem: ele)
            cout<<elem<<" ";
         cout<<"\n";
      }
   cout<<"\n -----------------\n";
}
