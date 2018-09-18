package multithreading;

import org.junit.jupiter.api.Test;

import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.fail;

public class DualThreadQueueTest {

    @Test
    void putAndGetWithYield() {
        DualThreadQueue<Integer> queue = new DualThreadQueue<>(100);
        final int maxCount = 1000000;
        Thread producer = new Thread(() -> {
            for(int i = 0; i < maxCount; ++i) {
                queue.put(i);
            }
        });
        ArrayList<Integer> result = new ArrayList<>();
        Thread consumer = new Thread(() -> {
            for(int i = 0; i < maxCount; ++i) {
                result.add(queue.get());
            }
        });
        consumer.start();
        producer.start();
        try {
            producer.join();
            consumer.join();
        } catch(InterruptedException e) {
            Thread.currentThread().interrupt();
            fail("threads interrupted");
        }
        assertEquals(result.size(), maxCount);
        assertTrue(queue.isEmpty());
        for(int i = 0; i < maxCount; ++i) {
            assertEquals(i, (int)result.get(i));
        }
    }

    @Test
    void putAndGetWithWait() {
        DualThreadQueueWithWait<Integer> queue = new DualThreadQueueWithWait<>(100);
        final int maxCount = 1000000;
        Thread producer = new Thread(() -> {
            for(int i = 0; i < maxCount; ++i) {
                queue.put(i);
            }
        });
        ArrayList<Integer> result = new ArrayList<>();
        Thread consumer = new Thread(() -> {
            for(int i = 0; i < maxCount; ++i) {
                result.add(queue.get());
            }
        });
        consumer.start();
        producer.start();
        try {
            producer.join();
            consumer.join();
        } catch(InterruptedException e) {
            Thread.currentThread().interrupt();
            fail("threads interrupted");
        }
        assertEquals(result.size(), maxCount);
        assertTrue(queue.isEmpty());
        for(int i = 0; i < maxCount; ++i) {
            assertEquals(i, (int)result.get(i));
        }
    }
}
