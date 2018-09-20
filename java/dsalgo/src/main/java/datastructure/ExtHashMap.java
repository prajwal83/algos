package datastructure;

public class ExtHashMap<K, V> {
    private class ValueNode {
        K key;
        V value;
        ValueNode next;
    }

    //main hash-table
    private Object[] currentTable;
    //keeps track of number of buckets used
    private int filledBucketCount = 0;

    //previous/old hash-table upon extending current
    private Object[] oldTable;
    //keeps track of the bucket index of old hash-table from where we want to copy/move an element to current hash-table
    private int oldTableMoveIndex = 0;

    public ExtHashMap() {
        //64 - initial capacity
        //load-factor = 100%
        currentTable = new Object[64];
        oldTable = null;
    }

    //-> use first element as head for simplicity
    //-> if the key already exists then overwrite
    //-> insert new elements to current table
    //-> move one element from old hash-table to current hash-table if old table exists
    public void put(K key, V value) {
        ValueNode node = getValueNode(key);
        //overwrite
        if(node != null) {
            node.value = value;
            return;
        }
        putToCurrentTable(key, value);
        copyFromOldTable();
    }

    //try get from current table
    //if not found in current table then try get from old table if it exists
    public V get(K key) {
        ValueNode node = getValueNode(key);
        if(node == null)
            return null;
        return node.value;
    }

    private ValueNode getValueNode(K key) {
        ValueNode node = getFromBucket(key, ((ValueNode)currentTable[indexForCurrent(key)]));
        if(node == null) {
            final int oldIndex = indexForOld(key);
            if(oldIndex >= oldTableMoveIndex)
                node = getFromBucket(key, ((ValueNode)oldTable[oldIndex]));
        }
        return node;
    }

    //get from a given ValueNode singly linked list
    private ValueNode getFromBucket(K key, ValueNode head) {
        if(head != null) {
            ValueNode curNode = head.next;
            while (curNode != null) {
                if (curNode.key.equals(key))
                    return curNode;
                curNode = curNode.next;
            }
        }
        return null;
    }

    //copy an element from old hash-table to current hash-table
    //if all elements in old hash-table are copied then reset old hash-table to null
    private void copyFromOldTable() {
        if(oldTable != null) {
            ValueNode head = ((ValueNode)oldTable[oldTableMoveIndex]);
            ValueNode nodeToMove = null;
            if(head != null && head.next != null) {
                nodeToMove = head.next;
                head.next = nodeToMove.next;
            }
            if(head.next == null)
                ++oldTableMoveIndex;
            if(oldTableMoveIndex == oldTable.length) {
                oldTable = null;
                oldTableMoveIndex = 0;
            }
            if(nodeToMove != null)
                putToCurrentTable(nodeToMove.key, nodeToMove.value);
        }
    }

    //put an element to current table
    //extend current table if we all buckets are filled but don't copy elements yet (lazy expansion)
    private void putToCurrentTable(K key, V value) {
        final int i = indexForCurrent(key);

        ValueNode cur = (ValueNode)currentTable[i];

        //first element in this bucket - for simplicity first element is head node
        if(cur == null) {
            ++filledBucketCount;
            cur = new ValueNode();
            currentTable[i] = cur;
        }

        while(cur.next != null)
            cur = cur.next;

        ValueNode newNode = new ValueNode();
        newNode.key = key;
        newNode.value = value;
        cur.next = newNode;

        //extend if we have reached capacity but don't copy elements yet
        if(filledBucketCount == currentTable.length) {
            Object[] newTable = new Object[currentTable.length * 2];

            oldTable = currentTable;
            oldTableMoveIndex = 0;

            currentTable = newTable;
            filledBucketCount = 0;
        }
    }

    private int indexForCurrent(K key) {
        return key.hashCode() % currentTable.length;
    }

    private int indexForOld(K key) {
        if(oldTable == null)
            return -1;
        return key.hashCode() % oldTable.length;
    }
}