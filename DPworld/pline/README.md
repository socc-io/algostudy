프로그램 명: pline

제한시간: 1 초

단어의길이가 주어짐. 줄에서 단어가 놓일 때는 한 칸의 공백을 주어야 함. 20 칸을 넘지 못하는 경우 남는 공백의 제곱의 합이 최소로 하는 값 찾기.



4 2 1 4 2 8 5 3 3 7 4 3 3 10

case 1:

12345678901234567890            남은공백  공백의제곱

xxxx xx x xxxx xx    4 2 1 4 2 .. 3        .. 9 

xxxxxxxx xxxxx xxx   8 5 3     .. 2        .. 4

xxx xxxxxxx xxxx xxx 3 7 4 3   .. 0        .. 0

xxx xxxxxxxxxx       3 10      .. 6        .. 36



case 2:

12345678901234567890

xxxx xx x xxxx xx    4 2 1 4 2 .. 3          .. 9

xxxxxxxx xxxxx xxx   8 5 3     .. 2          .. 4

xxx xxxxxxx xxxx     3 7 4     .. 4          .. 16

xxx xxx xxxxxxxxxx   3 3 10    .. 2          .. 4

case 2 가 더 최소

입력



첫번째 수는 최대 칸의 수 M 과 숫자의 개수 N 이고 , 숫자가 N 개 주어진다. (M <= 100 , N <= 10000)

어떤 단어도 M 보다 길지 않다는 것은 보장된다.



출력



최소값을 출력한다.

입출력 예



입력



20 14

4

2

1

4

2

8

5

3

3

7

4

3

3

10



출력



33

출처:Kaohsiung 2006


