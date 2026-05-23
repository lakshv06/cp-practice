import java.util.HashMap;
import java.util.Scanner;

public class two_sum {
    public static void main(String[] args){
        try(Scanner sc = new Scanner(System.in)){
            int target = Integer.parseInt(sc.nextLine());
            int n= Integer.parseInt(sc.nextLine());
            int [] arr = new int[n];
            for(int i = 0; i<n; i++){
                arr[i] = Integer.parseInt(sc.next());
            }
            int [] res = new int[2];
            boolean found = false;
            HashMap<Integer, Integer> mp = new HashMap<>();
            for(int i=0; i<n; i++){
                if(mp.containsKey(target-arr[i])){
                    res[0] = mp.get(target-arr[i]);
                    res[1] = i;
                    found = true;
                    break;
                }
                mp.put(arr[i], i);
            }
            if(found){
                System.out.println(res[0]+" "+res[1]);
            } else{
                System.out.println("No two sum solution");
            }
        } catch(Exception e){
            System.err.println("Error occured: "+e.getMessage());
        }
    }
}
