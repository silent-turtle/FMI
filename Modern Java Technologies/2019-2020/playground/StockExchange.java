public class StockExchange
{
    public static int maxProfit(int[] prices)
    {
        int min = prices[0], max = prices[0], res = 0;

        for(int i = 1; i < prices.length; ++i)
        {
            if (min > prices[i])
            {
                min = prices[i];
                max = prices[i];
                continue;
            }

            if (max > prices[i])
            {
                res += (max - min);

                min = prices[i];
                max = prices[i];
                continue;
            }

            max = prices[i];
        }

        res += (max - min);
        return res;
    }


    public static void main(String[] args)
    {
        int[] example1 = {7, 1, 5, 3, 6, 4};
        int[] example2 = {1, 2, 3, 4, 5};
        int[] example3 = {7, 6, 4, 3, 1};

        System.out.println(maxProfit(example1));
        System.out.println(maxProfit(example2));
        System.out.println(maxProfit(example3));
    }
}
