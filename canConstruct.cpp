#include<bits/stdc++.h>
using namespace std;

#define ll long long int

/*------------------------------Main Logic functions----------------------------*/
/* Function accepts target string and array of strings. 
The function should return a boolean indicating whether or not the target can be 
constructed by concatenating elements of the wordBank array*/


//without dynamic programming
bool canConstruct(string target, string wordBank[], int n) {
   // if target is empty then we select zero words and it is considered in our answer
   // so we return true.
   if(target.length() == 0)
         return true;
   
   //iterate our each word from word bank and remove the suffix from target
   // them, again call the subproblem on new reduced target.
   for(int i=0; i < n; i++) {
      // if word is suffix of target
      if(target.find(wordBank[i]) == 0) {
         // get the reduced target
         string suffix = target.substr(wordBank[i].length());

         // here, we are only removing the suffix as if we remove any substring
         // from middle then it might create a new sequence.

         if(canConstruct(suffix, wordBank, n) == true)
               return true;
      }
   } 

   // we get here if none of the combinations generate result.
   return false;
} // time - O((n ^ m) * m)

//--------------------------------------------------------------------------------

//with dynamic programming - memoization
//storing the overlapping subproblems
unordered_map<string, bool> memo;
bool canConstructdm(string target, vector<string> wordBank, int n) {
   // if target key is already stored return the value
   if(memo.find(target) != memo.end()) return memo[target];

   // if target is empty then we select zero words and it is considered in our answer
   // so we return true.
   if(target.length() == 0) return true;
   
   //iterate our each word from word bank and remove the suffix from target
   // them, again call the subproblem on new reduced target.
   for(int i=0; i < n; i++) {
      // if word is suffix of target
      if(target.find(wordBank[i]) == 0) {
         // get the reduced target
         string suffix = target.substr(wordBank[i].length());

         // here, we are only removing the suffix as if we remove any substring
         // from middle then it might create a new sequence.

         if(canConstructdm(suffix, wordBank, n) == true) {
            // store in hash for optimization
            memo[target] = true;
            return true;
         }
      }
   } 

   // we get here if none of the combinations generate result.
   memo[target] = false;
   return false;
} // time - O(n * m * m)

// ----------------------------------------------------------------------------

// with dynamic programming - tabulation
bool canConstructdt(string target, vector<string> wordBank) {
   // declare array of size target length + 1.
   // here, index i will mean the substing from target[0] to target[i-1].
   // index 0 will mean an empty substring
   bool table[target.length()+1];
   memset(table, false, sizeof(table));

   // empty substring is valid
   table[0] = true;

   //iterate for each index of target array.
   for(int i=0; i<= target.length(); i++) {
      // if current index is true that means substring from target[0] to target[i-1]
      // is already matched and is valid.
      if(table[i] == true) {
         // iterate for each word in wordbank
         for(int j=0;j<wordBank.size();j++) {
            // cout<<target.substr(i, i + wordBank[j].length())<<"\n";

            // if substring of target staring from current index upto length of 
            // current word is equal to current word that means it is a valid ssubstring. 
            if((target.compare(i, wordBank[j].length(), wordBank[j]))==0){
               // assign true at index i + (current word length) to represnt that
               // substring from target[0] to target[i-1] is possible to make from wordbank
               table[i + wordBank[j].length()] = true;
            }
         }
         // for(int k=0;k<=target.length();k++)
         //    cout<<table[k]<<" ";
         // cout<<"\n";
      }
   }

   // return the last index value.(last index will have bool value for complete target string)
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
   vector<string> wordBank({"ab", "abc", "cd", "def", "abcd"});
   (canConstructdt("abcdef", wordBank) == true) ? cout<<"true\n" : cout<<"false\n";

   vector<string> wordBank2({"bo", "rd", "ate", "t", "ska", "sk", "boar"});
   (canConstructdt("skateboard", wordBank2) == true) ? cout<<"true\n" : cout<<"false\n";

   vector<string> wordBank3({"a", "p", "ent", "enter", "ot", "o", "t"});
   (canConstructdt("enterapotentpot", wordBank3) == true) ? cout<<"true\n" : cout<<"false\n";

   vector<string> wordBank4({"e", "ee", "eee", "eeee", "eeeee", "eeeeee"});
   (canConstructdt("eeeeeeeeeeeeeeeeeeeeeeeeeeeef", wordBank4) == true) ? cout<<"true\n" : cout<<"false\n";
}
