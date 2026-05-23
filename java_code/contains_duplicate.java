import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;

public class contains_duplicate{
    public static void main (String[] args){
        try (Scanner sc = new Scanner(System.in);){
             int n = Integer.parseInt(sc.nextLine());
        int[] arr = new int[n];
        for(int i = 0; i<n; i++){
            arr[i] = Integer.parseInt(sc.next());
        }

        boolean res = false;
        Set<Integer>st = new HashSet<>();
        for(int i = 0; i<n; i++){
            if(st.contains(arr[i])){
                res = true;
                break;
            }
            st.add(arr[i]);
        }
        System.out.println(res);
        } catch (Exception e) {
            System.err.println("Error occured: "+e.getMessage());
        }
    }
}