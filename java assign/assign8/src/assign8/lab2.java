package assign8;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Scanner;
import java.util.TreeSet;

public class lab2 {
	//กำหนด ตัวแปร แบบ global
	static TreeSet<Dnode> data = new TreeSet<Dnode>();
	static int countDup = 0;
	static int countTot = 0;
	
	static boolean loadFile(String filename) {
		String str;
		try {//อ่าน file แบบ UTF8
			FileInputStream in = new FileInputStream(filename);
			InputStreamReader fr = new InputStreamReader(in,"UTF8");
			BufferedReader br = new BufferedReader(fr);
			
			int BOM = br.read(); //อ่านบรรทัดแรกที่เป็นส่วนหัวทิ้ง
			
			while((str=br.readLine())!=null ) { //วนรอบอ่านแต่ละบรรทัดไปเรื่อยๆจนกว่าจะหมด
				Dnode buff = new Dnode(str);
				countTot++;//นับจำนวนคำทั้งหมดที่อ่านได้
				if(data.contains(buff)) { //ถ้ามีคำซ้ำ ให้เพิ่มความหมายลงใน node เดิม
					TreeSet<Dnode> z = (TreeSet<Dnode>) data.subSet(buff, true , buff ,true); //เรียก sub tree ย่อยของคำนั้นมา
					if(!z.first().mean.contains(buff.mean.get(0))) { //ถ้าความหมายไม่ซ้ำกับที่มีอยู่ใน node ให้เพิ่มความหมายใหม่ทั้งหมดลงไป
						z.first().mean.addAll(buff.mean);
					}else {
						countDup++; //ถ้าความหมายซ้ำ ให้นับจำนวนคำที่ซ้ำกัน
					}
				}else {
					data.add(buff); //ถ้าไม่ซ้ำให้เพิ่ม node ใหม่
				}
			}
			br.close();//ปิดการอ่าน file
			return true;
		}catch(Exception e) {
			return false; //ถ้าอ่านไม่ได้ return false
		}
	}
	
	static Dnode findDup() {//method หาคำทีมีความหมายมากที่สุด
		Iterator<Dnode> it = data.iterator(); //ใช้ iterator มาช่วยในการ index ข้อมูล
		int max=0;
		Dnode wordDup = new Dnode();
		Dnode buff = new Dnode();
		while(it.hasNext()) { //วนรอบอ่านเมื่อมีตัวถัดไป
			buff = it.next(); //ให้ buff เป็นค่าของ node แต่ละ node ในการวนรอบ
			if(buff.mean.size()>max) { //ถ้า node ไหนมีความหมายมากที่สุด ให้จำ node นั้นไว้
				max = buff.mean.size();
				wordDup=buff;
			}
		}
		return wordDup; //return node ที่มีความหมายมากที่สุด
	}
	
	static void searchDict(String key) { // หาคำตามที่ผู้ใช้ป้อนเข้ามา
		Dnode buff = new Dnode();
		buff.addNode(key); // นำคำที่ผู้ใช้ป้อนเข้ามาไปแปลงเป็น object ที่มีแต่ word

		if (data.contains(buff)) { // ถ้ามี node นี้อยู่ใน tree ให้ ดึง sub tree node นั้นมาแสดงผล
			TreeSet<Dnode> z = (TreeSet<Dnode>) data.subSet(buff, true, buff, true);
			System.out.println(" found " + key + " " + z.first().mean.size() + " words.");
			z.first().printDnode();
			// found
		} else {
			// not found
			System.out.println("\n " + key + " Not found");
		}
	}
// ******************* main ********************//
	public static void main(String[] args) {
		String path = "C:\\Users\\Administrator.Admin-PC\\Desktop\\CPE100\\term2\\java assign\\assign8\\file\\utf8lexitron.csv";
		
		if(loadFile(path)) { //ถ้าอ่าน file สำเร็จ
			// กำหนดตัวแปรต่างๆ
			Dnode wordDup = new Dnode();
			Dnode buff = new Dnode();
			wordDup = findDup();
			Iterator<Dnode> it = data.iterator();
			boolean exit = false;
			Scanner in = new Scanner(System.in);

			System.out.println("\n Total Read : "+countTot+" records.");
			System.out.println(" Total Duplicate Found : "+countDup+" records.");
			System.out.println(" Total Remaining Size : "+(countTot-countDup)+" records.");
			System.out.println(" Maximun Meaning Word "+wordDup.word+" have "+wordDup.mean.size()+" meaning.\n");
			System.out.println(data.size());
			
			//แสดงผลคำที่มีความหมายมากที่สุด
			while(it.hasNext()) {
				buff = it.next(); 
				if(buff.compareTo(wordDup)==0) {
					buff.printDnode();
				}
			}
			
			do {
				//วนรอบรับ string จากผู้ใช้ เพื่อไปค้นหาใน tree ว่ามีคำๆนั้นไหม
				System.out.print("\n Enter word : ");
				String command = in.nextLine().trim().replaceAll("\\s+", " ");
				searchDict(command);
				if(command.compareToIgnoreCase("end")==0)
					exit = true;
				
			}while(!exit); //จะสิ้นสุดการทำงานเมื่อผู้ใช้ป้อนคำว่า end
			in.close(); //ปิดการรับข้อมูล
		}else { System.out.println(" Cannot Read file."); }//ไม่สามารถอ่าน file ได้
		System.out.println(" End program.");
	}
}
//******************** class ********************//
class Dnode implements Comparable<Dnode> {
	//class object Dnode
	String word;
	ArrayList<String> mean;
	
	public Dnode() { //constructor method แบบไม่มี พารามิเตอร์
		word="";
		mean = new ArrayList<String>();
	}
	public Iterator<Dnode> iterator() {
		return null;
	}
	public Dnode(String i) { //constructor method แบบมี พารามิเตอร์
		String [] str = i.split(","); //ตัดคำจาก ลูกน้ำ		
		String tmp = str[1].trim().replaceAll("\\s+", " ")+" ("+str[2].trim().replaceAll("\\s+", " ")+")";  //รวมความหมาย และชนิดเป็นตัวแปรเดียว
		//สร้างค่าให้ object
		word = str[0].trim().replaceAll("\\s+", " ");
		mean = new ArrayList<String>();
		mean.add(tmp);
		
	}
	//แสดงผลข้อมูล คำ ความหมาย 1 node
	public void printDnode() {
		System.out.println(" "+word);
		for(String s:mean) {

			System.out.println("     |"+s);
		}
	}
	//สร้าง node เปล่าๆที่มีแต่ word
	public void addNode(String s) {
		word = s;
		mean = new ArrayList<String>();
	}
	//method เปรียยบเทียบ
	@Override
	public int compareTo(Dnode s) {
		return (int)this.word.compareToIgnoreCase(s.word);
	}
	
}