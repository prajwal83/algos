package multithreading;

import java.util.concurrent.atomic.AtomicInteger;

public class DualThreadQueue<T> {
    final Object[] buffer;
    final int capacity;
    int readIndex;
    int writeIndex;
    AtomicInteger count;

    public DualThreadQueue(int capacity) {
        this.capacity = capacity;
        this.buffer = new Object[capacity];
        this.readIndex = 0;
        this.writeIndex = 0;
        this.count = new AtomicInteger(0);
    }

    public void put(T value) {
        while(isFull())
            Thread.yield();
        buffer[writeIndex] = value;
        writeIndex = (writeIndex + 1) % capacity;
        count.incrementAndGet();
    }

    public T get() {
        while(isEmpty())
            Thread.yield();
        T value = (T)buffer[readIndex];
        readIndex = (readIndex + 1) % capacity;
        count.decrementAndGet();
        return value;
    }

    public boolean isEmpty() {
        return count.get() == 0;
    }

    public boolean isFull() {
        return count.get() == capacity;
    }
}