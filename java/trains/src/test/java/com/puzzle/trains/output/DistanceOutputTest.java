package com.puzzle.trains.output;

import com.puzzle.trains.util.RandomTestData;
import org.junit.jupiter.api.Test;

import static com.puzzle.trains.util.RandomTestData.anyNumber;
import static org.junit.jupiter.api.Assertions.assertEquals;

class DistanceOutputTest {
    @Test
    void validDistanceOutput() {
        final int distance = RandomTestData.anyNumber();
        DistanceOutput output = new DistanceOutput(distance);
        assertEquals(distance, output.getDistance());
        assertEquals(String.valueOf(distance), output.toString());
    }
}
