package assign10;

public class KruskalEdge implements Comparable<KruskalEdge> {

	int weight;
	int from,to;
	String name;
	
	public KruskalEdge() {
	}
	
	public KruskalEdge(int i,int j,int weight) {
		String [] ch = {"A","B","C","D","E","F","G"};
		
		this.from = i;
		this.to = j;
		this.name = ch[i] + ch[j];		
		this.weight = weight;
	}
	
	public String toString() {
		return this.name + " : " + this.weight;
		
	}
	
	@Override
	public int compareTo(KruskalEdge y) {
		// TODO Auto-generated method stub
		return this.weight - y.weight;
	}
	
	

	
	
}

