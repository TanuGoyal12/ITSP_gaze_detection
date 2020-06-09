#include<iostream>
#include<fstream>
using namespace std;

int pow(int a,int b){
	int ans = 1;
	for (int i=0;i<b;i++){
		ans = ans*a;
	}
	return ans;
}


void prod(double M1[], double M2[],double target[], int m, int n, int p){
	for (int i=0;i<m;i++){
		for (int j=0;j<p;j++){
			double res;
			res = 0.0;
			for (int k=0;k<n;k++){
				//res = res + M1[i][k]*M2[k][j];                                  
				res = res + M1[i*n + k]*M2[k*p + j];
			}
			target[i*p + j] = res;
		}
	}
	return;

}

void transpose(double M[],double target[], int m, int n){
	for (int i=0;i<m;i++){
		for (int j=0;j<n;j++){
			target[j*m + i] = M[i*n+ j];
		}
	}
	return;
}

double det(double M[], int n){
	double ans;
	ans = 0.0;
	if(n==1){
		return M[0];
	}
	for (int i=0;i<n;i++){
		double m[(n-1)*(n-1)];
		
		for (int j=1;j<n;j++){
			for (int k=0;k<i;k++){
				//m[j-1][k] = M[j][k];
				m[(j-1)*(n-1) + k] = M[j*n + k];
			}
			for (int k=i+1;k<n;k++){
				//m[j-1][k-1] = M[j][k];
				m[(j-1)*(n-1) + (k-1)] = M[j*n + k];
			}
		}
		ans = ans + pow(-1,i)*M[i]*det(m,n-1);
	}
	return ans;

}

void inverse(double M[], double target[], int n){
	double p;
	p = det(M,n);

	for (int i=0;i<n;i++){
		for (int j=0;j<n;j++){
			double m[(n-1)*(n-1)];
			
			for (int i1=0;i1<i;i1++){
				for (int j1=0;j1<j;j1++){
					//m[i1][j1] = M[i1][j1];
					m[i1*(n-1) + j1] = M[i1*n + j1];
				}
				for (int j1=j+1;j1<n;j1++){
					//m[i1][j1-1] = M[i1][j1];
					m[i1*(n-1) + j1-1] = M[i1*n + j1];
				}
			}
			for (int i1=i+1;i1<n;i1++){
				for (int j1=0;j1<j;j1++){
					//m[i1-1][j1] = M[i1][j1];
					m[(i1-1)*(n-1) + j1] = M[i1*n + j1];
				}
				for (int j1=j+1;j1<n;j1++){
					//m[i1-1][j1-1] = M[i1][j1];
					m[(i1-1)*(n-1) + j1-1] = M[i1*n + j1];
				}
			}
			double element;
			element = double(pow(-1,i+j)*det(m,n-1))/p;
			target[i*n + j] = element;
		}
	}
}

int main(){
	int d;
	d = 50;
	double X[2*d],y1[d],y2[d],X_ag[6*d],T1[6*d],T2[6*6],T3[6*6],T4[6],Theta[6];

	ifstream file("me2.txt");
    char data;
    int n = 0;
    while (n < 50){
        //cout<<" ="<<n<<"= ";
        for (int i=0; i<4; i++){
            file>>data;
            int res = 0;

            while(data != ',' && data != '\n'){
                if (data =='1' || data =='2' || data =='3' ||data =='4' ||data =='5' ||data =='6' ||data =='7' ||data =='8' ||data =='9' ||data =='0' ){
                   int b = data - 48;
                   res = res*10+b;
                }
                file>>data;
            }
            if (i==0 || i==1){
            	X[n*2 + i] = res;
            }
            if (i==2){
            	y1[n] = res;
            }
            if (i==3){
            	y2[n] = res;
            }
        }

        n++;
    }
    file.close();

    for (int i=0;i<d;i++){
		X_ag[i*6 + 0] = 1.0;
		X_ag[i*6 + 1] = X[i*2 + 0];
		X_ag[i*6 + 2] = X[i*2 + 1];
		X_ag[i*6 + 3] = X[i*2 + 0]*X[i*2 + 0];
		X_ag[i*6 + 4] = X[i*2 + 0]*X[i*2 + 1];
		X_ag[i*6 + 5] = X[i*2 + 1]*X[i*2 + 1];
	}

	transpose(X_ag,T1,d,6);
	prod(T1,X_ag,T2,6,d,6);
	inverse(T2,T3,6);
	prod(T1,y1,T4,6,d,1);
	prod(T3,T4,Theta,6,6,1);

	for (int i=0;i<6;i++){
		cout<<Theta[i]<<endl;
	}


	return 0;
}