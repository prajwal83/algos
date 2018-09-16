package com.puzzle.trains.queries;

public class RouteFilter {
    public enum Operation {
        LT("<") {
            @Override boolean finalCheck(final int value, final int limit) { return value < limit; }
            @Override boolean intermediateCheck(final int value, final int limit) { return finalCheck(value, limit); }
        },
        LT_EQ("<=") {
            @Override boolean finalCheck(final int value, final int limit) { return value <= limit; }
            @Override boolean intermediateCheck(final int value, final int limit) { return finalCheck(value, limit); }
        },
        EQ("=") {
            @Override boolean finalCheck(final int value, final int limit) { return value == limit; }
            @Override boolean intermediateCheck(final int value, final int limit) { return value <= limit; }
        };

        private final String name;
        Operation(final String name) {
            this.name = name;
        }

        abstract boolean finalCheck(final int value, final int limit);
        abstract boolean intermediateCheck(final int value, final int limit);

        public static Operation from(final String opStr) {
            for(Operation op : Operation.values()) {
                if(op.name.compareTo(opStr) == 0)
                    return op;
            }
            throw new IllegalArgumentException("invalid operation " + opStr);
        }
    }

    private final int limit;
    private final Operation operation;

    public RouteFilter(Operation operation, int limit) {
        if(limit < 1)
            throw new IllegalArgumentException("limit should be greater than 0");
        this.limit = limit;
        this.operation = operation;
    }

    public int getLimit() { return limit; }
    public Operation getOperation() { return operation; }

    boolean finalCheck(final int value) { return operation.finalCheck(value, limit); }
    boolean intermediateCheck(final int value) { return operation.intermediateCheck(value, limit); }
}