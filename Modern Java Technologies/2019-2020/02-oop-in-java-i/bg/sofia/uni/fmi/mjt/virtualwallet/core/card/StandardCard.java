package bg.sofia.uni.fmi.mjt.virtualwallet.core.card;

import static java.lang.Math.abs;

public class StandardCard extends Card {
    public StandardCard(String name)
    {
        super(name);
    }

    @Override
    public boolean executePayment(double cost) {
        if(cost < 0) {
            return false;
        }

        if(abs(cost - this.getAmount()) < 0.001) {
            return false;
        }
        this.setAmount((this.getAmount() - cost));
        return true;
    }
}
