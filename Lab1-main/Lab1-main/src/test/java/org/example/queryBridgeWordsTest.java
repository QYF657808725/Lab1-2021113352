package org.example;

import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class queryBridgeWordsTest {
    /**
     * 表示图中单词之间的有向边.
     * 键是单词。值是该单词可以指向的单词集合.
     */
    private static Map<String, Set<String>> graph;

    /**
     * 存储每个单词出现的频率.
     * 键是单词，值是该单词出现的次数.
     */
    private static Map<String, Integer> wordFrequency;

    /**
     * 存储图中每条边的权重.
     * 键是起始单词，值是另一个映射，其键是目的单词，值是边的权重.
     */
    private static Map<String, Map<String, Integer>> edgeWeights;



    @BeforeClass
    public static void init() {
        graph = new HashMap<>();
        wordFrequency = new HashMap<>();
        edgeWeights = new HashMap<>();
        Main.readTextFileAndBuildGraph("C:\\Users\\65780\\Desktop\\Lab1-main\\Lab1-main\\test\\test1.txt", graph, wordFrequency, edgeWeights);
    }

    @Test
    public void test1() {
        String result = Main.queryBridgeWords(graph,"sun", "the");
        System.out.println(result);
        assertTrue(result.contains("and")&&result.contains("in"));
    }

    @Test
    public void test2() {
        String result = Main.queryBridgeWords(graph,"sun", "rises");
        System.out.println(result);
        assertEquals("No bridge words from sun to rises!", result);
    }

    @Test
    public void test3() {
        String result = Main.queryBridgeWords(graph,"sun", "brightly");
        System.out.println(result);
        assertTrue(result.contains("shines"));
    }

    @Test
    public void test4() {
        String result = Main.queryBridgeWords(graph,"mountains", "together");
        System.out.println(result);
        assertEquals("No bridge words from mountains to together!", result);
    }

    @Test
    public void test6() {
        String result = Main.queryBridgeWords(graph,"abc", "def");
        System.out.println(result);
        assertEquals("No abc or def in the graph!", result);
    }

    @Test
    public void test7() {
        String result = Main.queryBridgeWords(graph,"abc", "sun");
        System.out.println(result);
        assertEquals("No abc or sun in the graph!", result);
    }

    @Test
    public void test8() {
        String result = Main.queryBridgeWords(graph,"sun", "abc");
        System.out.println(result);
        assertEquals("No sun or abc in the graph!", result);
    }

}