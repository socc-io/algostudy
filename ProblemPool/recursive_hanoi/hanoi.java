package socc;

import java.util.Scanner;

public class hanoi {
	public static void main(String[] args){
		Scanner scan = new Scanner(System.in);
		int input = scan.nextInt();  
		
		hanoi(input,3);
		
	}
	public static void hanoi(int a,int b){
		if(a==1){
			System.out.println(1+"->"+b);
		}
		
		hanoi(a-1,2);
		hanoi(1,3);
		hanoi(a-1,3);
		
	}
}
