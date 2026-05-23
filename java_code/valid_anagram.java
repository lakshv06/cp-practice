import java.util.Scanner;

public class valid_anagram{
    public static void main(String[] args){
        try(Scanner sc = new Scanner(System.in)) {
            String s = sc.nextLine();
            String t = sc.nextLine();

            int [] count1 = new int[26];
            int [] count2 = new int[26];

            boolean res = true;
            if(s.length() != t.length()){
                res = false;
            } else{
                for(int i = 0; i<s.length(); i++){
                    count1[s.charAt(i)-'a']++;  
                    count2[t.charAt(i)-'a']++;
                }
                for(int i = 0; i<26; i++){
                    if(count1[i]!=count2[i]){
                        res = false;
                        break;
                    }
                }
            } 
            System.out.println(res);
        } catch (Exception e) {
            System.err.println("Error occured: "+e.getMessage());
        }

    }
}