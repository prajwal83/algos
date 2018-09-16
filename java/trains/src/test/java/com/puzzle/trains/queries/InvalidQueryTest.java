package com.puzzle.trains.queries;

import com.puzzle.trains.RouteGraph;
import com.puzzle.trains.output.ErrorOutput;
import com.puzzle.trains.output.Output;
import com.puzzle.trains.util.RandomTestData;
import org.junit.jupiter.api.Test;

import static com.puzzle.trains.util.RandomTestData.anyString;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.mockito.Mockito.mock;

class InvalidQueryTest {
    @Test
    void shouldReturnErrorOutput() {
        RouteGraph mockGraph = mock(RouteGraph.class);
        final String error = RandomTestData.anyString();
        InvalidQuery query = new InvalidQuery(error);
        Output output = query.execute(mockGraph);
        assertTrue(output instanceof ErrorOutput);
        assertEquals("Invalid query: " + error, output.toString());
    }
}
