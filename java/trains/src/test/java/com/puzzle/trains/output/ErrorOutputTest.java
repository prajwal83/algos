package com.puzzle.trains.output;

import com.puzzle.trains.util.RandomTestData;
import org.junit.jupiter.api.Test;

import static com.puzzle.trains.util.RandomTestData.anyString;
import static org.junit.jupiter.api.Assertions.assertEquals;

class ErrorOutputTest {
    @Test
    void validDistanceOutput() {
        final String error = RandomTestData.anyString();
        ErrorOutput output = new ErrorOutput(error);
        assertEquals(error, output.getError());
        assertEquals(error, output.toString());
    }
}
