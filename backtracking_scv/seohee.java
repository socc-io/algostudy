package dp;

import java.util.*;

public class scv_backtracking {

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		int n = scan.nextInt();
		int[][] a = new int[n][n];
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				a[i][j]=scan.nextInt();
			}
		}
		
		Stack stack = new Stack();
		
		findRoute(a, n, stack);
	}
	public static void xy(){
		
	}
	public static void findRoute(int[][] a, int n, Stack stack){
		int max = 0;
		int[] b = {0,0,a[0][0]}; //스택 0번째(x좌표,y좌표,미네랄개수)
		stack.push(b);
		
	
		while(true){
			if(stack.empty()){
				System.out.println(max);
				break;
			}
			int[] now = (int[])stack.pop();
			if(now[0]==n-1 && now[1]==n-1){
				if(now[2]>max){max=now[2];}
			}
			
			int i=now[0];
			int j=now[1];
			int m=now[2];
			
			if(i<n-1){
				int[] ca = {i+1,j,m+a[i+1][j]};
				stack.push(ca);
			}
			if(j<n-1){
				int[] ca= {i,j+1,m+a[i][j+1]};
				stack.push(ca);
			}
		}
		
	}

}
