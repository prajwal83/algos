package com.puzzle.trains.queries;

import com.puzzle.trains.RouteGraph;
import com.puzzle.trains.output.DistanceOutput;
import com.puzzle.trains.output.ErrorOutput;
import com.puzzle.trains.output.Output;
import com.puzzle.trains.util.RandomTestData;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import static com.puzzle.trains.util.RandomTestData.anyNumber;
import static com.puzzle.trains.util.RandomTestData.anyString;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.when;

public class RouteDistanceQueryTest {
    @Test
    void failWithShortRoute() {
        RouteGraph mockGraph = mock(RouteGraph.class);
        List<String> searchRoute = new ArrayList<>();
        RouteDistanceQuery query = new RouteDistanceQuery(searchRoute);
        Output output = query.execute(mockGraph);
        assertTrue(output instanceof ErrorOutput);
        assertEquals("search route should have at-least 2 stations", output.toString());

        searchRoute.add(RandomTestData.anyString());
        query = new RouteDistanceQuery(searchRoute);
        output = query.execute(mockGraph);
        assertTrue(output instanceof ErrorOutput);
        assertEquals("search route should have at-least 2 stations", output.toString());
    }

    @Test
    void failWithMissingStartStation() {
        RouteGraph mockGraph = mock(RouteGraph.class);
        List<String> searchRoute = new ArrayList<>();
        searchRoute.add("A");
        searchRoute.add("B");
        when(mockGraph.getStation("A")).thenReturn(Optional.empty());
        RouteDistanceQuery query = new RouteDistanceQuery(searchRoute);
        Output output = query.execute(mockGraph);
        assertTrue(output instanceof ErrorOutput);
        assertEquals("NO SUCH ROUTE", output.toString());
    }

    @Test
    void failWithMissingRouteToLastStation() {
        RouteGraph mockGraph = mock(RouteGraph.class);
        List<String> searchRoute = new ArrayList<>();
        searchRoute.add("A");
        searchRoute.add("B");
        searchRoute.add("C");
        RouteGraph.Station mockStatsionA = mock(RouteGraph.Station.class);
        RouteGraph.Station mockStatsionB = mock(RouteGraph.Station.class);
        RouteGraph.Station mockStatsionC = mock(RouteGraph.Station.class);

        when(mockGraph.getStation("A")).thenReturn(Optional.of(mockStatsionA));
        when(mockGraph.getStation("B")).thenReturn(Optional.of(mockStatsionB));
        when(mockGraph.getStation("C")).thenReturn(Optional.of(mockStatsionC));

        when(mockStatsionA.distanceTo(mockStatsionB)).thenReturn(Optional.of(RandomTestData.anyNumber()));
        when(mockStatsionB.distanceTo(mockStatsionC)).thenReturn(Optional.empty());

        RouteDistanceQuery query = new RouteDistanceQuery(searchRoute);
        Output output = query.execute(mockGraph);
        assertTrue(output instanceof ErrorOutput);
        assertEquals("NO SUCH ROUTE", output.toString());
    }

    @Test
    void failWithMissingRouteToIntermediateStation() {
        RouteGraph mockGraph = mock(RouteGraph.class);
        List<String> searchRoute = new ArrayList<>();
        searchRoute.add("A");
        searchRoute.add("B");
        searchRoute.add("C");
        searchRoute.add("D");
        RouteGraph.Station mockStatsionA = mock(RouteGraph.Station.class);
        RouteGraph.Station mockStatsionB = mock(RouteGraph.Station.class);
        RouteGraph.Station mockStatsionC = mock(RouteGraph.Station.class);
        RouteGraph.Station mockStatsionD = mock(RouteGraph.Station.class);

        when(mockGraph.getStation("A")).thenReturn(Optional.of(mockStatsionA));
        when(mockGraph.getStation("B")).thenReturn(Optional.of(mockStatsionB));
        when(mockGraph.getStation("C")).thenReturn(Optional.of(mockStatsionC));
        when(mockGraph.getStation("D")).thenReturn(Optional.of(mockStatsionD));

        when(mockStatsionA.distanceTo(mockStatsionB)).thenReturn(Optional.of(RandomTestData.anyNumber()));
        when(mockStatsionB.distanceTo(mockStatsionC)).thenReturn(Optional.empty());
        when(mockStatsionC.distanceTo(mockStatsionD)).thenReturn(Optional.of(RandomTestData.anyNumber()));

        RouteDistanceQuery query = new RouteDistanceQuery(searchRoute);
        Output output = query.execute(mockGraph);
        assertTrue(output instanceof ErrorOutput);
        assertEquals("NO SUCH ROUTE", output.toString());
    }

    @Test
    void shouldReturnDistance() {
        RouteGraph mockGraph = mock(RouteGraph.class);
        List<String> searchRoute = new ArrayList<>();
        searchRoute.add("A");
        searchRoute.add("B");
        searchRoute.add("C");
        searchRoute.add("D");
        RouteGraph.Station mockStatsionA = mock(RouteGraph.Station.class);
        RouteGraph.Station mockStatsionB = mock(RouteGraph.Station.class);
        RouteGraph.Station mockStatsionC = mock(RouteGraph.Station.class);
        RouteGraph.Station mockStatsionD = mock(RouteGraph.Station.class);

        when(mockGraph.getStation("A")).thenReturn(Optional.of(mockStatsionA));
        when(mockGraph.getStation("B")).thenReturn(Optional.of(mockStatsionB));
        when(mockGraph.getStation("C")).thenReturn(Optional.of(mockStatsionC));
        when(mockGraph.getStation("D")).thenReturn(Optional.of(mockStatsionD));

        int distanceAB = RandomTestData.anyNumber(50);
        int distanceBC = RandomTestData.anyNumber(50);
        int distanceCD = RandomTestData.anyNumber(50);
        String expectedOutput = String.valueOf(distanceAB + distanceBC + distanceCD);
        when(mockStatsionA.distanceTo(mockStatsionB)).thenReturn(Optional.of(distanceAB));
        when(mockStatsionB.distanceTo(mockStatsionC)).thenReturn(Optional.of(distanceBC));
        when(mockStatsionC.distanceTo(mockStatsionD)).thenReturn(Optional.of(distanceCD));

        RouteDistanceQuery query = new RouteDistanceQuery(searchRoute);
        Output output = query.execute(mockGraph);
        assertTrue(output instanceof DistanceOutput);
        assertEquals(expectedOutput, output.toString());
    }

    @Test
    void shouldReturnLoopDistance() {
        RouteGraph mockGraph = mock(RouteGraph.class);
        List<String> searchRoute = new ArrayList<>();
        searchRoute.add("A");
        searchRoute.add("B");
        searchRoute.add("C");
        searchRoute.add("A");
        RouteGraph.Station mockStatsionA = mock(RouteGraph.Station.class);
        RouteGraph.Station mockStatsionB = mock(RouteGraph.Station.class);
        RouteGraph.Station mockStatsionC = mock(RouteGraph.Station.class);

        when(mockGraph.getStation("A")).thenReturn(Optional.of(mockStatsionA));
        when(mockGraph.getStation("B")).thenReturn(Optional.of(mockStatsionB));
        when(mockGraph.getStation("C")).thenReturn(Optional.of(mockStatsionC));

        int distanceAB = RandomTestData.anyNumber(50);
        int distanceBC = RandomTestData.anyNumber(50);
        int distanceCA = RandomTestData.anyNumber(50);
        String expectedOutput = String.valueOf(distanceAB + distanceBC + distanceCA);
        when(mockStatsionA.distanceTo(mockStatsionB)).thenReturn(Optional.of(distanceAB));
        when(mockStatsionB.distanceTo(mockStatsionC)).thenReturn(Optional.of(distanceBC));
        when(mockStatsionC.distanceTo(mockStatsionA)).thenReturn(Optional.of(distanceCA));

        RouteDistanceQuery query = new RouteDistanceQuery(searchRoute);
        Output output = query.execute(mockGraph);
        assertTrue(output instanceof DistanceOutput);
        assertEquals(expectedOutput, output.toString());
    }
}
