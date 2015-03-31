package term01;

import java.util.Scanner;


public class quick_change {
	public static void main(String[] args) {
		
		Scanner scan = new Scanner(System.in);
		int input = scan.nextInt();
		System.out.println(checkShare(input, 1, 0));

	}
	
	static String result="";
	public static String checkShare(int n, int order, int share){
		int coin=0;
		switch (order) {
			case 1: 
				coin=25;
			break;
			case 2: 
				result+=share+" QUARTER(S), "; coin=10; 
			break;
			case 3: 
				result+=share+" DIME(S), "; coin=5;  
			break;
			case 4: 
				result+=share+" NICKEL(S), "; coin=1;  
			break;
			case 5 :
				result+=share+" PENNY(S)";
				return result;
		}
		
		share = n/coin;
		int remainder = n%coin;
		return checkShare(remainder, order+1, share);
	}
}
