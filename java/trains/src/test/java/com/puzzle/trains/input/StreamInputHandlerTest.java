package com.puzzle.trains.input;

import com.puzzle.trains.RouteGraph;
import org.junit.jupiter.api.Test;

import java.io.ByteArrayInputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.when;

class StreamInputHandlerTest {
    @Test
    void failForEmptyInput() {
        RouteGraph.Factory mockRouteGraphFactory = mock(RouteGraph.Factory.class);
        GraphInputParser mockGraphParser = mock(GraphInputParser.class);
        QueryInputParser mockQueryParser = mock(QueryInputParser.class);
        IllegalArgumentException error = assertThrows(IllegalArgumentException.class,
                () -> new StreamInputHandler(new Scanner(new ByteArrayInputStream("".getBytes())),
                        mockGraphParser,
                        mockRouteGraphFactory,
                        mockQueryParser));
        assertEquals("First input line should be a Graph definition", error.getMessage());
    }

    @Test
    void ignoreBlankLines() {
        RouteGraph.Factory mockRouteGraphFactory = mock(RouteGraph.Factory.class);
        GraphInputParser mockGraphParser = mock(GraphInputParser.class);
        QueryInputParser mockQueryParser = mock(QueryInputParser.class);
        RouteGraph mockGraph = mock(RouteGraph.class);
        List<RouteGraph.ParsedRoute> edges = new ArrayList<>();

        when(mockGraphParser.parse("Graph:")).thenReturn(edges);
        when(mockRouteGraphFactory.from(edges)).thenReturn(mockGraph);

        StreamInputHandler reader = new StreamInputHandler(
                new Scanner(new ByteArrayInputStream((System.lineSeparator() + "Graph:").getBytes())),
                mockGraphParser,
                mockRouteGraphFactory,
                mockQueryParser);
        assertEquals(mockGraph, reader.getRouteGraph());
    }

    @Test
    void ignoreCommentLines() {
        RouteGraph.Factory mockRouteGraphFactory = mock(RouteGraph.Factory.class);
        GraphInputParser mockGraphParser = mock(GraphInputParser.class);
        QueryInputParser mockQueryParser = mock(QueryInputParser.class);
        RouteGraph mockGraph = mock(RouteGraph.class);
        List<RouteGraph.ParsedRoute> edges = new ArrayList<>();

        when(mockGraphParser.parse("Graph:")).thenReturn(edges);
        when(mockRouteGraphFactory.from(edges)).thenReturn(mockGraph);

        StreamInputHandler reader = new StreamInputHandler(
                new Scanner(new ByteArrayInputStream((System.lineSeparator()
                        + "  " + System.lineSeparator()
                        + "# some comment  " + System.lineSeparator()
                        + "  # more comment  " + System.lineSeparator()
                        + " Graph:").getBytes())),
                mockGraphParser,
                mockRouteGraphFactory,
                mockQueryParser);
        assertEquals(mockGraph, reader.getRouteGraph());
    }
}
