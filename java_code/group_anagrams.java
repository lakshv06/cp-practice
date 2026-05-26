import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

public class group_anagrams {
    public static void main(String [] args){
        try (Scanner sc = new Scanner(System.in)){
            int n = Integer.parseInt(sc.nextLine());
            List<String>arr = new ArrayList<>();
            for(int i = 0; i<n; i++){
                String inp = sc.nextLine();
                arr.add(inp);
            }
            Map<ArrayList<Integer>, List<String>>mp = new HashMap<>();
            for(int i = 0; i<n; i++){
                String s= arr.get(i);
                ArrayList<Integer> count = new ArrayList<>(26);
                for(int j = 0; j<26; j++){
                    count.add(0);
                } 
                for(int j = 0; j<s.length(); j++){
                    count.set(s.charAt(j)-'a', count.get(s.charAt(j)-'a')+1);
                }
                if(mp.containsKey(count)){
                    mp.get(count).add(s);
                } else{
                    mp.put(count, new ArrayList<>());
                    mp.get(count).add(s);
                }
            }
            List<List<String>> res = new ArrayList<>();
            for(List<String> lst: mp.values()){
                res.add(lst);
            }
            for(List<String> lst: res){
                for(String s: lst){
                    System.out.print(s+" ");
                }
                System.out.println();
            }
        } catch(Exception e){
            System.err.println("Error occured: "+e.getMessage());
        }
    }
}
