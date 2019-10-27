public class Counter
{
    public static int countTriplets(String str)
    {
        int res = 0;

        for(int i = 0; i < str.length() - 3; ++i)
        {
            if(str.charAt(i) == str.charAt(i + 1) && str.charAt(i + 1) == str.charAt(i + 2))
            {
                ++res;
            }
        }

        return res;
    }


    public static void main(String[] args)
    {
        System.out.println(countTriplets("aBBBcdee"));
        System.out.println(countTriplets("AAAbCCCCdef"));
        System.out.println(countTriplets("a"));
    }
}
