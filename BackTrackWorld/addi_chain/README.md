http://59.23.113.171/30stair/addi_chain/addi_chain.php?pname=addi_chain

프로그램 명: addi_chain (special judge) 

제한시간: 1 초 
 
어떤 수 n 에 대한 합 연결은 
?a0 = 1 
?am = n 
?a0 < a1 < a2 < ... < am-1 < am 
? 임의의 k (1<=k<=m) 에 대해서 ak = ai + aj 이고 0 <= i , j <= k -1 인 두 개의 i,j 가 존재한다. i,j 는 같을수 도 있다. 

n 이 주어질 때 가장 짧은 연결을 찾는게 문제이다. 답이 여러개인 경우 그 중 하나 만을 출력한다. 

예를 들어 , 5 에 대한 답은 < 1 , 2 , 3 , 5 > 혹은 < 1 , 2 , 4 , 5 > 중 하나이다. 

입력
n 은 1 이상 200 이하의 정수이다. 
출력
가장 짧은 연결을 출력한다. 
입출력 예
입력

5

출력

1 2 4 5

입력

7

출력

1 2 4 6 7

입력

12

출력

1 2 4 8 12

입력

15

출력

1 2 4 5 10 15

입력

77

출력

1 2 4 8 9 17 34 68 77


보충 설명 
n 이 5 인 경우 연결 1 2 4 5 는 2= 1 + 1 로 
4= 2 + 2 로
5= 4 + 1 로  만들 수 있다.

출처: Ulm Local 1997(pku 2248)

