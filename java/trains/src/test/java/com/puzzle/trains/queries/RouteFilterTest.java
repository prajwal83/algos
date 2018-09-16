package com.puzzle.trains.queries;

import com.puzzle.trains.util.RandomTestData;
import org.junit.jupiter.api.Test;

import static com.puzzle.trains.util.RandomTestData.anyNumber;
import static com.puzzle.trains.util.RandomTestData.anyString;
import static org.junit.jupiter.api.Assertions.*;

class RouteFilterTest {
    @Test
    void failForInvalidLimit() {
        IllegalArgumentException error = assertThrows(IllegalArgumentException.class, () ->
            new RouteFilter(RandomTestData.anyFilterOperation(), -RandomTestData.anyNumber()));
        assertEquals("limit should be greater than 0", error.getMessage());

        error = assertThrows(IllegalArgumentException.class, () -> new RouteFilter(RandomTestData.anyFilterOperation(), 0));
        assertEquals("limit should be greater than 0", error.getMessage());
    }

    @Test
    void shouldFilterRouteByLimit() {
        final int limit = RandomTestData.anyNumber(1000);

        assertTrue(!new RouteFilter(RouteFilter.Operation.LT, limit).intermediateCheck(limit));
        assertTrue(!new RouteFilter(RouteFilter.Operation.LT, limit).finalCheck(limit));
        assertTrue(new RouteFilter(RouteFilter.Operation.LT, limit).intermediateCheck(
                limit - RandomTestData.anyNumber(limit) - 1));
        assertTrue(new RouteFilter(RouteFilter.Operation.LT, limit).finalCheck(
                limit - RandomTestData.anyNumber(limit) - 1));

        assertTrue(!new RouteFilter(RouteFilter.Operation.LT_EQ, limit).intermediateCheck(
                limit + RandomTestData.anyNumber(limit) + 1));
        assertTrue(!new RouteFilter(RouteFilter.Operation.LT_EQ, limit).finalCheck(
                limit + RandomTestData.anyNumber(limit) + 1));
        assertTrue(new RouteFilter(RouteFilter.Operation.LT_EQ, limit).intermediateCheck(limit));
        assertTrue(new RouteFilter(RouteFilter.Operation.LT_EQ, limit).finalCheck(limit));
        assertTrue(new RouteFilter(RouteFilter.Operation.LT_EQ, limit).intermediateCheck(
                limit - RandomTestData.anyNumber(limit) - 1));
        assertTrue(new RouteFilter(RouteFilter.Operation.LT_EQ, limit).finalCheck(
                limit - RandomTestData.anyNumber(limit) - 1));

        assertTrue(new RouteFilter(RouteFilter.Operation.EQ, limit).intermediateCheck(limit));
        assertTrue(new RouteFilter(RouteFilter.Operation.EQ, limit).finalCheck(limit));
        assertTrue(new RouteFilter(RouteFilter.Operation.EQ, limit).intermediateCheck(
                limit - RandomTestData.anyNumber(limit) - 1));
        assertTrue(!new RouteFilter(RouteFilter.Operation.EQ, limit).finalCheck(
                limit - RandomTestData.anyNumber(limit) - 1));
        assertTrue(!new RouteFilter(RouteFilter.Operation.EQ, limit).intermediateCheck(
                limit + RandomTestData.anyNumber(limit) + 1));
        assertTrue(!new RouteFilter(RouteFilter.Operation.EQ, limit).finalCheck(
                limit + RandomTestData.anyNumber(limit) + 1));
    }

    @Test
    void shouldReturnOperationFromString() {
        assertEquals(RouteFilter.Operation.LT, RouteFilter.Operation.from("<"));
        assertEquals(RouteFilter.Operation.LT_EQ, RouteFilter.Operation.from("<="));
        assertEquals(RouteFilter.Operation.EQ, RouteFilter.Operation.from("="));
        assertThrows(IllegalArgumentException.class, () -> {
            RouteFilter.Operation.from(RandomTestData.anyString());
        });
    }
}