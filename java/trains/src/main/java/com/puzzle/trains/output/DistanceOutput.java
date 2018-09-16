package com.puzzle.trains.output;

public class DistanceOutput implements Output {
    private final int distance;
    public DistanceOutput(int distance) {
        this.distance = distance;
    }
    int getDistance() { return distance; }
    @Override public String toString() { return String.valueOf(distance); }
}