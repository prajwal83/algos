package datastructure;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static util.RandomTestData.aString;

import org.junit.jupiter.api.Test;

import java.util.ArrayList;
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
    void putAndGetWithDuplicates() {
        ExtHashMap<Integer, Integer> extHashMap = new ExtHashMap<>();
        final int maxElements = 100000;

        for(int i = 0; i < maxElements; ++i) {
            extHashMap.put(i, i + 1);
            //duplicate key every 20th element with different value
            if(i > 0 && i % 20 == 0)
                extHashMap.put(i, i + 33);
        }

        //verify all elements at the end
        for(int i = 0; i < maxElements; ++i) {
            if(i > 0 && i % 20 == 0)
                assertEquals(i + 33, (int) extHashMap.get(i));
            else
                assertEquals(i + 1, (int) extHashMap.get(i));
        }
    }

    @Test
    void putAndGetLargeSizeMeasureTime() {
        ExtHashMap<Integer, Integer> extHashMap = new ExtHashMap<>();
        final int maxElements = 4000000; //4 MM

        long t1 = System.currentTimeMillis();
        for(int i = 0; i < maxElements; ++i) {
            extHashMap.put(i, i + 1);

            //intermediate checks where both old and new tables exists while doing lookups
            //verify elements exists once every 1000 elements while we continue to put more elements and grow the hash-table
            if(i > 0 && i % 1000 == 0) {
                for(int j = i - 1000; j < i; ++j) {
                    assertNotNull(extHashMap.get(j));
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

    @Test
    void putAndGetStringKey() {
        ExtHashMap<String, String> extHashMap = new ExtHashMap<>();
        final int maxElements = 1000000; //4 MM

        ArrayList<String> inputKeys = new ArrayList<>();
        for(int i = 0; i < maxElements; ++i)
            inputKeys.add(aString());

        long t1 = System.currentTimeMillis();
        for(int i = 0; i < maxElements; ++i) {
            final String key = inputKeys.get(i);
            extHashMap.put(key, key + ":");

            //intermediate checks where both old and new tables exists while doing lookups
            //verify elements exists once every 1000 elements while we continue to put more elements and grow the hash-table
            if(i > 0 && i % 1000 == 0) {
                for(int j = i - 1000; j < i; ++j) {
                    final String keyJ = inputKeys.get(j);
                    assertNotNull(extHashMap.get(keyJ));
                    assertEquals(keyJ + ":", extHashMap.get(keyJ));
                }
            }
        }

        //verify all elements at the end
        for(int i = 0; i < maxElements; ++i) {
            final String keyI = inputKeys.get(i);
            assertEquals(keyI + ":", extHashMap.get(keyI));
        }

        long t2 = System.currentTimeMillis();
        System.out.println("Approx time taken by ExtHashMap to put and get " + maxElements + " elements = " + ((t2 - t1) / 1000.0) + " seconds");
    }
}
