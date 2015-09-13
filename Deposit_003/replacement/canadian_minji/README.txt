http://183.106.113.109/30stair/canadian_tour/canadian_tour.php?pname=canadian_tour


프로그램 명: canadian_tour

제한시간: 1 초

당신은 항공사가 후원하는 어떤 경연대회에서 우승을 차지했다. 그래서 상으로 캐나다 곳곳을 여행할 수 있는 비행기 표를 받았다.



단, 이 표로 여행을 하는데는 몇가지 규칙이 있다.



우선 가장 서쪽에 있는 도시부터 시작해서 현재 있는 곳보다 동쪽에 있는 도시들만 거쳐서

동쪽 가장 끝에 있는 도시까지 간 뒤

돌아올 때는 지금보다 서쪽에 있는 도시만 거쳐서 출발지로 되돌아 올 수 있다. 그리고 , 왕 복 전과정에서 각 도시는 한 번만 거쳐가야 한다. 단, 출발지만 출발 할 때와 돌아 올 때 정확히 두 번 방문할 수 있다.

여행하는 동안 다른 항공편이나 다른 교통 수단을 이용해서는 안된다.

항공로에 든 도시와 , 비행기 직선 코스로 가는 두 도시의 목록이 있을 때 , 위의 조건을 만족하면서 가장 많은 도시를 방문할 수 있게 여행 일정을 잡는 프로그램을 작성하라. 목록에 있는 첫 번째 도시에서 출발하여, 목록의 맨 끝에 있는 도시를 반드시 거친 뒤 출발지로 되돌아 올수 있어야 한다.



입력



첫째 줄에는 항공로에 든 총 도시의 개수 N 과 직선 코스의 개수 V 를 나타내는 수치가 있다. N 은 100 이하인 자연수, v 는 0 보다 큰 임의의 정수이다.

다음 N 줄에는 각 줄마다 그 도시의 이름이 있다. 도시는 서쪽부터 동쪽의 순서로 정렬되어 있다. i < j 인 경우 목록의 i 번째 있는 도시는 j 번째에 있는 도시보다 서쪽에 있다고 말할 수 있다. 

도시 이름은 로마자와 숫자로 구성되어 있고 최대 15 글자인 문자열이다. 이름 사이에 공백은 없다.

그 다음 V 줄에는 각 줄마다 앞 목록에 든 도시 이름 중 두 개가 있다. 각 도시는 공백으로 구분한다. 

도시 1 과 도시 2 가 목록에 있다면 도시 1 에서 도시 2 로 또는 도시 2에서 도시 1 로 가는 직선 항로가 있다는 것을 의미한다.

출력



여행 일정에 잡힌 도시의 최대 개수 M 을 출력한다. 조건을 만족하는 일정을 짤 수 없다면 1 을 출력한다.

입출력 예



입력



8 9

Vancouver

Yellowknife

Edmonton

Calgary

Winnipeg

Toronto

Montreal

Halifax

Vancouver Edmonton

Vancouver Calgary

Calgary Winnipeg

Winnipeg Toronto

Toronto Halifax

Montreal Halifax

Edmonton Montreal

Edmonton Yellowknife

Edmonton Calgary



출력 



7



입력



5 5

C1

C2

C3

C4

C5

C5 C4

C2 C3

C3 C1

C4 C1

C5 C2



출력 



1

입출력 보충



첫 번째 입력 예에서 방문하는 도시

Vancouver

Edmonton

Montreal

Halifax-- 반환점 

Toronto 

Winnipeg

Calgary

Vancouver



