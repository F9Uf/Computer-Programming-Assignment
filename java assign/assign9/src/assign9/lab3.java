package assign9;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

public class lab3 {

	static HashMap<String, ArrayList<String>> dict = new HashMap<String, ArrayList<String>>(); //�ͧ�����Ẻ HashMap ����� key �� string ��� value �� arraylist string 
	static int total = 0; //����纨ӹǹ�����ŷ�����
	static int dup = 0; //����纨ӹǹ�����ŷ���ӡѹ

	static boolean readFile(String filename) {  //function ��ҹ�������红�����
		String str;
		try {
			FileInputStream in = new FileInputStream(filename); //���¡��������������
			InputStreamReader fr = new InputStreamReader(in, "UTF8"); //��˹������ҹẺ UTF8
			BufferedReader br = new BufferedReader(fr); //��ҹ���

			int BOM = br.read();  //��ҹ���������ǹ��Ƿ���������
			while ((str = br.readLine()) != null) { //��з���ѧ�բ����źѹ�Ѵ�Ѵ�
				total++; //�Ѻ�ӹǹ������
				addData(str); //�� string �����ҹ��价ӧҹ��� addData method
			}

			br.close(); //�Դ���
			return true; //�����ҹ����� return true
		} catch (Exception e) {
			return false; //�����ҹ����� �����Դ error return false

		}
	}

	static void addData(String s) { //method �Ѵ�红�����
		String[] buff = s.split(","); //�Ѵ string ����蹴����١���
		String key = buff[0].trim().replaceAll("\\s+", " ").toLowerCase(); //�Ѵ�����ä�����ŧ�繵������������ key
		String val = buff[1].trim().replaceAll("\\s+", " ").toLowerCase() + " ("
				+ buff[2].trim().replaceAll("\\s+", " ").toLowerCase() + ")"; //�Ӥ��� ��� ��Դ ������ѹ
		ArrayList<String> mean = new ArrayList<String>();//�ͧ����� arrayList

		if (dict.containsKey(key)) {
			// ����դ��Ѿ���ӡ�͹˹������
			mean = dict.get(key); //�֧ array���Ţͧ�ӹ���͡��

			if (!mean.contains(val)) {  //����ѧ����դ��Ź��
				mean.add(val); //���������������ŧ�
				dict.put(key, mean); //���� put ����������ŧ价Ѻ�ѹ���
			} else {
				dup++; //�Ѻ�ӷ���դ��ë�ӡѹ
			} 

		} else {//����ѧ����դ��Ѿ���������������ŧ� dict
			mean.add(val);
			dict.put(key, mean);
		}

	}

	static String MaxMean() {
		int max = 0;
		String word = "";
		for (String s : dict.keySet()) { //ǹ�ͺ�����ŷء���
			if (dict.get(s).size() > max) {
				// ��Ҥ��������ҡ����ش ���Ӥӹ�����
				max = dict.get(s).size();
				word = s;
			}
		}
		return word;
	}

	static void printD(String s) {  //�ʴ��Ţ����� 1 key
		int n=0;
		
		System.out.println(" " + s);
		for (String i : dict.get(s)) {
			System.out.println("     | " + (++n)+" | "+i);
		}
	}

	public static void main(String[] args) {

		String path = "file//utf8lexitron.csv";
		if (readFile(path)) { //�����ҹ��������
			boolean exit = false;
			Scanner in = new Scanner(System.in);
			//�ʴ��Ũӹǹ�����ŵ�ҧ�
			System.out.println("\n Total Read " + total + " records."); 
			System.out.println(" Total duplicate found " + dup + " records.");
			System.out.println(" Total remaining size " + (total - dup) + " records.");
			String maxmean = MaxMean();
			System.out.println(" Maximum Meaning word " + maxmean + " have " + dict.get(maxmean).size() + " meaning.");
			printD(maxmean);
			
			do {
				//ǹ�ͺ�Ѻ�Өҡ����� �Ҥ��� 
				System.out.print("\n Enter word :");
				String word = in.nextLine().trim().replaceAll("\\s+", " ").toLowerCase(); 
				//�Ѵ��äӷ���͹���¡�õѴ��ͧ��ҧ˹����ѧ ���� ᷹��������ä���� �������ä���� ��� �ŧ�繵����� ���ͨ�����µ�͡�ä���
				if(dict.containsKey(word)) {//����դӹ���� dict ����ʴ�������
					printD(word);
				}else {
					System.out.println(" "+word+" Not found."); //�������� ��� �ʴ���� not found.
				}
				
				if(word.compareToIgnoreCase("end")==0)
					exit = true;
				//���͡�ҡǹ�ͺ����� ������������� end 
			}while(!exit); 
			in.close();

		} else {
			System.out.println(" Can not read file."); //�����ҹ�������� ���� �� error
		}
		
		System.out.println(" End Program.");

	}

}
