package com.puzzle.trains;

import com.puzzle.trains.util.RandomTestData;
import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;

import static com.puzzle.trains.util.RandomTestData.anyString;
import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.mock;

class RouteGraphTest {
    @Test
    void createEmptyGraph() {
        RouteGraph emptyGraph = RouteGraph.Factory.getInstance().from(new ArrayList<>());
        assertEquals(0, emptyGraph.size());
        assertTrue(!emptyGraph.getStation(RandomTestData.anyString()).isPresent());
    }

    @Test
    void failForInvalidDistance() {
        List<RouteGraph.ParsedRoute> negativeEdges = new ArrayList<>();
        negativeEdges.add(new RouteGraph.ParsedRoute("A", "C", -1));
        negativeEdges.add(new RouteGraph.ParsedRoute("A", "X", 1));

        IllegalArgumentException error = assertThrows(IllegalArgumentException.class,
                () ->  RouteGraph.Factory.getInstance().from(negativeEdges));
        assertEquals("distance should be greater than 0 from A to C", error.getMessage());

        List<RouteGraph.ParsedRoute> zeroEdges = new ArrayList<>();
        zeroEdges.add(new RouteGraph.ParsedRoute("A", "C", 1));
        zeroEdges.add(new RouteGraph.ParsedRoute("A", "X", 0));

        error = assertThrows(IllegalArgumentException.class, () ->  RouteGraph.Factory.getInstance().from(zeroEdges));
        assertEquals("distance should be greater than 0 from A to X", error.getMessage());
    }

    @Test
    void failForSelfLoops() {
        List<RouteGraph.ParsedRoute> edges = new ArrayList<>();
        edges.add(new RouteGraph.ParsedRoute("A", "C", 7));
        edges.add(new RouteGraph.ParsedRoute("A", "A", 8));

        IllegalArgumentException error = assertThrows(IllegalArgumentException.class,
                () ->  RouteGraph.Factory.getInstance().from(edges));
        assertEquals("self loop edge for Station A", error.getMessage());
    }

    @Test
    void failForDuplicateEdge() {
        List<RouteGraph.ParsedRoute> edges = new ArrayList<>();
        edges.add(new RouteGraph.ParsedRoute("A", "C", 7));
        edges.add(new RouteGraph.ParsedRoute("A", "B", 8));
        edges.add(new RouteGraph.ParsedRoute("A", "C", 20));

        IllegalArgumentException error = assertThrows(IllegalArgumentException.class,
                () ->  RouteGraph.Factory.getInstance().from(edges));
        assertEquals("duplicate edge from A and C", error.getMessage());
    }

    @Test
    void createValidGraph() {
        List<RouteGraph.ParsedRoute> edges = new ArrayList<>();
        edges.add(new RouteGraph.ParsedRoute("A", "C", 70));
        edges.add(new RouteGraph.ParsedRoute("A", "B", 8));
        edges.add(new RouteGraph.ParsedRoute("C", "A", 10));

        RouteGraph routeGraph = RouteGraph.Factory.getInstance().from(edges);
        assertEquals(3, routeGraph.size());
        assertTrue(!routeGraph.getStation("D").isPresent());

        RouteGraph.Station stationA = routeGraph.getStation("A").get();
        RouteGraph.Station stationB = routeGraph.getStation("B").get();
        RouteGraph.Station stationC = routeGraph.getStation("C").get();

        assertEquals(2, stationA.adjacentStations().size());
        assertEquals(8, (int)stationA.distanceTo(stationB).get());
        assertEquals(70, (int)stationA.distanceTo(stationC).get());
        assertTrue(!stationA.distanceTo(stationA).isPresent());

        assertEquals(0, stationB.adjacentStations().size());
        assertTrue(!stationB.distanceTo(stationA).isPresent());
        assertTrue(!stationB.distanceTo(stationC).isPresent());
        assertTrue(!stationB.distanceTo(stationB).isPresent());

        assertEquals(1, stationC.adjacentStations().size());
        assertEquals(10, (int)stationC.distanceTo(stationA).get());
        assertTrue(!stationC.distanceTo(stationB).isPresent());
        assertTrue(!stationC.distanceTo(stationC).isPresent());
    }

    @Test
    void verifyCache() {
        RouteGraph.Station stationA = mock(RouteGraph.Station.class);
        RouteGraph.Station stationB = mock(RouteGraph.Station.class);
        RouteGraph.Station stationC = mock(RouteGraph.Station.class);

        RouteGraph.RouteCache cache = new RouteGraph.RouteCache();
        assertEquals(0, cache.cache.size());
        assertTrue(!cache.get(stationA, stationB).isPresent());
        assertTrue(!cache.get(stationA, stationC).isPresent());

        cache.set(stationA, stationB, 10);
        assertEquals(10, (int)cache.get(stationA, stationB).get());

        cache.set(stationA, stationC, 20);
        assertEquals(20, (int)cache.get(stationA, stationC).get());

        cache.set(stationA, stationB, 30);
        assertEquals(10, (int)cache.get(stationA, stationB).get());

        cache.set(stationA, stationC, 40);
        assertEquals(20, (int)cache.get(stationA, stationC).get());

        assertEquals(1, cache.cache.size());
        assertEquals(2, cache.cache.get(stationA).size());

        RouteGraph routeGraph = RouteGraph.Factory.getInstance().from(new ArrayList<>());
        assertNotNull(routeGraph.getShortestPathCache());
    }
}
