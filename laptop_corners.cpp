
#include<bits/stdc++.h>
using namespace std;
int mat[50][80];
int h=50;
int w=80;
vector<pair<int,int>>v;
void func1(){
int rt=0;
bool res=false;
while(true){
int x=0;
int y=rt;
while(y>=0 && y<w && x>=0 && x<h){
if(mat[x][y]){
//cout<<x<<y<<"\n";
v.push_back({x,y});
res=true;
break;
}

y=y-1;
x=x+1;
}
if(res)
break;
rt++;}
return;
}

void func2(){
int rt=0;
bool res=false;
while(true){
int x=h-1;
int y=rt;
while(y>=0 && y<w && x>=0 && x<h){
if(mat[x][y]){
v.push_back({x,y});
res=true;
break;
}

y=y-1;
x=x-1;
}
if(res)
break;
rt++;}
return;
}

void func3(){
int rt=0;
bool res=false;
while(true){
int x=0;
int y=w-1-rt;
while(y>=0 && y<w && x>=0 && x<h ){
if(mat[x][y]){
v.push_back({x,y});
res=true;
break;
}

y=y+1;
x=x+1;
}
if(res)
break;
rt++;}
return;
}

void func4(){
int rt=0;
bool res=false;
while(true){
int x=h-1;
int y=w-1-rt;
while(y>=0 && y<w && x>=0 && x<h){
if(mat[x][y]){
//cout<<x<<y<<"\n";
v.push_back({x,y});
res=true;
break;
}

y=y+1;
x=x-1;
}
if(res)
break;
rt++;}
return;
}
int main()
{  ios_base::sync_with_stdio(false);
    cin.tie(NULL);
for(int i=0;i<50;i++){
for(int j=0;j<80;j++){
mat[i][j]=0;}
}
mat[20][50]=1;
mat[20][51]=1;
mat[21][50]=1;
mat[11][51]=1;
mat[20][70]=1;
mat[31][70]=1;
mat[20][71]=1;
mat[21][70]=1;
mat[40][60]=1;
mat[40][61]=1;
mat[41][60]=1;
mat[41][61]=1;
mat[42][76]=1;
mat[42][76]=1;
mat[41][76]=1;
mat[41][76]=1;

func1();
func2();
func3();
func4();
for(int i=0;i<4;i++){
cout<<v[i].first<<" "<<v[i].second<<"\n";
}

// vector for storing the coordinates of the vertices of laptop

return 0;}
