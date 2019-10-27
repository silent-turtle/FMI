public class FractionSimplifier
{

    private static int gcd(int x, int y)
    {
        if (y == 0)
        {
            return x;
        }

        return gcd(y, x % y);
    }

    public static String simplify(String fraction)
    {
        String[] nums = fraction.split("/");

        int nominator = Integer.parseInt(nums[0]);
        int denominator = Integer.parseInt(nums[1]);

        int gcd = gcd(nominator, denominator);

        nominator /= gcd;
        denominator /= gcd;

        if (denominator == 1)
        {
            return Integer.toString(nominator);
        }

        return Integer.toString(nominator) + "/" + Integer.toString(denominator);

    }

    public static void main(String[] args)
    {
        System.out.println(simplify("-4/6"));
        System.out.println(simplify("10/11"));
        System.out.println(simplify("100/400"));
        System.out.println(simplify(("8/4")));

    }
}
