package com.puzzle.trains;

import com.puzzle.trains.input.GraphInputParser;
import com.puzzle.trains.input.QueryInputParser;
import com.puzzle.trains.input.StreamInputHandler;
import com.puzzle.trains.output.PrintStreamOutputHandler;

import java.io.File;
import java.util.Optional;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        try {
            Optional<Scanner> scanner = Optional.empty();

            if (args.length == 0 || (args.length == 1 && args[0].compareTo("-i") == 0)) {
                scanner = Optional.of(new Scanner(System.in));
            } else if (args.length == 2 && args[0].compareTo("-f") == 0) {
                scanner = Optional.of(new Scanner(new File(args[1])));
            } else
                System.out.println("Usage: <program> [-i|-f <input file>]");

            scanner.ifPresent(reader -> {
                ServiceRunner service = new ServiceRunner(
                        new StreamInputHandler(
                                reader,
                                GraphInputParser.getInstance(),
                                RouteGraph.Factory.getInstance(),
                                QueryInputParser.getInstance()),
                        new PrintStreamOutputHandler(System.out));
                service.Run();
            });
        } catch(Exception e) {
            System.out.println("ERROR: " + e.getMessage());
        }
    }
}
