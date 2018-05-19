package assign8;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Scanner;
import java.util.TreeSet;

public class lab2 {
	//��˹� ����� Ẻ global
	static TreeSet<Dnode> data = new TreeSet<Dnode>();
	static int countDup = 0;
	static int countTot = 0;
	
	static boolean loadFile(String filename) {
		String str;
		try {//��ҹ file Ẻ UTF8
			FileInputStream in = new FileInputStream(filename);
			InputStreamReader fr = new InputStreamReader(in,"UTF8");
			BufferedReader br = new BufferedReader(fr);
			
			int BOM = br.read(); //��ҹ��÷Ѵ�á�������ǹ��Ƿ��
			
			while((str=br.readLine())!=null ) { //ǹ�ͺ��ҹ���к�÷Ѵ�������樹���Ҩ����
				Dnode buff = new Dnode(str);
				countTot++;//�Ѻ�ӹǹ�ӷ����������ҹ��
				if(data.contains(buff)) { //����դӫ�� ���������������ŧ� node ���
					TreeSet<Dnode> z = (TreeSet<Dnode>) data.subSet(buff, true , buff ,true); //���¡ sub tree ���¢ͧ�ӹ����
					if(!z.first().mean.contains(buff.mean.get(0))) { //��Ҥ�����������ӡѺ���������� node ������������������������ŧ�
						z.first().mean.addAll(buff.mean);
					}else {
						countDup++; //��Ҥ������«�� ���Ѻ�ӹǹ�ӷ���ӡѹ
					}
				}else {
					data.add(buff); //��������������� node ����
				}
			}
			br.close();//�Դ�����ҹ file
			return true;
		}catch(Exception e) {
			return false; //�����ҹ����� return false
		}
	}
	
	static Dnode findDup() {//method �Ҥӷ��դ��������ҡ����ش
		Iterator<Dnode> it = data.iterator(); //�� iterator �Ҫ���㹡�� index ������
		int max=0;
		Dnode wordDup = new Dnode();
		Dnode buff = new Dnode();
		while(it.hasNext()) { //ǹ�ͺ��ҹ������յ�ǶѴ�
			buff = it.next(); //��� buff �繤�Ңͧ node ���� node 㹡��ǹ�ͺ
			if(buff.mean.size()>max) { //��� node �˹�դ��������ҡ����ش ���� node ������
				max = buff.mean.size();
				wordDup=buff;
			}
		}
		return wordDup; //return node ����դ��������ҡ����ش
	}
	
	static void searchDict(String key) { // �Ҥӵ����������͹�����
		Dnode buff = new Dnode();
		buff.addNode(key); // �Ӥӷ�������͹�������ŧ�� object ������� word

		if (data.contains(buff)) { // ����� node �������� tree ��� �֧ sub tree node ������ʴ���
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
		
		if(loadFile(path)) { //�����ҹ file �����
			// ��˹�����õ�ҧ�
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
			
			//�ʴ��Ťӷ���դ��������ҡ����ش
			while(it.hasNext()) {
				buff = it.next(); 
				if(buff.compareTo(wordDup)==0) {
					buff.printDnode();
				}
			}
			
			do {
				//ǹ�ͺ�Ѻ string �ҡ����� ����令���� tree ����դ�������
				System.out.print("\n Enter word : ");
				String command = in.nextLine().trim().replaceAll("\\s+", " ");
				searchDict(command);
				if(command.compareToIgnoreCase("end")==0)
					exit = true;
				
			}while(!exit); //������ش��÷ӧҹ����ͼ�����͹����� end
			in.close(); //�Դ����Ѻ������
		}else { System.out.println(" Cannot Read file."); }//�������ö��ҹ file ��
		System.out.println(" End program.");
	}
}
//******************** class ********************//
class Dnode implements Comparable<Dnode> {
	//class object Dnode
	String word;
	ArrayList<String> mean;
	
	public Dnode() { //constructor method Ẻ����� ����������
		word="";
		mean = new ArrayList<String>();
	}
	public Iterator<Dnode> iterator() {
		return null;
	}
	public Dnode(String i) { //constructor method Ẻ�� ����������
		String [] str = i.split(","); //�Ѵ�Өҡ �١���		
		String tmp = str[1].trim().replaceAll("\\s+", " ")+" ("+str[2].trim().replaceAll("\\s+", " ")+")";  //����������� ��Ъ�Դ�繵��������
		//���ҧ������ object
		word = str[0].trim().replaceAll("\\s+", " ");
		mean = new ArrayList<String>();
		mean.add(tmp);
		
	}
	//�ʴ��Ţ����� �� �������� 1 node
	public void printDnode() {
		System.out.println(" "+word);
		for(String s:mean) {

			System.out.println("     |"+s);
		}
	}
	//���ҧ node ����������� word
	public void addNode(String s) {
		word = s;
		mean = new ArrayList<String>();
	}
	//method ����º��º
	@Override
	public int compareTo(Dnode s) {
		return (int)this.word.compareToIgnoreCase(s.word);
	}
	
}