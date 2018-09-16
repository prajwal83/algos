package com.puzzle.trains;

import java.util.*;
import java.util.concurrent.ConcurrentHashMap;

public class RouteGraph {
    private Map<String, Station> stations = new HashMap<>();
    private final RouteCache shortestPathCache = new RouteCache();

    private RouteGraph(List<ParsedRoute> edges) {
        for(ParsedRoute edge : edges)
            createOrGetStation(edge.from).add(createOrGetStation(edge.to), edge.distance);
    }

    int size() { return stations.size(); }

    public RouteCache getShortestPathCache() { return shortestPathCache; }

    public Optional<Station> getStation(String name) {
        return stations.containsKey(name) ? Optional.of(stations.get(name)) : Optional.empty();
    }

    private Station createOrGetStation(String name) {
        return getStation(name).orElseGet(() -> {
            Station newStation = new Station(name);
            stations.put(name, newStation);
            return newStation;
        });
    }

    public static class Factory {
        private static final Factory instance = new Factory();
        private Factory() {}

        public static Factory getInstance() {
            return instance;
        }

        public RouteGraph from(List<ParsedRoute> edges) {
            return new RouteGraph(edges);
        }
    }

    public static class ParsedRoute {
        final String from;
        final String to;
        final int distance;

        public ParsedRoute(String from, String to, int distance) {
            this.from = from;
            this.to = to;
            this.distance = distance;
        }

        public String getFrom() {
            return from;
        }

        public String getTo() {
            return to;
        }

        public int getDistance() {
            return distance;
        }
    }

    public class Station {
        private final String name;
        private Map<Station, Integer> routeMap = new HashMap<>();

        public Station(String name) {
            this.name = name;
        }

        void add(Station dest, int distance) {
            if(distance <= 0)
                throw new IllegalArgumentException("distance should be greater than 0 from " + name + " to " + dest.name);
            if(dest == this)
                throw new IllegalArgumentException("self loop edge for Station " + dest.name);
            if (routeMap.containsKey(dest))
                throw new IllegalArgumentException("duplicate edge from " + name + " and " + dest.name);
            routeMap.put(dest, distance);
        }

        public Optional<Integer> distanceTo(Station dest) {
            return routeMap.containsKey(dest) ? Optional.of(routeMap.get(dest)) : Optional.empty();
        }

        public Set<Station> adjacentStations() {
            return Collections.unmodifiableSet(routeMap.keySet());
        }
    }

    public static class RouteCache {
        final ConcurrentHashMap<Station, ConcurrentHashMap<Station, Integer>> cache = new ConcurrentHashMap<>();

        public Optional<Integer> get(final Station from, final Station to) {
            return Optional.ofNullable(cache.get(from)).map(secondCache -> secondCache.get(to));
        }

        public void set(final Station from, final Station to, Integer value) {
            ConcurrentHashMap<Station, Integer> secondCache = cache.get(from);
            if(secondCache == null)
                secondCache = cache.computeIfAbsent(from, key -> new ConcurrentHashMap<>());
            secondCache.putIfAbsent(to, value);
        }
    }
}