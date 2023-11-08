#include<bits/stdc++.h>
using namespace std;
vector<int>leftShift(vector<int>&arr,int k){
       if(k == 0 || k == arr.size()){
          return arr;
        }
        int n=arr.size();
        k=k%n;
        vector<int>ans(n);
        int j=0;
        for(int i=n-k;i<n;i++){
            ans[j++]=arr[i];
        }
        for(int i=0;i<n-k;i++){
            ans[j++]=arr[i];
        }
       return ans;
    }
int main(){
vector<int>arr={1,0,1,0,1,0,1,0};
arr = leftShift(arr,1);
for(auto it:arr){
    cout<<it<<" ";
}

return 0;
}