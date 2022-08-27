#include<bits/stdc++.h>
using namespace std;
class SgTree{
  public:
  vector<int>seg;
  SgTree(int n){
    seg.resize(4*n);
  }
void build(int index,int low ,int high,vector<int>&v){
     if(low==high){
         seg[index]= v[low];
         return;
     }
     int mid=(low+high)/2;
     build(2*index+1,low,mid,v);
     build(2*index+2,mid+1,high,v);
     seg[index]=min(seg[2*index+1],seg[2*index+2]);
 }
 int query(int index,int low ,int high,int l,int r){
             // no over low
             if(low>r || high < l) return INT_MAX;
             // complete overlap [l,low,high,r]
             if(low>=l and high <=r) return seg[index];
             else{
                 // partial overlap
                 int mid=(low+high)/2;
                 int left=query(2*index+1,low,mid,l,r);
                 int right=query(2*index+2,mid+1,high,l,r);
               return  min(left,right);
             }
 }
 void point_updates(int index,int low,int high,int i,int value){
            if(low==high){
              seg[index]=value;
              return;
            }
            int mid=(low+high)/2;
            if(i<=mid) point_updates(2*index+1,low,mid,i,value);
            else point_updates(2*index+2,mid+1,high,i,value);
            seg[index]=min(seg[2*index+1],seg[2*index+2]);
 }

};

solve(){
    int n;
    cin>>n;
    vector<int>v(n);
    for(int i=0;i<n;i++) cin>>v[i];
    SgTree s(n);
    s.build(0,0,n-1,v);
    int q;
    cin>>q;
    while(q--){
        int l,r;
        cout<<"enter the value of l and r between them you want to find minimum"<<endl;
        cin>>l>>r;
        cout<<s.query(0,0,n-1,l,r)<<endl;
        int index,value;
        cout<<"enter the index and value which you want to update"<<endl;
        cin>>index>>value;
        v[index]=value;
        s.point_updates(0,0,n-1,index,value);

    }
}
int main(){
    solve();
    return 0;
}