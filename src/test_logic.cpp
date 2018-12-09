#include<bits/stdc++.h>
using namespace std;

uint64_t fun(vector<uint64_t> &stops){
     uint64_t position=0, flag=0, diff_pos=0;
  for(int i=0; i<stops.size()-1; i++){ //travel through the stops taking one pair at a time
  uint64_t xored = stops[i] ^ stops[i+1];  // getting the bit positions where they differ
  diff_pos = log2(xored);// getting the MSB bit position where they differ.
   if(flag & 1<<diff_pos ) {
       if(position& 1<<diff_pos == stops[i]& 1<<diff_pos){
           return -1;
       }
   }
   else{
       flag |= 1<<diff_pos;
    position = position | stops[i] & 1<<diff_pos;
   }
  }
  return position;
}

int main()
{
    vector<uint64_t> stops={386, 385, 384, 388, 259, 258, 257, 256};
    cout<<"position:"<<fun(stops)<<endl;
    return 0;
}
