
http://183.106.113.109/30stair/necklace/necklace.php?pname=necklace

프로그램 명: necklace
=======

제한시간: 1 초

총 N(3 <= N <= 350)-- 빨간 , 흰 , 파란색의 구슬--개의 구슬을 가진 목걸이를 가지고 있다. 이 구슬들은 여러가지 색이 섞여 있다.

아래 그림은 구슬 수가 29 인 두 목걸이의 예이다.


              1 2                               1 2

          r b b r                           b r r b

        r         b                       b         b

       r           r                     b           r

      r             r                   w             r

     b               r                 w               w

    b                 b               r                 r

    b                 b               b                 b

    b                 b               r                 b

     r               r                 b               r

      b             r                   r             r

       b           r                     r           r

         r       r                         r       b

           r b r                             r r w

          그림. A                           그림. B

                      r 빨간 구슬

                      b 파란 구슬 

                      w 흰 구슬 


설명의 용이를 위해서 그림에서 첫 번째 지점과 두 번째 지점을 표시하였다.
그림 A 는 빨간 구슬과 파란구슬로 brbrrr...
그림 B 는 빨간 , 파란 , 흰 구슬로 rbbrrwr...
로 이루어져 있다.
문제는 구슬의 임의의 지점을 끊은 후 이 구슬을 직선으로 폈을 때 양 쪽 끝에서 같은 색의 구슬이 최대가 나오게 하는 것이다.

그림 A 에서는 8 개의 구슬을 모을 수 있다.(9 번째와 10 번째 사이 혹은 24 번째와 25 번째 사이를 절단한 경우)

단,흰 구슬(w)은 어떤 색으로도 색칠이 가능하다

입력형식

첫 라인은 구슬의 수 와 다음 라인은 r,b,w 문자들이 입력된다.

출력 형식

같은 색으로 만들 수 있는 최대 구슬 수를 출력한다.

입출력 예

입력

29

wwwbbrwrbrbrrbrbrwrwwrbwrwrrb

출력

11

출처: ioi 기출
