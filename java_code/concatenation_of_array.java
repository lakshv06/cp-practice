
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;


public class concatenation_of_array {

    public static int[] getConcatenation(List<Integer> arr, int n) {
        int [] res = new int[2*n];
        for(int i = 0; i<n; i++){
            res[i] = arr.get(i);
            res[i+n] = arr.get(i);
        }
        return res;
    }
    public static void main(String[] args){
        try(Scanner sc = new Scanner(System.in)){
        int n;
        System.out.print("Enter the size of the array: ");
        n = Integer.parseInt(sc.nextLine());

        List<Integer>arr = new ArrayList<>();
        for(int i= 0; i<n; i++){
            int inp = Integer.parseInt(sc.next());
            arr.add(inp);
        }
        int[] ans = getConcatenation(arr, n);
        for(int i: ans){
            System.out.print(i+" ");
        }
        System.out.println();
        }
    }
}
