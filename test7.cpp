#include<bits/stdc++.h>
using namespace std;
 vector<int> convertSarrayToPos(vector<string>& sarray) {
        unordered_map<int,int>mp;
        vector<pair<string, int>> v;
        vector<string> s2 = sarray;
        vector<int> ans(sarray.size(), 0);
        for (int i = 0; i < s2.size(); i++) {
            v.push_back({s2[i], i});
        }
        sort(sarray.begin(), sarray.end());
        vector<int> vis(sarray.size(), 0);
        for (int i = 0; i < sarray.size(); i++) {
            string st = sarray[i];
            if (!vis[i]) {
                for (int j = 0; j < v.size(); j++) {
                    if (st == v[j].first) {
                        ans[v[j].second] = i;
                        mp[v[j].second]=i;
                        vis[i] = true;
                    }
                }
            }
        }
        return ans;
    }
int main(){
vector<string>sarray = {"k","ca","sc","ti","v","cr","mn","fe"};
vector<int>ans = convertSarrayToPos(sarray);
for(auto it:ans){
    cout<<it<<" ";
}
int n=ans.size();
int *arr=new int[n];
vector<int>arr2;
for(int i=0;i<n;i++){
    arr[ans[i]]=i;
}
for(int i=0;i<n;i++){
    arr2.push_back(arr[i]);
}
cout<<endl;
for(auto it:arr2){
    cout<<it<<" ";
}


return 0;
}