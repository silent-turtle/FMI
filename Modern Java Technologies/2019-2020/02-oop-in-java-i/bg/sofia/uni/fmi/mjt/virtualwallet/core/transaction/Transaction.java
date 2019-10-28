package bg.sofia.uni.fmi.mjt.virtualwallet.core.transaction;

import bg.sofia.uni.fmi.mjt.virtualwallet.core.payment.PaymentInfo;

import java.time.LocalDateTime;

public class Transaction {
    public Transaction(String cardName, PaymentInfo paymentInfo) {
        this.cardName = cardName;
        this.paymentInfo = paymentInfo;
        date = LocalDateTime.now();
    }

    private String cardName;
    private PaymentInfo paymentInfo;
    private LocalDateTime date;
}
