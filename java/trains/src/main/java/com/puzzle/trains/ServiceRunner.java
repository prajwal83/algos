package com.puzzle.trains;

import com.puzzle.trains.input.InputHandler;
import com.puzzle.trains.output.OutputHandler;
import com.puzzle.trains.queries.Query;

import java.util.Optional;

class ServiceRunner {
    private final InputHandler inputHandler;
    private final OutputHandler outputHandler;

    ServiceRunner(InputHandler inputHandler, OutputHandler outputHandler) {
        this.inputHandler = inputHandler;
        this.outputHandler = outputHandler;
    }

    void Run() {
        RouteGraph graph = inputHandler.getRouteGraph();
        while(true) {
            Optional<Query> query = inputHandler.getNextQuery();
            if(query.isPresent())
                outputHandler.send(query.get().execute(graph));
            else
                break;
        }
    }
}
