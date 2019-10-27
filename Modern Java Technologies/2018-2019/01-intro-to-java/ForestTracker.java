public class ForestTracker
{
    private static int helper(char[][] forest, int r, int c)
    {
        int res = 0;
        int[] help_arr = {-1, 0, 1};
        for(int i = 0; i < help_arr.length; ++i)
        {
            for(int j = 0; j < help_arr.length; ++j)
            {
                if((r + help_arr[i]) >= 0 && (c + help_arr[j]) >= 0 &&
                        (r + help_arr[i]) < forest.length && (c + help_arr[j]) < forest[r].length &&
                        (help_arr[i] != 0 || help_arr[j] != 0) && forest[r + help_arr[i]][c + help_arr[j]] == '4')
                {
                    ++res;
                }
            }
        }

        return res;
    }

    public static char[][] trackForestTerrain(char[][] forest, int years)
    {
        while (years / 10 != 0)
        {
            for(int i = 0; i < forest.length; ++i)
            {
                for(int j = 0; j < forest[i].length; ++j)
                {
                    if(Character.isDigit(forest[i][j]))
                    {
                        if(forest[i][j] == '1')
                        {
                            forest[i][j] = '2';
                            continue;
                        }

                        if(forest[i][j] == '2')
                        {
                            forest[i][j] = '3';
                            continue;
                        }

                        if(forest[i][j] == '3')
                        {
                            forest[i][j] = '4';
                            continue;
                        }

                        if(forest[i][j] == '4')
                        {
                            if(helper(forest, i, j) >= 3)
                            {
                                forest[i][j] = '3';
                            }
                            continue;
                        }
                    }
                }
            }
            years /= 10;
        }
        return forest;
    }

    public static void printMatrix(char[][] mat)
    {
        for(int i = 0; i < mat.length; ++i)
        {
            for(int j = 0; j < mat[i].length; ++j)
            {
                System.out.print(mat[i][j] + " ");
            }
            System.out.print("\n");
        }
    }

    public static void main(String[] args)
    {
        char[][] forest1 =
                {
                        {'R', 'R', 'S', '1', '4'},
                        {'S', '2', '4', '4', '2'},
                        {'1', '3', 'S', '3', '4'}
                };

        char[][] forest2 =
                {
                        {'S', '1', 'S', '1', 'R'},
                        {'S', '2', '4', '4', '4'},
                        {'1', '3', 'S', '3', '4'}
                };

        char[][] updated1 = trackForestTerrain(forest1, 10);
        char[][] updated2 = trackForestTerrain(forest2, 5);

        printMatrix(updated1);
        System.out.println("");
        printMatrix(updated2);
    }
}
