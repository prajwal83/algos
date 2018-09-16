package com.puzzle.trains.output;

import com.puzzle.trains.util.RandomTestData;
import org.junit.jupiter.api.Test;

import java.io.PrintStream;

import static com.puzzle.trains.util.RandomTestData.anyString;
import static org.mockito.Mockito.*;

class PrintStreamOutputHandlerTest {
    @Test
    void sendOutput() {
        String data = RandomTestData.anyString();
        Output output = mock(Output.class);
        when(output.toString()).thenReturn(data);

        PrintStream outputStream = mock(PrintStream.class);
        PrintStreamOutputHandler handler = new PrintStreamOutputHandler(outputStream);
        handler.send(output);
        verify(outputStream).println(output);
    }
}
