#include <iostream>
#include <vector>
#include <array>
#include <cmath>

#define lli long long int
using namespace std;

void initialize(int ****digit_table[][7][18][18]){
	digit_table[0][0][1][0] = 1; //7
	digit_table[0][1][0][0] = 2; //1 8
	digit_table[0][2][0][0] = 2; //2 9
	digit_table[0][3][0][0] = 1; //3
	digit_table[0][4][0][1] = 1; //4
	digit_table[0][5][0][0] = 1; //5
	digit_table[0][6][0][0] = 1; //6
}
void project_table(int ****digit_table[][7][18][18],int digit_num,int remain,int add){
	if(add == 4){
	for(int i = 0; i <= digit_num; i++)
			for(int j = 0; j + i <= digit_num; j++)
				digit_table[digit_num + 1][(remain * 10 + add) % 7][i][j + 1] += digit_table[digit_num][remain][i][j];
	}
	else if(add == 7){
		for(int i = 0; i <= digit_num; i++)
			for(int j = 0; j + i <= digit_num; j++)
				digit_table[digit_num + 1][(remain * 10 + add) % 7][i + 1][j] += digit_table[digit_num][remain][i][j];
	}
	else{
		for(int i = 0; i <= digit_num; i++)
			for(int j = 0; j + i <= digit_num; j++)
				digit_table[digit_num + 1][(remain * 10 + add) % 7][i][j] += digit_table[digit_num][remain][i][j];
	}
}

void build_next(int ****digit_table[][7][18][18],int digit_num){
	for(int i = 0; i < 7; i ++){
		for(int j = 0; j < 10; j++){
			project_table(****digit_table,digit_num,i,j);
		}
	}
}

void build_table(int ****digit_table[][7][18][18],const lli &bound,int & now_where){
	int to_where = (int) log10(lli);
	if(to_where <= now_where)
		return;
	while(now_where < to_where){
		build_next(digit_table,now_where);
		now_where ++;
	}
}
int caculate_number(int ****digit_tablem[][7][18][18],lli lower,lli upper){
	return 0;
}


int main (){
	int test_case;
	lli lower_bound,upper_bound;
	int digit_table[18][7][18][18] = {0}; //10^n , %7 == ?, seven_num, four_num
	int build_to_where = 0;
	initialize(digit_table);
	
	cin >> test_case;
	while(test_case --){
		cin >> lower_bound >> upper_bound;
		build_table(digit_table,upper_bound,build_to_where);
		cout << caculate_number(digit_table,lower_bound,upper_bound) << endl;
	}
	return 0;
}
