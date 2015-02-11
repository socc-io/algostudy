import java.util.Scanner;

public class Becxer {
	public final static int MAX_SIZE = 15;

	//현재 체스판을 표현하는 클래스
	class Chess {
		public int size = 0;
		public int rowForNextQueen = 0;
		public int[][] map = new int[MAX_SIZE][MAX_SIZE];

		public Chess(int size,int rowForNextQueen) {
			this.size = size;
			this.rowForNextQueen = rowForNextQueen;
		}

		//체스판을 초기화 한다.
		public Chess init() {
			// map 초기화
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					map[i][j] = 0;
				}
			}
			return this;
		}

		public Chess genCandidate(int col) {
			Chess next = null;
			if(map[this.rowForNextQueen][col] == 0){
				next = new Chess(this.size,this.rowForNextQueen);
				//지금까지의 체스판을 복사한다.
				for(int i = 0 ; i < size ; i++){
					for(int j = 0 ; j < size ; j++){
						next.map[i][j] = this.map[i][j];
					}
				}
				
				//현재의 일직선선상으로 못놓게 표시한다
				for(int j = 0 ; j < size ; j++){
					next.map[rowForNextQueen][j] = -1;
					if(rowForNextQueen+j < size) next.map[rowForNextQueen+j][col] = -1;
				}
				
				//대각선 못 놓게 표시한다
				for(int j = 0 ; j+rowForNextQueen <size ; j++){
					if(col-j >= 0){
						next.map[j+rowForNextQueen][col-j] = -1;
					}
					if(col+j < size){
						next.map[j+rowForNextQueen][col+j] = -1;
					}
				}
				
				//새로운 위치에 퀸을 놓는다, 퀸은 9!
				next.map[rowForNextQueen][col] = 9;
				next.rowForNextQueen++;
			}
			return next;
		}

		public boolean isFullQueen() {
			return (rowForNextQueen == size) ? true : false;
		}

		public void print_queen() {
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					//퀸이 있는 곳만 출력한다
					if (map[i][j] == 9)
						System.out.print(""+(j+1) + " ");
				}
			}
			System.out.println();
		}
	}

	//스택구현
	class Stack<T> {
		private T[] arr;
		private int top;

		public Stack(T[] buffer) {
			this.arr = buffer;
			this.top = 0;
		}

		public void push(T c) {
			arr[top++] = c;
		}

		public T pop() {
			return arr[--top];
		}

		public boolean isEmpty() {
			return (top == 0) ? true : false;
		}
	}

	//백트래킹 솔루션
	public void solution(int size) {
		int count = 0;
		Stack<Chess> st = new Stack<Chess>(new Chess[100000]);
		st.push(new Chess(size,0).init());
		while (!st.isEmpty()) {
			Chess now = st.pop();
			if (now.isFullQueen()) {
				if (count++ < 3)
					now.print_queen();
			} else {
				for (int i = size - 1; i >= 0; i--) {
					Chess next = now.genCandidate(i);
					if (next != null)
						st.push(next);
				}
			}
		}
		System.out.println("" + count);
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner in = new Scanner(System.in);
		int size = Integer.parseInt(in.next());
		Becxer m = new Becxer();
		m.solution(size);
	}
}
