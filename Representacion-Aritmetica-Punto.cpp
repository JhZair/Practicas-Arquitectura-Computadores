#include <iostream>
using namespace std;

	float divisionFp(float div1, float div2){
		if (div1 == 0){
			return 0;
		}
		else if(div2 == 0){
			return 0;
		}
		
	}


	int main(){

		float dividendo, divisor;
		
		cout << "Ingresa el dividendo: "<<endl;
		cin >> dividendo;
		
		cout << "Ingresa el divisor: " << endl;
		cin >> divisor;
		
		cout << divisionFp(dividendo, divisor) << endl;
		
		return 0;
	}


	//g++ -o booth_dinamico Arq.cpp
