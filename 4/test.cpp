#include <iostream>
using namespace std;
int number_num(int number,int want){
	int total = 0;
	while(number > 0){
		if(number % 10 == want) total ++;
		number /= 10;
	}
	return total;
}

int main() {
	int total = 0;
	for(int i = 7654321; i <= 987654321; i++)
		if(i % 7 == 0 && number_num(i, 7) > number_num(i,4) && number_num(i,7) > 2){
		total ++;
//cout <<i << ' ' <<total <<endl;
		}
		cout << total <<endl;
	return 0;
}