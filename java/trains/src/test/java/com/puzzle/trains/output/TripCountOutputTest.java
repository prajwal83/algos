package com.puzzle.trains.output;

import com.puzzle.trains.util.RandomTestData;
import org.junit.jupiter.api.Test;

import static com.puzzle.trains.util.RandomTestData.anyNumber;
import static org.junit.jupiter.api.Assertions.assertEquals;

class TripCountOutputTest {
    @Test
    void validTripCountOutput() {
        final int tripCount = RandomTestData.anyNumber();
        TripCountOutput output = new TripCountOutput(tripCount);
        assertEquals(tripCount, output.getTripCount());
        assertEquals(String.valueOf(tripCount), output.toString());
    }
}
