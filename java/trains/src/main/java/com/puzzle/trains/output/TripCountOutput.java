package com.puzzle.trains.output;

public class TripCountOutput implements Output {
    private final int tripCount;
    public TripCountOutput(int tripCount) {
        this.tripCount = tripCount;
    }
    int getTripCount() { return tripCount; }
    @Override public String toString() { return String.valueOf(tripCount); }
}