package multithreading;

import java.util.concurrent.atomic.AtomicInteger;

public class DualThreadQueueWithWait<T> {
    final Object[] buffer;
    final int capacity;
    int readIndex;
    int writeIndex;
    AtomicInteger count;

    public DualThreadQueueWithWait(int capacity) {
        this.capacity = capacity;
        this.buffer = new Object[capacity];
        this.readIndex = 0;
        this.writeIndex = 0;
        this.count = new AtomicInteger(0);
    }

    private interface ThreadAction {
        void apply() throws InterruptedException;
    }

    private synchronized void doWait(ThreadAction action) {
        try {
            action.apply();
        } catch(InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    public void put(T value) {
        if(isFull()) {
            doWait(() -> {
                while(isFull())
                    this.wait();
            });
        }
        buffer[writeIndex] = value;
        writeIndex = (writeIndex + 1) % capacity;

        synchronized (this) {
            count.incrementAndGet();
            this.notify();
        }
    }

    public T get() {
        if(isEmpty()) {
            doWait(() -> {
                while(isEmpty())
                    this.wait();
            });
        }
        T value = (T)buffer[readIndex];
        readIndex = (readIndex + 1) % capacity;

        synchronized (this) {
            count.decrementAndGet();
            this.notify();
        }

        return value;
    }

    public boolean isEmpty() {
        return count.get() == 0;
    }

    public boolean isFull() {
        return count.get() == capacity;
    }
}