import java.io.*;
import java.math.*;
import java.text.*;
import java.util.*;
import java.util.regex.*;
public class Solution {
    static char ashtonString(String a, int k) {
        TreeSet<String> subStringSet = new TreeSet<>();
        TreeSet<String> resultSet = new TreeSet<>();
        int index = -1;
        long len   = a.length();
        int tempIndex = 1;
        String str = a;
        int charIndex = -1;
        int finalLen = 0;
        for(int i=97; i<123; i++){
            str = a;
            int fromIndex = 0;
            while ((charIndex=str.indexOf(i,fromIndex)) != -1){
                str = str.substring(charIndex);
                subStringSet.add(str);
                fromIndex=1;
            }
            while((str=subStringSet.pollFirst())!=null) {
                if (str.length() > 1) {
                    if (str.charAt(1) == i) {
                    }else if (str.charAt(0) != i) {
                        subStringSet.clear();
                        resultSet.clear();
                        break;
                    }
                }
                len = str.length();
                tempIndex = 0;
                long totLen = (len*(len+1))/2;
                if(totLen >= k){
                    int lenFnd = 0;
                    for(String strFnd : resultSet){
                        if(str.startsWith(strFnd)){
                            lenFnd += strFnd.length();
                        }
                    }
                    k+=lenFnd;
                    for (int n=1;n<=len;n++){
                        if((n*(n+1))/2 > k){
                            int diff = k-((n-1)*n)/2;
                            return str.charAt(diff-1);
                        } else if((n*(n+1))/2 == k){
                            return str.charAt(n-1);
                        }
                    }
                } else {
                    while (tempIndex++ < (len > 100 ? 100 : len)) {
                        String res = str.substring(0, tempIndex);
                        if (resultSet.add(res)) {
                            k -= res.length();
                        }
                    }
                    for(int n=tempIndex;n<len+1;n++){
                        k-=n;
                    }
                    resultSet.add(str);
                }
            }
        }
        return '$';
    }
    
    static char ashtonString7(String a, int k) {
        TreeSet<String> subStringSet = new TreeSet<>();
        TreeSet<String> resultSet = new TreeSet<>();
        int index = -1;
        int len   = a.length();
        int tempIndex = 1;
        String str = a;
        int charIndex = -1;
        int finalLen = 0;
        for(int i=97; i<123; i++){
            //System.out.println(i+"-----"+i);
            str = a;
            while ((charIndex=str.indexOf(i)) != -1){
                str = str.substring(charIndex+1);
                subStringSet.add((char)i+str);
            }
            while((str = subStringSet.pollFirst())!=null) {
                if (str.length() > 1) {
                     if (str.charAt(1) == i) {
                        subStringSet.add(str.substring(1));
                    }else if (str.charAt(0) != i) {
                        subStringSet.clear();
                        resultSet.clear();
                        break;
                    }
                }
                len = str.length();
                tempIndex = 0;
                while (tempIndex++ < len) {
                    String res = str.substring(0, tempIndex);
                    if (resultSet.add(res)) {
                        if (res.length() >= k) {
                            char ch = res.charAt(k - 1);
                            resultSet.clear();
                            subStringSet.clear();
                            resultSet = null;
                            subStringSet = null;
                            return ch;
                        } else {
                            k -= res.length();
                        }
                    }
                }
            }
        }
        return '$';
    }
    static char ashtonString1(String a, int k) {
        TreeSet<String> subStringSet = new TreeSet<>();
        TreeSet<String> resultSet = new TreeSet<>();
        int index = 0;
        int len   = a.length();
        int tempIndex = 1;
        while (index < len){
            subStringSet.add(a.substring(index++));
        }
        StringBuilder stringBuilder = new StringBuilder();
        while (true){
            String str = subStringSet.pollFirst();
            if(str.length() > 1){
                subStringSet.add(str.substring(1));
            }
            len   = str.length();
            tempIndex = 0;
            while (tempIndex++ < len){
                String res = str.substring(0, tempIndex);
                if(resultSet.add(res)){
                    stringBuilder.append(res);
                }
            }
            int strLen = stringBuilder.length();
            if(strLen > k){
                char ch = stringBuilder.charAt(k-1);
                resultSet.clear();
                subStringSet.clear();
                resultSet = null;
                subStringSet = null;
                stringBuilder = null;
                return ch;
            }
        }
    }
    private static final Scanner scanner = new Scanner(System.in);
    public static void main(String[] args) throws IOException {
        BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(System.getenv("OUTPUT_PATH")));
        int t = Integer.parseInt(scanner.nextLine().trim());
        for (int tItr = 0; tItr < t; tItr++) {
            String s = scanner.nextLine();
            int k = Integer.parseInt(scanner.nextLine().trim());
            char res = ashtonString(s, k);
            bufferedWriter.write(String.valueOf(res));
            bufferedWriter.newLine();
        }
        bufferedWriter.close();
    }
}
