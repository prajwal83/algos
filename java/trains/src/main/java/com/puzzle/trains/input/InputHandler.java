package com.puzzle.trains.input;

import com.puzzle.trains.RouteGraph;
import com.puzzle.trains.queries.Query;

import java.util.Optional;

public abstract class InputHandler {
    private final RouteGraph routeGraph;
    final QueryInputParser queryInputParser;

    InputHandler(String graphCommand,
                 GraphInputParser graphInputParser,
                 RouteGraph.Factory graphFactory,
                 QueryInputParser queryInputParser) {
        this.routeGraph = graphFactory.from(graphInputParser.parse(graphCommand));
        this.queryInputParser = queryInputParser;
    }

    public RouteGraph getRouteGraph() { return routeGraph; }
    public abstract Optional<Query> getNextQuery();
}
