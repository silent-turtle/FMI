package bg.sofia.uni.fmi.mjt.virtualwallet.core;

import bg.sofia.uni.fmi.mjt.virtualwallet.core.card.Card;
import bg.sofia.uni.fmi.mjt.virtualwallet.core.payment.PaymentInfo;
import bg.sofia.uni.fmi.mjt.virtualwallet.core.transaction.Transaction;

import java.util.LinkedList;
import java.util.List;

public class VirtualWallet implements VirtualWalletAPI {
    private final static int CARDS_SIZE = 5;
    private final static int TRANSACTIONS_SIZE = 10;
    private Card[] cards;
    private int cardAmmount;
    private List<Transaction> transactions;
    private int transactionAmmount;

    public VirtualWallet() {
        cards = new Card[CARDS_SIZE];
        transactions = new LinkedList<Transaction>();
        cardAmmount = 0;
    }

    public boolean registerCard(Card card) {
        if(cardAmmount == CARDS_SIZE) {
            return false;
        }

        for(int i = 0; i < getTotalNumberOfCards(); ++i) {
            if (card.getName().equals(cards[i].getName())) {
                return false;
            }
        }

        cards[getTotalNumberOfCards()] = card;
        ++cardAmmount;

        return true;
    }

    public boolean executePayment(Card card, PaymentInfo paymentInfo) {
        if(getCardByName(card.getName()) != null) {
            if (getCardByName(card.getName()).executePayment(paymentInfo.getCost())) {
                registerTransaction(getCardByName(card.getName()), paymentInfo);

                return true;
            }
        }

        return false;
    }

    public boolean feed(Card card, double amount) {
        if(amount < 0) {
            return false;
        }

        if(getCardByName(card.getName()) != null) {
            getCardByName(card.getName()).setAmount(amount);
            return true;
        }

        return false;
    }

    public Card getCardByName(String name) {
        for(int i = 0; i < getTotalNumberOfCards(); ++i) {
            if(cards[i].getName().equals((name))) {
                return cards[i];
            }
        }

        return null;
    }

    public int getTotalNumberOfCards() {
        return cardAmmount;
    }

    public boolean registerTransaction(Card card, PaymentInfo paymentInfo) {
        if(getCardByName(card.getName()) == null) {
            return false;
        }

        if(transactionAmmount == TRANSACTIONS_SIZE) {
            transactions.remove(0);
            --transactionAmmount;
        }

        transactions.add(new Transaction(card.getName(), paymentInfo));
        ++transactionAmmount;

        return true;
    }
}
