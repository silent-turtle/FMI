package bg.sofia.uni.fmi.mjt.virtualwallet.core.card;

public abstract class Card {
    private String name;
    private double amount;

    public Card(String name) {
        setName(name);
        setAmount(0.0);
    }

    public abstract boolean executePayment(double cost);

    public String getName()
    {
        return name;
    }

    private void setName(String name)
    {
        this.name = name;
    }

    public double getAmount()
    {
        return amount;
    }

    public void setAmount(double amount) {
        if(amount < 0.0) {
            System.out.println("negative number\n");
            return;
        }
        this.amount = amount;
    }
}
