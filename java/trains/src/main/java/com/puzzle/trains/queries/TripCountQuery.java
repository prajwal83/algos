package com.puzzle.trains.queries;

import com.puzzle.trains.RouteGraph;
import com.puzzle.trains.output.Output;
import com.puzzle.trains.output.TripCountOutput;

public class TripCountQuery implements Query {
    private final String from;
    private final String to;
    private final RouteFilter filter;
    private final ParameterType paramType;
    private int tripCount = 0;

    public enum ParameterType {
        BY_STOPS,
        BY_DISTANCE
    };

    public TripCountQuery(final String from, final String to, final ParameterType paramType, final RouteFilter filter) {
        this.from = from;
        this.to = to;
        this.filter = filter;
        this.paramType = paramType;
    }

    public String getFrom() {
        return from;
    }
    public String getTo() {
        return to;
    }
    public ParameterType getParamType() { return paramType; }
    public RouteFilter getFilter() { return filter; }

    @Override
    public Output execute(RouteGraph routeGraph) {
        tripCount = 0;
        routeGraph.getStation(from).ifPresent(startStation -> {
            routeGraph.getStation(to).ifPresent(endStation -> {
                calculateTripCount(startStation, endStation, 0, 0);
            });
        });

        return new TripCountOutput(tripCount);
    }

    private void calculateTripCount(final RouteGraph.Station currentStation,
                                    final RouteGraph.Station endStation,
                                    final int stops,
                                    final int distance) {
        for(RouteGraph.Station adjacentStation : currentStation.adjacentStations()) {
            final int newStops = stops + 1;
            final int newDistance = distance + currentStation.distanceTo(adjacentStation).get();

            if(!filter.intermediateCheck(getParameterByType(newStops, newDistance)))
                continue;

            if(adjacentStation == endStation && filter.finalCheck(getParameterByType(newStops, newDistance)))
                ++tripCount;

            calculateTripCount(adjacentStation, endStation, newStops, newDistance);
        }
    }

    //TODO: Can this be improved by separating ParameterType into a strategy?
    private int getParameterByType(int stops, int distance) {
        switch(paramType) {
            case BY_STOPS: return stops;
            case BY_DISTANCE: return distance;
        }
        return stops;
    }
}
