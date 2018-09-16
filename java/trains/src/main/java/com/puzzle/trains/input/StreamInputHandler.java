package com.puzzle.trains.input;

import com.puzzle.trains.RouteGraph;
import com.puzzle.trains.queries.Query;

import java.util.Optional;
import java.util.Scanner;

public class StreamInputHandler extends InputHandler {
    private Scanner scanner;

    public StreamInputHandler(Scanner scanner,
                              GraphInputParser graphInputParser,
                              RouteGraph.Factory graphFactory,
                              QueryInputParser queryInputParser) {
        super(getGraphDefinition(scanner), graphInputParser, graphFactory, queryInputParser);
        this.scanner = scanner;
    }

    @Override public Optional<Query> getNextQuery() {
        return getNextCommand(this.scanner).map(queryInputParser::parse);
    }

    private static String getGraphDefinition(Scanner scanner) {
        return getNextCommand(scanner).orElseThrow(() -> new IllegalArgumentException("First input line should be a Graph definition"));
    }

    private static Optional<String> getNextCommand(Scanner scanner) {
        while(scanner.hasNext()) {
            String command = scanner.nextLine();
            command = command.trim();
            if(command.isEmpty() || command.charAt(0) == '#')
                continue;
            return Optional.of(command);
        }
        return Optional.empty();
    }
}
