package com.puzzle.trains;

import com.puzzle.trains.input.InputHandler;
import com.puzzle.trains.output.Output;
import com.puzzle.trains.output.OutputHandler;
import com.puzzle.trains.queries.Query;
import org.junit.jupiter.api.Test;
import org.mockito.invocation.InvocationOnMock;

import java.util.Optional;
import java.util.Stack;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.*;

class ServiceRunnerTest {
    @Test
    void createEmptyGraph() {
        InputHandler inputHandler = mock(InputHandler.class);
        OutputHandler outputHandler = mock(OutputHandler.class);
        RouteGraph mockGraph = mock(RouteGraph.class);

        when(inputHandler.getRouteGraph()).thenReturn(mockGraph);

        Query mockQuery1 = mock(Query.class);
        Query mockQuery2 = mock(Query.class);
        Stack<Query> mockQueries = new Stack<>();
        mockQueries.push(mockQuery1);
        mockQueries.push(mockQuery2);

        Output mockOutput1 = mock(Output.class);
        Output mockOutput2 = mock(Output.class);
        when(mockQuery1.execute(mockGraph)).thenReturn(mockOutput1);
        when(mockQuery2.execute(mockGraph)).thenReturn(mockOutput2);

        when(inputHandler.getNextQuery()).thenAnswer((InvocationOnMock var1) -> {
            if (mockQueries.empty())
                return Optional.empty();
            return Optional.of(mockQueries.pop());
        });

        ServiceRunner runner = new ServiceRunner(inputHandler, outputHandler);
        runner.Run();
        assertEquals(0, mockQueries.size());
        verify(outputHandler).send(mockOutput1);
        verify(outputHandler).send(mockOutput2);
    }
}
