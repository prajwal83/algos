package multithreading;

import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicReference;

public class LockFreeLinkedList<T> {
    private class Node {
        T value;
        Node next;
    }

    AtomicReference<Node> head;
    AtomicInteger count;

    public LockFreeLinkedList() {
        this.head = new AtomicReference<>(null);
        this.count = new AtomicInteger(0);
    }

    public void pushFront(T value) {
        Node x = new Node();
        x.value = value;
        x.next = head.get();
        while(!head.compareAndSet(x.next, x)) {
            x.next = head.get();
        }
        count.incrementAndGet();
    }

    public T popFront() {
        Node first = head.get();
        while(first != null && !head.compareAndSet(first, first.next)) {
            first = head.get();
        }
        if(first == null)
            return null;
        count.decrementAndGet();
        return first.value;
    }

    public Node find(T value) {
        Node cur = head.get();
        while(cur != null && cur.value != value)
            cur = cur.next;
        return cur;
    }

    public int size() {
        return count.get();
    }
}
