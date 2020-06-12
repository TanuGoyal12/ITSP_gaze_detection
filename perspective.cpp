#include <iostream>

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


void get_perspective(int x1,int y1, int x2,int y2, int x3,int y3, int x4,int y4, int x_1,int y_1, int x_2,int y_2, int x_3,int y_3, int x_4,int y_4, double M[])
{
	double basis_1[] = {x1, x2, x3, y1, y2, y3, 1, 1, 1};
	double v_4_1[] = {x4, y4, 1};

	double basis_2[] = {x_1, x_2, x_3, y_1, y_2, y_3, 1, 1, 1};
	double v_4_2[] = {x_4, y_4, 1};

	double basis_1_inv[9], weights_1[3];
	inverse(basis_1, basis_1_inv, 3);
	prod(basis_1_inv, v_4_1, weights_1, 3, 3, 1);
	double diag_1[] = {weights_1[0], 0, 0,  0, weights_1[1], 0,  0, 0, weights_1[2]};
	double A[9];
	prod(basis_1, diag_1, A, 3, 3, 1);

	double basis_2_inv[9], weights_2[3];
	inverse(basis_2, basis_2_inv, 3);
	prod(basis_2_inv, v_4_2, weights_2, 3, 3, 1);
	double diag_2[] = {weights_2[0], 0, 0,  0, weights_2[1], 0,  0, 0, weights_2[2]};
	double B[9];
	prod(basis_2, diag_2, B, 3, 3, 1);

	double A_inv[9];
	inverse(A, A_inv, 3);
	prod(B, A_inv, M, 3, 3, 3);

}

void map_focus_point(double point[], double M[], double mapped_point[])
{
	double product[3];
	prod(M, point, product, 3, 3, 1);

	mapped_point[0] = (product[0] / product[2]);
	mapped_point[1] = (product[1] / product[2]);
}
