import java.util.Arrays;

public class Anagram
{
    public static boolean isAnagram(String input)
    {
        boolean isAnagram = true;
        String[] arr = input.split(" ");

        char[] sorted1 = arr[0].toLowerCase().toCharArray();
        char[] sorted2 = arr[1].toLowerCase().toCharArray();

        Arrays.sort(sorted1);
        Arrays.sort(sorted2);
/*
        int cnt1 = 0, cnt2 = 0;

        while(!Character.isLetter(sorted1[cnt1]))
        {
            ++cnt1;
        }

        while(!Character.isLetter(sorted2[cnt2]))
        {
            ++cnt2;
        }

        int min = Math.min(sorted1.length, sorted2.length);

        for(int i = 0; i < min; ++i)
        {
            if (Character.isLetter(sorted1[cnt1 + i]) &&
                    Character.isLetter(sorted2[cnt2 + i]) &&
                    sorted1[cnt1 + i] != sorted2[cnt2 + i])
            {
                isAnagram = false;
                break;
            }
        }

        int max = Math.max(sorted1.length, sorted2.length);

        for(int i = min; i < max; ++i)
        {

        }*/

        int cnt1 = 0, cnt2 = 0;
        while(cnt1 < sorted1.length || cnt2 < sorted2.length)
        {
            if(cnt1 >= sorted1.length)
            {
                if(Character.isLetter(sorted2[cnt2]))
                {
                    isAnagram = false;
                    break;
                }
            }

            if(cnt2 >= sorted2.length)
            {
                if(Character.isLetter(sorted1[cnt1]))
                {
                    isAnagram = false;
                    break;
                }
            }

            while(!Character.isLetter(sorted1[cnt1]))
            {
                ++cnt1;
            }

            while(!Character.isLetter(sorted2[cnt2]))
            {
                ++cnt2;
            }

            if(sorted1[cnt1] != sorted2[cnt2])
            {
                isAnagram = false;
                break;
            }

            ++cnt1;
            ++cnt2;
        }

        return isAnagram;
    }

    public static void main(String[] args)
    {
        System.out.println(isAnagram("night thing"));
        System.out.println(isAnagram("tired dire"));
        System.out.println(isAnagram("eaT ate$"));
        System.out.println(isAnagram("beer beere"));
    }
}
