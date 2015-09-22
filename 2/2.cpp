#include<iostream>

using namespace std;

int main(){
	int n;
	cin >> n;
	while(n--){
		int a;
		cin >> a;
		if(a > 1000)
			cout << a - 1000 <<' ' << 1000 << endl;
		else
			cout << '0'<<' '<< a<< endl;
	}
	return 0;
}

