package com.puzzle.trains.queries;

import com.puzzle.trains.RouteGraph;
import com.puzzle.trains.input.GraphInputParser;
import com.puzzle.trains.output.Output;
import com.puzzle.trains.output.TripCountOutput;
import com.puzzle.trains.util.RandomTestData;
import org.junit.jupiter.api.Test;

import java.util.Optional;

import static com.puzzle.trains.util.RandomTestData.anyString;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.when;

class TripCountQueryTest {

    @Test
    void failForMissingStartStation() {
        RouteGraph mockGraph = mock(RouteGraph.class);
        final String from = RandomTestData.anyString();
        final String to = RandomTestData.anyString();
        RouteFilter mockFilter = mock(RouteFilter.class);
        TripCountQuery query = new TripCountQuery(from, to, RandomTestData.anyParamType(), mockFilter);
        when(mockGraph.getStation(from)).thenReturn(Optional.empty());

        Output output = query.execute(mockGraph);
        assertTrue(output instanceof TripCountOutput);
        assertEquals("0", output.toString());
    }

    @Test
    void failForMissingEndStation() {
        RouteGraph mockGraph = mock(RouteGraph.class);
        final String from = RandomTestData.anyString();
        final String to = RandomTestData.anyString();
        RouteFilter mockFilter = mock(RouteFilter.class);
        TripCountQuery query = new TripCountQuery(from, to, RandomTestData.anyParamType(), mockFilter);

        RouteGraph.Station mockStation = mock(RouteGraph.Station.class);
        when(mockGraph.getStation(from)).thenReturn(Optional.of(mockStation));
        when(mockGraph.getStation(to)).thenReturn(Optional.empty());

        Output output = query.execute(mockGraph);
        assertTrue(output instanceof TripCountOutput);
        assertEquals("0", output.toString());
    }

    @Test
    void tripCountByStopsLimit() {
        RouteGraph routeGraph = RouteGraph.Factory.getInstance().from(
                GraphInputParser.getInstance().parse("Graph: AB5, BC4, CD8, DC8, DE6, AD5, CE2, EB3, AE7"));
        TripCountQuery query = new TripCountQuery("C", "C",
                TripCountQuery.ParameterType.BY_STOPS,
                new RouteFilter(RouteFilter.Operation.LT_EQ, 3));

        Output output = query.execute(routeGraph);
        assertTrue(output instanceof TripCountOutput);
        assertEquals("2", output.toString());
    }

    @Test
    void tripCountByExactStopCount() {
        RouteGraph routeGraph = RouteGraph.Factory.getInstance().from(
                GraphInputParser.getInstance().parse("Graph: AB5, BC4, CD8, DC8, DE6, AD5, CE2, EB3, AE7"));
        TripCountQuery query = new TripCountQuery("A", "C",
                TripCountQuery.ParameterType.BY_STOPS,
                new RouteFilter(RouteFilter.Operation.EQ, 4));

        Output output = query.execute(routeGraph);
        assertTrue(output instanceof TripCountOutput);
        assertEquals("3", output.toString());
    }

    @Test
    void multiPathLinearByDistance() {
        RouteGraph routeGraph = RouteGraph.Factory.getInstance().from(
                GraphInputParser.getInstance().parse("Graph: AB5, BC4, CD8, DC8, DE6, AD5, CE2, EB3, AE7"));
        TripCountQuery query = new TripCountQuery("C", "C",
                TripCountQuery.ParameterType.BY_DISTANCE, new RouteFilter(RouteFilter.Operation.LT, 30));

        Output output = query.execute(routeGraph);
        assertTrue(output instanceof TripCountOutput);
        assertEquals("7", output.toString());
    }
}
