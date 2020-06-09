vector<pair<int,int>>:: iterator it;
for(it=v.begin();it!=v.end();it++){
cout<<it->first<<" "<<it->second<<"\n";
}

#include<iostream>
#include<vector>
using namespace std;
int main(){

int mat[60][60]; //matrix of image after thresholding
int h=60;
bool ret=false;
int w=60;
vector<pair<int,int>>v; // vector for storing the coordinates of the vertices of laptop
int r=1;
while(true){
for(int i=0;i<h;i++)
{ for(int j=0;j<w;j++){
if(j*j+i*i<=(r-1)*(r-1))
continue;
else if(j*j+i*i >r*r)
break;
else{
if(mat[i][j]==1){

v.push_back({i,j});
ret=true;
break;
}
}
}
if(ret==true)
break;
}
if(ret==true)
break;

r++;
}
ret=false;
 r=1;
while(true){
for(int i=h-1;i>=0;i--)
{ for(int j=0;j<w;j++){
if(j*j+(i-h+1)*(i-h+1)<=(r-1)*(r-1))
continue;
else if(j*j+(i-h+1)*(i-h+1) >r*r)
break;
else{
if(mat[i][j]==1){

v.push_back({i,j});
ret=true;
break;
}
}
}
if(ret==true)
break;
}
if(ret==true)
break;

r++;
}
ret=false;
 r=1;
while(true){
for(int i=0;i<h;i++)
{ for(int j=w-1;j>=0;j--){
if((j-w+1)*(j-w+1)+i*i<=(r-1)*(r-1))
continue;
else if((j-w+1)*(j-w+1)+i*i >r*r)
break;
else{
if(mat[i][j]==1){

v.push_back({i,j});
ret=true;
break;
}
}
}
if(ret==true)
break;
}
if(ret==true)
break;

r++;
}



ret=false;
 r=1;
while(true){
for(int i=h-1;i>=0;i--)
{ for(int j=w-1;j>=0;j--){
if((j-w+1)*(j-w+1)+(i-h+1)*(i-h+1)<(r-1)*(r-1))
continue;
else if((j-w+1)*(j-w+1)+(i-h+1)*(i-h+1) >r*r)
break;
else{
if(mat[i][j]==1){

v.push_back({i,j});
ret=true;
break;
}
}
}
if(ret==true)
break;
}
if(ret==true)
break;

r++;
}



}


