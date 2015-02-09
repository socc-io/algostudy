package dp;
import java.util.Scanner;

public class scv_dp {
	public static void main(String[] args){
		Scanner scan = new Scanner(System.in);
		int n = scan.nextInt();
		int[][] a = new int[n][n];
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				a[i][j]=scan.nextInt();
			}
		}
		
		System.out.println(findRoute(a,n));
	}
	
	public static int findRoute(int[][] a, int n){
		int[][] b = new int[n][n];
		
		b[0][0] = a[0][0];
		for(int i=1; i<n; i++){
			b[0][i]=b[0][i-1]+a[0][i];
			b[i][0]=b[i-1][0]+a[i][0];
		}
		for(int i=1; i<n; i++){
			for(int j=1; j<n; j++){
				if(b[i-1][j]>=b[i][j-1]){
					b[i][j] = b[i-1][j]+a[i][j];
				}else{
					b[i][j] = b[i][j-1]+a[i][j];
				}
			}
		}
		
		return b[n-1][n-1];
		
	}
	
}
