http://59.23.113.171/30stair/dijkstra/dijkstra.php?pname=dijkstra


프로그램 명: dijkstra (special judge)
제한시간: 1 초
출발 정점이 주어질 때 이 점으로 부터 각 정점으로의 최단 경로를 구하는 문제이다.

그림은 1 번 정점이 출발정점일 때 입출력 예의 보기이다.



입력

입력의 첫 줄은 정점의 수 N ( 2 <= N <= 1000 ) , 간선의 수 M (1 <= M <= 100,000) , 출발 정점 S 가 주어진다.
다음 M 줄에는 Ai , Bi , Ci 가 주어진다. Ai 에서 Bi 로의 길이 있고 가는 Ci ( 1 <= Ci <= 100 ) 의 비용이 듣다.

출력

출발 정점 S 로 부터의 최단 거리 패스를 출력한다. 정점이 커지는 순으로 출력한다.
출발 정점인 경우 그 줄에 해당 정점의 번호만 출력하고 답이 여러개인 경우 그 중 하나만 출력한다.

입출력 예

입력

5 8 1
1 2 7
1 3 4
1 4 6
1 5 1
3 2 2
3 4 5
4 2 3
5 4 1

출력

1
1 5 4 2
1 3
1 5 4
1 5
*스페셜 저지가 잘못 되어 재 채점 했습니다.