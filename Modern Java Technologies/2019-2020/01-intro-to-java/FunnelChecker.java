public class FunnelChecker
{
    public static boolean isFunnel(String str1, String str2)
    {
        if(str1.length() <= str2.length())
        {
            return false;
        }

        boolean isFunnel = false;

        for(int i = 0; i < str2.length(); ++i)
        {
            if(str1.charAt(i) != str2.charAt(i))
            {
                String subStr1 = str1.substring(i + 1);
                String subStr2 = str2.substring(i);

                if(subStr1.equals((subStr2)))
                {
                    isFunnel = true;
                    break;
                }
                else
                    {
                    isFunnel = false;
                    break;
                    }
            }
        }

        return isFunnel;
    }

    public static void main(String[] args)
    {
        String str1 = "";
        String str2 = "";

        System.out.println(isFunnel(str1, str2));
    }
}
