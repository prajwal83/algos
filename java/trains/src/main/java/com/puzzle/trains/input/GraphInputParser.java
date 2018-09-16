package com.puzzle.trains.input;

import com.puzzle.trains.RouteGraph;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class GraphInputParser {
    private static final String COMMAND = "Graph:";
    private static final GraphInputParser instance = new GraphInputParser();
    private GraphInputParser() {}

    public static GraphInputParser getInstance() { return instance; }

    public List<RouteGraph.ParsedRoute> parse(String command) {
        try {
            return validateEdges(validateCommand(command));
        } catch(IllegalArgumentException e) {
            throw new IllegalArgumentException("Invalid Graph definition: " + e.getMessage() + ", usage -> 'Graph: [<A-Z><A-Z><1-9>,... ]");
        }
    }

    private static String validateCommand(String command) {
        command = command.trim();
        if(command.startsWith(COMMAND))
            command = command.substring(COMMAND.length());
        else
            throw new IllegalArgumentException(command);
        return command;
    }

    private static List<RouteGraph.ParsedRoute> validateEdges(String command) {
        List<String> edges = Arrays.stream(command.split(","))
                .map(String::trim)
                .filter(x -> !x.isEmpty())
                .collect(Collectors.toList());

        List<RouteGraph.ParsedRoute> parsedRoutes = new ArrayList<>();
        for(String edge : edges) {
            if(edge.length() < 3
                    || !Character.isAlphabetic(edge.charAt(0))
                    || !Character.isAlphabetic(edge.charAt(1)))
                throw new IllegalArgumentException(edge);

            int weight;
            try {
                weight = Integer.parseInt(edge.substring(2));
            } catch(NumberFormatException e) {
                throw new IllegalArgumentException(edge);
            }

            parsedRoutes.add(new RouteGraph.ParsedRoute(edge.substring(0, 1), edge.substring(1, 2), weight));
        }

        return parsedRoutes;
    }
}
