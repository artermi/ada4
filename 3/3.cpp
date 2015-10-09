#include <stdio.h>
#include <stdlib.h>

bool fight(const int i,const int j,const int c,const long long e,const int p){
	long long answer = 1;
	long long ground = i + j;
	long long power = e;
	long long cp = c,pp = p,min = i - j;
	while(power > 0){
		if(power & 1){
			answer *= ground;
			answer %= pp;
		}
		ground = (ground * ground) % pp;
		power /= 2;
	}

	answer = ( (cp % pp) * (min % pp) * answer) % pp;
	if(answer < 0)
		answer += pp;
	return answer  > (pp / 2);
}

void sort_internal(int *array,const int start,const int end,const int c,const long long e,const int p);
void sort(int *array, const int n,const int c,const long long e,const int p){
	// assume array is 1,2,3,4,5 0~4
	sort_internal(array,0,n - 1,c,e,p);
}
void sort_internal(int *array,const int start,const int end,const int c,const long long e,const int p){
	if(start == end)
		return;
	else if(start == end - 1){
		if(fight(array[start],array[end],c,e,p))
			return;
		else{
			int tmp = array[start];array[start] = array[end];array[end] =tmp;
			return;
		}
	}
	int first_start = start,first_end = (start + end) / 2;
	int second_start = first_end + 1, second_end = end;
//	printf("%d %d %d %d\n",first_start,first_end,second_start,second_end);
	sort_internal(array,second_start,second_end,c,e,p);
	sort_internal(array,first_start,first_end,c,e,p);
	//4 5 3~4
	int *tmp = (int*) malloc( (end - start + 1) *sizeof(int));
	// total is 5 
	if(fight(array[first_end],array[second_start],c,e,p)){
		return;
	}
	else if(fight(array[second_end],array[first_start],c,e,p)){
		int j = 0;
		for(int i = second_start; i <= second_end; i ++,j++)
			tmp[j] = array[i];
		for(int i = first_start; i <= first_end;i ++, j ++)
			tmp[j] = array[i];
		j --;
		for(int i = end; i >= start; i --,j --)
			array[i] = tmp[j];
	}
	else{
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
			if(fight(array[first_i],array[second_i],c,e,p)){
				tmp[j] = array[first_i];first_i ++; j++;
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
//		printf("%d %d %llu %llu\n",n,c,e,p);
		int array[n];
		for(int i = 0; i < n; i++)
			array[i] = i + 1;
		sort(array,n,c,e,p);
		for(int i = 0; i < n; i ++)
			printf("%d ",array[i]);
		printf("\n");
	}
	return 0;
}
