#include <iostream>
#include <cmath>

typedef long long int lli;
using namespace std;

void initialize(lli digit_table[][7][18][18]){
	digit_table[0][0][1][0] = 1; //7
	digit_table[0][1][0][0] = 2; //1 8
	digit_table[0][2][0][0] = 2; //2 9
	digit_table[0][3][0][0] = 1; //3
	digit_table[0][4][0][1] = 1; //4
	digit_table[0][5][0][0] = 1; //5
	digit_table[0][6][0][0] = 1; //6
}
void project_table(lli digit_table[][7][18][18],int digit_num,int remain,int add){
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

void build_next(lli digit_table[][7][18][18],int digit_num){
	for(int i = 0; i < 7; i ++){
		for(int j = 0; j < 10; j++){
			project_table(digit_table,digit_num,i,j);
		}
	}
}

void build_table(lli digit_table[][7][18][18],const lli &bound,int & now_where){
	int to_where = (int) log10(bound);
	while(now_where < to_where){
		build_next(digit_table,now_where);
		now_where ++;
	}
}

lli how_many_need(lli digit_table[][7][18][18], int digit, int number){
	/*	digit = 7, now is 10^6 ~ 10^7 -1
	 *	4\7  0 1 2 3 4 5 6 7
	 *	0    x x x o o o o o
	 * 	1    x x x o o o o
	 *	2    x x x o o o
	 *	3    x x x x x
	 *	4    x x x x
	 *	5    x x x
	 *	6    x x
	 *	7    x
	 */
	lli lucky_num = 0;
	for(int i = 3; i <= digit; i++)
		for(int j = 0; j + i <= digit && j < i; j ++)
			lucky_num += digit_table[digit][number][i][j];
	return lucky_num;
}

lli number_smaller_than(lli digit_table[][7][18][18],lli number, bool cover){
	lli lucky_num = 0;
	for(int i = 1; i < (int)log10(number); i++){
		lucky_num += how_many_need(digit_table,i,0); 
	}
	return lucky_num;
}

lli caculate_number(lli digit_table[][7][18][18],lli lower,lli upper){
	return number_smaller_than(digit_table,upper,1) - number_smaller_than(digit_table,lower,0);
}

void print_table(lli digit_table[][7][18][18],int where){
	for(int i = 0; i <= where; i++){
		cout << "how many number: "<< i + 1<<endl; 
		for(int j = 0; j < 7; j ++){
			cout << "remain is: " << j<<endl;
			for(int k = 0; k <= i + 1; k ++){
				for(int l = 0; l + k <= i + 1; l++)
					cout << digit_table[i][j][k][l] << " ";
			cout << endl;
			}
		}
	}
}


int main (){
	int test_case;
	lli lower_bound,upper_bound;
	lli digit_table[18][7][18][18] = {0}; //10^n , %7 == ?, seven_num, four_num
	int build_to_where = 0;
	initialize(digit_table);
	
	cin >> test_case;
	while(test_case --){
		cin >> lower_bound >> upper_bound;
		build_table(digit_table,upper_bound,build_to_where);
		print_table(digit_table,build_to_where);
		cout << caculate_number(digit_table,lower_bound,upper_bound) << endl;
	}
	return 0;
}
