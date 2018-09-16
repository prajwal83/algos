package com.puzzle.trains.output;

import java.io.PrintStream;

public class PrintStreamOutputHandler implements OutputHandler {
    private final PrintStream outputStream;
    public PrintStreamOutputHandler(PrintStream outputStream) {
        this.outputStream = outputStream;
    }
    @Override public void send(Output output) {
        outputStream.println(output);
    }
}
