package prim;

import java.util.ArrayList;
import java.util.PriorityQueue;

public class lab5 {
	
	public static PriorityQueue<primEdge> primMap = new PriorityQueue<primEdge>();
	
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
		System.out.println("------ prim's Algorithm ------- \n");
		
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
		PriorityQueue<primEdge> edge = new PriorityQueue<primEdge>();
		
		for(i=0;i<row;i++) {
			for(j=0;j<col;j++) {
				if(graph[i][j] != 0) {
					primEdge e = new primEdge(i,j,graph[i][j]);
					edge.add(e);
				}
			}
		}
		//prim Process
		
		
		primEdge e;
		e = edge.poll();
		primMap.add(e);	 //select first edge or minimum edge.
	
		ArrayList<primEdge> MST = new ArrayList<primEdge>();
			
		//loop for find the correct edge and add to array of MST.
		
		while((e = primMap.poll())!=null){
			if(!MST.contains(e)) {
				if(!isCycle(MST,e)) {
					edge = findConnectEdge(e,edge);
					MST.add(e);
					System.out.println("Select edge : "+e.toString());
				}else {
					System.out.println("Delete edge : "+e.toString());
				}
				
			}
		}
		
		//print answer and sum weight
		int sum = 0;
		System.out.println("\n\n\n ----------- MST -------------");
		for(primEdge x : MST) {
			System.out.println(x.toString());
			sum += x.weight;
		}
		System.out.println("Total weight : "+sum);
		
		
	}
	//find other edge that connect with edge that is selected.
	public static PriorityQueue<primEdge> findConnectEdge(primEdge e, PriorityQueue<primEdge> edge) {
		primEdge a;
		PriorityQueue<primEdge> buff = new PriorityQueue<primEdge>();
		
		while((a = edge.poll())!=null) {
			if((a.from == e.from) || (a.from == e.to) || (a.to == e.from) || (a.to == e.to)) {
				primMap.add(a);
			}else {
				buff.add(a);
			}
		}
		return buff;
		
	}
	//check edge that is selected is cycle?
	public static boolean isCycle(ArrayList<primEdge> MST,primEdge e) {
		int check=0;
		for(primEdge x : MST) {
			if((e.from == x.from) || (e.from == x.to)) {
				for(primEdge y : MST) {
					if((e.to == y.from) || (e.to == y.to)) {
						check = 1;
					}
				}
			}
		}
		
		if(check>0) return true;
		else return false;
	}

}
