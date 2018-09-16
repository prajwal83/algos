package com.puzzle.trains.input;

import com.puzzle.trains.queries.*;
import com.puzzle.trains.util.RandomTestData;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class QueryInputParserTest {
    @Test
    void failForEmptyQuery() {
        Query query = QueryInputParser.getInstance().parse("");
        assertTrue(query instanceof InvalidQuery);
    }

    @Test
    void failForInvalidQuery() {
        Query query = QueryInputParser.getInstance().parse(RandomTestData.anyString());
        assertTrue(query instanceof InvalidQuery);
    }

    @Test
    void failForInvalidDistanceQuery() {
        Query query = QueryInputParser.getInstance().parse("distance oF A B C");
        assertTrue(query instanceof InvalidQuery);
    }

    @Test
    void distanceQuery() {
        RouteDistanceQuery query = (RouteDistanceQuery)QueryInputParser.getInstance().parse(" distance of ");
        assertEquals(1, query.getSearchRoute().size());

        query = (RouteDistanceQuery)QueryInputParser.getInstance().parse(" distance of  A");
        assertEquals(1, query.getSearchRoute().size());
        assertEquals("A", query.getSearchRoute().get(0));

        query = (RouteDistanceQuery)QueryInputParser.getInstance().parse("distance of  A B C");
        assertEquals(3, query.getSearchRoute().size());
        assertEquals("A", query.getSearchRoute().get(0));
        assertEquals("B", query.getSearchRoute().get(1));
        assertEquals("C", query.getSearchRoute().get(2));
    }

    @Test
    void failForInvalidShortestPathQuery() {
        Query query = QueryInputParser.getInstance().parse("shortest path from A to ");
        assertTrue(query instanceof InvalidQuery);

        query = QueryInputParser.getInstance().parse("shortest path from to B");
        assertTrue(query instanceof InvalidQuery);

        query = QueryInputParser.getInstance().parse("shortest path from  to ");
        assertTrue(query instanceof InvalidQuery);
    }

    @Test
    void shortestPathQuery() {
        ShortestDistanceQuery query = (ShortestDistanceQuery)QueryInputParser.getInstance().parse("shortest path from A to B");
        assertEquals("A", query.getFrom());
        assertEquals("B", query.getTo());
    }

    @Test
    void failWithInvalidTripCountQuery() {
        Query query = QueryInputParser.getInstance().parse("trip count from A to B with stops > 20");
        assertTrue(query instanceof InvalidQuery);

        query = QueryInputParser.getInstance().parse("trip count from A to B with stops = A0");
        assertTrue(query instanceof InvalidQuery);

        query = QueryInputParser.getInstance().parse("trip count from A to Bwith distance < 1");
        assertTrue(query instanceof InvalidQuery);
    }

    @Test
    void tripCountQueryByStops() {
        TripCountQuery query = (TripCountQuery)QueryInputParser.getInstance().parse(
                "trip count from A to B with stops < 20");
        assertEquals("A", query.getFrom());
        assertEquals("B", query.getTo());
        assertEquals(TripCountQuery.ParameterType.BY_STOPS, query.getParamType());
        assertEquals(20, query.getFilter().getLimit());
        assertEquals(RouteFilter.Operation.LT, query.getFilter().getOperation());

        query = (TripCountQuery)QueryInputParser.getInstance().parse(
                "trip count from A to B with stops <= 2");
        assertEquals("A", query.getFrom());
        assertEquals("B", query.getTo());
        assertEquals(TripCountQuery.ParameterType.BY_STOPS, query.getParamType());
        assertEquals(2, query.getFilter().getLimit());
        assertEquals(RouteFilter.Operation.LT_EQ, query.getFilter().getOperation());

        query = (TripCountQuery)QueryInputParser.getInstance().parse(
                "trip count from A to B with stops = 10 ");
        assertEquals("A", query.getFrom());
        assertEquals("B", query.getTo());
        assertEquals(TripCountQuery.ParameterType.BY_STOPS, query.getParamType());
        assertEquals(10, query.getFilter().getLimit());
        assertEquals(RouteFilter.Operation.EQ, query.getFilter().getOperation());
    }

    @Test
    void tripCountQueryByDistance() {
        TripCountQuery query = (TripCountQuery)QueryInputParser.getInstance().parse(
                "trip count from A to B with distance < 20");
        assertEquals("A", query.getFrom());
        assertEquals("B", query.getTo());
        assertEquals(TripCountQuery.ParameterType.BY_DISTANCE, query.getParamType());
        assertEquals(20, query.getFilter().getLimit());
        assertEquals(RouteFilter.Operation.LT, query.getFilter().getOperation());

        query = (TripCountQuery)QueryInputParser.getInstance().parse(
                "trip count from A to B with distance <= 2");
        assertEquals("A", query.getFrom());
        assertEquals("B", query.getTo());
        assertEquals(TripCountQuery.ParameterType.BY_DISTANCE, query.getParamType());
        assertEquals(2, query.getFilter().getLimit());
        assertEquals(RouteFilter.Operation.LT_EQ, query.getFilter().getOperation());

        query = (TripCountQuery)QueryInputParser.getInstance().parse(
                "trip count from A to B with distance = 10 ");
        assertEquals("A", query.getFrom());
        assertEquals("B", query.getTo());
        assertEquals(TripCountQuery.ParameterType.BY_DISTANCE, query.getParamType());
        assertEquals(10, query.getFilter().getLimit());
        assertEquals(RouteFilter.Operation.EQ, query.getFilter().getOperation());
    }
}
