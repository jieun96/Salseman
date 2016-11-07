#include <stdio.h>
#include <math.h>
#define BIG 100000   //무한대 표시
int travel(int,const int (*)[]);
int main(){
	int n;   //도시의 수
	int i,j;
	printf("도시의 수를 입력하시오 : ");
	scanf("%d",&n);
	int w[n][n];    //가중치 배열
	for(i=0;i<n;i++){    //가중치 입력
		for(j=0;j<n;j++){
			printf("%d->%d의 가중치 입력 : ",i+1,j+1);
			scanf("%d",&w[i][j]);
			if(w[i][j] == -1)    //-1을 입력시 무한대 값 저장
				w[i][j] = BIG;
			if(i==j)   //자기 자신으로 가는 경우 무한대 값 저장
				w[i][j] = BIG;
		}
	}

	int minlength;   //최소거리
	minlength = travel(n,w);
	printf("minlength = %d\n",minlength);
	return 0;
}
int travel(int n,const int (*w)[n]){
	int i,j,k,l,m;
	int sub;   //v1을 제외한 부분집합의 갯수
	sub = pow(2,n-1);
	int d[n][sub];    //최소거리 저장 배열
	int p[n][sub];    //다음 도시 저장 배열
	int subset[sub];   //부분집합 저장 배열(비트)
	int s[sub];   //부분집합에 있는 도시의 개수 저장배열
	int minlength;   //최소거리
	int path,total;   //다음 도시,모든 도시-v1값 저장(비트)
	int pow1,pow2,pow3=0;
	for(i=0;i<sub;i++){   //부분집함(비트)
		subset[i] = i*2;
	}
	for(i=0;i<sub;i++){   //subset배열값의 1의 개수
		s[i] = 0;
		for(j=0;j<n;j++){
			l = pow(2,j);
			if((subset[i]&l)!=0)
				s[i]++;
		}
	}
	for(i=0;i<n;i++){    //시작지점에서 v1으로 가는 최소거리 저장
		d[i][0] = w[i][0];
	}
	for(k=1;k<=n-2;k++){   //시작도시와 v1을 제외한 도시의 개수(최대 n-2)
		for(i=1;i<sub;i++){   //부분집합
			if(s[i]==k){    //도시의 개수가 일치하면
				for(j=0;j<n;j++){   
					d[j][i] = BIG;   //무한대 저장
					for(l=0;l<n;l++){
						pow1 = pow(2,l);
						if((subset[i]&pow1)!=0){    //부분집합에 l이 가르키는(?) 도시가 존제하면
							pow2 = subset[i]-pow1;    //부분집합에서 l이 가르키는(?) 도시 제외
							pow3 = 0;
							while(1){
								if(subset[pow3]==pow2)   
									break;
								pow3++;    //pow2가 가르키는(?) 도시
							}		
							if(d[j][i]>w[j][l]+d[l][pow3]){   //새로운 값이 무한대보다 작으면
								d[j][i] = w[j][l]+d[l][pow3];   //저장
								p[j][i] = l;   //경로 저장
							}
						}
					}
				}
			}
		}
	}
	k = -1;
	minlength = BIG;
	for(i=1;i<=n;i++){    //최종 최소 거리 구하기
		for(j=k+1;j<sub;j++){
			if(s[j] == n-2){   //도시의 개수가 최대인 것만 계산
		 		if(minlength > w[0][n-i] + d[n-i][j]){   //원래 거리보다
					minlength = w[0][n-i] + d[n-i][j];   //저장
					path = n-i;   //경로 저장
				}
				k=j;   //계산한 도시 제외
				break;
			}
		}
	}
	printf("path : 1->");
	total = pow(2,n)-2;
	for(i=0;i<n-2;i++){   //경로 출력
		printf("%d->",path+1);  //도시 순서대로 출력
		pow1 = pow(2,path);
		total = total-pow1;   //지나간 도시 제외
		for(j=0;j<sub;j++){
			if(total == subset[j]){
				path = p[path][j];
			}
		}
	}
	printf("%d->1\n",path+1);   //마지막 남은 도시 출력
	return minlength;
}

