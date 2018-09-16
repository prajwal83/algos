package com.puzzle.trains.input;

import com.puzzle.trains.RouteGraph;
import com.puzzle.trains.util.RandomTestData;
import org.junit.jupiter.api.Test;

import java.util.List;

import static com.puzzle.trains.util.RandomTestData.anyString;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

class GraphInputParserTest {
    @Test
    void createEmptyGraph() {
        List<RouteGraph.ParsedRoute> edges = GraphInputParser.getInstance().parse("Graph:");
        assertEquals(0, edges.size());
    }

    @Test
    void failForEmptyHeader() {
        IllegalArgumentException error = assertThrows(IllegalArgumentException.class,
                () -> GraphInputParser.getInstance().parse(""));
        assertEquals("Invalid Graph definition: , usage -> 'Graph: [<A-Z><A-Z><1-9>,... ]", error.getMessage());
    }

    @Test
    void failForInvalidHeader() {
        final String wrongCommand = RandomTestData.anyString();
        IllegalArgumentException error = assertThrows(IllegalArgumentException.class,
                () ->  GraphInputParser.getInstance().parse(wrongCommand));
        assertEquals("Invalid Graph definition: " + wrongCommand + ", usage -> 'Graph: [<A-Z><A-Z><1-9>,... ]", error.getMessage());
    }

    @Test
    void failForInvalidGraphInput() {
        IllegalArgumentException error = assertThrows(IllegalArgumentException.class,
                () ->  GraphInputParser.getInstance().parse("Graph: ABC7"));
        assertEquals("Invalid Graph definition: ABC7, usage -> 'Graph: [<A-Z><A-Z><1-9>,... ]", error.getMessage());

        error = assertThrows(IllegalArgumentException.class, () ->  GraphInputParser.getInstance().parse("Graph: AB7, ADE6"));
        assertEquals("Invalid Graph definition: ADE6, usage -> 'Graph: [<A-Z><A-Z><1-9>,... ]", error.getMessage());

        error = assertThrows(IllegalArgumentException.class, () ->  GraphInputParser.getInstance().parse("Graph: AB7, ADE, ABX7"));
        assertEquals("Invalid Graph definition: ADE, usage -> 'Graph: [<A-Z><A-Z><1-9>,... ]", error.getMessage());
    }

    @Test
    void createSingleEdgeGraph() {
        List<RouteGraph.ParsedRoute> edges = GraphInputParser.getInstance().parse("Graph: AB70");
        assertEquals(1, edges.size());
        assertEquals("A", edges.get(0).getFrom());
        assertEquals("B", edges.get(0).getTo());
        assertEquals(70, edges.get(0).getDistance());
    }

    @Test
    void createValidMultiEdgeGraph() {
        List<RouteGraph.ParsedRoute> edges = GraphInputParser.getInstance().parse("Graph: AC70, AB8, CA10");
        assertEquals(3, edges.size());
        assertEquals("A", edges.get(0).getFrom());
        assertEquals("C", edges.get(0).getTo());
        assertEquals(70, edges.get(0).getDistance());

        assertEquals("A", edges.get(1).getFrom());
        assertEquals("B", edges.get(1).getTo());
        assertEquals(8, edges.get(1).getDistance());

        assertEquals("C", edges.get(2).getFrom());
        assertEquals("A", edges.get(2).getTo());
        assertEquals(10, edges.get(2).getDistance());
    }
}
