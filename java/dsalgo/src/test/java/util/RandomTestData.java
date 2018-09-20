package util;

import java.math.BigDecimal;
import java.util.Random;

public class RandomTestData {
    private static final String ALPHA_SET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    private static Random random = new Random();

    public static String aString() {
        return aString(10);
    }

    public static String aString(final int len) {
        int count = (int)(Math.random() * len);
        StringBuilder sb = new StringBuilder();
        while(count-- != 0) {
            sb.append(ALPHA_SET.charAt((int)(Math.random() * ALPHA_SET.length())));
        }
        return sb.toString();
    }

    public static int aNumber() {
        return aNumber(Integer.MAX_VALUE);
    }

    public static int aNumber(final int max) {
        return (int)(Math.random() * max);
    }

    public static double aDecimalNumber() {
        return aDecimalNumber(Integer.MAX_VALUE);
    }

    public static double aDecimalNumber(double max) {
        return Math.random() * max;
    }

    public static BigDecimal aBigDecimal() {
        return BigDecimal.valueOf(aDecimalNumber());
    }

    public static BigDecimal aBigDecimal(double max) {
        return BigDecimal.valueOf(aDecimalNumber(max));
    }
}