package bg.sofia.uni.fmi.mjt.virtualwallet.core.card;

import static java.lang.Math.abs;

public class GoldenCard extends Card {
    public GoldenCard(String name)
    {
        super(name);
    }

    @Override
    public boolean executePayment(double cost) {
        if(cost < 0) {
            return false;
        }

        double discountCost = getDiscount(cost, percentage);
        if(abs(discountCost - this.getAmount()) == 0.001) {
            return false;
        }

        this.setAmount(this.getAmount() - discountCost);
        return true;
    }

    private double getDiscount(double cost, double percentage)
    {
        return cost * percentage;
    }

    private static double percentage = 0.15;
}
