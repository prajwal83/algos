package com.puzzle.trains.queries;

import com.puzzle.trains.RouteGraph;
import com.puzzle.trains.output.ErrorOutput;
import com.puzzle.trains.output.Output;

public interface Query {
    ErrorOutput NO_SUCH_ROUTE = new ErrorOutput("NO SUCH ROUTE");
    public Output execute(RouteGraph routeGraph);
}