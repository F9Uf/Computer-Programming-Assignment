package prim;

public class primEdge implements Comparable<primEdge> {
	String name;
	int to,from,weight;
	
	public primEdge() {
		
	}
	
	public primEdge(int i,int j,int weight) {
		String [] ch = { "A", "B", "C", "D", "E", "F", "G" };
		
		this.to = i;
		this.from = j;
		this.weight = weight;
		this.name = ch[i] + ch[j];

	}
	
	public String toString() {
		return this.name + " : " + this.weight ;
	}

	@Override
	public int compareTo(primEdge y) {
		
		return this.weight - y.weight;
	}
}
