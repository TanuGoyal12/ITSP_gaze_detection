#include<iostream>
using namespace std;

int pow(int a,int b){
	int ans = 1;
	for (int i=0;i<b;i++){
		ans = ans*a;
	}
	return ans;
}

struct Matrix{
	int h;
	int w;
	int data[100][100];


	Matrix(int a,int b){
		h = a;
		w = b;
	}

	void print(){
		for (int i=0;i<h;i++){
			for (int j=0;j<w;j++){
				cout<<data[i][j]<<" ";
			}
			cout<<endl;
		}
		cout<<endl;
	}

	Matrix transpose(){
		Matrix T(w,h);
		for (int i=0;i<h;i++){
			for (int j=0;j<w;j++){
				T.data[j][i] = data[i][j];
			}
		}
		return T;
	}

	Matrix prod(Matrix P){
		int m,n,p;
		m = h;
		n = w;
		p = P.w;

		Matrix T(m,p);

		for (int i=0;i<m;i++){
			for (int j=0;j<p;j++){
				int res;
				res = 0;
				for (int k=0;k<n;k++){
					res = res + data[i][k]*P.data[k][j];
				}
				T.data[i][j] = res;
			}
		}
		return T;
	}

	int det(){
		int ans;
		int n;
		ans = 0;
		n = h;
		if(n==1){
			return data[0][0];
		}
		for (int i=0;i<n;i++){
			Matrix m(n-1,n-1);
			for (int j=1;j<n;j++){
				for (int k=0;k<i;k++){
					m.data[j-1][k] = data[j][k];
				}
				for (int k=i+1;k<n;k++){
					m.data[j-1][k-1] = data[j][k];
				}
			}
			ans = ans + pow(-1,i)*data[0][i]*m.det();
		}
		return ans;
	}

	Matrix adj(){
		int n = h;
		Matrix T(n,n);
		for (int i=0;i<n;i++){
			for (int j=0;j<n;j++){
				Matrix m(n-1,n-1);
				
				for (int i1=0;i1<i;i1++){
					for (int j1=0;j1<j;j1++){
						m.data[i1][j1] = data[i1][j1];
					}
					for (int j1=j+1;j1<n;j1++){
						m.data[i1][j1-1] = data[i1][j1];
					}
				}
				for (int i1=i+1;i1<n;i1++){
					for (int j1=0;j1<j;j1++){
						m.data[i1-1][j1] = data[i1][j1];
					}
					for (int j1=j+1;j1<n;j1++){
						m.data[i1-1][j1-1] = data[i1][j1];
					}
				}
				int element;
				element = pow(-1,i+j)*m.det();
				T.data[i][j] = element;
			}
		}
		return T;	
	}
};

int main(){
	Matrix A(3,4);
	Matrix B(4,2);
	Matrix P(3,2);
	Matrix M(3,3);
	Matrix N(3,3);
	for (int i=0;i<3;i++){
		for (int j=0;j<4;j++){
			A.data[i][j] = i+j;
		}
	}
	for (int i=0;i<4;i++){
		for (int j=0;j<2;j++){
			B.data[i][j] = i*i + j*j;
		}
	}
	for (int i=0;i<3;i++){
		for (int j=0;j<3;j++){
			M.data[i][j] = i*i + j*j + 1;
		}
	}
	M.data[2][2] = 10;
	M.data[0][0] = 12;
	P = A.prod(B);
	P.print();	
	cout<<M.det();
	N = M.adj();
	N.print();

}