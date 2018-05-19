package assign9;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

public class lab3 {

	static HashMap<String, ArrayList<String>> dict = new HashMap<String, ArrayList<String>>(); //จองตัวแปรแบบ HashMap ที่เก็บ key เป็น string และ value เป็น arraylist string 
	static int total = 0; //ไว้เก็บจำนวนข้อมูลทั้งหมด
	static int dup = 0; //ไว้เก็บจำนวนข้อมูลที่ซ้ำกัน

	static boolean readFile(String filename) {  //function อ่านไฟล์และเก็บข้อมูล
		String str;
		try {
			FileInputStream in = new FileInputStream(filename); //เรียกไฟล์เข้ามาในโปรแกรม
			InputStreamReader fr = new InputStreamReader(in, "UTF8"); //กำหนดการอ่านแบบ UTF8
			BufferedReader br = new BufferedReader(fr); //อ่านไฟล์

			int BOM = br.read();  //อ่านไฟล์ที่เป็นส่วนหัวที่ไม่ใช้ทิ้ง
			while ((str = br.readLine()) != null) { //ขณะที่ยังมีข้อมูลบันทัดถัดไป
				total++; //นับจำนวนทั้งหมด
				addData(str); //นำ string ที่อ่านได้ไปทำงานที่ addData method
			}

			br.close(); //ปิดไฟล์
			return true; //ถ้าอ่านไฟล์ได้ return true
		} catch (Exception e) {
			return false; //ถ้าอ่านไม่ได้ หรือเกิด error return false

		}
	}

	static void addData(String s) { //method จัดเก็บข้อมูล
		String[] buff = s.split(","); //ตัด string ที่คั่นด้วยลูกน้ำ
		String key = buff[0].trim().replaceAll("\\s+", " ").toLowerCase(); //ตัดเว้นวรรคแล้วแปลงเป็นตัวเล็กเก็บไว้ที่ key
		String val = buff[1].trim().replaceAll("\\s+", " ").toLowerCase() + " ("
				+ buff[2].trim().replaceAll("\\s+", " ").toLowerCase() + ")"; //นำคำแปล และ ชนิด มารวมกัน
		ArrayList<String> mean = new ArrayList<String>();//จองตัวแปร arrayList

		if (dict.containsKey(key)) {
			// ถ้ามีคำศัพท์ซ้ำก่อนหน้าแล้ว
			mean = dict.get(key); //ดึง arrayคำแปลของคำนั้นออกมา

			if (!mean.contains(val)) {  //ถ้ายังไม่มีคำแปลนี้
				mean.add(val); //ให้เพิ่มคำแปลใหม่ลงไป
				dict.put(key, mean); //แล้ว put ข้อมูลใหม่ลงไปทับอันเดิม
			} else {
				dup++; //นับคำที่มีคำแปรซ้ำกัน
			} 

		} else {//ถ้ายังไม่มีคำศัพท์นี้ให้เพิ่มใหม่ลงใน dict
			mean.add(val);
			dict.put(key, mean);
		}

	}

	static String MaxMean() {
		int max = 0;
		String word = "";
		for (String s : dict.keySet()) { //วนรอบข้อมูลทุกตัว
			if (dict.get(s).size() > max) {
				// ถ้าความหมายมากที่สุด ให้จำคำนั้นไว้
				max = dict.get(s).size();
				word = s;
			}
		}
		return word;
	}

	static void printD(String s) {  //แสดงผลข้อมูล 1 key
		int n=0;
		
		System.out.println(" " + s);
		for (String i : dict.get(s)) {
			System.out.println("     | " + (++n)+" | "+i);
		}
	}

	public static void main(String[] args) {

		String path = "file//utf8lexitron.csv";
		if (readFile(path)) { //ถ้าอ่านไฟล์สำเร็จ
			boolean exit = false;
			Scanner in = new Scanner(System.in);
			//แสดงผลจำนวนข้อมูลต่างๆ
			System.out.println("\n Total Read " + total + " records."); 
			System.out.println(" Total duplicate found " + dup + " records.");
			System.out.println(" Total remaining size " + (total - dup) + " records.");
			String maxmean = MaxMean();
			System.out.println(" Maximum Meaning word " + maxmean + " have " + dict.get(maxmean).size() + " meaning.");
			printD(maxmean);
			
			do {
				//วนรอบรับคำจากผู้ใช้ มาค้นหา 
				System.out.print("\n Enter word :");
				String word = in.nextLine().trim().replaceAll("\\s+", " ").toLowerCase(); 
				//จัดการคำที่ป้อนมาโดยการตัดช่องว่างหน้าหลัง แล้ว แทนที่เว้นวรรคยาวๆ เป็นเว้นวรรคเดียว และ แปลงเป็นตัวเล็ก เพื่อจะได้ง่ายต่อการค้นหา
				if(dict.containsKey(word)) {//ถ้ามีคำนนี้ใน dict ให้แสดงข้อมูล
					printD(word);
				}else {
					System.out.println(" "+word+" Not found."); //ถ้าไม่มี ให้ แสดงว่า not found.
				}
				
				if(word.compareToIgnoreCase("end")==0)
					exit = true;
				//จะออกจากวนรอบเมือ่ ผู้ใช้พิมพ์คำว่า end 
			}while(!exit); 
			in.close();

		} else {
			System.out.println(" Can not read file."); //ถ้าอ่านไฟล์ไม่ได้ หรือ มี error
		}
		
		System.out.println(" End Program.");

	}

}
