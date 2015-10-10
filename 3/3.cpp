#include <stdio.h>
#include <stdlib.h>

int build_power(int num, long long e,int p){
	long long power = e;
	long long ans = 1;
	long long number = num % p;
	while(power > 0){
		if(power & 1)
			ans = (ans * number) % p;
		number = (number * number) % p;
		power >>=1;
	}
	return (int)ans % p;
}


bool fight(const int i,const int j,const int c,const long long e,const int p,int *table){
	long long answer = table[i + j];
//	printf("table [i + j] = %d,build_power(i + j)=%d\n",table[i+j],build_power(i+j,e,p));
	long long cp = c,pp = p,min = i - j;
	answer = ( (((cp % pp) * (min % pp)) % pp) * answer) % pp;
	if(answer < 0)
		answer += pp;
	return answer  > (pp / 2);
}

void sort_internal(int *array,const int start,const int end,const int c,const long long e,const int p,int* table);
void sort(int *array, const int n,const int c,const long long e,const int p,int* table){
	// assume array is 1,2,3,4,5 0~4
	sort_internal(array,0,n - 1,c,e,p,table);
}
void sort_internal(int *array,const int start,const int end,const int c,const long long e,const int p,int *table){
	if(start == end)
		return;
	else if(start == end - 1){
		if(fight(array[start],array[end],c,e,p,table))
			return;
		else{
			int tmp = array[start];array[start] = array[end];array[end] =tmp;
			return;
		}
	}
	int first_start = start,first_end = (start + end) / 2;
	int second_start = first_end + 1, second_end = end;
	sort_internal(array,second_start,second_end,c,e,p,table);
	sort_internal(array,first_start,first_end,c,e,p,table);
	//4 5 3~4
	// total is 5 
	if(fight(array[first_end],array[second_start],c,e,p,table))
		return;	
	else if(fight(array[second_end],array[first_start],c,e,p,table)){
		int j = 0;
		int *tmp = (int*) malloc( (end - start + 1) *sizeof(int));
		for(int i = second_start; i <= second_end; i ++,j++)
			tmp[j] = array[i];
		for(int i = first_start; i <= first_end;i ++, j ++)
			tmp[j] = array[i];
		j --;
		for(int i = end; i >= start; i --,j --)
			array[i] = tmp[j];
	}
	else{
		int *tmp = (int*) malloc( (end - start + 1) *sizeof(int));
		int first_i = first_start;
		int second_i = second_start;
		int j = 0;
		while(first_i <= first_end  || second_i <= second_end){
			if(first_i > first_end ){
				while(second_i <= second_end){
					tmp[j] = array[second_i];
					j++;second_i ++;
				}
				break;
			}
			else if(second_i > second_end ){
				while(first_i <= first_end){
					tmp[j] = array[first_i];
					j++;first_i ++;
				}
				break;
			}
			if(fight(array[first_i],array[second_i],c,e,p,table)){
				tmp[j] = array[first_i]; first_i ++; j++;
			}
			else{
				tmp[j] = array[second_i]; second_i++; j ++;
			}
		}
		j --;
		for(int i = end; i >= start; i --,j --)
			array[i] = tmp[j];
	}
}


int main (){
	int time;
	scanf("%d",&time);
	while(time --){
		int c,n,p;
		long long e;
		scanf("%d%d%lld%d",&n,&c,&e,&p);
		int *array = (int *) malloc(n * sizeof(int));
		int *table = (int *) malloc(2 * n * sizeof(int));
		for(int i = 1; i < 2 * n; i++){
			if(i % 2 == 0 && i != 2)
				table[i] = (int)(((long long)table[2]  * (long long)table[i/2]) % p);
			else if(i % 3 == 0 && i != 3)
				table[i] = (int)(((long long)table[3]  * (long long)table[i/3]) % p);
			else if(i % 5 == 0 && i != 5)
				table[i] = (int)(((long long)table[5]  * (long long)table[i/5]) % p);
			else if(i % 7 == 0 && i != 7)
				table[i] = (int)(((long long)table[7]  * (long long)table[i/7]) % p);
			else if(i % 11 == 0 && i != 11)
				table[i] = (int)(((long long)table[11]  * (long long)table[i/11]) % p);
			else if(i % 13 == 0 && i != 13)
				table[i] = (int)(((long long)table[13]  * (long long)table[i/13]) % p);
			else if(i % 17 == 0 && i != 17)
				table[i] = (int)(((long long)table[17]  * (long long)table[i/17]) % p);
			else
				table[i] = build_power(i,e,p);
		}
		for(int i = 0; i < n; i++)
			array[i] = i + 1;
		sort(array,n,c,e,p,table);
		for(int i = 0; i < n; i ++)
			printf("%d ",array[i]);
		printf("\n");
	}
	return 0;
}
