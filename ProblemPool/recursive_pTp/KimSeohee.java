package socc;

import java.util.Scanner;

public class pTp {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner scan = new Scanner(System.in);
		int input = scan.nextInt();  
		
		System.out.println(getSol(input)+1);
		
	}
	
	public static String getSol(int a){
		if(a==1){
			return ""+1;
		}
		if(a==2){
			return ""+1+a;
		}
		
		return ""+getSol(a-1)+1+a+getSol(a-1);
	}

}
 