#include<bits/stdc++.h>
using namespace std;
vector<int> blockToBits(vector<vector<int>>&blocks){
    vector<int>result;
    for(auto it:blocks){
        for(auto i:it){
            result.push_back(i);
        }
    }
    result.pop_back();
    return result;
}
vector<vector<int>> convertToBlocks(vector<int>&bits){
    
}
int main(){
vector<vector<int>> blocks ={
    {1,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,0}
};
vector<int>bits = blockToBits(blocks);
for(auto it:bits){
    cout<<it<<" ";
}
return 0;
}