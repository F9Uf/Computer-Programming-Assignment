package assign6;

import java.util.Scanner;

public class lab0 {

	private static Scanner sc;


	@SuppressWarnings("unused")
	public static int checkStr(String token) {
		String [] func = {"sin","cos","tan","sqrt","log","exp"}; 
		String buff = token.toLowerCase();
		int j;
		double ans;
		boolean find = false ;
		
		for(j=0 ; j<func.length && !find ; j++) {  //loop for check this word equal each word in func[] ?
//			if(buff.equals(func[j])) {
//				find = true;
//				//this word is functions
//			}
			if(func[j].compareToIgnoreCase(token)==0) {
				find=true;
				
			}
			
		}
		
		if(find) {
			//true , this word is functions
			return 1;
			
		}else {
			//false , this word isn't functions
			
			try {
				ans = Double.parseDouble(buff); //convert string to Double number
				return 2;
				
			}catch(Exception e) {  //catch error
				return 0;
			}
			
		}
		
		
	}
	
	public static void main(String[] args) {

		String str;  //create variable
		int i,check;
		boolean succes = false;
		
		do {
			
			sc = new Scanner(System.in); 
			System.out.print("Enter String: ");
			str = sc.nextLine();  //get string 1 line from user
			String [] token = str.trim().split("\\s+");  //trim whitespace before and after string , split white space add to token[] 
			 
			if(token.length == 1 && token[0].compareToIgnoreCase("end")==0) {  //1 word and this word is "end" or "END"
				succes = true;  //change succes to true for end loop
			}else {
				for(i=0 ; i < token.length ; i++) {  // loop check all word
					
					check = checkStr(token[i]);
					if(check == 0) {
						//error
						System.out.println(i+"["+token[i]+"]"+" => "+token[i]+" is Error.");
					}else if(check == 1 ) {
						//functions
						System.out.println(i+"["+token[i]+"]"+" => "+token[i]+" is Function.");
					}else if(check == 2) {
						//number
						System.out.println(i+"["+token[i]+"]"+" => "+token[i]+" is Number.");
					}
				}
			}
			
			
		}while(!succes);
		
		System.out.println("End program");
		

		
	}

}
