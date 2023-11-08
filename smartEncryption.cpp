#include<bits/stdc++.h>
using namespace std;

/**
 * @brief class Utils is a helper class for all the extra function needed in order to encrypt the plain Text...
 * 
 */
class utils{
   private:

   /**
    * @brief function to convert number to binary...
    * 
    * @param num requires a number to convert it into binary and stores it into an vector array and returns it..
    * @return vector<int>  returns an array of bits..
    */
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
   public:
   /**
    * @brief function to add padding to plain text.. if plain text is not in the form to convert it into 64 bits..
    * we add padding such that it will be converted to 64 bits...
    * @param string (it requires a string as an input i.e plain text...) 
    * @return string (it returns the string with padded characters...)
    */
   string AddPadding(string s){
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
    * @brief This is a utill class function that takes a string and converts it to its corresponding ascii values ans stores it in 
    * vector of vectors ...
    * @param string (it takes string as input )
    * @return vector<vector<int>>  returns a vector of vector as output...
    */
   vector<vector<int>> convertToCorrespondingAscii(string s){
     string st=AddPadding(s);
     int len=st.length()/9;
     vector<vector<int>>ans;
     int x=0;
     for(int i=0;i<len;i++){
        int t=0;
        vector<int>temp;
        while(t<9 && t<st.length()){
          temp.push_back(st[x]);
          x++;
          t++;
        }
        ans.push_back(temp);
     }
     return ans;
   }
   /**
    * @brief This is a util class function that converts string into its bits..
    *  internally uses func AddPadding func and convertToCorrespondingAscii function..
    * @param takes string as an params..
    * @return returns vector of vector that stores converted bits of string...
    */
   vector<vector<int>>convertToBits(string s){
     string st=AddPadding(s);
     vector<vector<int>>AsciiValues = convertToCorrespondingAscii(st);
     int len=AsciiValues.size();
     vector<vector<int>>ans;
     for(int i=0;i<len;i++){
        vector<int>temp;
        temp.push_back(0);
        for(int j=0;j<AsciiValues[i].size();j++){
            vector<int>bi = ToBinary(AsciiValues[i][j]);
            for(auto it:bi){
                temp.push_back(it);
            }
        }
        ans.push_back(temp);
     }
     return ans;
   }
   /**
    * @brief This is a util class function that performs left shift operation..
    * 
    * @param vector<int>arr array on which left shift operation is to be performered..
    * @param k (integer) :-> how many bits left shift operation is to be performed..
    * @return returns vector with after performing left shift operation..
    */
   vector<int>leftShifter(vector<int>&nums,int k){
        if(k == 0 || k == nums.size()){
          return nums;
        }
        int n=nums.size();
        k=k%n;
        vector<int>ans(n);
        int j=0;
        for(int i=n-k;i<n;i++){
            ans[j++]=nums[i];
        }
        for(int i=0;i<n-k;i++){
            ans[j++]=nums[i];
        }
       return ans;
    }
   /**
    * @brief This is a utill class function that performs right shift operation..
    * 
    * @param nums array on which right shift operation is to be performed..
    * @param k no of times right shift operation is to be performed...
    * @return returns an array after performing right shift operation...
    */
   vector<int>rightShifter(vector<int>&nums,int k){
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
     * @brief This is a util class function used in key setup...
     * 
     * @param takes string (s) params which is the key...
     * @return returns a vector of int after performing required operation...
     */
    vector<int>keySetUp(string s){
       vector<string>ans;
       string st="";
       int x=0;
       for(int i=0;i<s.size();i++){
          if(s[i]==':'){
            ans.push_back(st);
            st="";
            continue;
          }else{
            st+=s[i];
          }
          x++;
       }
       ans.push_back(st);
       vector<int>v;
       for(auto it:ans){
         v.push_back(stoi(it));
       }
       vector<int>key;
       for(auto it:v){
         vector<int>x=ToBinary(it);
         for(auto j:x){
            key.push_back(j);
         }
       }
       int n=key.size();
       int pad=16-n;
       vector<int>res(pad,0);
       for(auto it:key){
         res.push_back(it);
       }
       return res;
    }
    /**
     * @brief This is a util class function which performs xor operation..
     * 
     * @param p  vector<int>..
     * @param key vector<int> (vector of keys ...)
     * @return returns a vector after performing xor operation....
     */
    vector<int>XorOperation(vector<int>&p,vector<int>&key){
       vector<int>ans;
       for(int i=0;i<p.size();i++){
         int x=(p[i]^key[i]);
         ans.push_back(x);
       }
       return ans;
    }

   //  setting up the s-array ..
   
    vector<int>Sarray(vector<string>&sarray){
       vector<pair<string,int>>v;
       vector<string>s2=sarray;
        vector<int>ans(sarray.size(),0);
        for(int i=0;i<s2.size();i++){
            v.push_back({s2[i],i});
        }

        sort(sarray.begin(),sarray.end());
        vector<int>vis(sarray.size(),0);
        for(int i=0;i<sarray.size();i++){
            string st=sarray[i];
            if(!vis[i]){
                for(int j=0;j<v.size();j++){
                    if(st==v[j].first){
                        ans[v[j].second]=i;
                        vis[i]=true;
                    }
                }
            }
        }
        return ans; 
    }

   //  Arranging p-Boxes according to s-array...

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

   //  convertint to decimal from binary...
   
   int BinaryToDecimal(vector<int>&num){
      int dec_value = 0;
      // Initializing base value to 1, i.e 2^0
      int base = 1;
      int n=num.size();
      int y=0;
      for(int i=num.size()-1;i>=0;i--){
         int x=pow(2,y)*num[i];
         dec_value+=x;
         y++;
      }
      return dec_value;
   }
};
class Encryption{
   int noOfRounds=8;
   vector<string>s_array={"ar","k","ca","sc","ti","v","cr","mn"};
   public:
   utils u;
   /**
    * Step 1. of encryption...
    * @brief Construct a new vector<vector<int>>Initial Encrypt object
    * 
    * @param msg 
    * @param k 
    */
   vector<vector<int>>InitialEncrypt(string msg,string k){
      
       vector<vector<int>> output;
      // converting the message to bits...
       vector<vector<int>>Box = u.convertToBits(msg);

      //  Initial configruation...
       int BoxSize = Box.size();

      //  setting up the key...
       vector<int>key=u.keySetUp(k);

      //  implenting the Rounds....
      
      for(int j=0;j<BoxSize;j++){
         vector<int>bitToPush;
         vector<int> InitialBits = Box[j];

         for(int roundNo = 1;roundNo <= noOfRounds;roundNo++){ 

            //  left shifting the initial 64 bits... based on the round no
            vector<int> leftShifting = u.leftShifter(InitialBits,roundNo);

            // Breaking the 64 bits into 4 p-boxes..

            vector<int>p1,p2,p3,p4;
            
            for(int bits=0;bits<=leftShifting.size();bits++){
               if(bits>=0 && bits < 16){
                  p1.push_back(leftShifting[bits]);
               }else if(bits >= 16 && bits < 32){
                  p2.push_back(leftShifting[bits]);
               }else if(bits >= 32 && bits < 48){
                  p3.push_back(leftShifting[bits]);
               }else if(bits >=48 && bits <64){
                  p4.push_back(leftShifting[bits]);
               }
            }

            // right shifting the bits of p-boxes...
            
            vector<int> q1=u.rightShifter(p1,roundNo);
            vector<int> q2=u.rightShifter(p2,roundNo);
            vector<int> q3=u.rightShifter(p3,roundNo);
            vector<int> q4=u.rightShifter(p4,roundNo);
            
            // performing initial xor operation..

            vector<int>ix1 = u.XorOperation(q1,key);
            vector<int>ix2 = u.XorOperation(q2,key);
            vector<int>ix3 = u.XorOperation(q3,key);
            vector<int>ix4 = u.XorOperation(q4,key);

             // dividing into a,b,c,d,e,f,g,h;
            vector<int>a,b,c,d,e,f,g,h;
            
            for(int xbits=0; xbits<ix1.size(); xbits++){
               if(xbits >= 0 && xbits < 8){
                  a.push_back(ix1[xbits]);
               }else if(xbits >=8 && xbits < 16){
                  b.push_back(ix1[xbits]);
               }
            }
             for(int xbits=0; xbits<ix2.size(); xbits++){
               if(xbits >= 0 && xbits < 8){
                  c.push_back(ix2[xbits]);
               }else if(xbits >=8 && xbits < 16){
                  d.push_back(ix2[xbits]);
               }
            }
             for(int xbits=0; xbits<ix3.size(); xbits++){
               if(xbits >= 0 && xbits < 8){
                  e.push_back(ix3[xbits]);
               }else if(xbits >=8 && xbits < 16){
                  f.push_back(ix3[xbits]);
               }
            }
             for(int xbits=0; xbits<ix4.size(); xbits++){
               if(xbits >= 0 && xbits < 8){
                  g.push_back(ix4[xbits]);
               }else if(xbits >=8 && xbits < 16){
                  h.push_back(ix4[xbits]);
               }
            }

            vector<vector<int>> PBoxContainer;
            PBoxContainer.push_back(a);
            PBoxContainer.push_back(b);
            PBoxContainer.push_back(c);
            PBoxContainer.push_back(d);
            PBoxContainer.push_back(e);
            PBoxContainer.push_back(f);
            PBoxContainer.push_back(g);
            PBoxContainer.push_back(h);

            // arranging a,b,c,d,e,f,g,h according s-array...

            vector<int>sarray = u.Sarray(s_array);
            
            // arranging pBox container a/c to s_array

            vector<vector<int>>SBox = u.ArrangepBox(PBoxContainer,sarray);

            // cout<<"printing SBOX after arranging with s-array "<<endl;
            // for(auto it:SBox){
            //    for(auto xt:it){
            //       cout<<xt;
            //    }cout<<endl;
            // }

            // dividing the key .... into two parts...

            vector<int>k1,k2;
            for(int ik=0;ik<key.size();ik++){
               if(ik >= 0 && ik < 8){
                  k1.push_back(key[ik]);
               }else if(ik >= 8 && ik < 16){
                  k2.push_back(key[ik]);
               }
            }

            // left shifting the key1 ... 
            k1=u.leftShifter(k1,roundNo);

            // performing xor-operation with the pBoxcontainer after s-array transformation...

            for(int sb=0;sb<SBox.size();sb++){
               SBox[sb]=u.XorOperation(SBox[sb],k1);
            }

            // // printing s-Box after xor-operation...
            // cout<<"printing sbox after xor "<<endl;
            // for(auto it:SBox){
            //    for(auto xt:it){
            //       cout<<xt;
            //    }cout<<endl;
            // }

            // left shifting the sarray...based on round numbers..

            sarray=u.leftShifter(sarray,roundNo);

            // arranging the xored sbox according to sarray again after left shifting...

            SBox = u.ArrangepBox(SBox,sarray);

            // cout<<"printing after 2nd arrangement "<<endl;

            // for(auto it:SBox){
            //    for(auto xt:it){
            //       cout<<xt;
            //    }cout<<endl;
            // }

            // right shifting the k2 for another xor - operation...
            k2=u.rightShifter(k2,roundNo);

            // performing xor operation with k2.... 

            for(int sb=0;sb<SBox.size();sb++){
               SBox[sb]=u.XorOperation(SBox[sb],k2);
            }

            // cout<<"printing after 2nd xor operation "<<endl;

            // for(auto it:SBox){
            //    for(auto xt:it){
            //       cout<<xt;
            //    }cout<<endl;
            // }
            
            leftShifting.clear();

            // again insertint the sbox data to leftshifting bits for further rounds..

            for(auto it:SBox){
               for(auto xt:it){
                  leftShifting.push_back(xt);
               }
            }
            
            bitToPush = leftShifting;
         }
         
         output.push_back(bitToPush);

      }
      return output;
   }

   string CipherText(string &msg,string &key){
      vector<vector<int>> Box = InitialEncrypt(msg,key);

      string ct="";

      // printing box

      cout<<"Box "<<Box[0].size()<<endl;
      for(auto it:Box){
         for(auto i:it){
            cout<<i<<" ";
         }cout<<endl;
      }cout<<endl;
      
      vector<vector<int>> pt;
      for(int i=0;i<Box.size();i++){
         vector<int> a,b,c,d,e,f,g,h,ik;
         for(int j=0;j<Box[i].size();j++){
            if(j >= 1 && j < 8){
               a.push_back(Box[i][j]);
            }else if(j >= 8 && j < 15){
               b.push_back(Box[i][j]);
            }else if(j >= 15 && j < 22){
               c.push_back(Box[i][j]);
            }else if(j >= 22 && j < 29){
               d.push_back(Box[i][j]);
            }else if(j >= 29 && j < 36){
               e.push_back(Box[i][j]);
            }else if(j >= 36 && j < 43){
               f.push_back(Box[i][j]);
            }else if(j >= 43 && j < 50){
                g.push_back(Box[i][j]);
            }else if(j >= 50 && j < 57){
               h.push_back(Box[i][j]);
            }else if(j>=57 && j<=63){
               ik.push_back(Box[i][j]);
            }
         }
         
         int n1=(u.BinaryToDecimal(a));
         if(n1 == 127 || n1 == 32 || n1 == 0){
            ct += '@';
         }else ct+=char(n1);
         int n2=(u.BinaryToDecimal(b));
         if(n2 == 127 || n2 == 32 || n1 == 0){
           ct += '@';
         }
         int n3=(u.BinaryToDecimal(c));
         if(n3 == 127 || n3 == 32 || n1 == 0){
            ct += '@';
         }else ct+=char(n3);
         int n4=(u.BinaryToDecimal(d));
         if(n4 == 127 || n4 == 32 || n1 == 0){
            ct += '@';
         }else ct+=char(n4);
         int n5=(u.BinaryToDecimal(e));
          if(n5 == 127 || n5 == 32 || n1 == 0){
            ct += '@';
         }else ct+=char(n5);
         int n6=(u.BinaryToDecimal(f));
          if(n6 == 127 || n6 == 32 || n1 == 0){
            ct += '@';
         }else ct+=char(n6);
         int n7=(u.BinaryToDecimal(g));
          if(n7 == 127 || n7 == 32 || n1 == 0){
            ct += '@';
         }else ct+=char(n7);
         int n8=(u.BinaryToDecimal(h));
          if(n8 == 127 || n8 == 32 || n1 == 0){
            ct += '@';
         }else ct+=char(n8);
         int n9=(u.BinaryToDecimal(ik));
          if(n9 == 127 || n9 == 32 || n1 == 0){
            ct += '@';
         }else ct+=char(n9);
      }
      return ct;
   }
};
class Decryption{
   public:
   vector<vector<int>> InitialDecrypt(string &ct,string &key){
      vector<vector<int>> Box;
      vector<int>a,b,c,d,e,f,g,h,i,j;
   }
};
int main(){
cout<<"Enter your message "<<endl;
string msg;
getline(cin,msg);
Encryption e;
// Decryption d;

cout<<"Enter the key in this  (hr:min:sec)  format..."<<endl;
string key;
cin>>key;

cout<<"Cipher text after encryption : "<<e.CipherText(msg,key)<<endl;

return 0;

}