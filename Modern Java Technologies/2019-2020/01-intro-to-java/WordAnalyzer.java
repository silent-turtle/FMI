import java.util.Arrays;

public class WordAnalyzer
{
    public static String getSharedLetters(String word1, String word2)
    {
        char[] lower1 = word1.toLowerCase().toCharArray();
        char[] lower2 = word2.toLowerCase().toCharArray();

        Arrays.sort(lower1);
        Arrays.sort(lower2);

        String res = new String("");

        for(int i = 0; i < lower2.length; ++i)
        {
            if(Arrays.binarySearch(lower1, lower2[i]) > -1)
            {
                res += String.valueOf(lower2[i]);
            }
        }

        return res;
    }

    public static void main(String[] args)
    {
        System.out.println(getSharedLetters("", ""));
        System.out.println(getSharedLetters("house", "home"));
        System.out.println(getSharedLetters("Micky", "mouse"));
        System.out.println(getSharedLetters("house", "villa"));
        System.out.println(getSharedLetters("x", ""));
    }
}
