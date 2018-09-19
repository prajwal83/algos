package datastructure;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.Test;

import java.util.HashMap;
import java.util.TreeMap;

class ExtHashMapTest {

    @Test
    void putAndGetWithoutGrowing() {
        ExtHashMap<Integer, Integer> extHashMap = new ExtHashMap<>();
        final int maxElements = 200;

        for(int i = 0; i < maxElements; ++i)
            extHashMap.put(i, i + 1);

        //verify all elements at the end
        for(int i = 0; i < maxElements; ++i)
            assertEquals(i + 1, (int)extHashMap.get(i));
    }

    @Test
    void putAndGetLargeSize() {
        ExtHashMap<Integer, Integer> extHashMap = new ExtHashMap<>();
        final int maxElements = 4000000; //4 MM

        long t1 = System.currentTimeMillis();
        for(int i = 0; i < maxElements; ++i) {
            extHashMap.put(i, i + 1);

            //intermediate checks where both old and new tables exists while doing lookups
            //verify elements exists once every 1000 elements while we continue to put more elements and grow the hash-table
            if(i > 0 && i % 1000 == 0) {
                for(int j = i - 1000; j < i; ++j) {
                    assertTrue(extHashMap.get(j) != null);
                    assertEquals(j + 1, (int)extHashMap.get(j));
                }
            }
        }

        //verify all elements at the end
        for(int i = 0; i < maxElements; ++i) {
            assertEquals(i + 1, (int)extHashMap.get(i));
        }

        long t2 = System.currentTimeMillis();
        System.out.println("Approx time taken by ExtHashMap to put and get " + maxElements + " elements = " + ((t2 - t1) / 1000.0) + " seconds");
    }
}
