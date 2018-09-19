package multithreading;

import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.Comparator;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.fail;

class LockFreeLinkedListTest {
    private class Producer extends Thread {
        private final int start;
        private final int end;
        private final LockFreeLinkedList<Integer> sll;

        Producer(int start, int end, LockFreeLinkedList<Integer> sll) {
            this.start = start;
            this.end = end;
            this.sll = sll;
        }

        @Override
        public void run() {
            for(int i = start; i < end; ++i)
                sll.pushFront(i);
        }
    }

    private class Consumer extends Thread {
        private int count;
        private final LockFreeLinkedList<Integer> sll;
        private ArrayList<Integer> results;
        Consumer(int count, LockFreeLinkedList<Integer> sll) {
            this.count = count;
            this.sll = sll;
            this.results = new ArrayList<>();
        }

        @Override
        public void run() {
            while(count > 0) {
                Integer value = sll.popFront();
                if(value != null) {
                    results.add(value);
                    --count;
                }
            }
        }

        public ArrayList<Integer> getResults() {
            return results;
        }
    }

    @Test
    void pushAndPop() {
        LockFreeLinkedList<Integer> sll = new LockFreeLinkedList<>();
        //producers
        ArrayList<Thread> threads = new ArrayList<>();
        threads.add(new Producer(0, 300000, sll));
        threads.add(new Consumer(200000, sll));
        threads.add(new Consumer(200000, sll));
        threads.add(new Consumer(200000, sll));
        threads.add(new Consumer(100000, sll));
        threads.add(new Producer(300000, 600000, sll));
        threads.add(new Producer(600000, 900000, sll));
        threads.add(new Producer(900000, 1000000, sll));

        for(Thread t : threads)
            t.start();

        try {
            for (Thread t : threads)
                t.join();
        } catch(InterruptedException e) {
            Thread.currentThread().interrupt();
            fail("thread interrupted");
        }

        assertEquals(300000, sll.size());

        ArrayList<Integer> results = new ArrayList<>();
        for(int i = 0; i < 300000; ++i) {
            results.add(sll.popFront());
        }
        for(Thread t : threads) {
            if (t instanceof Consumer) {
                results.addAll(((Consumer) t).getResults());
            }
        }
        results.sort(Comparator.naturalOrder());
        ArrayList<Integer> expected = new ArrayList<>();
        for(int i = 0; i < 1000000; ++i) {
            expected.add(i);
        }

        assertEquals(1000000, results.size());
        assertEquals(expected, results);
    }
}
