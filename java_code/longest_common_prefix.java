import java.util.Scanner;

public class longest_common_prefix {

    public static String commonPrefix(String s1, String s2){
        String res = "";
        for(int i = 0; i<Math.min(s1.length(), s2.length()); i++){
            if(s1.charAt(i)==s2.charAt(i)){
                res+=s1.charAt(i);
            } else{
                break;
            }
        }
        return res;
    }
    public static void main (String[] args){
        try(Scanner sc = new Scanner(System.in)){
            int n = Integer.parseInt(sc.nextLine());
            String [] arr = new String[n];
            for(int i = 0; i<n; i++){
                arr[i] = sc.nextLine();
            }
            String res = arr[0];
            for(int i = 1; i<n; i++){
                res = commonPrefix(res, arr[i]);
                if(res.isEmpty())break;
            }
            System.out.println(res);
        }
    }
}
