package com.puzzle.trains.queries;

import com.puzzle.trains.RouteGraph;
import com.puzzle.trains.output.ErrorOutput;
import com.puzzle.trains.output.Output;

public class InvalidQuery implements Query {
    private final String invalidQuery;

    public InvalidQuery(String invalidQuery) {
        this.invalidQuery = invalidQuery;
    }

    @Override
    public Output execute(RouteGraph graph) {
        return new ErrorOutput("Invalid query: " + invalidQuery);
    }
}
