package com.puzzle.trains.input;

import com.puzzle.trains.queries.*;

import java.util.Arrays;
import java.util.Optional;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.stream.Collectors;

public class QueryInputParser {
    private static final QueryInputParser instance = new QueryInputParser();
    private enum QueryType {
        RouteDistance("^\\s*distance\\s+of\\s+(.*)$") {
            @Override Optional<Query> apply(String command) {
                Matcher m = pattern.matcher(command);
                if(m.matches()) {
                    return Optional.of(new RouteDistanceQuery(Arrays.stream(m.group(1).split(" "))
                                    .map(String::trim).collect(Collectors.toList())));
                }
                return Optional.empty();
            }
        },
        ShortestPath("^\\s*shortest\\s+path\\s+from\\s+(\\w)\\s+to\\s+(\\w)\\s*$") {
            @Override Optional<Query> apply(String command) {
                Matcher m = pattern.matcher(command);
                if(m.matches())
                    return Optional.of(new ShortestDistanceQuery(m.group(1), m.group(2)));
                return Optional.empty();
            }
        },
        TripCount("^\\s*trip\\s+count\\s+from\\s+(\\w)\\s+to\\s+(\\w)\\s+with\\s+(stops|distance)\\s+(<|<=|=)\\s+(\\d+)\\s*$") {
            @Override Optional<Query> apply(String command) {
                Matcher m = pattern.matcher(command);
                if(m.matches()) {
                    try {
                        final TripCountQuery.ParameterType parameterType = m.group(3).compareTo("stops") == 0 ?
                                TripCountQuery.ParameterType.BY_STOPS : TripCountQuery.ParameterType.BY_DISTANCE;
                        final int limit = Integer.parseInt(m.group(5));
                        final RouteFilter.Operation operation = RouteFilter.Operation.from(m.group(4));
                        return Optional.of(new TripCountQuery(m.group(1), m.group(2), parameterType, new RouteFilter(operation, limit)));
                    } catch(Exception e) {
                        System.out.println(e.getMessage());
                    }
                }
                return Optional.empty();
            }
        };

        final Pattern pattern;
        QueryType(String regexPattern) {
            this.pattern = Pattern.compile(regexPattern);
        }

        abstract Optional<Query> apply(String command);
    }

    private QueryInputParser() {}

    public static QueryInputParser getInstance() { return instance; }

    Query parse(String command) {
        for(QueryType queryType : QueryType.values()) {
            Optional<Query> query = queryType.apply(command);
            if(query.isPresent())
                return query.get();
        }
        return new InvalidQuery(command);
    }
}
