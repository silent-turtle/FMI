package bg.sofia.uni.fmi.mjt.virtualwallet.core.payment;

public class PaymentInfo {

    public PaymentInfo(String reason, String location, double cost) {
        setReason(reason);
        setLocation(location);
        setCost(cost);
    }


    public String getReason()
    {
        return reason;
    }

    public String getLocation()
    {
        return location;
    }

    public double getCost()
    {
        return cost;
    }

    private void setReason(String reason)
    {
        this.reason = reason;
    }

    private void setLocation(String location)
    {
        this.location = location;
    }

    private void setCost(double cost)
    {
        this.cost = cost;
    }

    private String reason;
    private String location;
    private double cost;
}
