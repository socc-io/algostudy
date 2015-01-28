package socc;

public class mergesort {
	public static void main(String[] args){
		int[] a = {5,3,4,2,1,9,7,6};
		ms(a,0,7);
		int[] a1={1,3,5};
		int[] a2 ={2,4,6};
		
		merge2(a1,a2);
		
	}
	
	public static int[] ms(int[] a, int s, int e){
		
		if(s==e || e==s+1){
			int[] b = {a[s]};
			return b;
		}
		
		else{
			int[] a1 = ms(a, s, e/2);
			System.out.println(s+" "+e/2);
			int[] a2 = ms(a, e/2, e);
			return merge2(a1,a2);
		}
		
	}
	
	public static int[] merge2(int[] a1, int[] a2){
		int len_i=a1.length;
		int len_j=a2.length;
		
		int[] c = new int[8];
		int i=0, j=0, k=0;
		
		while(k<len_i+len_j){
			/*
			if(i==len_i){
				
				c[k]=a2[j]; j++;
				break;
			}
			if( j==len_j){
				break;
			}
			*/
			if(k==len_i+len_j-1){
				if(i<j){ c[k]=a1[i];}
				else{ c[k]=a2[j];}

				break;
			}
			
			if(a1[i]<=a2[j]){
				c[k]=a1[i];
				k++;
				i++;
			}
			else{
				c[k]=a2[j];
				k++;
				j++;
			}
			
		}
		for(int n=0; n<len_i+len_j; n++){
			System.out.println(c[n]);
		}
		return c;
	}
}
