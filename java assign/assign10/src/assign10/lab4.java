package assign10;

import java.util.ArrayList;
import java.util.PriorityQueue;

public class lab4 {

	
	public static void main(String[] args) {
				
		int graph[][] = new int [][] {
			{0,2,4,1,0,0,0},
			{2,0,0,3,10,0,0},
			{4,0,0,2,0,5,0},
			{1,3,2,0,7,8,4},
			{0,10,0,7,0,0,6},
			{0,0,5,8,0,0,1},
			{0,0,0,4,6,1,0},
		};
		
		//display
		System.out.println("------ Kruskal Algorithm ------- \n");
		//delete duplicate node
		int row,col;
		row = col = graph.length;
		int i,j;
		for(i=0;i<row;i++) {
			for(j=0;j<col;j++) {
				if(graph[i][j]==graph[j][i])
					graph[j][i] = 0;
			}
		}
		
		//cover array to graph
		PriorityQueue<KruskalEdge> edge = new PriorityQueue<KruskalEdge>();
		
		for(i=0; i<graph.length ; i++) {
			for(j=0; j<graph[i].length; j++) {
				if(graph[i][j]!=0) {
					KruskalEdge e = new KruskalEdge(i,j,graph[i][j]);
					edge.add(e);
				}
				
			}
		}

		//Kruskal process
		
		ArrayList<KruskalEdge> MST = new ArrayList<KruskalEdge>();
		boolean loop[][] = new boolean[row][col]; //array for warshall
		KruskalEdge e;
		while((e = edge.poll()) != null) {

			if(loop[e.from][e.to] == false) {
				System.out.println("Select edge : "+e.toString());
				loop[e.from][e.to] = true;
				loop[e.to][e.from] = true;
				warshall(loop,row,col);
				MST.add(e);			
			}
			else {
				System.out.println("Delete edge : "+e.toString());
			}
			
		}
		//show all Edge are selected
		System.out.println("\n------ Success ------\n");
		int sum = 0;
		for(KruskalEdge x : MST) {
			System.out.println(x.toString());
			sum += x.weight;
		}
		System.out.println("Total weight : "+sum);
		
		
	}
	// warshall's algorithm for check the edge that is selected make cycle ?
	public static void warshall(boolean[][] loop,int row,int col) {
		for(int m=0;m<row;m++) {
			for(int i=0;i<col;i++) {
				for(int j=0;j<row;j++) {
					loop[i][j] = loop[i][j] || (loop[i][m] && loop[m][j]);
				}
			}
		}
	}

}








