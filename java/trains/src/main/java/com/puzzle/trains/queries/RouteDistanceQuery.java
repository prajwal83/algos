package com.puzzle.trains.queries;

import com.puzzle.trains.RouteGraph;
import com.puzzle.trains.output.DistanceOutput;
import com.puzzle.trains.output.ErrorOutput;
import com.puzzle.trains.output.Output;

import java.util.Collections;
import java.util.List;
import java.util.Optional;

public class RouteDistanceQuery implements Query {
    private final List<String> searchRoute;

    public RouteDistanceQuery(List<String> searchRoute) {
        this.searchRoute = Collections.unmodifiableList(searchRoute);
    }

    public List<String> getSearchRoute() {
        return searchRoute;
    }

    @Override
    public Output execute(RouteGraph routeGraph) {
        if(searchRoute.size() < 2)
            return new ErrorOutput("search route should have at-least 2 stations");

        Optional<RouteGraph.Station> currentStation = routeGraph.getStation(searchRoute.get(0));
        if(!currentStation.isPresent())
            return NO_SUCH_ROUTE;

        int totalDistance = 0;
        for(int i = 1; i < searchRoute.size(); ++i) {
            Optional<RouteGraph.Station> nextStation = routeGraph.getStation(searchRoute.get(i));
            if(!nextStation.isPresent())
                return NO_SUCH_ROUTE;

            Optional<Integer> distance = currentStation.get().distanceTo(nextStation.get());
            if(!distance.isPresent())
                return NO_SUCH_ROUTE;

            totalDistance += distance.get();
            currentStation = nextStation;
        }

        return new DistanceOutput(totalDistance);
    }
}
