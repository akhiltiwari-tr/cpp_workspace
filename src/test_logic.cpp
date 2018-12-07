#include<bits/stdc++.h>
using namespace std;

uint64_t fun(vector<uint64_t> &stops){
     uint64_t position=0, flag=0, diff_pos=0;
    //  what if the values are same.
    //  uint64_t x=0, y=0;
  for(int i=0; i<stops.size()-1; i++){ //travel through the stops taking one pair at a time
   diff_pos= ffs(stops[i] ^ stops[i+1]); //ffs= find_first_set bit position, this gives the position where the bits differ.
   if(flag & 1<<diff_pos ) return -1; //no such point exists
   else{
       flag |= 1<<diff_pos;
       position |=  stops[i] & 1<<position;
   }
  }
  return position;
}

int main()
{
    vector<uint64_t> stops={386, 385, 384, 388,259, 258, 257, 256};
    cout<<"position:"<<fun(stops)<<endl;
    return 0;
}
