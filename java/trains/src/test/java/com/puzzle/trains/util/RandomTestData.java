package com.puzzle.trains.util;

import com.puzzle.trains.queries.RouteFilter;
import com.puzzle.trains.queries.TripCountQuery;

import java.util.Random;

public class RandomTestData {
    private static final String ALPHA_SET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    private static Random random = new Random();

    public static String anyString() {
        return anyString(10);
    }

    public static String anyString(final int len) {
        int count = (int)(Math.random() * len);
        StringBuilder sb = new StringBuilder();
        while(count-- != 0) {
            sb.append(ALPHA_SET.charAt((int)(Math.random() * ALPHA_SET.length())));
        }
        return sb.toString();
    }

    public static int anyNumber() {
        return anyNumber(Integer.MAX_VALUE);
    }

    public static int anyNumber(final int max) {
        return (int)(Math.random() * max);
    }

    public static TripCountQuery.ParameterType anyParamType() {
        return random.nextBoolean() ? TripCountQuery.ParameterType.BY_DISTANCE : TripCountQuery.ParameterType.BY_STOPS;
    }

    public static RouteFilter.Operation anyFilterOperation() {
        return RouteFilter.Operation.values()[(int)(Math.random() * RouteFilter.Operation.values().length)];
    }
}
