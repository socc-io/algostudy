package sort;

public class mergesort {
	public static void main(String[] args){
		int[] a = {5,3,4,2,1,9,7,6};
		int[] c=ms(a,0,7);
		for(int i=0; i<c.length; i++){
			System.out.print(c[i]);
		}
	}
	
	public static int[] ms(int[] a, int s, int e){
		
		if(s==e ){
			int[] b = {a[s]};
			return b;
		}
		
		else{
			int[] a1 = ms(a, s, (s+e)/2);
			int[] a2 = ms(a, ((s+e)/2)+1, e);
			return merge2(a1,a2);
		}
		
	}
	
	public static int[] merge2(int[] a1, int[] a2){
		int len_i=a1.length;
		int len_j=a2.length;
		
		int[] c = new int[len_i+len_j];
		int i=0, j=0, k=0;
		
		while(k<8){
			
			if(i==len_i){
				for(int a=j; a<len_j; a++){
					c[k]=a2[a];
					k++;
				}
				break;
			}
			if(j==len_j){
				for(int a=i; a<len_i; a++){
					c[k]=a1[a];
					k++;
				}
				break;
			}
			
			if(a1[i]<=a2[j]){
				c[k]=a1[i];
				k++; i++;
			}
			else{
				c[k]=a2[j];
				k++; j++;
			}
			
		}
		return c;
	}
}
