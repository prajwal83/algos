package com.puzzle.trains.queries;

import com.puzzle.trains.RouteGraph;
import com.puzzle.trains.output.DistanceOutput;
import com.puzzle.trains.output.Output;

import java.util.*;

public class ShortestDistanceQuery implements Query {
    private final String from;
    private final String to;

    public ShortestDistanceQuery(final String from, final String to) {
        this.from = from;
        this.to = to;
    }

    public String getFrom() {
        return from;
    }

    public String getTo() {
        return to;
    }

    @Override
    public Output execute(RouteGraph routeGraph) {
        Optional<RouteGraph.Station> startStation = routeGraph.getStation(from);
        if(!startStation.isPresent())
            return NO_SUCH_ROUTE;

        Optional<RouteGraph.Station> endStation = routeGraph.getStation(to);
        if(!endStation.isPresent())
            return NO_SUCH_ROUTE;

        final Integer shortestPath = routeGraph.getShortestPathCache().get(startStation.get(), endStation.get())
                .orElse(calculateShortestPath(startStation.get(), endStation.get()));

        routeGraph.getShortestPathCache().set(startStation.get(), endStation.get(), shortestPath);

        if(shortestPath == Integer.MAX_VALUE)
            return NO_SUCH_ROUTE;
        else
            return new DistanceOutput(shortestPath);
    }

    private Integer calculateShortestPath(final RouteGraph.Station startStation, final RouteGraph.Station endStation) {
        Map<RouteGraph.Station, Integer> distanceMap = new HashMap<>();
        Set<RouteGraph.Station> queue = new HashSet<>();
        Set<RouteGraph.Station> visited = new HashSet<>();
        queue.add(startStation);
        distanceMap.put(startStation, 0);

        while (!queue.isEmpty()) {
            RouteGraph.Station currentStation = nextNearestStation(queue, distanceMap);
            queue.remove(currentStation);
            if (startStation != endStation || startStation != currentStation)
                visited.add(currentStation);

            final int currentDistance = distanceMap.get(currentStation);

            for (RouteGraph.Station adjacentStation : currentStation.adjacentStations()) {
                if (visited.contains(adjacentStation))
                    continue;

                final int newDistance = currentDistance + currentStation.distanceTo(adjacentStation).get();
                final int distance = distanceMap.getOrDefault(adjacentStation, Integer.MAX_VALUE);
                if (newDistance < distance || distance == 0)
                    distanceMap.put(adjacentStation, newDistance);

                queue.add(adjacentStation);
            }
        }

        return distanceMap.getOrDefault(endStation, Integer.MAX_VALUE);
    }

    private RouteGraph.Station nextNearestStation(Set<RouteGraph.Station> queue, Map<RouteGraph.Station, Integer> distanceMap) {
        RouteGraph.Station nearestStation = null;
        int minDistance = Integer.MAX_VALUE;
        for(RouteGraph.Station station : queue) {
            if(nearestStation == null || distanceMap.get(station) < minDistance) {
                nearestStation = station;
                minDistance = distanceMap.get(station);
            }
        }
        return nearestStation;
    }
}
