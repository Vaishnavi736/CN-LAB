#include <stdio.h>
#define MAX 10
#define INF 9999

int main() {
    int nodes, i, j, k, count = 0;
    int distance[MAX][MAX], via[MAX][MAX];

    printf("Enter the number of nodes: ");
    scanf("%d", &nodes);

    printf("Enter the cost/delay adjacency matrix (%d for no link/infinite delay):\n", INF);
    for(i = 0; i < nodes; i++) {
        for(j = 0; j < nodes; j++) {
            scanf("%d", &distance[i][j]);

            // Replace 0 with INF for non-self nodes
            if(i != j && distance[i][j] == 0) 
                distance[i][j] = INF;

            // Initially next hop is the destination node itself
            via[i][j] = j;
        }
    }

    // Distance Vector Algorithm
    do {
        count = 0;
        for(i = 0; i < nodes; i++) {
            for(j = 0; j < nodes; j++) {
                for(k = 0; k < nodes; k++) {
                    if(distance[i][j] > distance[i][k] + distance[k][j]) {
                        distance[i][j] = distance[i][k] + distance[k][j];
                        via[i][j] = k;
                        count++;
                    }
                }
            }
        }
    } while(count != 0);

    // Display routing tables
    for(i = 0; i < nodes; i++) {
        printf("\nRouting table for node %d:\n", i);
        printf("Destination\tNext Hop\tTotal Cost\n");
        for(j = 0; j < nodes; j++) {
            if (i == j)
                printf("%d\t\t-\t\t0\n", j);
            else
                printf("%d\t\t%d\t\t%d\n", j, via[i][j], distance[i][j]);
        }
    }

    return 0;
}
