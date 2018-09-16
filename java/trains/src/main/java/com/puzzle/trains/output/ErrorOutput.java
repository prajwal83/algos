package com.puzzle.trains.output;

public class ErrorOutput implements Output {
    private final String error;
    public ErrorOutput(String error) {
        this.error = error;
    }
    public String getError() { return error; }
    @Override public String toString() { return error; }
}
