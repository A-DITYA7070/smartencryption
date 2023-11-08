#include<bits/stdc++.h>
using namespace std;
  vector<int> performXor(vector<int>&arr,vector<int>&key){
         int len=arr.size();
        try{
            if(arr.size() != key.size())return {};
            vector<int>ans;
            for(int i=0;i<arr.size();i++){
                int x = arr[i]^key[i];
                ans.push_back(x);
            }
            return ans;
        }catch(exception e){
            cout<<"Exception occured Try again "<<endl;
            exit(0);
        }
        return {};
    }
int main(){
vector<int>bits={1,0,0,1,1,1,0,0};
vector<int>keys={0,1,0,1,1,0,1,0};
vector<int>ans = performXor(bits,keys);
for(auto it:ans){
    cout<<it<<" ";
}
return 0;
}