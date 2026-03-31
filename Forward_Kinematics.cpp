#include<iostream>
#include<vector>
#include<algorithm>
#include<math.h>


std::vector<std::vector<float>> DH_make(std::vector<std::vector<float>> &A, float d, float theta, float a, float alpha){
	std::vector<float> B(4);
	float ct = static_cast<float>(cos(theta*M_PI/180));
	float st = static_cast<float>(sin(theta*M_PI/180));
	float ca = static_cast<float>(cos(alpha*M_PI/180));
	float sa = static_cast<float>(sin(alpha*M_PI/180));
	
    A = {
        {ct, -st*ca,  st*sa, a*ct},
        {st,  ct*ca, -ct*sa, a*st},
        {0,   sa,     ca,    d},
        {0,   0,      0,     1}
    };
	return A;
}

template<typename T>
std::vector<std::vector<T>> multiply(const std::vector<std::vector<T>> &A, const std::vector<std::vector<T>> &B){
    int m = static_cast<int>(A.size());
    int n = static_cast<int>(A[0].size());

    // Check if B is compatible
    if (static_cast<int>(B.size()) != n) {
        std::cout << "Error: Matrix dimensions do not match\n";
        return {};  // return empty matrix
    }

    int p = static_cast<int>(B[0].size());

    std::vector<std::vector<T>> C(m, std::vector<T>(p, 0));

    for (int i = 0; i < m; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < p; j++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

std::vector<std::vector<float>> DH_multi(int n, std::vector<std::vector<float>> &A){
	float theta, alpha, d, a;
	
	std::vector<std::vector<float>> C(4, std::vector<float>(4));
	for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            C[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }
	
	for(int i = 1; i<=n; i++){
		std::cout<<"Matrix for joint "<<i<<" wrt "<<i-1<<":\n";
		
		std::cout<<"\nEnter d: ";
		std::cin>>d;
		std::cout<<"Enter theta: ";
		std::cin>>theta;
		std::cout<<"Enter a: ";
		std::cin>>a;
		std::cout<<"Enter alpha: ";
		std::cin>>alpha;
		std::cout<<"\n\n";
		
		
		
		C = multiply(C, DH_make(A, d, theta, a, alpha));
		
	}
		return C;
}

void matrix_print(std::vector<std::vector<float>> &A){
	float val = 0;
	std::cout<<"\n\nDH Transformation Matrix:\n";
	for(std::vector<float> B:A){
		for(float i:B){
			if(std::abs(i)<1e-6){
				val = 0;
			}else{
				val = i;
			}
			std::cout<<val<<"  ";
		}
		std::cout<<"\n";
	}
	std::cout<<"\n";
	
	return;
}



int main(){
	
	std::vector<std::vector<float>> A(4);
	std::vector<std::vector<float>> C;
	bool open = true;
	char option;
	float theta, alpha, d, a;
	int n;
	while(open){
		std::cout<<"Choose an operation:\n"<<"A: Create DH Transformation matrix\n"<<"B: Mutiply DH Transformation matrices\n"<<"C: exit\n";
		std::cin>>option;
		if(option == 'C'){
			open = false;
			break;
		}else if(option == 'A'){
			std::cout<<"\nEnter d: ";
			std::cin>>d;
			std::cout<<"Enter theta: ";
			std::cin>>theta;
			std::cout<<"Enter a: ";
			std::cin>>a;
			std::cout<<"Enter alpha: ";
			std::cin>>alpha;
			DH_make(A, d, theta, a, alpha);
			matrix_print(A);
		}else if(option == 'B'){
			std::cout<<"\nNumber of matrices: ";
			std::cin>>n;
			std::cout<<"\n\n\n";
			C = DH_multi(n,A);
			matrix_print(C);
		}else{
			open = false;
		}
	}
	std::cin.get();
	std::cin.get();
	return 0;
}
