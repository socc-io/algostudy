http://183.106.113.109/30stair/robot/robot.php?pname=robot

프로그램 명: robot
==================
제한시간: 1 초

r 행 c 열의 지도 정보가주어지고 , 1 행 s 열의 시작 위치가 주어질 때 이 맵을 빠져나가는 경우 , 아니면 꼬리를 무는 경우의 정보를 출력하는 문제이다.

N 위
S 아래
E 오른쪽
W 왼쪽
grid 1 인 경우 10 번 만에 탈출하는 경우이고 , grid 2 인 경우 3 단계 전진 후 8 단계의 루핑이 발생하는 경우이다.

입력
r 과 c 는 10 이하의 정수이다.

출력

입출력 예

입력

3 6 5

NEESWE

WWWESS

SNWWWW


출력

10 step(s) to exit

입력

4 5 1

SESWE

EESNW

NWEEN

EWSEN

출력

3 step(s) before a loop of 8 step(s)