package org.example;

import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class calcShortestPathTest {
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
        Main.readTextFileAndBuildGraph("C:\\Users\\lc\\Desktop\\Lab1-main\\Lab1-main\\Lab1-main\\test\\test1.txt", graph, wordFrequency, edgeWeights);
    }

    // 测试用例1: word1或word2不在图中
    @Test
    public void testCalcShortestPath_WordNotInGraph() {
        String result = Main.calcShortestPath(graph,"windd", "aaaa");
        System.out.println(result);
        assertEquals("No windd or aaaa in the graph!", result);
    }

    // 测试用例2: word1和word2都在图中，但没有路径
    @Test
    public void testCalcShortestPath_NoPathBetweenWords() {
        String result = Main.calcShortestPath(graph,"colors", "a");
        System.out.println(result);
        assertEquals("No path between colors and a.", result);
    }

    // 测试用例3: word1和word2都在图中，有直接路径
    @Test
    public void testCalcShortestPath_DirectPath() {
        String result = Main.calcShortestPath(graph,"sky", "into");
        System.out.println(result);
        assertTrue(result.contains("The shortest path distance from sky to into is:"));
    }

    // 测试用例4: word1和word2都在图中，有间接路径
    @Test
    public void testCalcShortestPath_IndirectPath() {
        String result = Main.calcShortestPath(graph,"sun", "over");
        System.out.println(result);
        assertTrue(result.contains("The shortest path distance from sun to over is:"));
    }



}

