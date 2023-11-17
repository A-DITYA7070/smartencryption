/**
 * @file algorithm.cpp
 * @author Aditya Raj
 * @brief Symmmetric key encryption algorithm..
 * @version 0.1
 * @date 2023-11-08
 * 
 * @copyright Copyright (c) 2023 smartencryption.com
 * 
 */

#include<bits/stdc++.h>
using namespace std;

/**
 * @brief class that contains functions that are being used along with actual functions 
 *        Basically these are helper functions.
 * 
 */

class Utils{

    public:

    /**
     * Utils function to convert a given number to its binary..
     * returns a vector that contains binary bits of corresponding number..
     */
    vector<int>convertToBinary(int num){
        vector<int>ans;
        while(num != 0){
            int dig=num%2;
            num=num/2;
            ans.push_back(dig);
        }
        reverse(ans.begin(),ans.end());
        int len = 7 - ans.size();
        // vector<int>ans2;
        // for(int i=0;i<len;i++){
        //     ans2.push_back(0);
        // }
        // for(auto it:ans){
        //     ans2.push_back(it);
        // }
        return ans;
    }
    /**
     * Utils function to convert a given binary number to integer...
     * @returns an integer after converting from binary bits array..
     */
    int binaryToInteger(vector<int>&arr){
        int count=0;
        int ans=0;
        for(int i=arr.size()-1;i>=0;i--){
            ans += (arr[i] * pow(2,count));
            count++;
        }
        return ans;
    }
    /**
     * Utils function that add padding to plain text means if text is impure it makes 
     * it pure/ready to be encrypted...
     */
    string addPadding(string &s){
       string st="";
      for(int i=0;i<s.length();i++){
        if(s[i]==' '){
            st.push_back('@');
        }else{
            st.push_back(s[i]);
        }
      }
      int n=st.length();
      if(n>9){
        if(n%9 != 0){
            n=n+9-(n%9);
            int len=st.length();
            while(len != n){
                st.push_back('@');
                len++;
            }
         }
      }else if(n<9){
         int len=st.length();
         while(len != 9){
            st.push_back('@');
            len++;
         }
      }
      return st;
    }
    /**
     *Utils function to get corresponding ascii value of a character... 
     */
    int getAscii(char x){
       return int(x);
    }
    /**
     * Utils function to left shift an array of bits with its required position...
     */
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
    /**
     * Utils function to right shift the given array by given position...
     * @return a vector of right shifted array by given position..
     */
    vector<int>rightShift(vector<int>&nums,int k){
        if(k == 0 || k == nums.size()){
          return nums;
        }
        int n=nums.size();
        k=k%n;
        vector<int>ans(n);
        int j=0;
        for(int i=k;i<n;i++){
            ans[j++]=nums[i];
        }
        for(int i=0;i<k;i++){
            ans[j++]=nums[i];
        }
        return ans;
    }
    /**
     * Utils function to get ascii value of each corresponding chars of plain text..
     */
    vector<int>asciiValueOfPt(string &pt){
        vector<int>ans;
        for(int i=0;i<pt.length();i++){
            int x=getAscii(pt[i]);
            ans.push_back(x);
        }
        return ans;
    }
    /**
     * utils function to set up initial key i.e set up key for xor operation..
     * @returns a vector of bits required for performing xor operation...
     */
    vector<int>inititalKeySetUp(string st){
        vector<string>v;
        string x="";
        for(int i=0;i<st.length();i++){
            if(st[i] == ':'){
                v.push_back(x);
                x="";
            }else{
                if(st[i]=='0' && st[i-1]==':')continue;
                x+=st[i];
            }
        }
        v.push_back(x);
        vector<int>ans;
        vector<int>hr;
        vector<int>min;
        vector<int>sec;
        for(int i=0;i<v.size();i++){
            if(i == 0){
                int result=0;
                string str=v[i];
                for(int j=0;j<str.length();j++){
                    result = result*10 + (str[j]-'0');
                }
                hr=convertToBinary(result);
            }else if(i == 1){
                int result=0;
                string str=v[i];
                for(int j=0;j<str.length();j++){
                    result = result*10 + (str[j]-'0');
                }
                min=convertToBinary(result);
            }else{
                int result=0;
                string str=v[i];
                for(int j=0;j<str.length();j++){
                    result = result*10 + (str[j]-'0');
                }
                sec=convertToBinary(result);
            }
        }
        int len1=hr.size();
        int len1short = 4-len1;
        if(len1short != 0){
            for(int i=0;i<len1short;i++){
            ans.push_back(0);
            }
        }
        for(auto it:hr)ans.push_back(it);
        int len2=min.size();
        int min1short = 6-len2;
        if(min1short != 0){
            for(int i=0;i<min1short;i++){
                ans.push_back(0);
            }
        }
        for(auto it:min)ans.push_back(it);
        int len3=sec.size();
        int sec1short=6-len3;
        if(sec1short!=0){
            for(int i=0;i<sec1short;i++){
                ans.push_back(0);
            }
        }
        for(auto it:sec)ans.push_back(it);
        return ans;
    }
    /**
     * Utils class function that takes 16 bits keys array and converts to two keys k1 of 8 bits and k2 of 8 bits
     * for further xor operation...
     * @returns vector<vector<int>> having key1 at 0th pos and key2 at 1th pos..
     */
    vector<vector<int>> divideKeys(vector<int>&keyBits){
        vector<vector<int>>ans;
        vector<int>temp1;
        vector<int>temp2;
        for(int i=0;i<keyBits.size();i++){
            if(i<8){
               temp1.push_back(keyBits[i]);
            }else{
                temp2.push_back(keyBits[i]);
            }
        }
        ans.push_back(temp1);
        ans.push_back(temp2);
        temp1.clear();
        temp2.clear();
        return ans;
    }
    /**
     * utils function to convert sarray to its corresponding position..
     * @returns vector<int> having position of each ele ...
     */
    vector<int> convertSarrayToPos(vector<string>& sarray) {
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
                        vis[i] = true;
                    }
                }
            }
        }
        return ans;
    }
    /**
     * Utils function to arrange PBoxes according to s-array..
     * @return vector<vector<int>> of blocks after arranging them according to s-array..
     */
    vector<vector<int>>ArrangepBox(vector<vector<int>>&temp,vector<int>&sarray){
        vector<vector<int>>res(temp.size(),vector<int>(temp[0].size()));
        for(int i=0;i<temp.size();i++){
            int t=sarray[i];
            for(int j=0;j<temp[i].size();j++){
                res[t][j]=temp[i][j];
            }
        }
        return res;
    }
    /**
     * Utils function to generate bits of 63 bits size from blocks...
     * ans last bit is stored and sent for decryption purpose...
     * @return a pair in which first ele is vector of bits and second ele is stored bit ...
     */
    pair<vector<int>,int> blockToBits(vector<vector<int>>&blocks){
        vector<int>result;
        for(auto it:blocks){
            for(auto i:it){
                result.push_back(i);
            }
        }
        int stored = result[result.size()-1];
        result.pop_back();
        return {result,stored};
    }
    /**
     * Encryption function that takes bits array after completion of 8th round and convert it to cipher text.
     * it does not considers the last remaining bits beacause it will be sent along with header to decryption side...
     * since we added one extra bits during encryption hence we are removing it for now..
     * @returns cipher text generated by the algorithm...
     */
    string convertToCipherText(vector<vector<int>>&bits){
       string ans="";
       for(int i=0;i<bits.size();i++){
          int x=binaryToInteger(bits[i]);
          ans += char(x);
       }
       return ans;
    }
    /**
     * Encryption function that converts plain text into 64 bits ..
     * we add one extra bit to the end of the generated bits because its len will be 63 and to make it 64 we 
     * add one extra bit.. to perform further operation during decryption this extra bit is sent along with header 
     * and used in decryption process to get the original plain text...
     * @returns a vector of 64 bits binary converted array
     */
    vector<int>convertToBits(string &pt){
       vector<int>ans;
       vector<int>ascii = asciiValueOfPt(pt);
    //    for(auto it:ascii)cout<<it<<" ";
    //    cout<<endl;
       for(auto &it:ascii){
           vector<int>temp = convertToBinary(it);
           for(auto i:temp){
              ans.push_back(i);
           }
           temp.clear();
       }
       ans.push_back(0);
       return ans;
    }
    /**
     * Encryption function that converts 64 bits into 8 bits blocks..
     * @returns vector<vector<int>> that contains 8 bits block each.. 
     */
    vector<vector<int>> convertToBlocks(vector<int>&bits,int pos){
        vector<vector<int>>ans;
        int j=0;
        for(int i=0;i<bits.size();i=i+pos){
            vector<int>temp;
            while(j<(i+pos) && j<bits.size()){
                temp.push_back(bits[j]);
                j++;
            }
            ans.push_back(temp);
            temp.clear();
        }
        return ans;
    }
    /**
     * Encryption function to perform xor operation between two arrays ...
     * @returns a array after performing xor operation...
     */
    vector<int> performXor(vector<int>&arr,vector<int>&key){
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
};

/**
 * @brief This class contains template/skeleton for creating object for encrypting the messages..
 */
class Encryption{
    private:
    
    public:
    /**
     * @brief Object of utils class neccessary for using utils class functions..
     */
    Utils obj;
    /**
     * @brief :- SARRAY is used for the shifting of blocks after performing xor operation with first key i.e k1
     *           and after shifting according to sarray we perform another xor operation with second key i.e k2..
     * 
     */
    vector<string>SARRAY = {"K","CA","SC","TI","V","CR","MN","FE"};

    /**
     * Encryption function to encrypt the plain text to cipher text we will perform this is following steps...
     * 1.perform padding of plain text... (To be implemented)..
     * 2.convert (first 9 text) of pt to bits...(after its encryption process other 9 and so on till all letters processed.)
     * 3.convert bitsPt to blocks (8 P-Blocks)..
     * 4.make keys available for performing xor operation...
     *   a). convert keys into bits
     *   b). divide keysbits to key1 and key2..
     * 5.go ahead with round functions...
     *   a)left shift each blocks (a,b,c...h) by round number..
     *   b)perform xor operation with key1..
     *   c)shift blocks based on SARRAY...
     *   d)perform xor operation with k2..
     *   e)left shift sarray based on round number...
     *   f)combine each blocks again to 64 bits.. (rename it from a..h);
     *   g)process them to next block for same operation..
     * 6.perform 8 round ...
     * 7.combine the 8 blocks to obtains 64 bits..
     * 8.record last bit and send it along with header for decryption process.
     * 9.from rest 63 bits generate cipher text by converting them back to char from ascii..
     * 10.The obtained cipher text is the required cipher text after converting...
     * 
     * @returns pair of {string,int} where string is the cipher text obtained and int is the stored text for decryption purpose...
     * 
     */
    pair<string,int> encryptPlainText(string pt,string key){

        // perform padding to plain text ... (to be implemented....)

        vector<int>keyBits=obj.inititalKeySetUp(key);
        vector<vector<int>>keys=obj.divideKeys(keyBits);
        vector<int>k1 = keys[0];
        vector<int>k2 = keys[1];
        vector<int> sarraypos = obj.convertSarrayToPos(SARRAY);
         
        // converting the plain text to bits array...

        vector<int>bitsPt=obj.convertToBits(pt);
        
        // Initial shifting of bits ...

        // bitsPt = obj.leftShift(bitsPt,1);

        // converting the bits array to blocks..

        vector<vector<int>>blocks = obj.convertToBlocks(bitsPt,8);
       
        int roundNo = 1;

        // while(roundNo <= 8){

            // step 1. performing left shift..

            for(int i=0;i<blocks.size();i++){
                blocks[i] = obj.leftShift(blocks[i],roundNo-1);
            }
            
            // step 2. performing xor operation with key1 -> (k1)...
            
            for(int i=0;i<blocks.size();i++){
                blocks[i] = obj.performXor(blocks[i],k1);
            }
            
            // step 3. shifting blocks based on sarray ...

             blocks = obj.ArrangepBox(blocks,sarraypos);

            // step 4. perform xor operation with key2 -> (k2)...

            for(int i=0;i<blocks.size();i++){
                blocks[i] = obj.performXor(blocks[i],k2);
            }
            
            //step 5. shift sarray based on roundNo-1; (to be implemented...)
            
            //  sarraypos = obj.leftShift(sarraypos,1);

            //step . shift key based on round No ...

            k1 = obj.rightShift(k1,roundNo-1);
            k2 = obj.rightShift(k2,roundNo-1);

            // increase roundNo...
            roundNo ++;
        // }
        
        pair<vector<int>,int> fbits = obj.blockToBits(blocks);
        int storedBit = fbits.second;
        vector<int>finalBits = fbits.first;
        
        //last step :- performing last shifting operation..

        finalBits = obj.leftShift(finalBits,1);

        vector<vector<int>>fblocks = obj.convertToBlocks(finalBits,7);
        
        string ct = obj.convertToCipherText(fblocks);

        return {ct,storedBit};
    }
       
};

/**
 * @brief This class contains functions to manage decryption of the cipher text..
 */
class Decryption{
    private:
    vector<int>converttobits(string &ct){
       vector<int>ascii = obj.asciiValueOfPt(ct);
       vector<int> ans;
       for(auto it:ascii){
          vector<int>temp = obj.convertToBinary(it);
          int len=7-temp.size();
          while(len != 0){
            ans.push_back(0);
            len--;
          }
          for(auto i:temp){
            ans.push_back(i);
          }
       }
       return ans;
    }
    public:

    vector<string>SARRAY = {"K","CA","SC","TI","V","CR","MN","FE"};
    
    Utils obj;

    string decryptCipherText(string &ct,string key,int storedbit){
        
        vector<int>keyBits=obj.inititalKeySetUp(key);
        vector<vector<int>>keys=obj.divideKeys(keyBits);
        vector<int>k1 = keys[0];
        vector<int>k2 = keys[1];
        
        // performing neccessary operation for s-array..

        vector<int> sarraypos = obj.convertSarrayToPos(SARRAY);
        int n=sarraypos.size();
        int *arr=new int[n];
        vector<int>arr2;
        for(int i=0;i<n;i++){
            arr[sarraypos[i]]=i;
        }
        for(int i=0;i<n;i++){
            arr2.push_back(arr[i]);
        }
        
        vector<int>bits = converttobits(ct);

        // initial shifting ...

        bits = obj.rightShift(bits,1);
        
        bits.push_back(storedbit);

        // converting the given bits.. array  to blocks...
      
        vector<vector<int>> blocks = obj.convertToBlocks(bits,8);
        
        int roundNumber = 1;

        // while(roundNumber >= 1){
            
            // shift key based on round No...

            k1 = obj.leftShift(k1,roundNumber-1);
            k2 = obj.leftShift(k2,roundNumber-1);
            // step 1. perform xor operation with k2..

            for(int i=0;i<blocks.size();i++){
                blocks[i]=obj.performXor(blocks[i],k2);
            }
            
            // step 2. shifting blocks based on sarray...
            
            blocks = obj.ArrangepBox(blocks,arr2);
    
            // step 3. performing xor operation with k1..

            for(int i=0;i<blocks.size();i++){
                blocks[i] = obj.performXor(blocks[i],k1);
            }
            
            //step 4. performing right shift..

            for(int i=0;i<blocks.size();i++){
                blocks[i]=obj.rightShift(blocks[i],roundNumber-1);
            }
        
            roundNumber--;
        // }
        
        
        
        pair<vector<int>,int> fbits = obj.blockToBits(blocks);

        vector<int>finalBits = fbits.first;
        
        // performing initial shifting of bits..
        

        


        vector<vector<int>>fblocks = obj.convertToBlocks(finalBits,7);
       
        string pt = obj.convertToCipherText(fblocks);

        return pt;
    }
};


int main(){
cout<<"Enter the plain text to encrypt it "<<endl;
string msg;
getline(cin,msg);
cout<<"Enter the key (hh:min:sec) in format "<<endl;
string key;
cin>>key;

Encryption encObj;
Decryption decObj;

Utils obj;

msg = obj.addPadding(msg);

if(msg.length() > 9){
    cout<<"I am not coded to handle length more than 9 terminating the program... ): "<<endl;
    exit(0);
}

// Ideally it will encrypt upto 9 text ....

pair<string,int>ct = encObj.encryptPlainText(msg,key);

cout<<"Cipher text obtained after encryption is : "<<ct.first<<endl;

string dec = decObj.decryptCipherText(ct.first,key,ct.second);

cout<<dec<<endl;

string decryptedText = "";

for(int i=0;i<dec.length();i++){
    if(dec[i] == '@'){
        continue;
    }else if(dec[i]=='='){
        decryptedText+=' ';
    }else{
        decryptedText+=dec[i];
    }
}

cout<<"The plain text after decryption is : "<<decryptedText<<endl;

return 0;
}