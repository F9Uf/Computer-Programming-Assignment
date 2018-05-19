package assign7;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;


public class lab1 {

	static ArrayList<Dict> data = new ArrayList<Dict> ();  //��˹������ ArrayList ��������� data �� Ẻ Global
	

	static boolean loadFile(String filename) {  // method load file
		String str;
		try {
			FileInputStream in = new FileInputStream(filename);  //�繡�����¡ file ������������ͧ���
			InputStreamReader fr = new InputStreamReader(in,"UTF8"); //�͡�����Ҩ���ҹ���Ẻ UTF8
			BufferedReader br = new BufferedReader(fr); //���¡�� �����ҹ file
			
			int BOM = br.read();  //��ҹ �����ź�÷Ѵ�á���� ���ͧ�ҡ����ǹ��Ƿ���������ͧ���
			
			while((str=br.readLine())!=null) {  //��ҹ���к�÷Ѵ�����
				Dict buff = new Dict(str);  //�ŧ�����ŷ����������� object
				data.add(buff); //���ǹ� object ������ arrayList ���������ҧ���
				
			}
			br.close();  //�Դ�����ҹ���
			return true; //return true ��ҷ���
			
		}catch(Exception e) {

			return false; //����Դ error ��� return false
		}
	}
	
	static int searchDuplicate() {  //method ���ҵ�Ƿ���ӡѹ
		int i,count=0;
		
		for(i=0;i<data.size()-1;i++) {  //ǹ�ͺ���º��º n-1  ���
			
			if(data.get(i).compareAll(data.get(i+1))==1) {
				//����յ�ǶѴ仫�ӡѹ���ź��� ���ǹӨӹǹ
				data.remove(i+1);
				count++;
			}
		}
		return count;
		
	}
	
	static int searchMaxMean(String [] s) {  // ���ҵ�Ƿ���դ��������ҡ����ش
		int i,count=0,max=0;
		for(i=0;i<data.size()-1;i++) {  //ǹ�ͺ n-1 ���
			if(data.get(i).compareTo(data.get(i+1))==0) {  //��ҵ�ǶѴ��դ�����͹�ѹ���Өӹǹ
				count++;
			}else {  //��ҵ�ǶѴ��դӷ���������͹�ӻѨ�غѹ
				if(count > max) {  //��Ǩ�ͺ��� �ӹǹ���Ѻ�Ңͧ�ӻѨ�غѹ�դ���ҡ���Ҥӷ���ҡ����ش��͹˹���������
					max = count;  //��������ӵ�ǹ��
					s[0] = data.get(i).word;  // ����纤ӹ��������� string
				}
				count = 0; //reset ��ùѺ�ӹǹ
			}
		}
		return max+1; // max+1 ���Ф���á���Ѻ ��ҹѺ��§������������ 2 ��� �֧�ǡ 1 ����
	}
	
	static void searchWord(String s) {  //���Ҥӷ������͹�Ѻ�����һ�͹����
		Dict buff = new Dict(); 
		buff.addWord(s);  //���ҧ object ������ ������� word ������ search Ẻ binary search
		int x = Collections.binarySearch(data, buff); //�� binary search ���ҵ��˹�
		int first,last,i,j=1;
		
		
		
		if(x>=0) {  //found
			first = x-1;
			last = x+1;
			if(first!=0) {  //�����������á ���ǹ�ͺ�����ѧ�Ҩӹǹ�ӷ������͹�ѹ��������
				while(data.get(first).compareTo(buff)==0 ) {
					first--;
				}
			}
			if(last!=(data.size()-1)) {  //�����������ش���� ���ǹ�ͺ仴�ҹ˹�������Ҥӷ������͹��������
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
			System.out.println(s+" not found"); //��������
		}

	}
	public static void main(String[] args) {
		
		String path = "C:\\Users\\Administrator.Admin-PC\\Desktop\\CPE100\\term2\\java assign\\assign7\\file\\utf8lexitron.csv" ;
		String [] maxWord = new String[1];
		int same = 0, max = 0, i = 1;
		Scanner in = new Scanner(System.in);  //���¡�� class Scanner
		
		if(loadFile(path)) {
			//if load file success
			Boolean succes= false;
			System.out.println(" Total Read "+data.size()+" records");

			Collections.sort(data); //sort data
			
			same = searchDuplicate(); // search Duplicate data
			
			max = searchMaxMean(maxWord);  //�Ҥӷ���դ��������ҡ����ش

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
			do { //ǹ�ͺ��������͹�����ͤ��Ң����������ͺ� �����Ҩо�������� end
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

class Dict implements Comparable <Dict>{ //���ҧ class object ����� method ���º��º
	String word;
	String meaning;
	String type;
	
	public Dict() {
		//constructor method
	}
	
	public Dict(String i) {  //method ���������ҧ object ����  ���������� �� string
		String [] str = i.split(","); //�Ѵ�ӷ���蹴��� �١��� ��������� array
		
		word = str[0].trim().replaceAll("\\s+", " "); //������� word �ͧ object �繤��á
		meaning = str[1].trim().replaceAll("\\s+", " "); //������� meaning �ͧ object �繤ӷ���ͧ
		type = str[2].trim().replaceAll("\\s+", " ");  //������� type �ͧ object �繤ӷ�����
	}
	public void addWord(String s) {  //method ����Ѻ���ҧ object ������� word
		word = s;
		meaning = null;
		type = null;
	}
	public void printData() { //method �ʴ��Ţ����� 1 ���
		System.out.println(" "+word+"\t"+meaning+" ("+type+")");
	}

	
	public int compareAll(Dict s) {  //method ���������º��º�����ŷء�ѡɳ� (word , meaning , type )
		
		if(this.word.compareToIgnoreCase(s.word)==0 && this.meaning.compareToIgnoreCase(s.meaning)==0 && this.type.compareToIgnoreCase(s.type)==0 ) {
			return 1;
		}else {
			return 0;
		}
	}
	
	public int compareWord(String s) {  //method ���º��º ੾�� word ����� parameter �� string
		if(this.word.compareToIgnoreCase(s)==0)
			return 1;
		else 
			return 0;
	}
	
	@Override
	public int compareTo(Dict s) {
		
		return (int)this.word.compareToIgnoreCase(s.word); //method ���º��º ੾�� word ����� parameter �� object 
		//���������Ѻ sort ��� binary search
	}
}




