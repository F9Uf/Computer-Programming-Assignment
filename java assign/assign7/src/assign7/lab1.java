package assign7;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;


public class lab1 {

	static ArrayList<Dict> data = new ArrayList<Dict> ();  //กำหนดตัวแปร ArrayList ที่ชื่อว่า data เป็น แบบ Global
	

	static boolean loadFile(String filename) {  // method load file
		String str;
		try {
			FileInputStream in = new FileInputStream(filename);  //เป็นการเรียก file มาไว้ในโรแกรมของเรา
			InputStreamReader fr = new InputStreamReader(in,"UTF8"); //บอกว่าเราจะอ่านไฟล์แบบ UTF8
			BufferedReader br = new BufferedReader(fr); //เรียกใช้ ตัวอ่าน file
			
			int BOM = br.read();  //อ่าน ข้อมูลบรรทัดแรกทิ้งไป เนื่องจากเป็นส่วนหัวที่เราไม่ต้องการ
			
			while((str=br.readLine())!=null) {  //อ่านทีละบรรทัดจนหมด
				Dict buff = new Dict(str);  //แปลงข้อมูลที่เราได้มาเป็น object
				data.add(buff); //แล้วนำ object ไปเก็บใส่ arrayList ที่เราสร้างไว้
				
			}
			br.close();  //ปิดการอ่านไฟล์
			return true; //return true ถ้าทำได้
			
		}catch(Exception e) {

			return false; //ถ้าเกิด error ให้ return false
		}
	}
	
	static int searchDuplicate() {  //method ค้นหาตัวที่ซ้ำกัน
		int i,count=0;
		
		for(i=0;i<data.size()-1;i++) {  //วนรอบเปรียบเทียบ n-1  ตัว
			
			if(data.get(i).compareAll(data.get(i+1))==1) {
				//ถ้ามีตัวถัดไปซ้ำกันให้ลบทิ้ง แล้วนำจำนวน
				data.remove(i+1);
				count++;
			}
		}
		return count;
		
	}
	
	static int searchMaxMean(String [] s) {  // ค้นหาตัวที่มีความหมายมากที่สุด
		int i,count=0,max=0;
		for(i=0;i<data.size()-1;i++) {  //วนรอบ n-1 ตัว
			if(data.get(i).compareTo(data.get(i+1))==0) {  //ถ้าตัวถัดไปมีคำเหมือนกันให้นำจำนวน
				count++;
			}else {  //ถ้าตัวถัดไปมีคำที่ไม่เหมือนคำปัจจุบัน
				if(count > max) {  //ตรวจสอบว่า จำนวนที่นับมาของคำปัจจุบันมีค่ามากกว่าคำที่มากที่สุดก่อนหน้าหรือไม่
					max = count;  //ถ้าใช่ให้จำตัวนั้น
					s[0] = data.get(i).word;  // และเก็บคำนั้นใส่ไว้ใน string
				}
				count = 0; //reset การนับจำนวน
			}
		}
		return max+1; // max+1 เพราะคู่แรกที่นับ เรานับเพียงครั้งเดียวแต่ได้ 2 ตัว จึงบวก 1 ชดเชย
	}
	
	static void searchWord(String s) {  //ค้นหาคำที่เหมือนกับที่เราป้อนเข้าไป
		Dict buff = new Dict(); 
		buff.addWord(s);  //สร้าง object เปล่่าๆ ที่มีแต่ word เพื่อใช้ search แบบ binary search
		int x = Collections.binarySearch(data, buff); //ใช้ binary search ค้นหาตำแหน่ง
		int first,last,i,j=1;
		
		
		
		if(x>=0) {  //found
			first = x-1;
			last = x+1;
			if(first!=0) {  //ถ้าไม่ใช่ตัวแรก ให้วนรอบถอยหลังหาจำนวนคำที่เหมือนกันไปเรื่อยๆ
				while(data.get(first).compareTo(buff)==0 ) {
					first--;
				}
			}
			if(last!=(data.size()-1)) {  //ถ้าไม่ใช่ตัวสุดท้าย ให้วนรอบไปด้านหน้าเพื่อหาคำที่เหมือนไปเรื่อยๆ
				while(data.get(last).compareTo(buff)==0) {
					last++;
				}
			}
			
			System.out.println("found "+s+" "+((last-first)+1)+" words at "+first+" - "+last);
			for(i=first;i<=last;i++) {
				System.out.print((j++)+")");
				data.get(i).printData();
			}

			
		}else {
			System.out.println(s+" not found"); //ถ้าไม่เจอ
		}

	}
	public static void main(String[] args) {
		
		String path = "C:\\Users\\Administrator.Admin-PC\\Desktop\\CPE100\\term2\\java assign\\assign7\\file\\utf8lexitron.csv" ;
		String [] maxWord = new String[1];
		int same = 0, max = 0, i = 1;
		Scanner in = new Scanner(System.in);  //เรียกใช้ class Scanner
		
		if(loadFile(path)) {
			//if load file success
			Boolean succes= false;
			System.out.println(" Total Read "+data.size()+" records");

			Collections.sort(data); //sort data
			
			same = searchDuplicate(); // search Duplicate data
			
			max = searchMaxMean(maxWord);  //หาคำที่มีความหมายมากที่สุด

			System.out.println(" Total duplicate found "+same+" records.");
			System.out.println(" Total remaining size "+data.size()+" records.");
			System.out.println(" Maximun Meaning Word "+maxWord[0]+" have "+max+" records.");

			
			for(Dict a:data) {
				if(a.compareWord(maxWord[0])==1) {
					System.out.print(i+")");
					a.printData();
					i++;
				}
			}
			do { //วนรอบให้ผู้ใช้ป้อนคำเพื่อค้นหาข้อมูลไปเรื่อบๆ จนกว่าจะพิมพ์คำว่า end
				System.out.print("\nEnter word: ");
				String word = in.nextLine().trim().replaceAll("\\s+", " ");	
				searchWord(word);
				if(word.equalsIgnoreCase("end")) {
					succes = true;
				}
			}while(!succes);
			in.close();
		}else {
			//if load file error
			System.out.println(" File read ERROR!!");
		}
		System.out.println(" End Program");
		
	}

}

class Dict implements Comparable <Dict>{ //สร้าง class object ที่มี method เปรียบเทียบ
	String word;
	String meaning;
	String type;
	
	public Dict() {
		//constructor method
	}
	
	public Dict(String i) {  //method ที่ไว้สร้าง object โดยมี  พารามิเตอร์ เป็น string
		String [] str = i.split(","); //ตัดคำที่คั่นด้วย ลูกน้ำ แล้วเก็บใส่ array
		
		word = str[0].trim().replaceAll("\\s+", " "); //ให้ตัวแปร word ของ object เป็นคำแรก
		meaning = str[1].trim().replaceAll("\\s+", " "); //ให้ตัวแปร meaning ของ object เป็นคำที่สอง
		type = str[2].trim().replaceAll("\\s+", " ");  //ให้ตัวแปร type ของ object เป็นคำที่สาม
	}
	public void addWord(String s) {  //method สำหรับสร้าง object ที่มีแค่ word
		word = s;
		meaning = null;
		type = null;
	}
	public void printData() { //method แสดงผลข้อมูล 1 ตัว
		System.out.println(" "+word+"\t"+meaning+" ("+type+")");
	}

	
	public int compareAll(Dict s) {  //method ที่ไว้เปรียบเทียบข้อมูลทุกลักษณะ (word , meaning , type )
		
		if(this.word.compareToIgnoreCase(s.word)==0 && this.meaning.compareToIgnoreCase(s.meaning)==0 && this.type.compareToIgnoreCase(s.type)==0 ) {
			return 1;
		}else {
			return 0;
		}
	}
	
	public int compareWord(String s) {  //method เปรียบเทียบ เฉพาะ word ที่มี parameter เป็น string
		if(this.word.compareToIgnoreCase(s)==0)
			return 1;
		else 
			return 0;
	}
	
	@Override
	public int compareTo(Dict s) {
		
		return (int)this.word.compareToIgnoreCase(s.word); //method เปรียบเทียบ เฉพาะ word ที่มี parameter เป็น object 
		//ไว้ใช้สำหรับ sort และ binary search
	}
}




