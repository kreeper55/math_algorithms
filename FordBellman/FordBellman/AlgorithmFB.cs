using System;
using System.Threading;

namespace FordBellman
{
    public class ALgorithm
    {
        private struct Edge
        {
            public int Source;
            public int Destination;
            public double Weight;
        }

        private struct Graph
        {
            public int VerticesCount;
            public int EdgesCount;
            public Edge[] edge;
        }

        private static Graph CreateGraph(int verticesCount, int edgesCount)
        {
            Graph graph = new Graph();
            graph.VerticesCount = verticesCount;
            graph.EdgesCount = edgesCount;
            graph.edge = new Edge[graph.EdgesCount];

            return graph;
        }

        public static double[] FordBellman(double[][] Matrix, int src)
        {
            int verticesCount = Matrix.Length;
            int edgesCount = 0;
            int source = src;
            if (source > verticesCount)
                throw new ArgumentException("the source is not contained in the column", "ErrorMessage");

            for (int i = 0; i < verticesCount; i++)
            {
                for (int j = 0; j < verticesCount; j++)
                {
                    edgesCount += (Matrix[i][j] != double.MaxValue ? 1 : 0);
                }
            }

            Graph graph = CreateGraph(verticesCount, edgesCount);
            int k = 0;
            for (int i = 0; i < verticesCount; i++)
            {
                for (int j = 0; j < verticesCount; j++)
                {
                    if (Matrix[i][j] != double.MaxValue)
                    {
                        graph.edge[k].Source = i;
                        graph.edge[k].Destination = j;
                        graph.edge[k].Weight = Matrix[i][j];
                        k++;
                    }
                }
            }

            double[] distance = new double[verticesCount];
            for (int i = 0; i < verticesCount; i++)
                distance[i] = double.MaxValue;
            distance[source] = 0;

            for (int i = 1; i <= verticesCount - 1; ++i)
            {
                for (int j = 0; j < edgesCount; ++j)
                {
                    int u = graph.edge[j].Source;
                    int v = graph.edge[j].Destination;
                    double weight = graph.edge[j].Weight;

                    if (distance[u] != double.MaxValue && distance[u] + weight < distance[v])
                        distance[v] = distance[u] + weight;
                }
            }

            for (int i = 0; i < edgesCount; ++i)
            {
                int u = graph.edge[i].Source;
                int v = graph.edge[i].Destination;
                double weight = graph.edge[i].Weight;

                if (distance[u] != int.MaxValue && distance[u] + weight < distance[v])
                    throw new ArgumentException("Graph contains negative weight cycle.");
            }

            Thread.Sleep(2000);
            return distance;
        }
    }
}
