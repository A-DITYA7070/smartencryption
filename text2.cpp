#include<bits/stdc++.h>
using namespace std;
vector<int> ToBinary(int num){
     vector<int>ans;
     while(num != 0){
        int dig=num%2;
        num=num/2;
        ans.push_back(dig);
     }
     reverse(ans.begin(),ans.end());
     return ans;
}
 int binaryToInteger(vector<int>&arr){
        int count=0;
        int ans=0;
        for(int i=arr.size()-1;i>=0;i--){
            ans += (arr[i] * pow(2,count));
            count++;
        }
        return ans;
    }
    vector<vector<int>> convertToBlocks(vector<int>&bits){
        vector<vector<int>>ans;
        int j=0;
        for(int i=0;i<bits.size();i=i+8){
            vector<int>temp;
            while(j<(i+8) && j<bits.size()){
                temp.push_back(bits[j]);
                j++;
            }
            ans.push_back(temp);
            temp.clear();
        }
        return ans;
    }
int main(){
// vector<int>ans={0,1,1,1};
// cout<<binaryToInteger(ans);
vector<int>bits={1,0,1,1,1,0,0,1,0,1,1,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,1,0,1,0,1,1,1,0,0,1,0,1,1,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,1,0};
cout<<bits.size()<<endl;
vector<vector<int>>ans = convertToBlocks(bits);
for(auto it:ans){
    for(auto i:it){
        cout<<i<<" ";
    }cout<<endl;
}
return 0;
}