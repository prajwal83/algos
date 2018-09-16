package com.puzzle.trains.queries;

import com.puzzle.trains.RouteGraph;
import com.puzzle.trains.output.DistanceOutput;
import com.puzzle.trains.output.ErrorOutput;
import com.puzzle.trains.output.Output;
import com.puzzle.trains.util.RandomTestData;
import org.junit.jupiter.api.Test;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Optional;

import static com.puzzle.trains.util.RandomTestData.anyString;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.mockito.Matchers.any;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;

class ShortestDistanceQueryTest {
    @Test
    void failForMissingStartStation() {
        RouteGraph mockGraph = mock(RouteGraph.class);
        final String from = RandomTestData.anyString();
        final String to = RandomTestData.anyString();
        ShortestDistanceQuery query = new ShortestDistanceQuery(from, to);
        when(mockGraph.getStation(from)).thenReturn(Optional.empty());
        Output output = query.execute(mockGraph);
        assertTrue(output instanceof ErrorOutput);
        assertEquals("NO SUCH ROUTE", output.toString());
    }

    @Test
    void failForMissingEndStation() {
        RouteGraph mockGraph = mock(RouteGraph.class);
        final String from = RandomTestData.anyString();
        final String to = RandomTestData.anyString();
        ShortestDistanceQuery query = new ShortestDistanceQuery(from, to);
        RouteGraph.Station mockFrom = mock(RouteGraph.Station.class);
        when(mockGraph.getStation(from)).thenReturn(Optional.of(mockFrom));
        when(mockGraph.getStation(to)).thenReturn(Optional.empty());
        Output output = query.execute(mockGraph);
        assertTrue(output instanceof ErrorOutput);
        assertEquals("NO SUCH ROUTE", output.toString());
    }

    @Test
    void failForMissingRoute() {
        RouteGraph mockGraph = mock(RouteGraph.class);
        RouteGraph.RouteCache mockCache = mock(RouteGraph.RouteCache.class);
        when(mockCache.get(any(), any())).thenReturn(Optional.empty());
        when(mockGraph.getShortestPathCache()).thenReturn(mockCache);

        final String from = RandomTestData.anyString();
        final String to = RandomTestData.anyString();
        ShortestDistanceQuery query = new ShortestDistanceQuery(from, to);

        RouteGraph.Station mockFrom = mock(RouteGraph.Station.class);
        RouteGraph.Station mockTo = mock(RouteGraph.Station.class);
        when(mockGraph.getStation(from)).thenReturn(Optional.of(mockFrom));
        when(mockGraph.getStation(to)).thenReturn(Optional.of(mockTo));
        when(mockFrom.distanceTo(mockTo)).thenReturn(Optional.empty());

        Output output = query.execute(mockGraph);
        assertTrue(output instanceof ErrorOutput);
        assertEquals("NO SUCH ROUTE", output.toString());
    }

    @Test
    void failForMissingIntermediateLink() {
        RouteGraph mockGraph = mock(RouteGraph.class);
        RouteGraph.RouteCache mockCache = mock(RouteGraph.RouteCache.class);
        when(mockCache.get(any(), any())).thenReturn(Optional.empty());
        when(mockGraph.getShortestPathCache()).thenReturn(mockCache);

        ShortestDistanceQuery query = new ShortestDistanceQuery("A", "E");

        RouteGraph.Station stationA = mock(RouteGraph.Station.class);
        RouteGraph.Station stationB = mock(RouteGraph.Station.class);
        RouteGraph.Station stationC = mock(RouteGraph.Station.class);
        RouteGraph.Station stationD = mock(RouteGraph.Station.class);
        RouteGraph.Station stationE = mock(RouteGraph.Station.class);

        when(mockGraph.getStation("A")).thenReturn(Optional.of(stationA));
        when(mockGraph.getStation("B")).thenReturn(Optional.of(stationB));
        when(mockGraph.getStation("C")).thenReturn(Optional.of(stationC));
        when(mockGraph.getStation("D")).thenReturn(Optional.of(stationD));
        when(mockGraph.getStation("E")).thenReturn(Optional.of(stationE));

        when(stationA.distanceTo(stationB)).thenReturn(Optional.of(10));
        when(stationA.distanceTo(stationC)).thenReturn(Optional.of(12));
        when(stationC.distanceTo(stationD)).thenReturn(Optional.of(5));

        Output output = query.execute(mockGraph);
        assertTrue(output instanceof ErrorOutput);
        assertEquals("NO SUCH ROUTE", output.toString());
    }

    @Test
    void shortestPathSingle() {
        RouteGraph mockGraph = mock(RouteGraph.class);
        RouteGraph.RouteCache mockCache = mock(RouteGraph.RouteCache.class);
        when(mockCache.get(any(), any())).thenReturn(Optional.empty());
        when(mockGraph.getShortestPathCache()).thenReturn(mockCache);

        ShortestDistanceQuery query = new ShortestDistanceQuery("A", "C");

        RouteGraph.Station stationA = mock(RouteGraph.Station.class);
        RouteGraph.Station stationB = mock(RouteGraph.Station.class);
        RouteGraph.Station stationC = mock(RouteGraph.Station.class);

        when(mockGraph.getStation("A")).thenReturn(Optional.of(stationA));
        when(mockGraph.getStation("B")).thenReturn(Optional.of(stationB));
        when(mockGraph.getStation("C")).thenReturn(Optional.of(stationC));

        when(stationA.distanceTo(stationB)).thenReturn(Optional.of(10));
        when(stationB.distanceTo(stationC)).thenReturn(Optional.of(10));
        when(stationA.adjacentStations()).thenReturn(new HashSet<>(Arrays.asList(stationB)));
        when(stationB.adjacentStations()).thenReturn(new HashSet<>(Arrays.asList(stationC)));

        Output output = query.execute(mockGraph);
        assertTrue(output instanceof DistanceOutput);
        assertEquals("20", output.toString());
        verify(mockCache).set(stationA, stationC, 20);
    }

    @Test
    void shortestPathBest() {
        RouteGraph mockGraph = mock(RouteGraph.class);
        RouteGraph.RouteCache mockCache = mock(RouteGraph.RouteCache.class);
        when(mockCache.get(any(), any())).thenReturn(Optional.empty());
        when(mockGraph.getShortestPathCache()).thenReturn(mockCache);

        ShortestDistanceQuery query = new ShortestDistanceQuery("A", "E");

        RouteGraph.Station stationA = mock(RouteGraph.Station.class);
        RouteGraph.Station stationB = mock(RouteGraph.Station.class);
        RouteGraph.Station stationC = mock(RouteGraph.Station.class);
        RouteGraph.Station stationD = mock(RouteGraph.Station.class);
        RouteGraph.Station stationE = mock(RouteGraph.Station.class);

        when(mockGraph.getStation("A")).thenReturn(Optional.of(stationA));
        when(mockGraph.getStation("B")).thenReturn(Optional.of(stationB));
        when(mockGraph.getStation("C")).thenReturn(Optional.of(stationC));
        when(mockGraph.getStation("D")).thenReturn(Optional.of(stationD));
        when(mockGraph.getStation("E")).thenReturn(Optional.of(stationE));

        when(stationA.distanceTo(stationB)).thenReturn(Optional.of(10));
        when(stationB.distanceTo(stationE)).thenReturn(Optional.of(1));

        when(stationA.distanceTo(stationC)).thenReturn(Optional.of(5));
        when(stationC.distanceTo(stationD)).thenReturn(Optional.of(3));
        when(stationD.distanceTo(stationE)).thenReturn(Optional.of(1));

        when(stationA.adjacentStations()).thenReturn(new HashSet<>(Arrays.asList(stationB, stationC)));
        when(stationB.adjacentStations()).thenReturn(new HashSet<>(Arrays.asList(stationE)));
        when(stationC.adjacentStations()).thenReturn(new HashSet<>(Arrays.asList(stationD)));
        when(stationD.adjacentStations()).thenReturn(new HashSet<>(Arrays.asList(stationE)));

        Output output = query.execute(mockGraph);
        assertTrue(output instanceof DistanceOutput);
        assertEquals("9", output.toString());
        verify(mockCache).set(stationA, stationE, 9);
    }

    @Test
    void shortestPathCircular() {
        RouteGraph mockGraph = mock(RouteGraph.class);
        RouteGraph.RouteCache mockCache = mock(RouteGraph.RouteCache.class);
        when(mockCache.get(any(), any())).thenReturn(Optional.empty());
        when(mockGraph.getShortestPathCache()).thenReturn(mockCache);

        ShortestDistanceQuery query = new ShortestDistanceQuery("A", "A");

        RouteGraph.Station stationA = mock(RouteGraph.Station.class);
        RouteGraph.Station stationB = mock(RouteGraph.Station.class);
        RouteGraph.Station stationC = mock(RouteGraph.Station.class);
        RouteGraph.Station stationD = mock(RouteGraph.Station.class);
        RouteGraph.Station stationE = mock(RouteGraph.Station.class);

        when(mockGraph.getStation("A")).thenReturn(Optional.of(stationA));
        when(mockGraph.getStation("B")).thenReturn(Optional.of(stationB));
        when(mockGraph.getStation("C")).thenReturn(Optional.of(stationC));
        when(mockGraph.getStation("D")).thenReturn(Optional.of(stationD));
        when(mockGraph.getStation("E")).thenReturn(Optional.of(stationE));

        when(stationA.distanceTo(stationB)).thenReturn(Optional.of(10));
        when(stationB.distanceTo(stationE)).thenReturn(Optional.of(1));

        when(stationA.distanceTo(stationC)).thenReturn(Optional.of(5));
        when(stationC.distanceTo(stationD)).thenReturn(Optional.of(3));
        when(stationC.distanceTo(stationE)).thenReturn(Optional.of(1));
        when(stationD.distanceTo(stationE)).thenReturn(Optional.of(1));

        when(stationE.distanceTo(stationA)).thenReturn(Optional.of(1));

        when(stationA.adjacentStations()).thenReturn(new HashSet<>(Arrays.asList(stationB, stationC)));
        when(stationB.adjacentStations()).thenReturn(new HashSet<>(Arrays.asList(stationE)));
        when(stationC.adjacentStations()).thenReturn(new HashSet<>(Arrays.asList(stationD, stationE)));
        when(stationD.adjacentStations()).thenReturn(new HashSet<>(Arrays.asList(stationE)));
        when(stationE.adjacentStations()).thenReturn(new HashSet<>(Arrays.asList(stationA)));

        Output output = query.execute(mockGraph);
        assertTrue(output instanceof DistanceOutput);
        assertEquals("7", output.toString());
        verify(mockCache).set(stationA, stationA, 7);
    }

    @Test
    void useCache() {
        RouteGraph mockGraph = mock(RouteGraph.class);
        RouteGraph.RouteCache mockCache = mock(RouteGraph.RouteCache.class);
        when(mockGraph.getShortestPathCache()).thenReturn(mockCache);

        ShortestDistanceQuery query = new ShortestDistanceQuery("A", "C");

        RouteGraph.Station stationA = mock(RouteGraph.Station.class);
        RouteGraph.Station stationB = mock(RouteGraph.Station.class);
        RouteGraph.Station stationC = mock(RouteGraph.Station.class);

        when(mockCache.get(stationA, stationC)).thenReturn(Optional.of(221));

        when(mockGraph.getStation("A")).thenReturn(Optional.of(stationA));
        when(mockGraph.getStation("B")).thenReturn(Optional.of(stationB));
        when(mockGraph.getStation("C")).thenReturn(Optional.of(stationC));

        when(stationA.distanceTo(stationB)).thenReturn(Optional.of(10));
        when(stationB.distanceTo(stationC)).thenReturn(Optional.of(10));
        when(stationA.adjacentStations()).thenReturn(new HashSet<>(Arrays.asList(stationB)));
        when(stationB.adjacentStations()).thenReturn(new HashSet<>(Arrays.asList(stationC)));

        Output output = query.execute(mockGraph);
        assertTrue(output instanceof DistanceOutput);
        assertEquals("221", output.toString());
    }
}
