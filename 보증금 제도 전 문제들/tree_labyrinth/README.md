http://183.106.113.109/30stair/labyrinth/labyrinth.php?pname=labyrinth

프로그램 명: labyrinth
제한시간: 1 초
[문제 요약] 큰 피라미드내부에 # 은 벽이고 . 은 길이다. 길은 트리형태를 가진다.(두 지점간의 길은 유일하다)

. 으로 연결된 가장 긴 길의 길이를 찾는 것이 문제이다.

입력

입력은 두 개의 정수 C , R ( 3 <= C,R <= 1000 ) 이 주어진다. C , R 은 각각 열과 행의 수이다.
다음 R 줄에는 C 개의 . 혹은 # 이 공백없이 주어진다.

출력

출력예의 형식으로 출력한다.
"Maximum rope length is X."

입출력 예

입력

3 3
###
#.#
###

출력

Maximum rope length is 0.

입력

7 6
#######
#.#.###
#.#.###
#.#.#.#
#.....#
#######

출력

Maximum rope length is 8.
Hint

Huge input, scanf is recommended. If you use recursion, maybe stack overflow. and now C++/c 's stack size is larger than G++/gcc
출처: Central Europe 1999
[질/답] [제출 현황] [푼 후(0)]
[ 채 점 ] [홈으로]  [뒤 로]